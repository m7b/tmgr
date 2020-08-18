///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "C_wxProperties.h"

///////////////////////////////////////////////////////////////////////////

property_panel::property_panel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxVERTICAL );

    m_propertyGrid1 = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_BOLD_MODIFIED|wxPG_DEFAULT_STYLE|wxPG_SPLITTER_AUTO_CENTER);
    bSizer3->Add( m_propertyGrid1, 1, wxALL|wxEXPAND, 5 );


    this->SetSizer( bSizer3 );
    this->Layout();
    bSizer3->Fit( this );

    // Connect Events
    m_propertyGrid1->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( property_panel::OnPropertyGridChanged ), NULL, this );
}

property_panel::~property_panel()
{
    // Disconnect Events
    m_propertyGrid1->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( property_panel::OnPropertyGridChanged ), NULL, this );

}
