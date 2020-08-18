#include "C_ReportOverview.h"

C_ReportOverview::C_ReportOverview(const ApplicationData *ad, const C_Settings *s)
: C_DbHandle(&ad->db_file), C_Report(ad, s)
{
    //ctor
}

C_ReportOverview::~C_ReportOverview()
{
    //dtor
}

void C_ReportOverview::rollout(void)
{
    query_Gebiete();
    query_Aktionen();
    create_process_data();
    create_process_data_file(ad->work_dir + "/report/data.tex");
    start_process();
    cleanup();
    open_result();
}

void C_ReportOverview::query_Gebiete()
{
    int rc;
    Gebiete.clear();

    rc = open_db();

    // Use new territory numbering
    std::string NbField = "tGebiet.Nr";
    if (settings->m_general.m_use_new_territory_numbers_in_maps)
        NbField = "tGebiet.NNr";

    std::string query = "";
    query += "SELECT tGebiet.Id, " + NbField + ", tGebiet.Bez, tGebiet.Act, tGebiet.WEinh, strftime('%d.%m.%Y', tGebiet.WEinh_Date) ";
    query += "FROM tGebiet ";
    query += "ORDER BY " + NbField + " ASC";

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
            Gebiete.push_back(tmp);
        }
        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportOverview::query_Aktionen(void)
{
    Aktionen.clear();

    open_db();

    std::string query = "";
    query += "SELECT Id, GebietId, Name, Kommentar, Ausgabe, strftime('%d.%m.%Y', Ausgabe) as Ausgabe2, Zurueck, strftime('%d.%m.%Y', Zurueck) as Zurueck2 ";
    query += "FROM tAktion ";
    query += "ORDER BY Ausgabe ASC";

    query_db(&query);

    while (true)
    {
        int res = step_db();
        if(res == SQLITE_ROW)
        {
            sAktion tmp;
            tmp.Id        = get_int(COL_0);
            tmp.GebId     = get_int(COL_1);
            tmp.Name      = get_text(COL_2);
            tmp.Kommentar = get_text(COL_3);
            tmp.Ausgabe   = get_text(COL_5);
            tmp.Zurueck   = get_text(COL_7);
            Aktionen.push_back(tmp);

        }
        if(done_or_error(res))
            break;
    }

    close_db();
}

void C_ReportOverview::query_Aktionen_of_Gebiet(int GebId)
{
    Aktionen.clear();

    open_db();

    std::string query = "";
    query += "SELECT Id, GebietId, Name, Kommentar ,strftime('%d.%m.%Y', Ausgabe) as Ausgabe, strftime('%d.%m.%Y', Zurueck) as Zurueck ";
    query += "FROM tAktion ";
    query += "WHERE GebietId=" + std::to_string(GebId);

    query_db(&query);

    while (true)
    {
        int res = step_db();
        if(res == SQLITE_ROW)
        {
            sAktion tmp;
            tmp.Id        = get_int(COL_0);
            tmp.GebId     = get_int(COL_1);
            tmp.Name      = get_text(COL_2);
            tmp.Kommentar = get_text(COL_3);
            tmp.Ausgabe   = get_text(COL_4);
            tmp.Zurueck   = get_text(COL_5);
            Aktionen.push_back(tmp);

        }
        if(done_or_error(res))
            break;
    }

    close_db();
}

