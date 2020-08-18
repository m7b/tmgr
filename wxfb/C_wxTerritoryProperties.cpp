///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "C_wxTerritoryProperties.h"

///////////////////////////////////////////////////////////////////////////

territory_property_panel::territory_property_panel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer( wxVERTICAL );

    m_propertyGrid = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_BOLD_MODIFIED|wxPG_DEFAULT_STYLE|wxPG_SPLITTER_AUTO_CENTER);
    bSizer->Add( m_propertyGrid, 1, wxALL|wxEXPAND, 5 );


    this->SetSizer( bSizer );
    this->Layout();

    // Connect Events
    m_propertyGrid->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( territory_property_panel::OnPropertyGridChanged ), NULL, this );
}

territory_property_panel::~territory_property_panel()
{
    // Disconnect Events
    m_propertyGrid->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( territory_property_panel::OnPropertyGridChanged ), NULL, this );

}
