#ifndef __C_wxPanelTerritoryProperties__
#define __C_wxPanelTerritoryProperties__

/**
@file
Subclass of territory_property_panel, which is generated by wxFormBuilder.
*/
#include <wx/datectrl.h>

#include "C_wxTerritoryProperties.h"
#include "C_Settings.h"
#include "appl_data.h"
#include "C_wxScrolledWindowCat.h"
#include "C_DbHandle.h"

#include "safe_wx_str.h"

//// end generated include

wxDECLARE_EVENT(EVT_ELEMENT_PROP_UPDATED, MyFooEvent);

/** Implementing territory_property_panel */
class C_wxPanelTerritoryProperties : public territory_property_panel, C_DbHandle
{
    public:
        /** Constructor */
        C_wxPanelTerritoryProperties( wxWindow* parent );
    //// end generated class members
        void set_settings(C_Settings* settings, ApplicationData* appl_data);
        void show(int geb_id);
        bool SetFont(const wxFont &font);

    protected:
        void OnPropertyGridChanged(wxPropertyGridEvent& event);

    private:
        struct PropertyLine
        {
            wxString m_label;
            wxPGProperty *p_wxPGProperty_Parent;
            wxPGProperty *p_wxPGProperty;
            bool read_only;
        };

        C_Settings *s;
        ApplicationData *ad;
        int m_GebId;

        std::vector<PropertyLine> m_Properties;

        void prepare_properties(void);
        void add_properties(void);

        void post_element_updated(void);

        static const wxString CATEGORY_TERRITORY_IDENTIFICATION;
        static const wxString TERRITORY_ID;
        static const wxString TERRITORY_DESCRIPTION;
        static const wxString TERRITORY_NUMBER;
        static const wxString TERRITORY_NEW_NUMBER;

        static const wxString CATEGORY_OWN_LANGUAGE;
        static const wxString OWN_LANGUAGE_AMOUNT;
        static const wxString OWN_LANGUAGE_DATE;

        static const wxString CATEGORY_MAP_CREATION;
        static const wxString MAP_CREATION_DATE;
        static const wxString MAP_ORIENTATION;
        static const wxString MAP_SCALE;
        static const wxString MAP_CENTER_POSITION;
        static const wxString MAP_HEIGHT_MM;
        static const wxString MAP_WIDTH_MM;
        static const wxString MAP_MRULE_FILE;
        static const wxString MAP_BORDER_FILE;
};

#endif // __C_wxPanelTerritoryProperties__
