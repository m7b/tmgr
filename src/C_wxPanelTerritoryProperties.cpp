#include "C_wxPanelTerritoryProperties.h"

const wxString C_wxPanelTerritoryProperties::CATEGORY_TERRITORY_IDENTIFICATION = wxT("Identifikation");
const wxString C_wxPanelTerritoryProperties::TERRITORY_ID                      = wxT("Id");
const wxString C_wxPanelTerritoryProperties::TERRITORY_DESCRIPTION             = wxT("Bezeichnung");
const wxString C_wxPanelTerritoryProperties::TERRITORY_NUMBER                  = wxT("Nummer");
const wxString C_wxPanelTerritoryProperties::TERRITORY_NEW_NUMBER              = wxT("Neue Nummer");
const wxString C_wxPanelTerritoryProperties::CATEGORY_OWN_LANGUAGE             = wxT("Anzahl deutschsprachiger Familien");
const wxString C_wxPanelTerritoryProperties::OWN_LANGUAGE_AMOUNT               = wxT("Anzahl");
const wxString C_wxPanelTerritoryProperties::OWN_LANGUAGE_DATE                 = wxT("Datum der Zählung");
const wxString C_wxPanelTerritoryProperties::CATEGORY_MAP_CREATION             = wxT("Kartenerzeugung");
const wxString C_wxPanelTerritoryProperties::MAP_CREATION_DATE                 = wxT("Erzeugnisstand");
const wxString C_wxPanelTerritoryProperties::MAP_ORIENTATION                   = wxT("Orientierung");
const wxString C_wxPanelTerritoryProperties::MAP_SCALE                         = wxT("Scale");
const wxString C_wxPanelTerritoryProperties::MAP_CENTER_POSITION               = wxT("Center Position");
const wxString C_wxPanelTerritoryProperties::MAP_HEIGHT_MM                     = wxT("Höhe (mm)");
const wxString C_wxPanelTerritoryProperties::MAP_WIDTH_MM                      = wxT("Breite (mm)");
const wxString C_wxPanelTerritoryProperties::MAP_MRULE_FILE                    = wxT("mrule-Datei");
const wxString C_wxPanelTerritoryProperties::MAP_BORDER_FILE                   = wxT("border-Datei");


C_wxPanelTerritoryProperties::C_wxPanelTerritoryProperties( wxWindow* parent )
:
territory_property_panel(parent), C_DbHandle(0), s(nullptr), ad(nullptr)
{

}

void C_wxPanelTerritoryProperties::OnPropertyGridChanged( wxPropertyGridEvent& event )
{
    wxAny Bez            = m_propertyGrid->GetProperty(TERRITORY_DESCRIPTION)->GetValue();
    wxAny Nr             = m_propertyGrid->GetProperty(TERRITORY_NUMBER)->GetValue();
    wxAny NNr            = m_propertyGrid->GetProperty(TERRITORY_NEW_NUMBER)->GetValue();
    //TODO(mjb): Implement OnPropertyGridChanged for territories (Act)
    wxAny Act            = 0;
    wxAny WEinh          = m_propertyGrid->GetProperty(OWN_LANGUAGE_AMOUNT)->GetValue();
    wxVariant WEinh_Date = m_propertyGrid->GetProperty(OWN_LANGUAGE_DATE)->GetValue();
    wxVariant ErzStand   = m_propertyGrid->GetProperty(MAP_CREATION_DATE)->GetValue();

    wxAny orientation    = m_propertyGrid->GetProperty(MAP_ORIENTATION)->GetValue();
    wxAny scale          = m_propertyGrid->GetProperty(MAP_SCALE)->GetValue();
    wxAny center         = m_propertyGrid->GetProperty(MAP_CENTER_POSITION)->GetValue();
    wxAny height         = m_propertyGrid->GetProperty(MAP_HEIGHT_MM)->GetValue();
    wxAny width          = m_propertyGrid->GetProperty(MAP_WIDTH_MM)->GetValue();
    wxAny mrule          = m_propertyGrid->GetProperty(MAP_MRULE_FILE)->GetValue();
    wxAny border_file    = m_propertyGrid->GetProperty(MAP_BORDER_FILE)->GetValue();

    open_db();

    std::string query = "";
    query += "UPDATE tGebiet ";
    query += "SET ";
    query += "Nr = '"         + std::string(Nr.As<wxString>().ToUTF8())                        + "', ";
    query += "Bez = '"        + std::string(Bez.As<wxString>().ToUTF8())                       + "', ";
    query += "Act = '"        + std::to_string(Act.As<int>())                                  + "', ";
    query += "WEinh = '"      + std::to_string(WEinh.As<int>())                                + "', ";
    query += "WEinh_Date = '" + std::string(WEinh_Date.GetDateTime().FormatISODate().ToUTF8()) + "', ";
    query += "ErzStand = '"   + std::string(ErzStand.GetDateTime().FormatISODate().ToUTF8())   + "', ";
    query += "NNr = '"        + std::string(NNr.As<wxString>().ToUTF8())                       + "' ";
    query += "WHERE Id = "    + std::to_string(m_GebId);
    query += ";";

    query += "\n";
    query += "UPDATE tMaperitive ";
    query += "SET ";
    query += "mrule = '"         + std::string(mrule.As<wxString>().ToUTF8())       + "', ";
    query += "height = '"        + std::to_string(height.As<double>())              + "', ";
    query += "width = '"         + std::to_string(width.As<double>())               + "', ";
    query += "orientation = '"   + std::string(orientation.As<wxString>().ToUTF8()) + "', ";
    query += "center = '"        + std::string(center.As<wxString>().ToUTF8())      + "', ";
    query += "scale = '"         + std::to_string(scale.As<double>())               + "', ";
    query += "border_file = '"   + std::string(border_file.As<wxString>().ToUTF8()) + "' ";
    query += "WHERE GebietId = " + std::to_string(m_GebId);
    query += ";";

    exec_db(&query);
    close_no_finalize_db();

    post_element_updated();
}

