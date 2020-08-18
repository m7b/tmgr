#include "C_ReportMapCreator.h"

C_ReportMapCreator::C_ReportMapCreator(const ApplicationData *ad, const C_Settings *s, int GebId)
: C_DbHandle(&ad->db_file), C_Report(ad, s), GebId(GebId)
{
    //ctor
    m_width_mm  = 150.0;
    m_height_mm =  94.0;
    m_DSGVO = DSGVO;
}

C_ReportMapCreator::~C_ReportMapCreator()
{
    //dtor
}

void C_ReportMapCreator::create_mapimg(void)
{
    query_Gebiete();
    query_Maperitive();
    create_process_data_map(EXPORT);
    create_process_data_file(ad->work_dir + "/maperitive/card.mscript");
    start_process_map(EXPORT);
    cleanup_map();
}

void C_ReportMapCreator::join_mapimg_with_border(void)
{
    query_Maperitive();
    create_process_data_im();
    create_process_data_file(ad->work_dir + "/maperitive/im.bat");
    start_process_im();
    cleanup_im();
}

void C_ReportMapCreator::rollout(void)
{
    create_mapimg();
    join_mapimg_with_border();
    push_card_viewer();
}

void C_ReportMapCreator::rollout_description(void)
{
    double card_width  = settings->m_general.m_infopage_map_width_mm;
    double card_height = settings->m_general.m_infopage_map_height_mm;

    query_Gebiete();
    query_Nichtbesuche();
    query_Hinweise();
    set_description_image_size(card_width, card_height);
    create_process_data_descr();
    create_process_data_file(ad->work_dir + "/maperitive/map_info.tex");
    if(!start_process_descr())
    {
        cleanup_descr();
        return;
    }

    cleanup_descr();

    std::string old_name = ad->work_dir + "\\maperitive\\map_info.pdf";
    std::string new_name = ad->work_dir + "\\maperitive\\" + Gebiet.Nr + "_" + Gebiet.Bez + ".pdf";
    file_rename(old_name, new_name);

    open_result_descr(new_name);
}

void C_ReportMapCreator::rollout_booklet(void)
{
    query_Gebiete();
    query_Nichtbesuche();
    query_Hinweise();

    create_process_data_booklet();
    create_process_data_file(ad->work_dir + "/maperitive/booklet.tex");
    if(!start_process_booklet())
    {
        cleanup_booklet();
        return;
    }

    cleanup_booklet();

    std::string old_name = ad->work_dir + "\\maperitive\\booklet.pdf";
    std::string new_name = ad->work_dir + "\\maperitive\\booklet_" + Gebiet.Nr + ".pdf";
    file_rename(old_name, new_name);

    open_result_booklet();
}

void C_ReportMapCreator::open_with_app(void)
{
    query_Maperitive();
    query_Gebiete();
    create_process_data_map(EDIT);
    create_process_data_file(ad->work_dir + "/maperitive/card.mscript");
    start_process_map(EDIT);
}

void C_ReportMapCreator::query_Maperitive(void)
{
    int rc;

    rc = open_db();

    std::string query = "";

    query += "SELECT * FROM tMaperitive WHERE GebietId = " + std::to_string(GebId) + " ";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if (rc == SQLITE_ROW)
        {
            Maperitive.Id          = get_int(COL_0);
            Maperitive.GebietId    = get_int(COL_1);
            Maperitive.mrule       = get_text(COL_2);
            Maperitive.height      = get_text(COL_3);
            Maperitive.width       = get_text(COL_4);
            Maperitive.orientation = get_text(COL_5);
            Maperitive.center      = get_text(COL_6);
            Maperitive.scale       = get_text(COL_7);
            Maperitive.border_file = get_text(COL_8);
        }

        if (done_or_error(rc))
        {
            break;
        }
    }

    rc = close_db();
}

