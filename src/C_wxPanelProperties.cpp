#include "C_wxPanelProperties.h"

//http://docs->wxwidgets->org/3.1/overview_propgrid.html#propgrid_fromfile
#include <wx/propgrid/advprops.h>

const wxString C_wxPanelProperties::CATEGORY_GENERAL                 = wxT("Generell");
const wxString C_wxPanelProperties::LAST_USED_DB                     = wxT("Verwendete Datenbank");
const wxString C_wxPanelProperties::USE_NEW_NUMBERING                = wxT("Benutze neue Gebietsnummern");
const wxString C_wxPanelProperties::USE_TILE_TOOLTIP                 = wxT("Zeige Tooltip über Gebietskachel");
const wxString C_wxPanelProperties::TERRITORY_DIMENSION              = wxT("Gebietsgrenze");
const wxString C_wxPanelProperties::MINLNG                           = wxT("Min Longitude");
const wxString C_wxPanelProperties::MINLAT                           = wxT("Min Latitude");
const wxString C_wxPanelProperties::MAXLNG                           = wxT("Max Longitude");
const wxString C_wxPanelProperties::MAXLAT                           = wxT("Max Latitude");
const wxString C_wxPanelProperties::OSM_SERVICE_URL                  = wxT("OSM Service URL");
const wxString C_wxPanelProperties::DEL_TEMP_FILES                   = wxT("Löschen temporärer Dateien");
const wxString C_wxPanelProperties::TEMP_FILES_MAPERITIVE            = wxT("Maperitive");
const wxString C_wxPanelProperties::TEMP_FILES_IMAGEMAGICK           = wxT("ImageMagick");
const wxString C_wxPanelProperties::TEMP_FILES_LATEX                 = wxT("LaTeX");
const wxString C_wxPanelProperties::PDF_VIEWER                       = wxT("PDF Viewer");
const wxString C_wxPanelProperties::FADE_ASSIGNEE_TERRITORIES_MONTHS = wxT("Ausblenden letzte Zuteilungen (Monate)");

const wxString C_wxPanelProperties::CATEGORY_APPEARANCE    = wxT("Darstellung");
const wxString C_wxPanelProperties::FONT                   = wxT("Font");
const wxString C_wxPanelProperties::TILE                   = wxT("Kachel");
const wxString C_wxPanelProperties::TILE_LENGTH            = wxT("Länge (px)");
const wxString C_wxPanelProperties::TILE_HEIGHT            = wxT("Höhe (px)");
const wxString C_wxPanelProperties::SASH_SIZE              = wxT("Fensterrahmengröße (px)");

const wxString C_wxPanelProperties::CATEGORY_TILE_COLOUR   = wxT("Kachelfarben");
const wxString C_wxPanelProperties::CATEGORY_ASSIGNED      = wxT("Zugeteilt");
const wxString C_wxPanelProperties::TILE_ASS_COLOUR_1      = wxT("Kachelfarbe 1");
const wxString C_wxPanelProperties::TILE_ASS_DAYS_1        = wxT("Zuteilung Tage 1");
const wxString C_wxPanelProperties::TILE_ASS_COLOUR_2      = wxT("Kachelfarbe 2");
const wxString C_wxPanelProperties::TILE_ASS_DAYS_2        = wxT("Zuteilung Tage 2");
const wxString C_wxPanelProperties::TILE_ASS_COLOUR_3      = wxT("Kachelfarbe 3");
const wxString C_wxPanelProperties::TILE_ASS_DAYS_3        = wxT("Zuteilung Tage 3");
const wxString C_wxPanelProperties::TILE_ASS_COLOUR_4      = wxT("Kachelfarbe 4");
const wxString C_wxPanelProperties::TILE_ASS_DAYS_4        = wxT("Zuteilung Tage 4");
const wxString C_wxPanelProperties::TILE_ASS_COLOUR_5      = wxT("Kachelfarbe 5");
const wxString C_wxPanelProperties::CATEGORY_UNASSIGNED    = wxT("Nicht zugeteilt");
const wxString C_wxPanelProperties::TILE_UNASS_COLOUR_1    = wxT("NZ Kachelfarbe 1");
const wxString C_wxPanelProperties::TILE_UNASS_DAYS_1      = wxT("NZ Zuteilung Tage 1");
const wxString C_wxPanelProperties::TILE_UNASS_COLOUR_2    = wxT("NZ Kachelfarbe 2");
const wxString C_wxPanelProperties::TILE_UNASS_DAYS_2      = wxT("NZ Zuteilung Tage 2");
const wxString C_wxPanelProperties::TILE_UNASS_COLOUR_3    = wxT("NZ Kachelfarbe 3");
const wxString C_wxPanelProperties::TILE_UNASS_DAYS_3      = wxT("NZ Zuteilung Tage 3");
const wxString C_wxPanelProperties::TILE_UNASS_COLOUR_4    = wxT("NZ Kachelfarbe 4");
const wxString C_wxPanelProperties::TILE_UNASS_DAYS_4      = wxT("NZ Zuteilung Tage 4");
const wxString C_wxPanelProperties::TILE_UNASS_COLOUR_5    = wxT("NZ Kachelfarbe 5");