void C_ReportOverview::create_process_data(void)
{
    process_data = "";

    //Iteriere durch Anzahl Gebiete
    for(std::vector<sGebInfo>::iterator it_G = Gebiete.begin(); it_G != Gebiete.end(); ++it_G)
    {
        std::string tmpWEinh = "";
        std::string tmpDate  = "";

        //Keine Anzahl angegeben
        if (it_G->WEinh > 0)
        {
            tmpWEinh = "ca. " + std::to_string(it_G->WEinh);
            tmpDate = it_G->WEinh_Date;
        }

        //Build table head
        process_data += R"(\TrickSupertabularIntoMulticols)" + sCR_LF;
        process_data += R"(\tablefirsthead{})" + sCR_LF;
        process_data += R"(\tablehead{\hline \multicolumn{2}{|r|}{\tiny{\emph{Fortsetzung ...}}} \\ \hline} )" + sCR_LF;
        process_data += R"(\tabletail{\hline \multicolumn{2}{|r|}{\tiny{\emph{naechsten Spalte ...}}} \\ \hline} )" + sCR_LF;
        process_data += R"(\tablelasttail{} )" + sCR_LF;
        process_data += R"(\begin{supertabular}{|c|c|} \hline)" + sCR_LF;
        process_data += R"(\rowcolor{blaud}\multicolumn{2}{|c|}{)" + it_G->Bez + R"(} \\)" + sCR_LF;
        process_data += R"(\rowcolor{blaud}\multicolumn{1}{|l}{Geb.-Nr.:} & \multicolumn{1}{r|}{)" + it_G->Nr   + R"(} \\)" + sCR_LF;
        process_data += R"(\rowcolor{blaud}\multicolumn{1}{|l}{Familien:} & \multicolumn{1}{r|}{)" + tmpWEinh + R"(} \\)" + sCR_LF;
        process_data += R"(\rowcolor{blaud}\multicolumn{1}{|l}{Stand:}    & \multicolumn{1}{r|}{)" + tmpDate  + R"(} \\ \hline\hline)" + sCR_LF;
        process_data += R"(\rowcolor{blaue}\multicolumn{2}{|c|}{\it Name} \\ \hline )" + sCR_LF;
        process_data += R"(\rowcolor{blaue}{\it Ausgabe} & {\it Zurück} \\ \hline)" + sCR_LF;

        //Iteriere durch Anzahl Aktionen
        for(std::vector<sAktion>::iterator it_A = Aktionen.begin(); it_A != Aktionen.end(); ++it_A)
        {
            if (it_G->Id == it_A->GebId)
            {
                process_data += R"(\hline)";
                process_data += R"(\multicolumn{2}{|C{32.5mm}|}{)" + it_A->Name + R"(}\\ \hline )" + sCR_LF;
                if (it_A->Kommentar.size() > 0)
                    process_data += R"(\multicolumn{2}{|C{32.5mm}|}{)" + it_A->Kommentar + R"(}\\ \hline )" + sCR_LF;
                process_data += it_A->Ausgabe + R"( & )";
                process_data += it_A->Zurueck + R"( \\ \hline)" + sCR_LF;
            }
        }
        process_data += R"(\end{supertabular})" + sCR_LF;

        if (it_G != Gebiete.end()-1)  //last element
        {
            process_data += R"(\columnbreak \\)";
        }
        process_data += sCR_LF;
    }
}

void C_ReportOverview::start_process(void)
{
    if (!check_file_present(process_data_file))
        return;

    std::string executable = settings->m_latex.bin_path + "/pdflatex.exe";
    process_file = ad->work_dir + "/report/report_tmpl.tex";
    output_file  = ad->work_dir + "/report/report_tmpl.pdf";
    report_file  = ad->work_dir + "/report/Zuteilungskarte_" + build_timestamp() + ".pdf";

    std::vector<std::string> args;
    args.push_back(executable);
    args.push_back("-output-directory=report");
    args.push_back(process_file);
    exec_cmd(&args);

    rename_output_file_to_report_file();
}

void C_ReportOverview::cleanup(void)
{
    std::vector<std::string> files_to_delete;

    if (settings->m_latex.del_latex_aux_files)
    {
        files_to_delete.push_back(ad->work_dir + "/report/report_tmpl.aux");
        files_to_delete.push_back(ad->work_dir + "/report/report_tmpl.log");
        files_to_delete.push_back(output_file);
    }

    if (settings->m_latex.del_latex_data_tex)
        files_to_delete.push_back(ad->work_dir + "/report/data.tex");

    if (files_to_delete.size() > 0)
        cleanup_processing_files(&files_to_delete);
}

void C_ReportOverview::open_result(void)
{
  //TODO(mjb) pdf opening: after report has been created
  //if (settings->m_latex.open_report_after_creation)
    {
        std::vector<std::string> args;
        args.push_back(settings->m_pdf_application);
        args.push_back(report_file);
        exec_cmd(&args, DETACHED);
    }
}
