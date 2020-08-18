#include "C_ReportNotAssigned.h"

C_ReportNotAssigned::C_ReportNotAssigned(const ApplicationData *ad, const C_Settings *s)
: C_DbHandle(&ad->db_file), C_Report(ad, s)
{
    //ctor
    init_Choices();
}

C_ReportNotAssigned::~C_ReportNotAssigned()
{
    //dtor
}

std::vector<std::pair<int, std::string>> *C_ReportNotAssigned::get_sort_choices(void)
{
    return &Choices;
}

void C_ReportNotAssigned::set_sort_choice(int Sortierung)
{
    //Iteriere durch Choices
    for(auto el : Choices)
        if (el.first == Sortierung)
        {
            this->Sortierung = el;
            break;
        }
}

void C_ReportNotAssigned::rollout(void)
{
    query_Nichtzuteilungen();
    create_process_data();
    create_process_data_file(ad->work_dir + "/report/data.tex");
    start_process();
    cleanup();
    open_result();
}

void C_ReportNotAssigned::init_Choices(void)
{
    Choices.push_back(std::make_pair(0, "sortiert nach Gebietsnummer"));
    Choices.push_back(std::make_pair(1, "sortiert nach Gebietsbezeichnung"));
    Choices.push_back(std::make_pair(2, "sortiert nach letztes Bearbeitungsdatum"));
    Choices.push_back(std::make_pair(3, "für die Zuteilung"));
}