void C_ReportMapCreator::query_Gebiete(void)
{
    int rc;

    rc = open_db();

    //Use old or new territory numbering
    std::string col_for_number = "tGebiet.Nr";
    if (settings->m_general.m_use_new_territory_numbers_in_maps)
        col_for_number = "tGebiet.NNr";

    std::string query = "";
    query += "SELECT tGebiet.Id, " + col_for_number + ", tGebiet.Bez, tGebiet.Act, tGebiet.WEinh, strftime('%d.%m.%Y', tGebiet.WEinh_Date), strftime('%d.%m.%Y', tGebiet.ErzStand) ";
    query += "FROM tGebiet ";
    query += "WHERE tGebiet.Id = " + std::to_string(GebId);

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if (rc == SQLITE_ROW)
        {
            Gebiet.Id         = get_int(COL_0);
            Gebiet.Nr         = get_text(COL_1);
            Gebiet.Bez        = get_text(COL_2);
            Gebiet.Act        = get_int(COL_3);
            Gebiet.WEinh      = get_int(COL_4);
            Gebiet.WEinh_Date = get_text(COL_5);
            Gebiet.ErzStand   = get_text(COL_6);
        }
        if (done_or_error(rc))
        {
            break;
        }
    }

    rc = close_db();
}

void C_ReportMapCreator::query_Nichtbesuche(void)
{
    int rc;
    Nichtbesuche.clear();

    rc = open_db();

    std::string query = "";

    query += "SELECT Adresse, Name, strftime('%d.%m.%Y', Datum), Kommentar ";
    query += "FROM tNichtbesuche ";
    query += "WHERE GebietId = " + std::to_string(GebId);

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            sNoVisits tmp;
            tmp.Adresse    = get_text(COL_0);
            tmp.Name       = get_text(COL_1);
            tmp.Datum      = get_text(COL_2);
            tmp.Kommentar  = get_text(COL_3);
            Nichtbesuche.push_back(tmp);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportMapCreator::query_Hinweise(void)
{
    int rc;
    Hinweise.clear();

    rc = open_db();

    std::string query = "";

    query += "SELECT Id, GebietId, Strasse ";
    query += "FROM tStrasse ";
    query += "WHERE GebietId = " + std::to_string(GebId);

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            sHints tmp;
            tmp.Strasse = get_text(COL_2);
            Hinweise.push_back(tmp);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportMapCreator::create_process_data_map(mode m)
{
    process_data.clear();

    process_data += u8R"(clear-map)" + sCR_LF;
    process_data += u8R"(change-directory )" + ad->work_dir + u8R"(\maperitive\)" + sCR_LF;
    process_data += u8R"(use-ruleset location=)" + settings->m_maperitive.rules_path + u8R"(\)" + Maperitive.mrule + u8R"( as-alias=card_small)" + sCR_LF;
    process_data += u8R"(set-setting name=map.decoration.grid value=false)" + sCR_LF;
    process_data += u8R"(set-setting name=map.decoration.attribution value=false)" + sCR_LF;
    process_data += u8R"(set-setting name=map.decoration.scale value=false)" + sCR_LF;
    process_data += u8R"(load-source )" + settings->m_maperitive.m_osm_file + sCR_LF;
    process_data += u8R"(set-paper height=)" + Maperitive.height + u8R"( width=)" + Maperitive.width + u8R"( orientation=)" + Maperitive.orientation + sCR_LF;
    process_data += u8R"(set-print-bounds-paper center=)" + Maperitive.center + u8R"( map-scale=)" + Maperitive.scale + sCR_LF;

    switch (m)
    {
    case EXPORT:
        process_data += u8R"(export-bitmap file=)" + Gebiet.Nr + R"(.png dpi=300)" + sCR_LF;
        process_data += u8R"(set-paper type=A5)" + sCR_LF;
        break;

    case EDIT:
        //TODO(mjb): maperitive: Zoomstufe beim Öffnen von Maperitive evtl. einstellbar machen
        if (false)
            process_data += u8R"(move-pos )" + transform_xy_coordinates(Maperitive.center) + u8R"( zoom=13.5)" + sCR_LF;
        else
        {
            process_data += u8R"(move-pos )" + transform_xy_coordinates(Maperitive.center) + sCR_LF;
            process_data += u8R"(zoom-map-scale )" + Maperitive.scale + sCR_LF;
            process_data += u8R"(//--> Geöffnet mit Gebietnr. )" + Gebiet.Nr + ", " + Gebiet.Bez + sCR_LF;
        }
        break;
    }
}

void C_ReportMapCreator::start_process_map(mode m)
{
    if (!check_file_present(process_data_file))
        return;

    std::string exec;
    exec_mode em;

    switch (m)
    {
    case EXPORT:
        exec = settings->m_maperitive.con_exe;
        em   = BLOCKING;
        break;
    case EDIT:
        exec = settings->m_maperitive.app_exe;
        em   = DETACHED;
        break;
    default:
        exec = settings->m_maperitive.con_exe;
        em   = BLOCKING;
    }

    std::vector<std::string> args;
    args.push_back(exec);
    args.push_back(process_data_file);
    exec_cmd(&args, em);

    //LOG(INFO) << exec_string;
}

void C_ReportMapCreator::cleanup_map(void)
{
    if (!settings->m_maperitive.m_del_tmp_files)
        return;

    std::vector<std::string> files_to_delete;

    files_to_delete.push_back(ad->work_dir + "/maperitive/" + Gebiet.Nr + ".png.georef");;
    files_to_delete.push_back(ad->work_dir + "/maperitive/card.mscript");

    if (files_to_delete.size() > 0)
        cleanup_processing_files(&files_to_delete);
}

void C_ReportMapCreator::create_process_data_im(void)
{
    std::string CardPNG    = ad->work_dir + "\\maperitive\\" + Gebiet.Nr + ".png";
    std::string BorderSVG  = settings->m_im.borders_path + "\\" + Maperitive.border_file;
    std::string FinalPNG   = ad->work_dir + "\\maperitive\\" + Gebiet.Nr + ".png";

    std::string Windrose          = ad->work_dir + "\\maperitive\\templates\\Compass-Arrow-300dpi.png";
    std::string Windrose_90degree = ad->work_dir + "\\maperitive\\templates\\Compass-Arrow-300dpi-90degree.png";

    std::string IM_im_receip_mapinfo = ad->work_dir + "\\maperitive\\im_receip_mapinfo.mvg";
    std::string IM_im_receip_osm     = ad->work_dir + "\\maperitive\\im_receip_osm.mvg";
    std::string IM_im_dimension      = ad->work_dir + "\\maperitive\\dimension.tmp";


    process_data = "";
    process_data += u8R"(fill rgba(255, 255, 255, 0.75))" + sCR_LF;
    process_data += u8R"(rectangle 0,0 1773,70)" + sCR_LF;
    process_data += u8R"(rectangle 0,1072 1773,1110)" + sCR_LF;
    process_data += u8R"(font-size 12)" + sCR_LF;
    process_data += u8R"(font 'Arial')" + sCR_LF;
    process_data += u8R"(fill 'black')" + sCR_LF;
    process_data += u8R"(stroke 'none')" + sCR_LF;
    process_data += u8R"(stroke-width 3)" + sCR_LF;
    process_data += u8R"(gravity NorthWest)" + sCR_LF;
    process_data += u8R"(text 10,8 ')" + Gebiet.Bez + u8R"(')" + sCR_LF;
    process_data += u8R"(gravity NorthEast)" + sCR_LF;
    process_data += u8R"(text 10,8 'Nr.: )" + Gebiet.Nr + u8R"(')" + sCR_LF;
    process_data += u8R"(font-size 8)" + sCR_LF;
    process_data += u8R"(font 'Arial')" + sCR_LF;
    process_data += u8R"(fill 'black')" + sCR_LF;
    process_data += u8R"(stroke 'none')" + sCR_LF;
    process_data += u8R"(stroke-width 3)" + sCR_LF;
    process_data += u8R"(gravity North)" + sCR_LF;
    process_data += u8R"(text 0,18 'Erzeugnisstand: )" + Gebiet.ErzStand + u8R"(')" + sCR_LF;
    process_data += u8R"(font-size 4)" + sCR_LF;
    process_data += u8R"(font 'Arial')" + sCR_LF;
    process_data += u8R"(fill 'black')" + sCR_LF;
    process_data += u8R"(stroke 'black')" + sCR_LF;
    process_data += u8R"(stroke-width 0)" + sCR_LF;
    process_data += u8R"(gravity South)" + sCR_LF;
    process_data += u8R"(text 0,10 'Bewahre diese Karte bitte in der Schutzhülle auf. Beschmutze, beschreibe und knicke sie nicht. Teile bitte dem Bruder, des sich um die Gebietsbearbeitung kümmert, jede Bearbeitung des Gebiets mit. (S-12-X)')" + sCR_LF;
    create_process_data_file(IM_im_receip_mapinfo);

    process_data = "";
    process_data += u8R"(font 'Arial')" + sCR_LF;
    process_data += u8R"(font-size 7)" + sCR_LF;
    process_data += u8R"(fill 'white')" + sCR_LF;
    process_data += u8R"(stroke 'none')" + sCR_LF;
    process_data += u8R"(text-undercolor #00000088)" + sCR_LF;
    process_data += u8R"(gravity South)" + sCR_LF;
    process_data += u8R"(text 0,0 ' Kartendaten © OpenStreetMap contributors ')" + sCR_LF;
    create_process_data_file(IM_im_receip_osm);



    //TODO(mjb): imagemagick: komische meldungen
    process_data = "";
//  process_data += u8R"(@ECHO OFF)" + sCR_LF;
    process_data += settings->m_im.magick_exe + u8R"( ^)" + sCR_LF;
    process_data += u8R"(    )" + CardPNG + u8R"( ^)" + sCR_LF;

    if (Maperitive.orientation.find("landscape") == std::string::npos)
        process_data += u8R"(    -rotate 270 ^)" + sCR_LF;

    process_data += u8R"(    -density 300 ^)" + sCR_LF;
    process_data += u8R"(    -background transparent ^)" + sCR_LF;
    process_data += u8R"(    )" + BorderSVG + u8R"( ^)" + sCR_LF;
    process_data += u8R"(    -composite ^)" + sCR_LF;
    process_data += u8R"(    -density 300 ^)" + sCR_LF;
    process_data += u8R"(    -draw @)" + IM_im_receip_mapinfo + u8R"( ^)" + sCR_LF;
    process_data += u8R"(    )" + FinalPNG + sCR_LF;

    //Add Windrose
    process_data += sCR_LF;
    process_data += sCR_LF;
    process_data += settings->m_im.magick_exe + u8R"( ^)" + sCR_LF;
    process_data += u8R"(    )" + CardPNG + u8R"( ^)" + sCR_LF;
    process_data += u8R"(    -background transparent ^)" + sCR_LF;
    process_data += u8R"(    ( ^)" + sCR_LF;
    if (Maperitive.orientation.find("portrait") == std::string::npos)
        process_data += u8R"(    )" + Windrose + u8R"( ^)" + sCR_LF;
    else
        process_data += u8R"(    )" + Windrose_90degree + u8R"( ^)" + sCR_LF;

    process_data += u8R"(    -resize x65 ^)" + sCR_LF;
    process_data += u8R"(    -geometry +1330+3 ^)" + sCR_LF;
    process_data += u8R"(    -alpha on ^)" + sCR_LF;
    process_data += u8R"(    ) ^)" + sCR_LF;
    process_data += u8R"(    -composite ^)" + sCR_LF;
    process_data += u8R"(    )" + FinalPNG + sCR_LF;

    //Add OSM Hinweise
    process_data += sCR_LF;
    process_data += sCR_LF;
    process_data += settings->m_im.magick_exe + u8R"( identify -format "%%hx%%w" )" + FinalPNG + u8R"(>)" + IM_im_dimension + sCR_LF;
    process_data += u8R"(SET /P BildDimension=<)" + IM_im_dimension + sCR_LF;
    process_data += sCR_LF;
    process_data += settings->m_im.magick_exe + u8R"( ^)" + sCR_LF;
    process_data += u8R"(    )" + CardPNG + u8R"( ^)" + sCR_LF;
    process_data += u8R"(    ( ^)" + sCR_LF;
    process_data += u8R"(    -size %BildDimension% xc:none ^)" + sCR_LF;
    process_data += u8R"(    -density 300 ^)" + sCR_LF;
    process_data += u8R"(    -draw @)" + IM_im_receip_osm + u8R"( ^)" + sCR_LF;
    process_data += u8R"(    -rotate -90 ^)" + sCR_LF;
    process_data += u8R"(    ) ^)" + sCR_LF;
    process_data += u8R"(    -composite ^)" + sCR_LF;
    process_data += u8R"(    )" + FinalPNG + sCR_LF;


    process_data += sCR_LF;
    process_data += sCR_LF;
    process_data += u8R"(ECHO im.bat done!)" + sCR_LF;
}

void C_ReportMapCreator::start_process_im(void)
{
    if (!check_file_present(process_data_file))
        return;

    std::vector<std::string> args;
  //args.push_back("cmd /U /C");
    args.push_back(process_data_file);
    exec_cmd(&args);

    //LOG(INFO) << process_data_file;
    //LOG(INFO) << process_data;
}

void C_ReportMapCreator::cleanup_im(void)
{
    if (!settings->m_im.m_del_tmp_files)
        return;

    std::vector<std::string> files_to_delete;

    files_to_delete.push_back(ad->work_dir + "\\maperitive\\im.bat");
    files_to_delete.push_back(ad->work_dir + "\\maperitive\\im_receip_mapinfo.mvg");
    files_to_delete.push_back(ad->work_dir + "\\maperitive\\im_receip_osm.mvg");
    files_to_delete.push_back(ad->work_dir + "\\maperitive\\dimension.tmp");


    if (files_to_delete.size() > 0)
        cleanup_processing_files(&files_to_delete);
}

void C_ReportMapCreator::set_description_image_size(double width_mm, double height_mm)
{
    m_width_mm = width_mm;
    m_height_mm = height_mm;
}

void C_ReportMapCreator::create_process_data_descr(void)
{
    process_data = "";

    process_data += R"(\documentclass[10pt]{article})" + sCR_LF;
    process_data += R"(\usepackage[margin=1in]{geometry})" + sCR_LF;
    process_data += R"(\geometry{a4paper, top=25mm, left=20mm, right=20mm, bottom=30mm, headsep=10mm, footskip=12mm})" + sCR_LF;
    process_data += R"(\usepackage[utf8]{inputenc})" + sCR_LF;
    process_data += R"(\usepackage[T1]{fontenc})" + sCR_LF;
    process_data += R"(\usepackage[ngerman]{babel})" + sCR_LF;
    process_data += R"(\usepackage{fancyhdr})" + sCR_LF;
    process_data += R"(\usepackage{graphicx})" + sCR_LF;

    process_data += R"(\usepackage{supertabular})" + sCR_LF;
    process_data += R"(\usepackage{array})" + sCR_LF;
    process_data += R"(\newcolumntype{C}[1]{>{\centering}p{#1}})" + sCR_LF;
    process_data += R"(\newcolumntype{P}[1]{>{\raggedright\arraybackslash}p{#1}})" + sCR_LF;

    process_data += R"(\usepackage{colortbl})" + sCR_LF;
    process_data += R"(\definecolor{blaua}{cmyk}{0.00,0.00,0.00,0.75})" + sCR_LF;
    process_data += R"(\definecolor{blaub}{cmyk}{0.35,0.20,0.00,0.45})" + sCR_LF;
    process_data += R"(\definecolor{blauc}{cmyk}{0.35,0.20,0.00,0.34})" + sCR_LF;
    process_data += R"(\definecolor{blaud}{cmyk}{0.35,0.10,0.00,0.01})" + sCR_LF;
    process_data += R"(\definecolor{blaue}{cmyk}{0.15,0.05,0.00,0.05})" + sCR_LF;

    process_data += R"(\begin{document})" + sCR_LF;

    if (Gebiet.WEinh)
        process_data += R"(\subsection*{Anzahl Wohneinheiten: )" + std::to_string(Gebiet.WEinh) + R"( (Stand )" + Gebiet.WEinh_Date + R"()})" + sCR_LF;
    else
        process_data += R"(\subsection*{Bitte die Anzahl der Wohneinheiten zählen.})" + sCR_LF;

    process_data += R"(\includegraphics[width=)" + std::to_string(m_width_mm) + R"(mm,height=)" + std::to_string(m_height_mm) + R"(mm]{maperitive/)" + Gebiet.Nr + R"(.png})" + sCR_LF;

    //Ab hier die Nichtbesuche
    if (Nichtbesuche.size() > 0)
    {
        //Build table head
        if (m_DSGVO)
        {
            process_data += R"(\subsection*{Nichtbesuche})" + sCR_LF;
            process_data += R"(\tablehead{\hline \rowcolor{blaud} Adresse & Datum \\ \hline\hline})" + sCR_LF;
            process_data += R"(\tabletail{\hline \multicolumn{2}{|r|}{\tiny{\emph{Weiter auf der naechsten Seite ...}}} \\ \hline})" + sCR_LF;
            process_data += R"(\tablelasttail{\hline})" + sCR_LF;
            process_data += R"(\begin{supertabular}{|l|l|} \hline)" + sCR_LF;

            for(std::vector<sNoVisits>::iterator it = Nichtbesuche.begin(); it != Nichtbesuche.end(); ++it)
                process_data += it->Adresse + R"( & )" + it->Datum + R"( \\ \hline)" + sCR_LF;
        }
        else
        {
            process_data += R"(\subsection*{Nichtbesuche})" + sCR_LF;
            process_data += R"(\tablehead{\hline \rowcolor{blaud} Adresse & Name & Datum \\ \hline\hline})" + sCR_LF;
            process_data += R"(\tabletail{\hline \multicolumn{3}{|r|}{\tiny{\emph{Weiter auf der naechsten Seite ...}}} \\ \hline})" + sCR_LF;
            process_data += R"(\tablelasttail{\hline})" + sCR_LF;
            process_data += R"(\begin{supertabular}{|l|l|l|} \hline)" + sCR_LF;

            for(std::vector<sNoVisits>::iterator it = Nichtbesuche.begin(); it != Nichtbesuche.end(); ++it)
                process_data += it->Adresse + R"( & )" + it->Name + R"( & )" + it->Datum + R"( \\ \hline)" + sCR_LF;
        }

        process_data += R"(\end{supertabular} )" + sCR_LF;
    }

    //Ab hier die Hinweise
    if (Hinweise.size() > 0)
    {
        //Build table head
        process_data += R"(\subsection*{Hinweise})" + sCR_LF;
        process_data += R"(\tablehead{\hline \rowcolor{blaud} Hinweise \\ \hline\hline})" + sCR_LF;
        process_data += R"(\tabletail{\hline \multicolumn{1}{|r|}{\tiny{\emph{Weiter auf der naechsten Seite ...}}} \\ \hline})" + sCR_LF;
        process_data += R"(\tablelasttail{\hline})" + sCR_LF;
        process_data += R"(\begin{supertabular}{|l|} \hline)" + sCR_LF;

        for(std::vector<sHints>::iterator it = Hinweise.begin(); it != Hinweise.end(); ++it)
            process_data += it->Strasse + R"( \\ \hline)" + sCR_LF;

        process_data += R"(\end{supertabular} )" + sCR_LF;
    }

    process_data += R"(\end{document})" + sCR_LF;
}

bool C_ReportMapCreator::start_process_descr(void)
{
    if (!check_file_present(process_data_file))
        return false;

    std::string img_file = ad->work_dir + "\\maperitive\\" + Gebiet.Nr + ".png";
    if (!check_file_present(img_file))
        return false;

    std::string executable = settings->m_latex.bin_path + "/pdflatex.exe";

    std::vector<std::string> args;
    args.push_back(executable);
    args.push_back("-output-directory=maperitive");
    args.push_back(process_data_file);
    exec_cmd(&args);

    return true;
}

void C_ReportMapCreator::cleanup_descr(void)
{
    std::vector<std::string> files_to_delete;

    if (settings->m_latex.del_latex_aux_files)
    {
        files_to_delete.push_back(ad->work_dir + "/maperitive/map_info.aux");
        files_to_delete.push_back(ad->work_dir + "/maperitive/map_info.log");
    }

    if (settings->m_latex.del_latex_data_tex)
        files_to_delete.push_back(ad->work_dir + "/maperitive/map_info.tex");

    if (files_to_delete.size() > 0)
        cleanup_processing_files(&files_to_delete);
}

void C_ReportMapCreator::open_result_descr(std::string result_file)
{
  //TODO(mjb) pdf opening: after report has been created
  //if (settings->m_latex.open_report_after_creation)
    {
        std::vector<std::string> args;
        args.push_back(settings->m_pdf_application);
        args.push_back(result_file);
        exec_cmd(&args, DETACHED);
    }
}


void C_ReportMapCreator::create_process_data_booklet(void)
{
    process_data = "";

    process_data += R"(\documentclass[a4paper,12pt]{scrartcl})" + sCR_LF;
    process_data += R"(\usepackage[a4paper,top=0pt,bottom=0pt,left=0pt,right=0pt]{geometry})" + sCR_LF;
    process_data += R"(\usepackage[utf8]{inputenc})" + sCR_LF;
    process_data += R"(\usepackage[T1]{fontenc})" + sCR_LF;
    process_data += R"(\usepackage[ngerman]{babel})" + sCR_LF;
    process_data += R"(\usepackage{tikz})" + sCR_LF;
    process_data += R"(\usepackage{rotating})" + sCR_LF;
    process_data += R"(\pagestyle{empty})" + sCR_LF;
    process_data += R"(\begin{document})" + sCR_LF;
    process_data += R"(\noindent\begin{tikzpicture})" + sCR_LF;
    process_data += R"(\path[use as bounding box] (-0.5\paperwidth,-0.5\paperheight) rectangle (0.5\paperwidth,0.5\paperheight);)" + sCR_LF;
    process_data += R"(\draw[<->] (0,-0.5\paperheight) -- (0,0.5\paperheight);)" + sCR_LF;
    process_data += R"(\draw[<->] (-0.5\paperwidth,0) -- (0.5\paperwidth,0);)" + sCR_LF;
    process_data += R"(\draw[<->] (-0.5\paperwidth,.25\paperheight) -- (0.5\paperwidth,.25\paperheight);)" + sCR_LF;
    process_data += R"(\draw[<->] (-0.5\paperwidth,-.25\paperheight) -- (0.5\paperwidth,-.25\paperheight);)" + sCR_LF;
    process_data += R"(\node (myfirstpic) at (0.25\paperwidth,-.25\paperheight) {\includegraphics[width=14cm, angle=-90, origin=c]{)" + Gebiet.Nr + R"(.png}};)" + sCR_LF;



    //Ab hier Texte
    process_data += R"(\node[right] (box) at (-0.47\paperwidth,-.375\paperheight){%)" + sCR_LF;
    process_data += R"(    \begin{turn}{90})" + sCR_LF;
    process_data += R"(%   \fbox{%)" + sCR_LF;
    process_data += R"(    \begin{minipage}[t!]{0.22\paperheight})" + sCR_LF;

    //Ab hier Anzahl Familien
    if (Gebiet.WEinh)
        process_data += R"(\subsubsection*{Wohneinheiten: )" + std::to_string(Gebiet.WEinh) + R"( \tiny{()" + Gebiet.WEinh_Date + R"()}})" + sCR_LF;
    else
        process_data += R"(\subsubsection*{Bitte die Anzahl der Wohneinheiten zählen.})" + sCR_LF;


    //Ab hier Nichtbesuche
    if (Nichtbesuche.size() > 0)
    {
        if (m_DSGVO)
        {
            process_data += R"(        \subsubsection*{Nichtbesuche})" + sCR_LF;
            process_data += R"(        \begin{tiny})" + sCR_LF;
            process_data += R"(        \begin{tabular}{ll})" + sCR_LF;
            process_data += R"(        Adresse & Datum \\ \hline \hline)" + sCR_LF;

            for(std::vector<sNoVisits>::iterator it = Nichtbesuche.begin(); it != Nichtbesuche.end(); ++it)
                process_data += it->Adresse + R"( & )" + it->Datum + R"( \\ \hline)" + sCR_LF;
        }
        else
        {
            process_data += R"(        \subsubsection*{Nichtbesuche})" + sCR_LF;
            process_data += R"(        \begin{tiny})" + sCR_LF;
            process_data += R"(        \begin{tabular}{lll})" + sCR_LF;
            process_data += R"(        Adresse & Name & Datum \\ \hline \hline)" + sCR_LF;

            for(std::vector<sNoVisits>::iterator it = Nichtbesuche.begin(); it != Nichtbesuche.end(); ++it)
                process_data += it->Adresse + R"( & )" + it->Name + R"( & )" + it->Datum + R"( \\ \hline)" + sCR_LF;
        }

        process_data += R"(        \end{tabular})" + sCR_LF;
        process_data += R"(        \end{tiny})" + sCR_LF;
    }

    //Ab hier Hinweise
    if (Hinweise.size() > 0)
    {
        process_data += R"(        \subsubsection*{Hinweise})" + sCR_LF;
        process_data += R"(        \begin{tiny})" + sCR_LF;
        process_data += R"(        \begin{tabular}{l})" + sCR_LF;
        process_data += R"(        Hinweise \\ \hline \hline)" + sCR_LF;

        for(std::vector<sHints>::iterator it = Hinweise.begin(); it != Hinweise.end(); ++it)
            process_data += it->Strasse + R"( \\ \hline)" + sCR_LF;

        process_data += R"(        \end{tabular})" + sCR_LF;
        process_data += R"(        \end{tiny})" + sCR_LF;
    }

    process_data += R"(    \end{minipage})" + sCR_LF;
    process_data += R"(%   })" + sCR_LF;
    process_data += R"(    \end{turn})" + sCR_LF;
    process_data += R"(    };)" + sCR_LF;


    process_data += R"(\end{tikzpicture})" + sCR_LF;
    process_data += R"(\end{document})" + sCR_LF;
}

bool C_ReportMapCreator::start_process_booklet(void)
{
    if (!check_file_present(process_data_file))
        return false;

    std::string img_file = ad->work_dir + "\\maperitive\\" + Gebiet.Nr + ".png";
    if (!check_file_present(img_file))
        return false;

    std::string executable = settings->m_latex.bin_path + "/pdflatex.exe";

    std::vector<std::string> args;
    args.push_back(executable);
    args.push_back("-output-directory=maperitive");
    args.push_back(process_data_file);
    exec_cmd(&args);

    return true;
}

void C_ReportMapCreator::cleanup_booklet(void)
{
    std::vector<std::string> files_to_delete;

    if (settings->m_latex.del_latex_aux_files)
    {
        files_to_delete.push_back(ad->work_dir + "/maperitive/booklet.aux");
        files_to_delete.push_back(ad->work_dir + "/maperitive/booklet.log");
    }

    if (settings->m_latex.del_latex_data_tex)
        files_to_delete.push_back(ad->work_dir + "/maperitive/booklet.tex");

    if (files_to_delete.size() > 0)
        cleanup_processing_files(&files_to_delete);
}

void C_ReportMapCreator::open_result_booklet(void)
{
  //TODO(mjb) pdf opening: after report has been created
  //if (settings->m_latex.open_report_after_creation)
    {
        std::vector<std::string> args;
        args.push_back(settings->m_pdf_application);
        args.push_back(ad->work_dir + "\\maperitive\\booklet_" + Gebiet.Nr + ".pdf");
        exec_cmd(&args, DETACHED);
    }
}

std::string C_ReportMapCreator::transform_xy_coordinates(std::string xy_to_cut)
{
    std::string tmp;
    std::vector<std::string> strs;
    boost::split(strs, xy_to_cut, boost::is_any_of(","));
    tmp = "x=" + strs[0] + " y=" + strs[1];
    return tmp;
}

void C_ReportMapCreator::file_rename(std::string old_name, std::string new_name)
{
    if (!check_file_present(old_name))
        return;

    if (check_file_present(new_name))
        remove(new_name.c_str());

    rename(old_name.c_str(), new_name.c_str());
}

void C_ReportMapCreator::push_card_viewer(void)
{
    if (push_card)
        push_card(Gebiet.Nr);
}
