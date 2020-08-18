/****************************************************************************
 * Copyright (C) 2019 by Mark Buttig                                        *
 *                                                                          *
 * This file is part of tMGR.                                               *
 *                                                                          *
 *   tMGR is free software: you can redistribute it and/or modify it        *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   tMGR is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with tMGR.  If not, see <http://www.gnu.org/licenses/>.  *
 ****************************************************************************/

/**
 * @file C_ReportAssignementDuration.cpp
 * @author Mark Buttig
 * @date 11.01.2019
 * @brief Creates report of assignment duration
 */

#include "C_ReportAssignementDuration.h"

C_ReportAssignementDuration::C_ReportAssignementDuration(
    const ApplicationData *ad,
    const C_Settings *s
)
: C_DbHandle(&ad->db_file), C_Report(ad, s)
{
    //ctor
}

C_ReportAssignementDuration::~C_ReportAssignementDuration()
{
    //dtor
}

void C_ReportAssignementDuration::rollout(void)
{
    query_Data();
    filter_Data();
    create_process_data();
    create_process_data_file(ad->work_dir + "/report/data.tex");
    start_process();
    cleanup();
    open_result();
}

std::tuple<int, int, int> C_ReportAssignementDuration::get_stat(void)
{
    query_Data();
    filter_Data();

    int cat_0=0, cat_1=0, cat_2=0;

    for (auto const &el : DurationData)
    {
        int i = days_passed(el.Anfang_Date);
        if (i>1460)
        {
            cat_0++;
        }
        else if (i>1095)
        {
            cat_1++;
        }
        else if (i>730)
        {
            cat_2++;
        }
    }

    return std::make_tuple(cat_0, cat_1, cat_2);
}

void C_ReportAssignementDuration::query_Data()
{
    int rc;
    DataSet.clear();

    rc = open_db();

    // Use new territory numbering
    std::string NbField = "tGebiet.Nr";
    if (settings->m_general.m_use_new_territory_numbers_in_maps)
    {
        NbField = "tGebiet.NNr";
    }

    std::string query = "";
    query += "SELECT GId_in_work, NNr, Bez, tAktion.Name, Ausgabe, Zurueck ";
    query += "FROM tAktion, ";
    query += " ( ";
    query += "    SELECT tGebiet.Id AS GId_in_work, " + NbField +
             ", Bez, Name, Ausgabe as 'last upd' ";
    query += "    FROM tAktion ";
    query += "    INNER JOIN tGebiet ON tGebiet.Id = tAktion.GebietId ";
    query += "    WHERE tAktion.Zurueck IS NULL OR tAktion.Zurueck = '' ";
    query += "    ORDER BY tGebiet.Id ASC ";
    query += ") AS t1 ";
    query += "WHERE GId_in_work = tAktion.GebietId ";
    query += "ORDER BY NNr, Ausgabe DESC";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();

        if (rc == SQLITE_ROW)
        {
            sDataSet tmp;
            tmp.Id           = get_int(COL_0);
            tmp.Nr           = get_text(COL_1);
            tmp.Bez          = get_text(COL_2);
            tmp.Name         = get_text(COL_3);
            tmp.Ausgabe_Date = get_text(COL_4);
            tmp.Zurueck_Date = get_text(COL_5);
            DataSet.push_back(tmp);
        }

        if (done_or_error(rc))
        {
            break;
        }
    }

    rc = close_db();
}

void C_ReportAssignementDuration::filter_Data(void)
{
    DurationData.clear();
    std::string ge = "", na = "", sd = "", be = "", chdte = "";
    int id = 0;
    bool unbound = false;
    bool family  = false;

    for (auto const &el : DataSet)
    {
        if (ge != el.Nr)
        {
            if (ge != "") //not the first one of DataSet
            {
                sDurationData tmp;
                tmp.Id          = id;
                tmp.Nr          = ge;
                tmp.Bez         = be;
                tmp.Name        = na;
                tmp.Anfang_Date = sd + chdte;
                DurationData.push_back(tmp);
            }

            id = el.Id;
            ge = el.Nr;
            be = el.Bez;
            na = el.Name;
            sd = el.Ausgabe_Date;
            unbound = false;
            family  = false;
            chdte   = "";
        }
        else
        {
            if (na == el.Name || is_family(&na, &el.Name))
            {
                if (is_family(&na, &el.Name) && !family && !unbound)
                {
                    na += " (davor: " + el.Name + ")";
                    chdte = " (übergabe: " + sd + ")";
                    family = true;
                }

                if (unbound == false)
                {
                    sd = el.Ausgabe_Date;
                }
            }
            else
            {
                unbound = true;
            }

        }

    }

}

