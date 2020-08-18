#include "C_ReportAssignements.h"

C_ReportAssignements::C_ReportAssignements(const ApplicationData *ad, const C_Settings *s)
: C_DbHandle(&ad->db_file), C_Report(ad, s)
{
    //ctor
    init_Choices();
}

C_ReportAssignements::~C_ReportAssignements()
{
    //dtor
}

std::vector<std::pair<int, std::string>> *C_ReportAssignements::get_sort_choices(void)
{
    return &Choices;
}

void C_ReportAssignements::set_sort_choice(int Sortierung)
{
    //Iteriere durch Choices
    for(auto el : Choices)
        if (el.first == Sortierung)
        {
            this->Sortierung = el;
            break;
        }
}

void C_ReportAssignements::rollout(void)
{
    query_Zuteilungen();
    create_process_data();
    create_process_data_file(ad->work_dir + "\\report\\data.tex");
    start_process();
    cleanup();
    open_result();
}

void C_ReportAssignements::init_Choices(void)
{
    Choices.push_back(std::make_pair(0, "sortiert nach Verkündiger"));
    Choices.push_back(std::make_pair(1, "sortiert nach Gebiet"));
    Choices.push_back(std::make_pair(2, "sortiert nach Ausgabedatum"));
    Choices.push_back(std::make_pair(3, "zur Nachfrage"));
}