const wxString C_wxPanelProperties::CATEGORY_PATHS         = wxT("Programmpfade");
const wxString C_wxPanelProperties::MAPERITIVE_GUI         = wxT("Maperitive GUI (*.exe)");
const wxString C_wxPanelProperties::MAPERITIVE_CONSOLE     = wxT("Maperitive Konsole (*.exe)");
const wxString C_wxPanelProperties::IMAGEMAGICK_MAGICK     = wxT("ImageMagick (magick.exe)");
const wxString C_wxPanelProperties::LATEX_BIN_DIR          = wxT("LaTeX \\bin Verzeichnis");

const wxString C_wxPanelProperties::CATEGORY_MAPS          = wxT("Gebietskärtchen");
const wxString C_wxPanelProperties::PATH_MRULES            = wxT("Pfad zu mrules");
const wxString C_wxPanelProperties::PATH_BORDERS           = wxT("Pfad zu border");
const wxString C_wxPanelProperties::OSM_FILE               = wxT("OSM Datei");
const wxString C_wxPanelProperties::CREATION_SIZE          = wxT("Erzeugungsgröße");
const wxString C_wxPanelProperties::CREATION_WIDTH         = wxT("Breite (mm)");
const wxString C_wxPanelProperties::CREATION_HEIGHT        = wxT("Höhe (mm)");
const wxString C_wxPanelProperties::CREATION_DPI           = wxT("Auflösung (dpi)");
const wxString C_wxPanelProperties::PRINT_SIZE             = wxT("Druckgröße");
const wxString C_wxPanelProperties::PRINT_WIDTH            = wxT("Breite (mm)");
const wxString C_wxPanelProperties::PRINT_HEIGHT           = wxT("Höhe (mm)");


C_wxPanelProperties::C_wxPanelProperties( wxWindow* parent)
:
property_panel( parent ), s(nullptr), ad(nullptr)
{
}

void C_wxPanelProperties::set_settings(C_Settings* settings, ApplicationData* appl_data)
{
    s = settings;
    ad = appl_data;

    prepare_properties();
    add_properties();

    m_propertyGrid1->ExpandAll();

    m_propertyGrid1->SetSplitterLeft(true);
}


bool C_wxPanelProperties::SetFont(const wxFont &font)
{
    m_propertyGrid1->SetFont(font);
    return true;
}

