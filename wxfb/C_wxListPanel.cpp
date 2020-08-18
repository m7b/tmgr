///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "C_wxListPanel.h"

///////////////////////////////////////////////////////////////////////////

C_wxDataListPanel::C_wxDataListPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxHORIZONTAL );

    m_dataViewListCtrl = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
    m_dataViewListColumn = m_dataViewListCtrl->AppendTextColumn( wxT("Id"), wxDATAVIEW_CELL_INERT, 50, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE );
    bSizer3->Add( m_dataViewListCtrl, 1, wxALL|wxEXPAND, 5 );

    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxVERTICAL );

    m_button_add = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxSize( 40,40 ), wxBU_NOTEXT );

    m_button_add->SetBitmap( wxArtProvider::GetBitmap( wxART_PLUS, wxART_BUTTON ) );
    bSizer2->Add( m_button_add, 0, wxALL, 5 );

    m_button_remove = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxSize( 40,40 ), wxBU_NOTEXT );

    m_button_remove->SetBitmap( wxArtProvider::GetBitmap( wxART_MINUS, wxART_BUTTON ) );
    bSizer2->Add( m_button_remove, 0, wxALL, 5 );


    bSizer3->Add( bSizer2, 0, wxEXPAND, 5 );


    this->SetSizer( bSizer3 );
    this->Layout();

    // Connect Events
    m_dataViewListCtrl->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_EDITING_DONE, wxDataViewEventHandler( C_wxDataListPanel::OnEditingDone ), NULL, this );
    m_button_add->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxDataListPanel::OnClickAdd ), NULL, this );
    m_button_remove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxDataListPanel::OnClickRemove ), NULL, this );
}

C_wxDataListPanel::~C_wxDataListPanel()
{
    // Disconnect Events
    m_dataViewListCtrl->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_EDITING_DONE, wxDataViewEventHandler( C_wxDataListPanel::OnEditingDone ), NULL, this );
    m_button_add->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxDataListPanel::OnClickAdd ), NULL, this );
    m_button_remove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxDataListPanel::OnClickRemove ), NULL, this );

}
