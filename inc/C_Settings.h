#ifndef C_SETTINGS_H
#define C_SETTINGS_H

#include <set>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

struct TileColour
{
    int r;
    int g;
    int b;
};

struct TileColoursCategories
{
    int        days_1;
    TileColour colour_1;
    int        days_2;
    TileColour colour_2;
    int        days_3;
    TileColour colour_3;
    int        days_4;
    TileColour colour_4;
    TileColour colour_5;
};

struct AppearanceSettings
{
    int font_size;
    int m_square_size_x;
    int m_square_size_y;
    int m_sash_size;
    TileColoursCategories assigned;
    TileColoursCategories unassigned;
};

struct LaTeXSettings
{
    std::string bin_path;
    bool del_latex_aux_files;
    bool del_latex_data_tex;
    bool open_report_after_creation;
};

struct MaperitiveSettings
{
    std::string app_exe;
    std::string con_exe;
    std::string rules_path;
    std::string m_osm_file;
    std::string m_osm_xapi_url;
    bool m_del_tmp_files;
};

struct ImageMagickSettings
{
    std::string magick_exe;
    std::string borders_path;
    bool m_del_tmp_files;
};

struct GeneralSettings
{
    std::string m_last_used_db;
    std::string m_aui_setting_portrait;
    std::string m_aui_setting_landscape;
    std::string m_territory_bounds;
    double m_min_longitude;
    double m_min_latitude;
    double m_max_longitude;
    double m_max_latitude;
    double m_infopage_map_width_mm;
    double m_infopage_map_height_mm;
    bool m_use_new_territory_numbers_in_maps;
    bool m_use_tooltip_on_territory_tile;
    unsigned int m_assignee_past_months;
};

class C_Settings
{
    public:
        C_Settings();
        virtual ~C_Settings();

        AppearanceSettings m_appear;
        LaTeXSettings m_latex;
        MaperitiveSettings m_maperitive;
        ImageMagickSettings m_im;
        GeneralSettings m_general;

        std::string m_pdf_application;

        void load(const std::string &filename);
        void save(const std::string &filename);

    protected:
    private:
};

#endif // C_SETTINGS_H