bool C_ReportAssignementDuration::is_family(const std::string *a, const std::string *b)
{
    if (a->compare(*b) == 0)
    {
        return false;
    }

    bool rc = false;
    size_t a_pos = a->find(',');
    std::string a_fam = a->substr(0, a_pos);

    size_t b_pos = b->find(',');
    std::string b_fam = b->substr(0, b_pos);

    if (a_fam == b_fam)
    {
        rc = true;
    }

    return rc;
}

void C_ReportAssignementDuration::create_process_data(void)
{
    std::sort(DurationData.begin(), DurationData.end());

    process_data = "";

    process_data += R"(\section{Gebietszuteilungen (stand \today)} )" + sCR_LF;

    //Build table head
    process_data += R"(\tablehead{\hline)" + sCR_LF;
    process_data += R"(  \rowcolor{blaud} \multicolumn{4}{|l|}{{\color{red}$\blacksquare$} Über 3 Jahre zugeteilt} \\)" + sCR_LF;
    process_data += R"(  \rowcolor{blaud} \multicolumn{4}{|l|}{{\color{orange}$\blacksquare$} Länger als 2 Jahre zugeteilt} \\)" + sCR_LF;
    process_data += R"(  \rowcolor{blaud} \multicolumn{4}{|l|}{{\color{yellow}$\blacksquare$} Länger als 1 Jahr zugeteilt} \\ \shrinkheight{20pt})" + sCR_LF;
    process_data += R"(  \rowcolor{blaud} \multicolumn{4}{|l|}{{\color{white}$\blacksquare$} Bis zu 1 Jahr zugeteilt} \\ \hline\hline)" + sCR_LF;
    process_data += R"(  \rowcolor{blaud} Nr. & Bezeichnung & Name & Zugeteilt seit \\ \hline\hline)" + sCR_LF;
    process_data += R"(})" + sCR_LF;

    process_data += R"(\tabletail{\hline \multicolumn{4}{|r|}{\tiny{\emph{Weiter auf der nächsten Seite ...}}} \\ \hline} )" + sCR_LF;
    process_data += R"(\tablelasttail{\hline} )" + sCR_LF;

    process_data += R"(\begin{supertabular}{|l|l|l|l|} \hline )" + sCR_LF;

    //Iteriere durch Zuteilungen    //Iteriere durch Anzahl DataSet
    for (auto const &it : DurationData)
    {
        int i = days_passed(it.Anfang_Date);
        if (i>1095 /*1460 4 Jahre */)
        {
            process_data += R"(\rowcolor{red})";
        }
        else if (i>730 /*1095 3 Jahre*/)
        {
            process_data += R"(\rowcolor{orange})";
        }
        else if (i>365 /*730* 2 Jahre*/)
        {
            process_data += R"(\rowcolor{yellow})";
        }

        process_data += it.Nr + R"( & )" + it.Bez + R"( & )" + it.Name + R"( & )" + it.Anfang_Date + R"( \\ \hline )" + sCR_LF;
    }

    process_data += R"(\end{supertabular})" + sCR_LF;
}

void C_ReportAssignementDuration::start_process(void)
{
    if (not check_file_present(process_data_file))
        return;

    std::string executable = settings->m_latex.bin_path + "/pdflatex.exe";
    process_file = ad->work_dir + "/report/report_tmpl2.tex";
    output_file  = ad->work_dir + "/report/report_tmpl2.pdf";
    report_file  = ad->work_dir + "/report/Zuteilungsdauer_" + build_timestamp() + ".pdf";

    std::vector<std::string> args;
    args.push_back(executable);
    args.push_back("-output-directory=report");
    args.push_back(process_file);
    exec_cmd(&args);

    rename_output_file_to_report_file();
}

void C_ReportAssignementDuration::cleanup(void)
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

void C_ReportAssignementDuration::open_result(void)
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
