#include "C_ReportNoVisits.h"

C_ReportNoVisits::C_ReportNoVisits(const ApplicationData *ad, const C_Settings *s)
: C_DbHandle(&ad->db_file), C_Report(ad, s)
{
    //ctor
    init_Choices();
    m_DSGVO = DSGVO;
}

C_ReportNoVisits::~C_ReportNoVisits()
{
    //dtor
}

std::vector<std::pair<int, std::string>> *C_ReportNoVisits::get_sort_choices(void)
{
    return &Choices;
}

void C_ReportNoVisits::set_sort_choice(int Sortierung)
{
    //Iteriere durch Choices
    for(auto el : Choices)
        if (el.first == Sortierung)
        {
            this->Sortierung = el;
            break;
        }
}

void C_ReportNoVisits::rollout(void)
{
    query_Nichtbesuche();
    create_process_data();
    create_process_data_file(ad->work_dir + "/report/data.tex");
    start_process();
    cleanup();
    open_result();
}

void C_ReportNoVisits::init_Choices(void)
{
    Choices.push_back(std::make_pair(0, "sortiert nach Datum"));
    Choices.push_back(std::make_pair(1, "sortiert nach Gebiet"));
}

void C_ReportNoVisits::query_Nichtbesuche(void)
{
    int rc;
    Nichtbesuche.clear();

    // Use new territory numbering
    std::string NbField = "tGebiet.Nr";
    if (settings->m_general.m_use_new_territory_numbers_in_maps)
        NbField = "tGebiet.NNr";

    rc = open_db();

    std::string query = "";

    switch (Sortierung.first)
    {
    case 0: //sortiert nach Datum
        query += "SELECT tNichtbesuche.Id, " + NbField + ", tGebiet.Bez, Adresse, Name, strftime('%d.%m.%Y', Datum), Kommentar ";
        query += "FROM tNichtbesuche ";
        query += "INNER JOIN tGebiet ON tGebiet.Id = tNichtbesuche.GebietId ";
        query += "ORDER BY Datum ASC, " + NbField + " ASC";
        break;
    case 1: //sortiert nach Gebiet
        query += "SELECT tNichtbesuche.Id, " + NbField + ", tGebiet.Bez, Adresse, Name, strftime('%d.%m.%Y', Datum), Kommentar ";
        query += "FROM tNichtbesuche ";
        query += "INNER JOIN tGebiet ON tGebiet.Id = tNichtbesuche.GebietId ";
        query += "ORDER BY " + NbField + " ASC";
        break;
    }

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            sNoVisits tmp;
            tmp.Id         = get_int(COL_0);
            tmp.GebNr      = get_text(COL_1);
            tmp.GebBez     = get_text(COL_2);
            tmp.Adresse    = get_text(COL_3);
            tmp.Name       = get_text(COL_4);
            tmp.Datum      = get_text(COL_5);
            tmp.Kommentar  = get_text(COL_6);
            Nichtbesuche.push_back(tmp);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_ReportNoVisits::create_process_data(void)
{
    process_data = "";

    //Build table head
    process_data += R"(\section{Nichtbesuche )" + Sortierung.second + R"( (stand \today)} )" + sCR_LF;
    process_data += R"(\begin{footnotesize} )" + sCR_LF;
    
    if (m_DSGVO)
    {
        process_data += R"(\tablehead{\hline \rowcolor{blaud} Nr. & Bezeichnung & Adresse & Datum & Kommentar \\ \hline\hline} )" + sCR_LF;
        process_data += R"(\tabletail{\hline \multicolumn{5}{|r|}{\tiny{\emph{Weiter auf der naechsten Seite ...}}} \\ \hline} )" + sCR_LF;
    }
    else
    {
        process_data += R"(\tablehead{\hline \rowcolor{blaud} Nr. & Bezeichnung & Adresse & Name & Datum & Kommentar \\ \hline\hline} )" + sCR_LF;
        process_data += R"(\tabletail{\hline \multicolumn{6}{|r|}{\tiny{\emph{Weiter auf der naechsten Seite ...}}} \\ \hline} )" + sCR_LF;
    }

    process_data += R"(\tablelasttail{\hline} )" + sCR_LF;
    
    if (m_DSGVO)
        process_data += R"(\begin{supertabular}{|r|l|P{4cm}|l|P{4cm}|} \hline )" + sCR_LF;
    else
        process_data += R"(\begin{supertabular}{|r|l|P{4cm}|l|l|P{4cm}|} \hline )" + sCR_LF;

    //Iteriere durch Nichtbesuche
    for(std::vector<sNoVisits>::iterator it = Nichtbesuche.begin(); it != Nichtbesuche.end(); ++it)
    {
        if (m_DSGVO)
            process_data += it->GebNr + R"( & )" + it->GebBez + R"( & )" + it->Adresse + R"( & )" + it->Datum + R"( & )" + it->Kommentar + R"( \\ \hline )" + sCR_LF;
        else
            process_data += it->GebNr + R"( & )" + it->GebBez + R"( & )" + it->Adresse + R"( & )" + it->Name + R"( & )" + it->Datum + R"( & )" + it->Kommentar + R"( \\ \hline )" + sCR_LF;
    }

    process_data += R"(\end{supertabular} )" + sCR_LF;
    process_data += R"(\end{footnotesize} )" + sCR_LF;
}

void C_ReportNoVisits::start_process(void)
{
    if (!check_file_present(process_data_file))
        return;

    std::string executable = settings->m_latex.bin_path + "/pdflatex.exe";
    process_file = ad->work_dir + "/report/report_tmpl2.tex";
    output_file  = ad->work_dir + "/report/report_tmpl2.pdf";
    report_file  = ad->work_dir + "/report/Nichtbesuche_" + build_timestamp() + ".pdf";

    std::vector<std::string> args;
    args.push_back(executable);
    args.push_back("-output-directory=report");
    args.push_back(process_file);
    exec_cmd(&args);

    rename_output_file_to_report_file();
}

void C_ReportNoVisits::cleanup(void)
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

void C_ReportNoVisits::open_result(void)
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