void C_ReportAssignements::query_Zuteilungen(void)
{
    int rc;
    Zuteilungen.clear();

    // Use new territory numbering
    std::string NbField = "tGebiet.Nr";
    if (settings->m_general.m_use_new_territory_numbers_in_maps)
        NbField = "tGebiet.NNr";

    rc = open_db();

    std::string query = "";

    switch (Sortierung.first)
    {
    case 0: //Verkündiger
        query += "SELECT Name, " + NbField + ", tGebiet.Bez, strftime('%d.%m.%Y', Ausgabe) as slx, Ausgabe ";
        query += "FROM tAktion ";
        query += "INNER JOIN tGebiet ON tGebiet.Id = tAktion.GebietId ";
        query += "WHERE tAktion.Zurueck IS NULL OR tAktion.Zurueck = '' ";
        query += "ORDER BY Name ASC, Ausgabe ASC";
        break;
    case 1: //Gebiet
        query += "SELECT Name, " + NbField + ", tGebiet.Bez, strftime('%d.%m.%Y', Ausgabe) as slx, Ausgabe ";
        query += "FROM tAktion ";
        query += "INNER JOIN tGebiet ON tGebiet.Id = tAktion.GebietId ";
        query += "WHERE tAktion.Zurueck IS NULL OR tAktion.Zurueck = '' ";
        query += "ORDER BY tGebiet.Bez ASC, " + NbField + " ASC, Ausgabe ASC";
        break;
    case 2: //Ausgabedatum
    case 3: //Ausgabedatum zur Nachfrage
        query += "SELECT Name, " + NbField + ", tGebiet.Bez, strftime('%d.%m.%Y', Ausgabe) as slx, Ausgabe ";
        query += "FROM tAktion ";
        query += "INNER JOIN tGebiet ON tGebiet.Id = tAktion.GebietId ";
        query += "WHERE tAktion.Zurueck IS NULL OR tAktion.Zurueck = '' ";
        query += "ORDER BY Ausgabe ASC";
        break;
    }

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            sAssignements tmp;
            tmp.Name    = get_text(COL_0);
            tmp.GebNr   = get_text(COL_1);
            tmp.GebBez  = get_text(COL_2);
            tmp.AusgDat = get_text(COL_3);
            Zuteilungen.push_back(tmp);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportAssignements::create_process_data(void)
{
    process_data = "";
    
    switch (Sortierung.first)
    {
    case 0: //Verkündiger
    case 1: //Gebiet
    case 2: //Ausgabedatum
        process_data += R"(\section{Gebietszuteilungen )" + Sortierung.second + R"( (stand \today)} )" + sCR_LF;
        //Build table head
        process_data += R"(\tablehead{\hline \rowcolor{blaud} Name & Nr. & Bezeichnung & zuletzt \\ \hline\hline} )" + sCR_LF;
        process_data += R"(\tabletail{\hline \multicolumn{4}{|r|}{\tiny{\emph{Weiter auf der nächsten Seite ...}}} \\ \hline} )" + sCR_LF;
        process_data += R"(\tablelasttail{\hline} )" + sCR_LF;
        process_data += R"(\begin{supertabular}{|l|l|l|l|} \hline )" + sCR_LF;
        //Iteriere durch Zuteilungen
        for(std::vector<sAssignements>::iterator it = Zuteilungen.begin(); it != Zuteilungen.end(); ++it)
        {
            process_data += it->Name + R"( & )" + it->GebNr + R"( & )" + it->GebBez + R"( & )" + it->AusgDat + R"( \\ \hline )" + sCR_LF;
        }
        process_data += R"(\end{supertabular})" + sCR_LF;
        break;
    
    case 3: //Ausgabedatum zur Nachfrage
        process_data += R"(\section{Gebietszuteilungen )" + Sortierung.second + R"( (stand \today)} )" + sCR_LF;
        //Build table head
        process_data += R"(\renewcommand{\arraystretch}{1.4} )" + sCR_LF;
        process_data += R"(\tablehead{\hline \rowcolor{blaud} Name & Nr. & Bezeichnung & zuletzt & nachgefragt am & bearbeitet (ja/nein) \\ \hline\hline} )" + sCR_LF;
        process_data += R"(\tabletail{\hline \multicolumn{6}{|r|}{\tiny{\emph{Weiter auf der nächsten Seite ...}}} \\ \hline} )" + sCR_LF;
        process_data += R"(\tablelasttail{\hline} )" + sCR_LF;
        process_data += R"(\begin{supertabular}{|l|l|l|l||l|l|} \hline )" + sCR_LF;
        //Iteriere durch Zuteilungen
        for(std::vector<sAssignements>::iterator it = Zuteilungen.begin(); it != Zuteilungen.end(); ++it)
        {
            process_data += it->Name + R"( & )" + it->GebNr + R"( & )" + it->GebBez + R"( & )" + it->AusgDat + R"( & & \\ \hline )" + sCR_LF;
        }
        process_data += R"(\end{supertabular})" + sCR_LF;
        process_data += R"(\renewcommand{\arraystretch}{1.0} )" + sCR_LF;
        break;
    }

}

void C_ReportAssignements::start_process(void)
{
    if (!check_file_present(process_data_file))
        return;

    std::string executable = settings->m_latex.bin_path + "\\pdflatex.exe";
    process_file = ad->work_dir + "/report/report_tmpl2.tex";
    output_file  = ad->work_dir + "/report/report_tmpl2.pdf";
    report_file  = ad->work_dir + "/report/Zuteilungen_" + build_timestamp() + ".pdf";

    std::vector<std::string> args;
    args.push_back(executable);
    args.push_back("-output-directory=report");
    args.push_back(process_file);
    exec_cmd(&args);

    rename_output_file_to_report_file();
}

void C_ReportAssignements::cleanup(void)
{
    std::vector<std::string> files_to_delete;

    if (settings->m_latex.del_latex_aux_files)
    {
        files_to_delete.push_back(ad->work_dir + "\\report\\report_tmpl2.aux");
        files_to_delete.push_back(ad->work_dir + "\\report\\report_tmpl2.log");
        files_to_delete.push_back(output_file);
    }

    if (settings->m_latex.del_latex_data_tex)
        files_to_delete.push_back(ad->work_dir + "\\report\\data.tex");

    if (files_to_delete.size() > 0)
        cleanup_processing_files(&files_to_delete);
}

void C_ReportAssignements::open_result(void)
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