void C_wxPanelTerritoryProperties::set_settings(C_Settings* settings, ApplicationData* appl_data)
{
    s = settings;
    ad = appl_data;
    set_db_file(&ad->db_file);

    prepare_properties();
    add_properties();

    m_propertyGrid->ExpandAll();
}

void C_wxPanelTerritoryProperties::prepare_properties(void)
{
    PropertyLine p;

    p.m_label = CATEGORY_TERRITORY_IDENTIFICATION;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxPropertyCategory(p.m_label);
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = TERRITORY_ID;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, 0);
    p.read_only = true;
    m_Properties.push_back(p);

    p.m_label = TERRITORY_DESCRIPTION;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, "");
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = TERRITORY_NUMBER;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, "");
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = TERRITORY_NEW_NUMBER;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, "");
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = CATEGORY_OWN_LANGUAGE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxPropertyCategory(p.m_label);
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = OWN_LANGUAGE_AMOUNT;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxIntProperty(p.m_label, wxPG_LABEL, 0);
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = OWN_LANGUAGE_DATE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxDateProperty(p.m_label, wxPG_LABEL);
    p.p_wxPGProperty->SetAttribute(wxPG_DATE_FORMAT, "%d.%m.%Y");
    p.p_wxPGProperty->SetAttribute(wxPG_DATE_PICKER_STYLE, wxDP_DROPDOWN|wxDP_SHOWCENTURY);
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = CATEGORY_MAP_CREATION;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxPropertyCategory(p.m_label);
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = MAP_CREATION_DATE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxDateProperty(p.m_label, wxPG_LABEL);
    p.p_wxPGProperty->SetAttribute(wxPG_DATE_FORMAT, "%d.%m.%Y");
    p.p_wxPGProperty->SetAttribute(wxPG_DATE_PICKER_STYLE, wxDP_DROPDOWN|wxDP_SHOWCENTURY);
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = MAP_ORIENTATION;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, "");
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = MAP_SCALE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, 0.0);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 4);
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = MAP_CENTER_POSITION;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxStringProperty(p.m_label, wxPG_LABEL, "");
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = MAP_HEIGHT_MM;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, 0.0);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 2);
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = MAP_WIDTH_MM;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFloatProperty(p.m_label, wxPG_LABEL, 0.0);
    p.p_wxPGProperty->SetAttribute(wxPG_FLOAT_PRECISION, 2);
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = MAP_MRULE_FILE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFileProperty(p.m_label, wxPG_LABEL, "");
    p.p_wxPGProperty->SetAttribute(wxPG_FILE_WILDCARD, "mrules-File (*.mrules)|*.mrules");
    p.read_only = false;
    m_Properties.push_back(p);

    p.m_label = MAP_BORDER_FILE;
    p.p_wxPGProperty_Parent = nullptr;
    p.p_wxPGProperty = new wxFileProperty(p.m_label, wxPG_LABEL, "");
    p.p_wxPGProperty->SetAttribute(wxPG_FILE_WILDCARD, "SVG-File (*.svg)|*.svg");
    p.read_only = false;
    m_Properties.push_back(p);
}