void C_wxPanelProperties::OnPropertyGridChanged(wxPropertyGridEvent& event)
{
    wxPGProperty* property = event.GetProperty();

    // Do nothing if event did not have associated property
    if ( !property )
        return;

    // GetValue() returns wxVariant, but it is converted transparently to wxAny
    wxAny value = property->GetValue();

    // Also, handle the case where property value is unspecified
    if ( value.IsNull() )
        return;

    wxString PropName = property->GetName();

    // Handle changes in values, as needed
    if ( property->GetName() == LAST_USED_DB )
        s->m_general.m_last_used_db = value.As<wxString>().c_str();

    else if ( property->GetName() == USE_NEW_NUMBERING )
        s->m_general.m_use_new_territory_numbers_in_maps = value.As<bool>();

    else if ( property->GetName() == USE_TILE_TOOLTIP )
        s->m_general.m_use_tooltip_on_territory_tile = value.As<bool>();

    else if ( property->GetName() == TERRITORY_DIMENSION + "." + MINLNG )
        s->m_general.m_min_longitude = value.As<double>();

    else if ( property->GetName() == TERRITORY_DIMENSION + "." + MINLAT )
        s->m_general.m_min_latitude = value.As<double>();

    else if ( property->GetName() == TERRITORY_DIMENSION + "." + MAXLNG )
        s->m_general.m_max_longitude = value.As<double>();

    else if ( property->GetName() == TERRITORY_DIMENSION + "." + MAXLAT )
        s->m_general.m_max_latitude = value.As<double>();

    else if ( property->GetName() == OSM_SERVICE_URL )
        s->m_maperitive.m_osm_xapi_url = value.As<wxString>().c_str();

    else if ( property->GetName() == DEL_TEMP_FILES + "." + TEMP_FILES_MAPERITIVE )
        s->m_maperitive.m_del_tmp_files = value.As<bool>();

    else if ( property->GetName() == DEL_TEMP_FILES + "." + TEMP_FILES_IMAGEMAGICK )
        s->m_im.m_del_tmp_files = value.As<bool>();

    else if ( property->GetName() == DEL_TEMP_FILES + "." + TEMP_FILES_LATEX ){
        s->m_latex.del_latex_aux_files = value.As<bool>();
        s->m_latex.del_latex_data_tex = value.As<bool>();
    }

    else if ( property->GetName() == PDF_VIEWER )
        s->m_pdf_application = value.As<wxString>().c_str();

    else if ( property->GetName() == FADE_ASSIGNEE_TERRITORIES_MONTHS )
        s->m_general.m_assignee_past_months = value.As<unsigned int>();

    else if ( property->GetName() == FONT )
        s->m_appear.font_size = value.As<wxFont>().GetPointSize();

    else if ( property->GetName() == TILE + "." + TILE_LENGTH )
        s->m_appear.m_square_size_x = value.As<int>();

    else if ( property->GetName() == TILE + "." + TILE_HEIGHT )
        s->m_appear.m_square_size_y = value.As<int>();

    else if ( property->GetName() == SASH_SIZE )
        s->m_appear.m_sash_size = value.As<int>();

    /*************************************/

    else if ( property->GetName() == TILE_ASS_DAYS_1 )
        s->m_appear.assigned.days_1 = value.As<int>();

    else if ( property->GetName() == TILE_ASS_COLOUR_1 )
    {
        s->m_appear.assigned.colour_1.r = value.As<wxColour>().Red();
        s->m_appear.assigned.colour_1.g = value.As<wxColour>().Green();
        s->m_appear.assigned.colour_1.b = value.As<wxColour>().Blue();
    }

    else if ( property->GetName() == TILE_ASS_DAYS_2 )
        s->m_appear.assigned.days_2 = value.As<int>();

    else if ( property->GetName() == TILE_ASS_COLOUR_2 )
    {
        s->m_appear.assigned.colour_2.r = value.As<wxColour>().Red();
        s->m_appear.assigned.colour_2.g = value.As<wxColour>().Green();
        s->m_appear.assigned.colour_2.b = value.As<wxColour>().Blue();
    }

    else if ( property->GetName() == TILE_ASS_DAYS_3 )
        s->m_appear.assigned.days_3 = value.As<int>();

    else if ( property->GetName() == TILE_ASS_COLOUR_3 )
    {
        s->m_appear.assigned.colour_3.r = value.As<wxColour>().Red();
        s->m_appear.assigned.colour_3.g = value.As<wxColour>().Green();
        s->m_appear.assigned.colour_3.b = value.As<wxColour>().Blue();
    }

    else if ( property->GetName() == TILE_ASS_DAYS_4 )
        s->m_appear.assigned.days_4 = value.As<int>();

    else if ( property->GetName() == TILE_ASS_COLOUR_4 )
    {
        s->m_appear.assigned.colour_4.r = value.As<wxColour>().Red();
        s->m_appear.assigned.colour_4.g = value.As<wxColour>().Green();
        s->m_appear.assigned.colour_4.b = value.As<wxColour>().Blue();
    }

    else if ( property->GetName() == TILE_ASS_COLOUR_5 )
    {
        s->m_appear.assigned.colour_5.r = value.As<wxColour>().Red();
        s->m_appear.assigned.colour_5.g = value.As<wxColour>().Green();
        s->m_appear.assigned.colour_5.b = value.As<wxColour>().Blue();
    }
    /*************************************/



    else if ( property->GetName() == TILE_UNASS_DAYS_1 )
        s->m_appear.unassigned.days_1 = value.As<int>();

    else if ( property->GetName() == TILE_UNASS_COLOUR_1 )
    {
        s->m_appear.unassigned.colour_1.r = value.As<wxColour>().Red();
        s->m_appear.unassigned.colour_1.g = value.As<wxColour>().Green();
        s->m_appear.unassigned.colour_1.b = value.As<wxColour>().Blue();
    }

    else if ( property->GetName() == TILE_UNASS_DAYS_2 )
        s->m_appear.unassigned.days_2 = value.As<int>();

    else if ( property->GetName() == TILE_UNASS_COLOUR_2 )
    {
        s->m_appear.unassigned.colour_2.r = value.As<wxColour>().Red();
        s->m_appear.unassigned.colour_2.g = value.As<wxColour>().Green();
        s->m_appear.unassigned.colour_2.b = value.As<wxColour>().Blue();
    }

    else if ( property->GetName() == TILE_UNASS_DAYS_3 )
        s->m_appear.unassigned.days_3 = value.As<int>();

    else if ( property->GetName() == TILE_UNASS_COLOUR_3 )
    {
        s->m_appear.unassigned.colour_3.r = value.As<wxColour>().Red();
        s->m_appear.unassigned.colour_3.g = value.As<wxColour>().Green();
        s->m_appear.unassigned.colour_3.b = value.As<wxColour>().Blue();
    }

    else if ( property->GetName() == TILE_UNASS_DAYS_4 )
        s->m_appear.unassigned.days_4 = value.As<int>();

    else if ( property->GetName() == TILE_UNASS_COLOUR_4 )
    {
        s->m_appear.unassigned.colour_4.r = value.As<wxColour>().Red();
        s->m_appear.unassigned.colour_4.g = value.As<wxColour>().Green();
        s->m_appear.unassigned.colour_4.b = value.As<wxColour>().Blue();
    }

    else if ( property->GetName() == TILE_UNASS_COLOUR_5 )
    {
        s->m_appear.unassigned.colour_5.r = value.As<wxColour>().Red();
        s->m_appear.unassigned.colour_5.g = value.As<wxColour>().Green();
        s->m_appear.unassigned.colour_5.b = value.As<wxColour>().Blue();
    }








    /*************************************/
    else if ( property->GetName() == MAPERITIVE_GUI )
        s->m_maperitive.app_exe = value.As<wxString>().c_str();

    else if ( property->GetName() == MAPERITIVE_CONSOLE )
        s->m_maperitive.con_exe = value.As<wxString>().c_str();

    else if ( property->GetName() == IMAGEMAGICK_MAGICK )
        s->m_im.magick_exe = value.As<wxString>().c_str();

    else if ( property->GetName() == LATEX_BIN_DIR )
        s->m_latex.bin_path = value.As<wxString>().c_str();

    else if ( property->GetName() == PATH_MRULES )
        s->m_maperitive.rules_path = value.As<wxString>().c_str();

    else if ( property->GetName() == PATH_BORDERS )
        s->m_im.borders_path = value.As<wxString>().c_str();

    else if ( property->GetName() == OSM_FILE )
        s->m_maperitive.m_osm_file = value.As<wxString>().c_str();

    else if ( property->GetName() == CREATION_SIZE + "." + CREATION_WIDTH )
        ;
    else if ( property->GetName() == CREATION_SIZE + "." + CREATION_HEIGHT )
        ;
    else if ( property->GetName() == CREATION_SIZE + "." + CREATION_DPI )
        ;

    else if ( property->GetName() == PRINT_SIZE + "." + PRINT_WIDTH )
        s->m_general.m_infopage_map_width_mm = value.As<double>();

    else if ( property->GetName() == PRINT_SIZE + "." + PRINT_HEIGHT ){
        s->m_general.m_infopage_map_height_mm = value.As<double>();
    }

    s->save(ad->settings_file);
}


