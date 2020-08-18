#include "C_ReportMapCreatorAll.h"

C_ReportMapCreatorAll::C_ReportMapCreatorAll(const ApplicationData *ad, const C_Settings *s)
: C_ReportMapCreator(ad, s, 0)
{
    //ctor
}

C_ReportMapCreatorAll::~C_ReportMapCreatorAll()
{
    //dtor
}

void C_ReportMapCreatorAll::rollout_all(void)
{
    query_Maperitive();
    query_Gebiete();
    create_process_data();
    create_process_data_file(ad->work_dir + "/maperitive/all_cards.mscript");

    create_process_data_im();
    create_process_data_file(ad->work_dir + "/maperitive/all_cards_im.bat");

    start_process();
}

void C_ReportMapCreatorAll::printout_all(void)
{
    double card_width  = settings->m_general.m_infopage_map_width_mm;
    double card_height = settings->m_general.m_infopage_map_height_mm;

    set_description_image_size(card_width, card_height);
    query_Maperitive();
    query_Gebiete();

    create_process_data_printout();
    create_process_data_file(ad->work_dir + "/maperitive/all_plain_cards.tex");

    start_process_printout();
    cleanup_printout();
    open_result_printout();
}

void C_ReportMapCreatorAll::query_Maperitive(void)
{
    int rc;
    vec_Maperitive.clear();

    rc = open_db();

    std::string query = "";

    query += "SELECT * FROM tMaperitive";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            sMaperitive tmp;
            tmp.Id          = get_int(COL_0);
            tmp.GebietId    = get_int(COL_1);
            tmp.mrule       = get_text(COL_2);
            tmp.height      = get_text(COL_3);
            tmp.width       = get_text(COL_4);
            tmp.orientation = get_text(COL_5);
            tmp.center      = get_text(COL_6);
            tmp.scale       = get_text(COL_7);
            tmp.border_file = get_text(COL_8);
            vec_Maperitive.push_back(tmp);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportMapCreatorAll::query_Gebiete(void)
{
    int rc;
    vec_Gebiet.clear();

    rc = open_db();

    //Use old or new territory numbering
    std::string col_for_number = "tGebiet.Nr";
    if (settings->m_general.m_use_new_territory_numbers_in_maps)
        col_for_number = "tGebiet.NNr";

    std::string query = "";
    query += "SELECT tGebiet.Id, " + col_for_number + ", tGebiet.Bez, tGebiet.Act, tGebiet.WEinh, strftime('%d.%m.%Y', tGebiet.WEinh_Date), strftime('%d.%m.%Y', tGebiet.ErzStand) ";
    query += "FROM tGebiet ";
    query += "ORDER BY " + col_for_number;

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            sGebInfo tmp;
            tmp.Id         = get_int(COL_0);
            tmp.Nr         = get_text(COL_1);
            tmp.Bez        = get_text(COL_2);
            tmp.Act        = get_int(COL_3);
            tmp.WEinh      = get_int(COL_4);
            tmp.WEinh_Date = get_text(COL_5);
            tmp.ErzStand   = get_text(COL_6);
            vec_Gebiet.push_back(tmp);
        }
        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportMapCreatorAll::create_process_data(void)
{
    process_data.clear();

    process_data += u8R"(clear-map)" + sCR_LF;
    process_data += u8R"(change-directory )" + ad->work_dir + u8R"(\maperitive\)" + sCR_LF;
    process_data += u8R"(set-setting name=map.decoration.grid value=false)" + sCR_LF;
    process_data += u8R"(set-setting name=map.decoration.attribution value=false)" + sCR_LF;
    process_data += u8R"(set-setting name=map.decoration.scale value=false)" + sCR_LF;
    process_data += u8R"(use-ruleset alias=default)" + sCR_LF;
    process_data += u8R"(load-source )" + settings->m_maperitive.m_osm_file + sCR_LF;

    for (std::vector<sMaperitive>::iterator it = vec_Maperitive.begin(); it != vec_Maperitive.end(); ++it)
    {
        process_data += u8R"(use-ruleset location=)" + settings->m_maperitive.rules_path + u8R"(\)" + it->mrule + u8R"( as-alias=card_small)" + sCR_LF;
        process_data += u8R"(apply-ruleset)" + sCR_LF;
        process_data += u8R"(set-paper height=)" + it->height + u8R"( width=)" + it->width + u8R"( orientation=)" + it->orientation + sCR_LF;
        process_data += u8R"(set-print-bounds-paper center=)" + it->center + u8R"( map-scale=)" + it->scale + sCR_LF;
        process_data += u8R"(export-bitmap file=)" + ad->work_dir + u8R"(/maperitive/set/)" + get_GebNr_from_GebId(it->GebietId) + u8R"(.png dpi=300)" + sCR_LF;
    }

    process_data += u8R"(set-paper type=A5)" + sCR_LF;
}

void C_ReportMapCreatorAll::start_process(void)
{
    if (!check_file_present(process_data_file))
        return;

    std::vector<std::string> args;
    args.push_back(process_data_file);
    exec_cmd(&args, DETACHED);
}

void C_ReportMapCreatorAll::create_process_data_im(void)
{
    process_data = "";
    process_data += "REM Font for console has to be Lucida Console\n";
    process_data += u8R"(chcp 65001)";
    process_data += "\n";

    process_data += settings->m_maperitive.con_exe + " " + process_data_file;
    process_data += "\n";

    for (std::vector<sMaperitive>::iterator it = vec_Maperitive.begin(); it != vec_Maperitive.end(); ++it)
    {
        std::string Nr, Bez, ErzStand;
        get_GebData_by_Id(it->GebietId, &Nr, &Bez, &ErzStand);

        std::string CardPNG   = ad->work_dir + "\\maperitive\\set\\" + Nr + ".png";
        std::string BorderSVG = settings->m_im.borders_path + "\\" + it->border_file;
        std::string FinalPNG  = ad->work_dir + "\\maperitive\\set\\" + Nr + ".png";
        std::string BottomText = "Bewahre diese Karte bitte in der Schutzhülle auf. Beschmutze, beschreibe und knicke sie nicht. Teile bitte dem Bruder, des sich um die Gebietsbearbeitung kümmert, jede Bearbeitung des Gebiets mit. (S-12-X)";

        std::string Windrose          = ad->work_dir + "\\maperitive\\templates\\Compass-Arrow-300dpi.png";
        std::string Windrose_90degree = ad->work_dir + "\\maperitive\\templates\\Compass-Arrow-300dpi-90degree.png";

        process_data += settings->m_im.magick_exe + sBLANK;
        if (it->orientation.find("portrait") == std::string::npos)
            process_data += CardPNG + u8R"( -density 300 -background transparent )" + BorderSVG + u8R"( )";
        else
            process_data += CardPNG + u8R"( -rotate 270 -density 300 -background transparent )" + BorderSVG + u8R"( )";

        process_data += u8R"(-composite -density 300 )";
        process_data += u8R"(-fill "rgba(255, 255, 255, 0.75) " )";
        process_data += u8R"(-draw "rectangle 0,0 1773,70" )";
        process_data += u8R"(-draw "rectangle 0,1072 1773,1110" )";
        process_data += u8R"(-pointsize 12 -font Arial -fill black -stroke none -strokewidth 3 )";
        process_data += u8R"(-gravity Northwest -draw "text 10,8 ')"      + Bez + u8R"('" )";
        process_data += u8R"(-gravity Northeast -draw "text 10,8 'Nr.: )" + Nr  + u8R"('" )";
        process_data += u8R"(-pointsize 8 -font Arial -fill black -stroke none -strokewidth 3 )";
        process_data += u8R"(-gravity North -draw "text 0,18 'Erzeugnisstand: )" + ErzStand + u8R"('" )";
        process_data += u8R"(-pointsize 4 -font Arial -fill black -stroke black -strokewidth 0 )";
        process_data += u8R"(-gravity South -draw "text 0,10 ')" + BottomText + u8R"('" )";
        process_data += FinalPNG;

        //Add Windrose
        process_data += "\n";
        process_data += settings->m_im.magick_exe + sBLANK;
        if (it->orientation.find("portrait") == std::string::npos)
            process_data += CardPNG + u8R"( -background transparent ( )" + Windrose + u8R"( -rotate 0 -resize x65 -geometry +1330+3 -alpha on ) -composite  )" + FinalPNG;
        else
            process_data += CardPNG + u8R"( -background transparent ( )" + Windrose_90degree + u8R"( -rotate 0 -resize x65 -geometry +1330+3 -alpha on ) -composite  )" + FinalPNG;

        //Add OSM und CC Hinweise
        process_data += "\n";
        process_data += settings->m_im.magick_exe + sBLANK;
        process_data += CardPNG + R"( -rotate 90 ^)" + sCR_LF;
        process_data += R"( -font Arial -pointsize 26 ^)" + sCR_LF;
        process_data += R"( -fill white -undercolor "#00000088" ^)" + sCR_LF;
        process_data += R"( -gravity South ^)" + sCR_LF;
        process_data += R"( -annotate +0+0 "Kartendaten © OpenStreetMap contributors" ^)" + sCR_LF;
        process_data += R"( -rotate -90 )" + FinalPNG;

        process_data += "\n";
    }

    std::string del_a = u8R"(DEL )" + ad->work_dir + u8R"(/maperitive/set/*.georef)" + sCR_LF;
    std::string del_b = u8R"(DEL )" + ad->work_dir + u8R"(/maperitive/all_cards.mscript)" + sCR_LF;
    std::string del_c = ad->work_dir + u8R"(/maperitive/all_cards_im.bat)" + sCR_LF;

    std::replace(del_a.begin(), del_a.end(), '/', '\\');
    std::replace(del_b.begin(), del_b.end(), '/', '\\');
    std::replace(del_c.begin(), del_c.end(), '/', '\\');

    del_c = u8R"(DEL /F )" + del_c;

    if (settings->m_maperitive.m_del_tmp_files)
    {
        process_data += del_a;
        process_data += del_b;
    }

    if (settings->m_im.m_del_tmp_files)
        process_data += del_c;
}

std::string C_ReportMapCreatorAll::get_GebNr_from_GebId(int GebId)
{
    std::string ret_val = "not found";
    for (std::vector<sGebInfo>::iterator it = vec_Gebiet.begin(); it != vec_Gebiet.end(); ++it)
        if (it->Id == GebId)
            return it->Nr;

    return ret_val;
}

void C_ReportMapCreatorAll::get_GebData_by_Id(int Id, std::string *Nr, std::string *Bez, std::string *ErzStand)
{
    for (std::vector<sGebInfo>::iterator it = vec_Gebiet.begin(); it != vec_Gebiet.end(); ++it)
    {
        if (it->Id == Id)
        {
            if (Nr         != nullptr) { *Nr         = it->Nr; }
            if (Bez        != nullptr) { *Bez        = it->Bez; }
            if (ErzStand   != nullptr) { *ErzStand   = it->ErzStand; }
            break;
        }
    }
}

void C_ReportMapCreatorAll::create_process_data_printout(void)
{

    std::string width  = std::to_string(m_width_mm);
    std::string height = std::to_string(m_height_mm);

    process_data = "";

    process_data += R"(\documentclass[10pt]{article})" + sCR_LF;
    process_data += R"(\usepackage[margin=1in]{geometry})" + sCR_LF;
    process_data += R"(\geometry{a4paper, top=25mm, left=20mm, right=20mm, bottom=30mm, headsep=10mm, footskip=12mm})" + sCR_LF;
    process_data += R"(\usepackage[utf8]{inputenc})" + sCR_LF;
    process_data += R"(\usepackage[T1]{fontenc})" + sCR_LF;
    process_data += R"(\usepackage[ngerman]{babel})" + sCR_LF;
    process_data += R"(\usepackage{fancyhdr})" + sCR_LF;
    process_data += R"(\usepackage{graphicx})" + sCR_LF;

    process_data += R"(\begin{document})" + sCR_LF;

    for (std::vector<sGebInfo>::iterator it = vec_Gebiet.begin(); it != vec_Gebiet.end(); ++it)
    {
        std::string ImageFile;
        ImageFile = ad->work_dir + u8R"(/maperitive/)" + it->Nr + u8R"(.png)";
        if (check_file_present(ImageFile))
        {
            process_data += R"(\subsection*{()" + it->Nr + R"())" + sBLANK + it->Bez + R"(})" + sCR_LF;
            process_data += R"(\begin{center})" + sCR_LF;
            process_data += R"(\includegraphics[width=)" + width + R"(mm,height=)" + height + R"(mm]{maperitive/)" + it->Nr + R"(.png}\\)" + sCR_LF;
            process_data += R"({\tiny )" + width + "x" + height + R"( mm})";
            process_data += R"(\end{center})" + sCR_LF;
        }
    }

    process_data += R"(\end{document})" + sCR_LF;
}

void C_ReportMapCreatorAll::start_process_printout(void)
{
    if (!check_file_present(process_data_file))
        return;

    std::string executable = settings->m_latex.bin_path + "/pdflatex.exe";

    std::vector<std::string> args;
    args.push_back(executable);
    args.push_back("-output-directory=maperitive");
    args.push_back(process_data_file);
    exec_cmd(&args);
}

void C_ReportMapCreatorAll::cleanup_printout(void)
{
    std::vector<std::string> files_to_delete;

    if (settings->m_latex.del_latex_aux_files)
    {
        files_to_delete.push_back(ad->work_dir + "/maperitive/all_plain_cards.aux");
        files_to_delete.push_back(ad->work_dir + "/maperitive/all_plain_cards.log");
    }

    if (settings->m_latex.del_latex_data_tex)
        files_to_delete.push_back(ad->work_dir + "/maperitive/all_plain_cards.tex");

    if (files_to_delete.size() > 0)
        cleanup_processing_files(&files_to_delete);
}

void C_ReportMapCreatorAll::open_result_printout(void)
{
  //TODO(mjb) pdf opening: after report has been created
  //if (settings->m_latex.open_report_after_creation)
    {
        std::vector<std::string> args;
        args.push_back(settings->m_pdf_application);
        args.push_back(ad->work_dir + "\\maperitive\\all_plain_cards.pdf");
        exec_cmd(&args, DETACHED);
    }
}