void C_wxPanelTerritoryProperties::add_properties(void)
{
    for (auto prop : m_Properties)
    {
        if (prop.p_wxPGProperty_Parent)
            prop.p_wxPGProperty = m_propertyGrid->AppendIn(prop.p_wxPGProperty_Parent, prop.p_wxPGProperty);
        else
            prop.p_wxPGProperty = m_propertyGrid->Append(prop.p_wxPGProperty);

        //Set PropertyGridItem to ReadOnly
        if (prop.read_only)
            m_propertyGrid->SetPropertyReadOnly(prop.p_wxPGProperty, true);
    }

    m_propertyGrid->SetSplitterLeft(true);
}

void C_wxPanelTerritoryProperties::show(int geb_id)
{
    m_GebId = geb_id;

    int rc;

    rc = open_db();

    std::string query = "";
    query += "SELECT Id, Nr, Bez, NNr, WEinh, WEinh_Date, ErzStand ";
    query += "FROM tGebiet ";
    query += "WHERE Id=" + std::to_string(m_GebId);

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            m_propertyGrid->GetProperty(TERRITORY_ID)->SetValueFromInt(get_int(COL_0));
            m_propertyGrid->GetProperty(TERRITORY_NUMBER)->SetValueFromString(wxString::FromUTF8(safe_wx_str(get_text(COL_1))));
            m_propertyGrid->GetProperty(TERRITORY_DESCRIPTION)->SetValueFromString(wxString::FromUTF8(safe_wx_str(get_text(COL_2))));
            m_propertyGrid->GetProperty(TERRITORY_NEW_NUMBER)->SetValueFromString(wxString::FromUTF8(safe_wx_str(get_text(COL_3))));
            m_propertyGrid->GetProperty(OWN_LANGUAGE_AMOUNT)->SetValueFromInt(get_int(COL_4));
            if (get_text(COL_5).size())
            {
                std::string col_val = get_text(COL_5);
                m_propertyGrid->GetProperty(OWN_LANGUAGE_DATE)->SetValue(get_text(COL_5));
            }
            else
                m_propertyGrid->GetProperty(OWN_LANGUAGE_DATE)->SetValueToUnspecified();

            if (get_text(COL_6).size())
                m_propertyGrid->GetProperty(MAP_CREATION_DATE)->SetValue(get_text(COL_6));
            else
                m_propertyGrid->GetProperty(MAP_CREATION_DATE)->SetValueToUnspecified();
        }

        if(done_or_error(rc))
            break;
    }



    query = "";
    query += "SELECT orientation, scale, center, height, width ,mrule, border_file ";
    query += "FROM tMaperitive ";
    query += "WHERE GebietId=" + std::to_string(m_GebId);

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            m_propertyGrid->GetProperty(MAP_ORIENTATION)->SetValueFromString(wxString::FromUTF8(safe_wx_str(get_text(COL_0))));
            m_propertyGrid->GetProperty(MAP_SCALE)->SetValueFromString(wxString::FromUTF8(safe_wx_str(get_text(COL_1))));
            m_propertyGrid->GetProperty(MAP_CENTER_POSITION)->SetValueFromString(wxString::FromUTF8(safe_wx_str(get_text(COL_2))));
            m_propertyGrid->GetProperty(MAP_HEIGHT_MM)->SetValueFromString(wxString::FromUTF8(safe_wx_str(get_text(COL_3))));
            m_propertyGrid->GetProperty(MAP_WIDTH_MM)->SetValueFromString(wxString::FromUTF8(safe_wx_str(get_text(COL_4))));
            m_propertyGrid->GetProperty(MAP_MRULE_FILE)->SetValueFromString(wxString::FromUTF8(safe_wx_str(get_text(COL_5))));
            m_propertyGrid->GetProperty(MAP_BORDER_FILE)->SetValueFromString(wxString::FromUTF8(safe_wx_str(get_text(COL_6))));
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();

    m_propertyGrid->SetSplitterLeft(true);
}

bool C_wxPanelTerritoryProperties::SetFont(const wxFont &font)
{
    m_propertyGrid->SetFont(font);
    return true;
}

void C_wxPanelTerritoryProperties::post_element_updated(void)
{
    MyFooEvent e(EVT_ELEMENT_PROP_UPDATED);
    C_wxScrolledWindowCat::Element el;
    el.geb_id = m_GebId;
    e.SetElement(el);
    wxPostEvent(this, e); // to ourselves
}