void C_wxPanelProperties::prepare_properties(void)
{
    PropertyLine p;

    p.m_label = CATEGORY_GENERAL;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxPropertyCategory(p.m_label);
    m_Properties.push_back(p);

    p.m_label = LAST_USED_DB;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFileProperty(p.m_label, wxPG_LABEL, s->m_general.m_last_used_db);
    p.p_wxPGProperty->SetAttribute(wxPG_FILE_WILDCARD, wxT("sqlite db (*.*)|*.*"));
    m_Properties.push_back(p);

    p.m_label = USE_NEW_NUMBERING;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxBoolProperty(p.m_label, wxPG_LABEL, s->m_general.m_use_new_territory_numbers_in_maps);
    m_Properties.push_back(p);

    p.m_label = USE_TILE_TOOLTIP;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxBoolProperty(p.m_label, wxPG_LABEL, s->m_general.m_use_tooltip_on_territory_tile);
    m_Properties.push_back(p);

    p.m_label = TERRITORY_DIMENSION;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, "<composed>");
    m_Properties.push_back(p);

    p.m_label = MINLNG;
    p.p_wxPGProperty_Parent = m_Properties[4].p_wxPGProperty;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, s->m_general.m_min_longitude);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 17);
    m_Properties.push_back(p);

    p.m_label = MINLAT;
    p.p_wxPGProperty_Parent = m_Properties[4].p_wxPGProperty;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, s->m_general.m_min_latitude);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 17);
    m_Properties.push_back(p);

    p.m_label = MAXLNG;
    p.p_wxPGProperty_Parent = m_Properties[4].p_wxPGProperty;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, s->m_general.m_max_longitude);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 17);
    m_Properties.push_back(p);

    p.m_label = MAXLAT;
    p.p_wxPGProperty_Parent = m_Properties[4].p_wxPGProperty;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, s->m_general.m_max_latitude);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 17);
    m_Properties.push_back(p);

    p.m_label = OSM_SERVICE_URL;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, s->m_maperitive.m_osm_xapi_url);
    m_Properties.push_back(p);

    p.m_label = DEL_TEMP_FILES;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, "<composed>");
    m_Properties.push_back(p);

    p.m_label = TEMP_FILES_MAPERITIVE;
    p.p_wxPGProperty_Parent = m_Properties[10].p_wxPGProperty;
    p.p_wxPGProperty = new wxBoolProperty(p.m_label, wxPG_LABEL, s->m_maperitive.m_del_tmp_files);
    m_Properties.push_back(p);

    p.m_label = TEMP_FILES_IMAGEMAGICK;
    p.p_wxPGProperty_Parent = m_Properties[10].p_wxPGProperty;
    p.p_wxPGProperty = new wxBoolProperty(p.m_label, wxPG_LABEL, s->m_im.m_del_tmp_files);
    m_Properties.push_back(p);

    p.m_label = TEMP_FILES_LATEX;
    p.p_wxPGProperty_Parent = m_Properties[10].p_wxPGProperty;
    p.p_wxPGProperty = new wxBoolProperty(p.m_label, wxPG_LABEL, s->m_latex.del_latex_aux_files);
    m_Properties.push_back(p);

    p.m_label = PDF_VIEWER;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFileProperty(p.m_label, wxPG_LABEL, s->m_pdf_application);
    p.p_wxPGProperty->SetAttribute(wxPG_FILE_WILDCARD, "PDF Viewer (*.exe)|*.exe");
    m_Properties.push_back(p);

    p.m_label = FADE_ASSIGNEE_TERRITORIES_MONTHS;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_general.m_assignee_past_months);
    m_Properties.push_back(p);

    p.m_label = CATEGORY_APPEARANCE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxPropertyCategory(p.m_label);
    m_Properties.push_back(p);

    p.m_label = FONT;
    p.p_wxPGProperty_Parent = nullptr;
    wxFont thisFont = GetFont(); thisFont.SetPointSize(s->m_appear.font_size);
    p.p_wxPGProperty = new wxFontProperty(p.m_label, wxPG_LABEL, thisFont);
    m_Properties.push_back(p);

    p.m_label = TILE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, "<composed>");
    m_Properties.push_back(p);

    p.m_label = TILE_LENGTH;
    p.p_wxPGProperty_Parent = m_Properties[18].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.m_square_size_x);
    m_Properties.push_back(p);

    p.m_label = TILE_HEIGHT;
    p.p_wxPGProperty_Parent = m_Properties[18].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.m_square_size_y);
    m_Properties.push_back(p);

    p.m_label = SASH_SIZE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.m_sash_size);
    m_Properties.push_back(p);

    //*************************************************************************

    /*  static const wxString CATEGORY_TILE_COLOUR;
        static const wxString ASSIGNED;
        static const wxString TILE_COLOUR_1;  */

    p.m_label = CATEGORY_TILE_COLOUR;
    p.p_wxPGProperty_Parent = nullptr; //m_Properties[17].p_wxPGProperty;
    p.p_wxPGProperty = new wxPropertyCategory(p.m_label);
    m_Properties.push_back(p);

    p.m_label = CATEGORY_ASSIGNED;
    p.p_wxPGProperty_Parent = m_Properties[22].p_wxPGProperty;
    p.p_wxPGProperty = new wxPropertyCategory(p.m_label);
    m_Properties.push_back(p);

    p.m_label = TILE_ASS_DAYS_1;
    p.p_wxPGProperty_Parent = m_Properties[23].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.assigned.days_1);
    m_Properties.push_back(p);

    p.m_label = TILE_ASS_COLOUR_1;
    p.p_wxPGProperty_Parent = m_Properties[24].p_wxPGProperty;
    p.p_wxPGProperty = new wxColourProperty(p.m_label, wxPG_LABEL, wxColour(s->m_appear.assigned.colour_1.r,s->m_appear.assigned.colour_1.g,s->m_appear.assigned.colour_1.b));
    m_Properties.push_back(p);

    p.m_label = TILE_ASS_DAYS_2;
    p.p_wxPGProperty_Parent = m_Properties[23].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.assigned.days_2);
    m_Properties.push_back(p);

    p.m_label = TILE_ASS_COLOUR_2;
    p.p_wxPGProperty_Parent = m_Properties[23].p_wxPGProperty;
    p.p_wxPGProperty = new wxColourProperty(p.m_label, wxPG_LABEL, wxColour(s->m_appear.assigned.colour_2.r,s->m_appear.assigned.colour_2.g,s->m_appear.assigned.colour_2.b));
    m_Properties.push_back(p);

    p.m_label = TILE_ASS_DAYS_3;
    p.p_wxPGProperty_Parent = m_Properties[23].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.assigned.days_3);
    m_Properties.push_back(p);

    p.m_label = TILE_ASS_COLOUR_3;
    p.p_wxPGProperty_Parent = m_Properties[23].p_wxPGProperty;
    p.p_wxPGProperty = new wxColourProperty(p.m_label, wxPG_LABEL, wxColour(s->m_appear.assigned.colour_3.r,s->m_appear.assigned.colour_3.g,s->m_appear.assigned.colour_3.b));
    m_Properties.push_back(p);

    p.m_label = TILE_ASS_DAYS_4;
    p.p_wxPGProperty_Parent = m_Properties[23].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.assigned.days_4);
    m_Properties.push_back(p);

    p.m_label = TILE_ASS_COLOUR_4;
    p.p_wxPGProperty_Parent = m_Properties[23].p_wxPGProperty;
    p.p_wxPGProperty = new wxColourProperty(p.m_label, wxPG_LABEL, wxColour(s->m_appear.assigned.colour_4.r,s->m_appear.assigned.colour_4.g,s->m_appear.assigned.colour_4.b));
    m_Properties.push_back(p);

    p.m_label = TILE_ASS_COLOUR_5;
    p.p_wxPGProperty_Parent = m_Properties[23].p_wxPGProperty;
    p.p_wxPGProperty = new wxColourProperty(p.m_label, wxPG_LABEL, wxColour(s->m_appear.assigned.colour_5.r,s->m_appear.assigned.colour_5.g,s->m_appear.assigned.colour_5.b));
    m_Properties.push_back(p);

    //*********

    p.m_label = CATEGORY_UNASSIGNED;
    p.p_wxPGProperty_Parent = m_Properties[22].p_wxPGProperty;
    p.p_wxPGProperty = new wxPropertyCategory(p.m_label);
    m_Properties.push_back(p);

    p.m_label = TILE_UNASS_DAYS_1;
    p.p_wxPGProperty_Parent = m_Properties[33].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.unassigned.days_1);
    m_Properties.push_back(p);

    p.m_label = TILE_UNASS_COLOUR_1;
    p.p_wxPGProperty_Parent = m_Properties[33].p_wxPGProperty;
    p.p_wxPGProperty = new wxColourProperty(p.m_label, wxPG_LABEL, wxColour(s->m_appear.unassigned.colour_1.r,s->m_appear.unassigned.colour_1.g,s->m_appear.unassigned.colour_1.b));
    m_Properties.push_back(p);

    p.m_label = TILE_UNASS_DAYS_2;
    p.p_wxPGProperty_Parent = m_Properties[33].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.unassigned.days_2);
    m_Properties.push_back(p);

    p.m_label = TILE_UNASS_COLOUR_2;
    p.p_wxPGProperty_Parent = m_Properties[33].p_wxPGProperty;
    p.p_wxPGProperty = new wxColourProperty(p.m_label, wxPG_LABEL, wxColour(s->m_appear.unassigned.colour_2.r,s->m_appear.unassigned.colour_2.g,s->m_appear.unassigned.colour_2.b));
    m_Properties.push_back(p);

    p.m_label = TILE_UNASS_DAYS_3;
    p.p_wxPGProperty_Parent = m_Properties[33].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.unassigned.days_3);
    m_Properties.push_back(p);

    p.m_label = TILE_UNASS_COLOUR_3;
    p.p_wxPGProperty_Parent = m_Properties[33].p_wxPGProperty;
    p.p_wxPGProperty = new wxColourProperty(p.m_label, wxPG_LABEL, wxColour(s->m_appear.unassigned.colour_3.r,s->m_appear.unassigned.colour_3.g,s->m_appear.unassigned.colour_3.b));
    m_Properties.push_back(p);

    p.m_label = TILE_UNASS_DAYS_4;
    p.p_wxPGProperty_Parent = m_Properties[33].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, s->m_appear.unassigned.days_4);
    m_Properties.push_back(p);

    p.m_label = TILE_UNASS_COLOUR_4;
    p.p_wxPGProperty_Parent = m_Properties[33].p_wxPGProperty;
    p.p_wxPGProperty = new wxColourProperty(p.m_label, wxPG_LABEL, wxColour(s->m_appear.unassigned.colour_4.r,s->m_appear.unassigned.colour_4.g,s->m_appear.unassigned.colour_4.b));
    m_Properties.push_back(p);

    p.m_label = TILE_UNASS_COLOUR_5;
    p.p_wxPGProperty_Parent = m_Properties[33].p_wxPGProperty;
    p.p_wxPGProperty = new wxColourProperty(p.m_label, wxPG_LABEL, wxColour(s->m_appear.unassigned.colour_5.r,s->m_appear.unassigned.colour_5.g,s->m_appear.unassigned.colour_5.b));
    m_Properties.push_back(p);






    //*************************************************************************

    p.m_label = CATEGORY_PATHS;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxPropertyCategory(p.m_label);
    m_Properties.push_back(p);

    p.m_label = MAPERITIVE_GUI;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFileProperty(p.m_label, wxPG_LABEL, s->m_maperitive.app_exe);
    p.p_wxPGProperty->SetAttribute(wxPG_FILE_WILDCARD, "Executable (*.exe)|*.exe");
    m_Properties.push_back(p);

    p.m_label = MAPERITIVE_CONSOLE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFileProperty(p.m_label, wxPG_LABEL, s->m_maperitive.con_exe);
    p.p_wxPGProperty->SetAttribute(wxPG_FILE_WILDCARD, "Executable (*.exe)|*.exe");
    m_Properties.push_back(p);

    p.m_label = IMAGEMAGICK_MAGICK;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFileProperty(p.m_label, wxPG_LABEL, s->m_im.magick_exe);
    p.p_wxPGProperty->SetAttribute(wxPG_FILE_WILDCARD, "Executable (*.exe)|*.exe");
    m_Properties.push_back(p);

    p.m_label = LATEX_BIN_DIR;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxDirProperty(p.m_label, wxPG_LABEL, s->m_latex.bin_path);
    m_Properties.push_back(p);

    p.m_label = CATEGORY_MAPS;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxPropertyCategory(p.m_label);
    m_Properties.push_back(p);

    p.m_label = PATH_MRULES;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxDirProperty(p.m_label, wxPG_LABEL, s->m_maperitive.rules_path);
    m_Properties.push_back(p);

    p.m_label = PATH_BORDERS;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxDirProperty(p.m_label, wxPG_LABEL, s->m_im.borders_path);
    m_Properties.push_back(p);

    p.m_label = OSM_FILE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFileProperty(p.m_label, wxPG_LABEL, s->m_maperitive.m_osm_file);
    p.p_wxPGProperty->SetAttribute(wxPG_FILE_WILDCARD, "OSM file (*.*)|*.*");
    m_Properties.push_back(p);

    p.m_label = CREATION_SIZE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, "<composed>");
    m_Properties.push_back(p);

    p.m_label = CREATION_WIDTH;
    p.p_wxPGProperty_Parent = m_Properties[52].p_wxPGProperty;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, 150.0);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 4);
    m_Properties.push_back(p);

    p.m_label = CREATION_HEIGHT;
    p.p_wxPGProperty_Parent = m_Properties[52].p_wxPGProperty;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, 94.0);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 4);
    m_Properties.push_back(p);

    p.m_label = CREATION_DPI;
    p.p_wxPGProperty_Parent = m_Properties[52].p_wxPGProperty;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, 300);
    m_Properties.push_back(p);

    p.m_label = PRINT_SIZE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, "<composed>");
    m_Properties.push_back(p);

    p.m_label = PRINT_WIDTH;
    p.p_wxPGProperty_Parent = m_Properties[56].p_wxPGProperty;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, s->m_general.m_infopage_map_width_mm);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 4);
    m_Properties.push_back(p);

    p.m_label = PRINT_HEIGHT;
    p.p_wxPGProperty_Parent = m_Properties[56].p_wxPGProperty;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, s->m_general.m_infopage_map_height_mm);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 4);
    m_Properties.push_back(p);
}

void C_wxPanelProperties::add_properties(void)
{
    for (auto prop : m_Properties)
        if (prop.p_wxPGProperty_Parent)
            prop.p_wxPGProperty = m_propertyGrid1->AppendIn(prop.p_wxPGProperty_Parent, prop.p_wxPGProperty);
        else
            prop.p_wxPGProperty = m_propertyGrid1->Append(prop.p_wxPGProperty);

    m_propertyGrid1->SetSplitterLeft(true);
}
