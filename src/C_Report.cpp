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
 * @file C_Report.cpp
 * @author Mark Buttig
 * @date 11.01.2019
 * @brief Base class for reports
 */

#include "C_Report.h"

C_Report::C_Report(const ApplicationData *ad, const C_Settings *s)
: ad(ad), settings(s)
{
    //ctor
}

C_Report::~C_Report()
{
    //dtor
}

void C_Report::create_file(std::string &file, std::string &content)
{
    std::fstream f;
    f.open(file, std::ios::out|std::ios::trunc);
    if (f.is_open())
    {
        f << content;
    }

}

void C_Report::exec_cmd(std::vector<std::string> *args)
{
    namespace bp = boost::process;

    write_to_console("=====> " + deform_execution(args) + "\n");

    bp::ipstream is;
    bp::child c(deform_execution(args),
        bp::windows::hide,
        (bp::std_out & bp::std_err) > is);

    while (c.running())
    {
        if (callback)
        {
            std::string line;
            std::getline(is, line);
            write_to_console(line);
        }
    }

    c.wait();
    write_to_console("=====> Process Finished <=====\n");
}

void C_Report::exec_cmd(std::vector<std::string> *args, exec_mode em)
{
    namespace bp = boost::process;

    switch (em)
    {
    case BLOCKING:
        exec_cmd(args);
        break;

    case DETACHED:
        bp::spawn(deform_execution(args));
        break;
    }
}


void C_Report::cleanup_processing_files(std::vector<std::string> *files_to_delete)
{
    for (std::vector<std::string>::iterator it = files_to_delete->begin();
         it != files_to_delete->end(); ++it)
    {
        if (check_file_present(*it))
        {
            std::remove(it->c_str());
        }
    }
}


std::string C_Report::deform_execution(std::vector<std::string> *args)
{
    /// Transform arguments to execution command
    std::string execution_cmd = "";
    for (auto it : *args)
    {
        execution_cmd += it + " ";
    }

    return execution_cmd;
}

void C_Report::create_process_data_file(std::string pdf)
{
    process_data_file = pdf;
    create_file(process_data_file, process_data);
}

void C_Report::rename_output_file_to_report_file(void)
{
    std::rename(output_file.c_str(), report_file.c_str());
}

void C_Report::write_to_console(std::string line)
{
    if (callback)
    {
        callback(line + "\n");
    }
}