void C_ReportNotAssigned::query_Nichtzuteilungen(void)
{
    int rc;
    Nichtzuteilungen.clear();

    // Use new territory numbering
    std::string NbField = "tGebiet.Nr", t2NbField = "t2.GebietId";
    if (settings->m_general.m_use_new_territory_numbers_in_maps)
    {
        NbField   = "tGebiet.NNr";
        t2NbField = "tGebiet.NNr";
    }

    rc = open_db();

    std::string query = "";

    switch (Sortierung.first)
    {
    case 0: //Gebietsnummer
        query += "SELECT " + NbField + ", tGebiet.Bez, tGebiet.WEinh, t2.Name, strftime('%d.%m.%Y', t2.Ausgabe) AS Ausgabe, strftime('%d.%m.%Y', t2.Zurueck) AS Zurueck, t2.Kommentar ";
        query += "FROM (SELECT * FROM ( ";
        query += "SELECT Id, GebietId, Name, MAX(Ausgabe) as Ausgabe, Zurueck, Kommentar FROM tAktion GROUP BY GebietId ";
        query += ") WHERE Zurueck IS NOT NULL AND Zurueck <> '') AS t2 ";
        query += "INNER JOIN tGebiet ON tGebiet.Id = t2.GebietId ";
        query += "ORDER BY " + t2NbField + " ASC ";
        break;
    case 1: //Gebietsbezeichnung
        query += "SELECT " + NbField + ", tGebiet.Bez, tGebiet.WEinh, t2.Name, strftime('%d.%m.%Y', t2.Ausgabe) AS Ausgabe, strftime('%d.%m.%Y', t2.Zurueck) AS Zurueck, t2.Kommentar ";
        query += "FROM (SELECT * FROM ( ";
        query += "SELECT Id, GebietId, Name, MAX(Ausgabe) as Ausgabe, Zurueck, Kommentar FROM tAktion GROUP BY GebietId ";
        query += ") WHERE Zurueck IS NOT NULL AND Zurueck <> '') AS t2 ";
        query += "INNER JOIN tGebiet ON tGebiet.Id = t2.GebietId ";
        query += "ORDER BY tGebiet.Bez ASC, t2.Zurueck ASC";
        break;
    case 2: //letztes Bearbeitungsdatum
    case 3: //letztes Bearbeitungsdatum zur Zuteilung
        query += "SELECT " + NbField + ", tGebiet.Bez, tGebiet.WEinh, t2.Name, strftime('%d.%m.%Y', t2.Ausgabe) AS Ausgabe, strftime('%d.%m.%Y', t2.Zurueck) AS Zurueck, t2.Kommentar ";
        query += "FROM (SELECT * FROM ( ";
        query += "SELECT Id, GebietId, Name, MAX(Ausgabe) as Ausgabe, Zurueck, Kommentar FROM tAktion GROUP BY GebietId ";
        query += ") WHERE Zurueck IS NOT NULL AND Zurueck <> '') AS t2 ";
        query += "INNER JOIN tGebiet ON tGebiet.Id = t2.GebietId ";
        query += "ORDER BY t2.Zurueck ASC";
        break;
    }

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            sNotAssigned tmp;
            tmp.GebNr      = get_text(COL_0);
            tmp.GebBez     = get_text(COL_1);
            tmp.WEinh      = get_int(COL_2);
            tmp.Name       = get_text(COL_3);
            tmp.AusgDat    = get_text(COL_4);
            tmp.ZurueckDat = get_text(COL_5);
            tmp.Kommentar  = get_text(COL_6);
            Nichtzuteilungen.push_back(tmp);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportNotAssigned::create_process_data(void)
{
    process_data = "";
    
    switch (Sortierung.first)
    {
    case 0: //Gebietsnummer
    case 1: //Gebietsbezeichnung
    case 2: //letztes Bearbeitungsdatum
    
        //Build table head
        process_data += R"(\section{Nicht zugeteilte Gebiete )" + Sortierung.second + R"( (stand \today)} )" + sCR_LF;
        process_data += R"(\tablehead{\hline \rowcolor{blaud} Nr. & Bezeichnung & bearbeitet von & Zeitraum & Kommentar \\ \hline\hline} )" + sCR_LF;
        process_data += R"(\tabletail{\hline \multicolumn{5}{|r|}{\tiny{\emph{Weiter auf der naechsten Seite ...}}} \\ \hline} )" + sCR_LF;
        process_data += R"(\tablelasttail{\hline} )" + sCR_LF;
        process_data += R"(\begin{supertabular}{|l|l|l|l|P{4cm}|} \hline)" + sCR_LF;

        //Iteriere durch Nichtzuteilungen
        for(std::vector<sNotAssigned>::iterator it = Nichtzuteilungen.begin(); it != Nichtzuteilungen.end(); ++it)
            process_data += it->GebNr + R"( & )" + it->GebBez + R"( & )" + it->Name + R"( & )" + it->AusgDat + " - " + it->ZurueckDat + R"( & )" + it->Kommentar + R"( \\ \hline )" + sCR_LF;

        process_data += R"(\end{supertabular})" + sCR_LF;
        break;
        
    case 3: //letztes Bearbeitungsdatum zur Zuteilung
    
        //Build table head
        process_data += R"(\section{Nicht zugeteilte Gebiete )" + Sortierung.second + R"( (stand \today)} )" + sCR_LF;
        process_data += R"(\renewcommand{\arraystretch}{1.4} )" + sCR_LF;
        process_data += R"(\tablehead{\hline \rowcolor{blaud} Nr. & Bezeichnung & Fam. & zuletzt & Kommentar & zugeteilt an & wann \\ \hline\hline} )" + sCR_LF;
        process_data += R"(\tabletail{\hline \multicolumn{7}{|r|}{\tiny{\emph{Weiter auf der naechsten Seite ...}}} \\ \hline} )" + sCR_LF;
        process_data += R"(\tablelasttail{\hline} )" + sCR_LF;
        process_data += R"(\begin{supertabular}{|l|l|l|l|P{3cm}|P{3.5cm}|P{2cm}|} \hline)" + sCR_LF;

        //Iteriere durch Nichtzuteilungen
        std::string anzahl_familien;
        for(std::vector<sNotAssigned>::iterator it = Nichtzuteilungen.begin(); it != Nichtzuteilungen.end(); ++it)
        {
            anzahl_familien = (it->WEinh ? std::to_string(it->WEinh) : "-");
            process_data += it->GebNr + R"( & )" + it->GebBez + R"( & )" + anzahl_familien + R"( & )" + it->ZurueckDat + R"( & )" + it->Kommentar + R"( & & \\ \hline )" + sCR_LF;
        }

        process_data += R"(\end{supertabular})" + sCR_LF;
        process_data += R"(\renewcommand{\arraystretch}{1.0} )" + sCR_LF;
        break;
    }

}

void C_ReportNotAssigned::start_process(void)
{
    if (!check_file_present(process_data_file))
        return;

    std::string executable = settings->m_latex.bin_path + "/pdflatex.exe";
    process_file = ad->work_dir + "/report/report_tmpl2.tex";
    output_file  = ad->work_dir + "/report/report_tmpl2.pdf";
    report_file  = ad->work_dir + "/report/Nicht_zugeteilt_" + build_timestamp() + ".pdf";

    std::vector<std::string> args;
    args.push_back(executable);
    args.push_back("-output-directory=report");
    args.push_back(process_file);
    exec_cmd(&args);

    rename_output_file_to_report_file();
}

void C_ReportNotAssigned::cleanup(void)
{
    std::vector<std::string> files_to_delete;

    if (settings->m_latex.del_latex_aux_files)
    {
        files_to_delete.push_back(ad->work_dir + "/report/report_tmpl2.aux");
        files_to_delete.push_back(ad->work_dir + "/report/report_tmpl2.log");
        files_to_delete.push_back(output_file);
    }

    if (settings->m_latex.del_latex_data_tex)
        files_to_delete.push_back(ad->work_dir + "/report/data.tex");

    if (files_to_delete.size() > 0)
        cleanup_processing_files(&files_to_delete);
}

void C_ReportNotAssigned::open_result(void)
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
