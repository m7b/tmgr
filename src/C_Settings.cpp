#include "C_Settings.h"

C_Settings::C_Settings()
{
    //ctor
}

C_Settings::~C_Settings()
{
    //dtor
}

// Loads C_Settings structure from the specified XML file
void C_Settings::load(const std::string &filename)
{
    // Create an empty property tree object
    using boost::property_tree::ptree;
    ptree pt;

    // Load the XML file into the property tree. If reading fails
    // (cannot open file, parse error), an exception is thrown.
    try
    {
        read_xml(filename, pt);
    }
    catch (...)
    {
        //Fehler: Einstellungen laden
    }

    m_appear.font_size       = pt.get<int>("Settings.Appearance.font_size",      9);
    m_appear.m_square_size_x = pt.get<int>("Settings.Appearance.square_size_x", 40);
    m_appear.m_square_size_y = pt.get<int>("Settings.Appearance.square_size_y", 40);
    m_appear.m_sash_size     = pt.get<int>("Settings.Appearance.sash_size",     50);

    /*******************/
    m_appear.assigned.days_1     = pt.get<int>("Settings.Appearance.assigned.day_1",       90);
    m_appear.assigned.colour_1.r = pt.get<int>("Settings.Appearance.assigned.colour_1.r", 124);
    m_appear.assigned.colour_1.g = pt.get<int>("Settings.Appearance.assigned.colour_1.g", 245);
    m_appear.assigned.colour_1.b = pt.get<int>("Settings.Appearance.assigned.colour_1.b",   0);
    m_appear.assigned.days_2     = pt.get<int>("Settings.Appearance.assigned.day_2",      180);
    m_appear.assigned.colour_2.r = pt.get<int>("Settings.Appearance.assigned.colour_2.r", 210);
    m_appear.assigned.colour_2.g = pt.get<int>("Settings.Appearance.assigned.colour_2.g", 196);
    m_appear.assigned.colour_2.b = pt.get<int>("Settings.Appearance.assigned.colour_2.b",   0);
    m_appear.assigned.days_3     = pt.get<int>("Settings.Appearance.assigned.day_3",      270);
    m_appear.assigned.colour_3.r = pt.get<int>("Settings.Appearance.assigned.colour_3.r", 233);
    m_appear.assigned.colour_3.g = pt.get<int>("Settings.Appearance.assigned.colour_3.g", 168);
    m_appear.assigned.colour_3.b = pt.get<int>("Settings.Appearance.assigned.colour_3.b",   0);
    m_appear.assigned.days_4     = pt.get<int>("Settings.Appearance.assigned.day_4",      365);
    m_appear.assigned.colour_4.r = pt.get<int>("Settings.Appearance.assigned.colour_4.r", 233);
    m_appear.assigned.colour_4.g = pt.get<int>("Settings.Appearance.assigned.colour_4.g", 111);
    m_appear.assigned.colour_4.b = pt.get<int>("Settings.Appearance.assigned.colour_4.b",   0);
    m_appear.assigned.colour_5.r = pt.get<int>("Settings.Appearance.assigned.colour_5.r", 245);
    m_appear.assigned.colour_5.g = pt.get<int>("Settings.Appearance.assigned.colour_5.g",  42);
    m_appear.assigned.colour_5.b = pt.get<int>("Settings.Appearance.assigned.colour_5.b",   0);

    m_appear.unassigned.days_1     = pt.get<int>("Settings.Appearance.unassigned.day_1",       90);
    m_appear.unassigned.colour_1.r = pt.get<int>("Settings.Appearance.unassigned.colour_1.r",   0);
    m_appear.unassigned.colour_1.g = pt.get<int>("Settings.Appearance.unassigned.colour_1.g", 245);
    m_appear.unassigned.colour_1.b = pt.get<int>("Settings.Appearance.unassigned.colour_1.b", 113);
    m_appear.unassigned.days_2     = pt.get<int>("Settings.Appearance.unassigned.day_2",      180);
    m_appear.unassigned.colour_2.r = pt.get<int>("Settings.Appearance.unassigned.colour_2.r",   0);
    m_appear.unassigned.colour_2.g = pt.get<int>("Settings.Appearance.unassigned.colour_2.g", 233);
    m_appear.unassigned.colour_2.b = pt.get<int>("Settings.Appearance.unassigned.colour_2.b", 169);
    m_appear.unassigned.days_3     = pt.get<int>("Settings.Appearance.unassigned.day_3",      270);
    m_appear.unassigned.colour_3.r = pt.get<int>("Settings.Appearance.unassigned.colour_3.r",   0);
    m_appear.unassigned.colour_3.g = pt.get<int>("Settings.Appearance.unassigned.colour_3.g", 233);
    m_appear.unassigned.colour_3.b = pt.get<int>("Settings.Appearance.unassigned.colour_3.b", 232);
    m_appear.unassigned.days_4     = pt.get<int>("Settings.Appearance.unassigned.day_4",      365);
    m_appear.unassigned.colour_4.r = pt.get<int>("Settings.Appearance.unassigned.colour_4.r",   0);
    m_appear.unassigned.colour_4.g = pt.get<int>("Settings.Appearance.unassigned.colour_4.g", 159);
    m_appear.unassigned.colour_4.b = pt.get<int>("Settings.Appearance.unassigned.colour_4.b", 210);
    m_appear.unassigned.colour_5.r = pt.get<int>("Settings.Appearance.unassigned.colour_5.r",  90);
    m_appear.unassigned.colour_5.g = pt.get<int>("Settings.Appearance.unassigned.colour_5.g", 125);
    m_appear.unassigned.colour_5.b = pt.get<int>("Settings.Appearance.unassigned.colour_5.b", 245);

    /*******************/
    m_latex.bin_path                   = pt.get<std::string>("Settings.LaTeX.bin_path",           "");
    m_latex.del_latex_aux_files        = pt.get<bool>("Settings.LaTeX.delete_aux_files",           0);
    m_latex.del_latex_data_tex         = pt.get<bool>("Settings.LaTeX.delete_data_tex",            0);
    m_latex.open_report_after_creation = pt.get<bool>("Settings.LaTeX.open_report_after_creation", 0);

    m_maperitive.app_exe         = pt.get<std::string>("Settings.Map.Maperitiv",         "");
    m_maperitive.con_exe         = pt.get<std::string>("Settings.Map.Maperitiv_Console", "");
    m_maperitive.rules_path      = pt.get<std::string>("Settings.Map.Path_mrules",       "");
    m_maperitive.m_osm_file      = pt.get<std::string>("Settings.Map.OSM_file",          "");
    m_maperitive.m_osm_xapi_url  = pt.get<std::string>("Settings.Map.OSM_XAPI_URL",      "");
    m_maperitive.m_del_tmp_files = pt.get<bool>("Settings.Map.delete_tmp_files",  "");

    m_im.magick_exe     = pt.get<std::string>("Settings.Map.IM_magick",           "");
    m_im.borders_path    = pt.get<std::string>("Settings.Map.Path_borders",         "");
    m_im.m_del_tmp_files = pt.get<bool>("Settings.Map.IM_delete_tmp_files",  "");

    m_general.m_last_used_db           = pt.get<std::string>("Settings.General.last_used_db", "");
    m_general.m_aui_setting_portrait   = pt.get<std::string>("Settings.General.aui_setting_portrait", "");
    m_general.m_aui_setting_landscape  = pt.get<std::string>("Settings.General.aui_setting_landscape", "");
    m_general.m_territory_bounds       = pt.get<std::string>("Settings.Map.bounds",           "");
    m_general.m_min_longitude          = pt.get<double>("Settings.Map.min_longitude",        0.0);
    m_general.m_min_latitude           = pt.get<double>("Settings.Map.min_latitude",         0.0);
    m_general.m_max_longitude          = pt.get<double>("Settings.Map.max_longitude",        0.0);
    m_general.m_max_latitude           = pt.get<double>("Settings.Map.max_latitude",         0.0);
    m_general.m_infopage_map_width_mm  = pt.get<double>("Settings.Infopage.map_width",     150.0);
    m_general.m_infopage_map_height_mm = pt.get<double>("Settings.Infopage.map_height",     94.0);
    m_general.m_use_new_territory_numbers_in_maps = pt.get<bool>("Settings.Map.use_new_territory_numbers", "");
    m_general.m_use_tooltip_on_territory_tile     = pt.get<bool>("Settings.General.use_tooltip_on_territory_tile", "");
    m_general.m_assignee_past_months   = pt.get<unsigned int>("Settings.General.fade_territories_assignees_months", 36);

    m_pdf_application = pt.get<std::string>("Settings.Report.pdf_application",    "");
}

