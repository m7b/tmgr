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
 * @file C_OsmDownloader.cpp
 * @author Mark Buttig
 * @date 11.01.2019
 * @brief OSM downloader
 */

#include "C_OsmDownloader.h"

C_OsmDownloader::C_OsmDownloader(const ApplicationData *ad, const C_Settings *s)
: C_Report(ad, s)
{
    process_data_file = this->ad->work_dir + "\\maperitive\\dl_job.mscript";
}

C_OsmDownloader::~C_OsmDownloader()
{
    //dtor
}

void C_OsmDownloader::start(std::string *new_osm_file)
{
    *new_osm_file = "territory_" + build_timestamp() + ".osm";

    //create processdata
    process_data += "use-ruleset alias=default" + sCR_LF;
    process_data += "download-osm-overpass bounds=";
    process_data += std::to_string(settings->m_general.m_min_longitude) + ",";
    process_data += std::to_string(settings->m_general.m_min_latitude) + ",";
    process_data += std::to_string(settings->m_general.m_max_longitude) + ",";
    process_data += std::to_string(settings->m_general.m_max_latitude) + " ";
    process_data += R"(service-url=")" + settings->m_maperitive.m_osm_xapi_url + R"(")" + sCR_LF;
    process_data += "save-source " + ad->work_dir + "\\maperitive\\" + *new_osm_file + sCR_LF;

    //create processdata file
    create_file(process_data_file, process_data);
    if (!check_file_present(process_data_file))
    {
        return;
    }

    //start process
    std::string executable = settings->m_maperitive.con_exe;
    std::vector<std::string> args;
    args.push_back(executable);
    args.push_back(process_data_file);
    exec_cmd(&args);

    //cleanup
    std::vector<std::string> files_to_delete;
    if (settings->m_maperitive.m_del_tmp_files)
    {
        files_to_delete.push_back(process_data_file);
    }
    if (files_to_delete.size() > 0)
    {
        cleanup_processing_files(&files_to_delete);
    }
}
