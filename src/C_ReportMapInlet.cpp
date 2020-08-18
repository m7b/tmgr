#include "C_ReportMapInlet.h"

C_ReportMapInlet::C_ReportMapInlet(const ApplicationData *ad, const C_Settings *s, int GebId)
: C_DbHandle(&ad->db_file), C_Report(ad, s), GebId(GebId)
{
    //ctor
    m_DSGVO = DSGVO;
}

C_ReportMapInlet::~C_ReportMapInlet()
{
    //dtor
}

void C_ReportMapInlet::rollout(void)
{
    query_MapInfo();
    query_NoVisits();
    query_Streets();
    create_process_data();
    create_process_data_file(ad->work_dir + "/report/data.tex");
    start_process();
    cleanup();
    open_result();
}

void C_ReportMapInlet::query_MapInfo(void)
{
    int rc;

    // Use new territory numbering
    std::string NbField = "tGebiet.Nr";
    if (settings->m_general.m_use_new_territory_numbers_in_maps)
        NbField = "tGebiet.NNr";

    rc = open_db();

    std::string query = "";

    query += "SELECT tGebiet.Id, " + NbField + ", tGebiet.Bez, tGebiet.Act, tGebiet.WEinh, strftime('%d.%m.%Y', tGebiet.WEinh_Date) as Stand, t2.Name, strftime('%d.%m.%Y', t2.Ausgabe) AS Ausgabe, strftime('%d.%m.%Y', t2.Zurueck) AS Zurueck, t2.Kommentar ";
    query += "FROM ( ";
    query += "SELECT Id, GebietId, Name, Ausgabe, MAX(Zurueck) as Zurueck, Kommentar FROM tAktion GROUP BY GebietId ";
    query += ") ";
    query += "AS t2 ";
    query += "INNER JOIN tGebiet ON tGebiet.Id = t2.GebietId ";
    query += "WHERE tGebiet.Id = " + std::to_string(GebId);


    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            MapInfo.Id         = get_int(COL_0);
            MapInfo.Nr         = get_text(COL_1);
            MapInfo.Bez        = get_text(COL_2);
            MapInfo.Act        = get_int(COL_3);
            MapInfo.WEinh      = get_int(COL_4);
            MapInfo.WEinhStand = get_text(COL_5);
            MapInfo.Name       = get_text(COL_6);
            MapInfo.Ausgabe    = get_text(COL_7);
            MapInfo.Zurueck    = get_text(COL_8);
            MapInfo.Kommentar  = get_text(COL_9);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportMapInlet::query_NoVisits(void)
{
    int rc;
    NoVisits.clear();

    rc = open_db();

    std::string query = "";

    query += "SELECT GebietId, Name, Adresse, strftime('%d.%m.%Y', Datum), Kommentar ";
    query += "FROM tNichtbesuche ";
    query += "WHERE GebietId = " + std::to_string(GebId) + " ";
    query += "ORDER BY Adresse ASC";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            sNoVisits tmp;
            tmp.Id        = get_int(COL_0);
            tmp.Name      = get_text(COL_1);
            tmp.Adresse   = get_text(COL_2);
            tmp.Datum     = get_text(COL_3);
            tmp.Kommentar = get_text(COL_4);
            NoVisits.push_back(tmp);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportMapInlet::query_Streets(void)
{
    int rc;
    Streets.clear();

    rc = open_db();

    std::string query = "";

    query += "SELECT Strasse ";
    query += "FROM tStrasse ";
    query += "WHERE tStrasse.GebietId = " + std::to_string(GebId);

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            std::string tmp;
            tmp   = get_text(COL_0);
            Streets.push_back(tmp);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportMapInlet::create_process_data(void)
{
    process_data = "";

    //Build amount families
    std::string Familien;
    if (MapInfo.WEinh > 0)
        Familien = "Familien: " + std::to_string(MapInfo.WEinh) + " -- Stand: " + MapInfo.WEinhStand;
    else
        Familien = "Deutschsprachige Familien sollten noch gezählt werden!";

    //Iteriere durch Straßen
    std::string Strassen = "";
    bool first = false;
    for(std::vector<std::string>::iterator it = Streets.begin(); it != Streets.end(); ++it)
    {
        if (!first)
        {
            Strassen += R"($\cdot$ )" + *it;
            first = true;
        }
        else
            Strassen += R"($\newline \cdot$ )" + *it + R"( )";
    }

    //Erstelle Report
    if (m_DSGVO)
    {
        process_data += R"(\begin{supertabular}{|p{1.88cm}p{1.50cm}p{1.30cm}p{1.88cm}p{4.72cm}|} \hline )" + sCR_LF;
        process_data += R"( &  &  &  & \\ )" + sCR_LF;
        process_data += R"(\multicolumn{4}{|l}{\huge{)" + MapInfo.Bez + R"(}} & \multicolumn{1}{r|}{\huge{)" + MapInfo.Nr + R"(}} \\ )" + sCR_LF;
        process_data += R"(\multicolumn{5}{|l|}{)" + Familien + R"(} \\ )" + sCR_LF;
        process_data += R"( &  &  &  & \\ \hline\hline )" + sCR_LF;
        process_data += R"(\multicolumn{2}{|l}{{\bf\footnotesize Nichtbesuche$^\ast$ Anschrift}} & {\bf\footnotesize Datum} & \multicolumn{2}{|l|}{{\bf\footnotesize Hinweise}} \\ \hline )" + sCR_LF;
    }
    else
    {
        process_data += R"(\begin{supertabular}{|p{1.88cm}p{1.50cm}p{2.84cm}p{1.30cm}p{1.88cm}p{1.88cm}|} \hline )" + sCR_LF;
        process_data += R"( &  &  &  &  & \\ )" + sCR_LF;
        process_data += R"(\multicolumn{4}{|l}{\huge{)" + MapInfo.Bez + R"(}} & \multicolumn{2}{r|}{\huge{)" + MapInfo.Nr + R"(}} \\ )" + sCR_LF;
        process_data += R"(\multicolumn{6}{|l|}{)" + Familien + R"(} \\ )" + sCR_LF;
        process_data += R"( &  &  &  &  & \\ \hline\hline )" + sCR_LF;
        process_data += R"(\multicolumn{2}{|l}{{\bf\footnotesize Nichtbesuche$^\ast$ Anschrift}} & {\bf\footnotesize Name} & {\bf\footnotesize Datum} & \multicolumn{2}{|l|}{{\bf\footnotesize Hinweise}} \\ \hline )" + sCR_LF;
    }

    //Liste mit Nichtbesuche
    int i=0;
    for (std::vector<sNoVisits>::iterator it = NoVisits.begin(); it != NoVisits.end(); ++it)
    {
        if (m_DSGVO)
        {
            if (i == 0) //erste Zeile mit Gebietsstraßen
                process_data += R"(\multicolumn{2}{|l}{\footnotesize{)" + it->Adresse + R"(}} & \footnotesize{)" + it->Datum + R"(} & \multicolumn{2}{|l|}{\multirow{11}{4.1cm}{\footnotesize{)" + Strassen + R"(}}} \\ )" + sCR_LF;
            else
                process_data += R"(\multicolumn{2}{|l}{\footnotesize{)" + it->Adresse + R"(}} & \footnotesize{)" + it->Datum + R"(} & \multicolumn{2}{|l|}{} \\ )" + sCR_LF;
            i++;
        }
        else
        {        
            if (i == 0) //erste Zeile mit Gebietsstraßen
                process_data += R"(\multicolumn{2}{|l}{\footnotesize{)" + it->Adresse + R"(}} & \footnotesize{)" + it->Name + R"(} & \footnotesize{)" + it->Datum + R"(} & \multicolumn{2}{|l|}{\multirow{11}{4.1cm}{\footnotesize{)" + Strassen + R"(}}} \\ )" + sCR_LF;
            else
                process_data += R"(\multicolumn{2}{|l}{\footnotesize{)" + it->Adresse + R"(}} & \footnotesize{)" + it->Name + R"(} & \footnotesize{)" + it->Datum + R"(} & \multicolumn{2}{|l|}{} \\ )" + sCR_LF;
            i++;
        }
    }

    //Restlichen Platz mit leeren Zeilen auffüllen
    
    if (m_DSGVO)
    {
        for (; i<=8; i++)
            if (i == 0) //erste Zeile mit Gebietsstraßen
                process_data += R"(\multicolumn{2}{|l}{} & & \multicolumn{2}{|l|}{\multirow{11}{4.1cm}{\footnotesize{)" + Strassen + R"(}}} \\ )" + sCR_LF;
            else
                process_data += R"(\multicolumn{2}{|l}{} & & \multicolumn{2}{|l|}{} \\ )" + sCR_LF;

        process_data += R"(\multicolumn{2}{|l}{} & & \multicolumn{2}{|l|}{} \\ \hline\hline )" + sCR_LF;
        process_data += R"(\multicolumn{5}{|l|}{Bearbeitungsstand:} \\ )" + sCR_LF;
        process_data += MapInfo.Zurueck + R"( & \multicolumn{4}{l|}{)" + MapInfo.Kommentar + R"(} \\ )" + sCR_LF;
        process_data += R"( &  &  &  & \\ )" + sCR_LF;
        process_data += R"( &  &  &  & \\ )" + sCR_LF;
        process_data += R"( &  &  &  & \\ )" + sCR_LF;
        process_data += R"(\multicolumn{5}{|L{13.3cm}|}{\tiny{Leg bitte nach jeder Bearbeitung, spätestens 4 Monate nach der letzten Bearbeitung, die Gebietskarte dem Gebietsdiener vor.\newline $^\ast$Wenn eine Person ausdrücklich erklärt, nicht mehr von Jehovas Zeugen besucht werden zu wollen, muss Anschrift {\bf (ohne Namen)} und Datum hier notiert werden.}} \\ \hline)" + sCR_LF; // (Brief vom 13. Mai 2019)
    }
    else
    {
        for (; i<=8; i++)
            if (i == 0) //erste Zeile mit Gebietsstraßen
                process_data += R"(\multicolumn{2}{|l}{} & & & \multicolumn{2}{|l|}{\multirow{11}{4.1cm}{\footnotesize{)" + Strassen + R"(}}} \\ )" + sCR_LF;
            else
                process_data += R"(\multicolumn{2}{|l}{} & & & \multicolumn{2}{|l|}{} \\ )" + sCR_LF;

        process_data += R"(\multicolumn{2}{|l}{} & & & \multicolumn{2}{|l|}{} \\ \hline\hline )" + sCR_LF;
        process_data += R"(\multicolumn{6}{|l|}{Bearbeitungsstand:} \\ )" + sCR_LF;
        process_data += MapInfo.Zurueck + R"( & \multicolumn{5}{l|}{)" + MapInfo.Kommentar + R"(} \\ )" + sCR_LF;
        process_data += R"( &  &  &  &  & \\ )" + sCR_LF;
        process_data += R"( &  &  &  &  & \\ )" + sCR_LF;
        process_data += R"( &  &  &  &  & \\ )" + sCR_LF;
        process_data += R"(\multicolumn{6}{|L{13.3cm}|}{\tiny{Leg bitte nach jeder Bearbeitung, spätestens 4 Monate nach der letzten Bearbeitung, die Gebietskarte dem Gebietsdiener vor.\newline $^\ast$Wenn eine Person ausdrücklich erklärt, nicht mehr von Jehovas Zeugen besucht werden zu wollen, muss ihr Name, Anschrift und Datum hier notiert werden. Die Person muss aus Datenschutzgründen damit einverstanden sein (km 1/94 Fragekasten).}} \\ \hline)" + sCR_LF;
    }
    process_data += R"(\end{supertabular} )" + sCR_LF;
}

void C_ReportMapInlet::start_process(void)
{
    if (!check_file_present(process_data_file))
        return;

    std::string executable = settings->m_latex.bin_path + "/pdflatex.exe";
    process_file = ad->work_dir + "/report/report_tmpl3.tex";
    output_file  = ad->work_dir + "/report/report_tmpl3.pdf";
    report_file  = ad->work_dir + "/report/Inlet_" + MapInfo.Nr + "_" + build_timestamp() + ".pdf";


    std::vector<std::string> args;
    args.push_back(executable);
    args.push_back("-output-directory=report");
    args.push_back(process_file);
    exec_cmd(&args);

    rename_output_file_to_report_file();
}

void C_ReportMapInlet::cleanup(void)
{
    std::vector<std::string> files_to_delete;

    if (settings->m_latex.del_latex_aux_files)
    {
        files_to_delete.push_back(ad->work_dir + "/report/report_tmpl3.aux");
        files_to_delete.push_back(ad->work_dir + "/report/report_tmpl3.log");
        files_to_delete.push_back(output_file);
    }

    if (settings->m_latex.del_latex_data_tex)
        files_to_delete.push_back(ad->work_dir + "/report/data.tex");

    if (files_to_delete.size() > 0)
        cleanup_processing_files(&files_to_delete);
}

void C_ReportMapInlet::open_result(void)
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