// Saves the debug_settings structure to the specified XML file
void C_Settings::save(const std::string &filename)
{
   // Create an empty property tree object
   using boost::property_tree::ptree;
   ptree pt;

   pt.put("Settings.Appearance.font_size",     m_appear.font_size);
   pt.put("Settings.Appearance.square_size_x", m_appear.m_square_size_x);
   pt.put("Settings.Appearance.square_size_y", m_appear.m_square_size_y);
   pt.put("Settings.Appearance.sash_size",     m_appear.m_sash_size);

    /*******************/
   pt.put("Settings.Appearance.assigned.day_1",      m_appear.assigned.days_1);
   pt.put("Settings.Appearance.assigned.colour_1.r", m_appear.assigned.colour_1.r);
   pt.put("Settings.Appearance.assigned.colour_1.g", m_appear.assigned.colour_1.g);
   pt.put("Settings.Appearance.assigned.colour_1.b", m_appear.assigned.colour_1.b);
   pt.put("Settings.Appearance.assigned.day_2",      m_appear.assigned.days_2);
   pt.put("Settings.Appearance.assigned.colour_2.r", m_appear.assigned.colour_2.r);
   pt.put("Settings.Appearance.assigned.colour_2.g", m_appear.assigned.colour_2.g);
   pt.put("Settings.Appearance.assigned.colour_2.b", m_appear.assigned.colour_2.b);
   pt.put("Settings.Appearance.assigned.day_3",      m_appear.assigned.days_3);
   pt.put("Settings.Appearance.assigned.colour_3.r", m_appear.assigned.colour_3.r);
   pt.put("Settings.Appearance.assigned.colour_3.g", m_appear.assigned.colour_3.g);
   pt.put("Settings.Appearance.assigned.colour_3.b", m_appear.assigned.colour_3.b);
   pt.put("Settings.Appearance.assigned.day_4",      m_appear.assigned.days_4);
   pt.put("Settings.Appearance.assigned.colour_4.r", m_appear.assigned.colour_4.r);
   pt.put("Settings.Appearance.assigned.colour_4.g", m_appear.assigned.colour_4.g);
   pt.put("Settings.Appearance.assigned.colour_4.b", m_appear.assigned.colour_4.b);
   pt.put("Settings.Appearance.assigned.colour_5.r", m_appear.assigned.colour_5.r);
   pt.put("Settings.Appearance.assigned.colour_5.g", m_appear.assigned.colour_5.g);
   pt.put("Settings.Appearance.assigned.colour_5.b", m_appear.assigned.colour_5.b);

   pt.put("Settings.Appearance.unassigned.day_1",      m_appear.unassigned.days_1);
   pt.put("Settings.Appearance.unassigned.colour_1.r", m_appear.unassigned.colour_1.r);
   pt.put("Settings.Appearance.unassigned.colour_1.g", m_appear.unassigned.colour_1.g);
   pt.put("Settings.Appearance.unassigned.colour_1.b", m_appear.unassigned.colour_1.b);
   pt.put("Settings.Appearance.unassigned.day_2",      m_appear.unassigned.days_2);
   pt.put("Settings.Appearance.unassigned.colour_2.r", m_appear.unassigned.colour_2.r);
   pt.put("Settings.Appearance.unassigned.colour_2.g", m_appear.unassigned.colour_2.g);
   pt.put("Settings.Appearance.unassigned.colour_2.b", m_appear.unassigned.colour_2.b);
   pt.put("Settings.Appearance.unassigned.day_3",      m_appear.unassigned.days_3);
   pt.put("Settings.Appearance.unassigned.colour_3.r", m_appear.unassigned.colour_3.r);
   pt.put("Settings.Appearance.unassigned.colour_3.g", m_appear.unassigned.colour_3.g);
   pt.put("Settings.Appearance.unassigned.colour_3.b", m_appear.unassigned.colour_3.b);
   pt.put("Settings.Appearance.unassigned.day_4",      m_appear.unassigned.days_4);
   pt.put("Settings.Appearance.unassigned.colour_4.r", m_appear.unassigned.colour_4.r);
   pt.put("Settings.Appearance.unassigned.colour_4.g", m_appear.unassigned.colour_4.g);
   pt.put("Settings.Appearance.unassigned.colour_4.b", m_appear.unassigned.colour_4.b);
   pt.put("Settings.Appearance.unassigned.colour_5.r", m_appear.unassigned.colour_5.r);
   pt.put("Settings.Appearance.unassigned.colour_5.g", m_appear.unassigned.colour_5.g);
   pt.put("Settings.Appearance.unassigned.colour_5.b", m_appear.unassigned.colour_5.b);

    /*******************/

   pt.put("Settings.LaTeX.bin_path",                   m_latex.bin_path);
   pt.put("Settings.LaTeX.delete_aux_files",           m_latex.del_latex_aux_files);
   pt.put("Settings.LaTeX.delete_data_tex",            m_latex.del_latex_data_tex);
   pt.put("Settings.LaTeX.open_report_after_creation", m_latex.open_report_after_creation);

   pt.put("Settings.Map.Maperitiv",         m_maperitive.app_exe);
   pt.put("Settings.Map.Maperitiv_Console", m_maperitive.con_exe);
   pt.put("Settings.Map.Path_mrules",       m_maperitive.rules_path);
   pt.put("Settings.Map.OSM_file",          m_maperitive.m_osm_file);
   pt.put("Settings.Map.OSM_XAPI_URL",      m_maperitive.m_osm_xapi_url);
   pt.put("Settings.Map.delete_tmp_files",  m_maperitive.m_del_tmp_files);

   pt.put("Settings.Map.IM_magick",           m_im.magick_exe);
   pt.put("Settings.Map.Path_borders",        m_im.borders_path);
   pt.put("Settings.Map.IM_delete_tmp_files", m_im.m_del_tmp_files);

   pt.put("Settings.General.last_used_db",          m_general.m_last_used_db);
   pt.put("Settings.General.aui_setting_portrait",  m_general.m_aui_setting_portrait);
   pt.put("Settings.General.aui_setting_landscape", m_general.m_aui_setting_landscape);
   pt.put("Settings.Map.bounds",            m_general.m_territory_bounds);
   pt.put("Settings.Map.min_longitude",     m_general.m_min_longitude);
   pt.put("Settings.Map.min_latitude",      m_general.m_min_latitude);
   pt.put("Settings.Map.max_longitude",     m_general.m_max_longitude);
   pt.put("Settings.Map.max_latitude",      m_general.m_max_latitude);
   pt.put("Settings.Infopage.map_width",    m_general.m_infopage_map_width_mm);
   pt.put("Settings.Infopage.map_height",   m_general.m_infopage_map_height_mm);
   pt.put("Settings.Map.use_new_territory_numbers",             m_general.m_use_new_territory_numbers_in_maps);
   pt.put("Settings.General.use_tooltip_on_territory_tile",     m_general.m_use_tooltip_on_territory_tile);
   pt.put("Settings.General.fade_territories_assignees_months", m_general.m_assignee_past_months);

   pt.put("Settings.Report.pdf_application", m_pdf_application);

   // Write the property tree to the XML file.
   write_xml(filename, pt);
}
