///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 13 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "C_wxActions.h"

///////////////////////////////////////////////////////////////////////////

C_wxActions::C_wxActions( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
    bSizer11 = new wxBoxSizer( wxVERTICAL );

    m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
    m_scrolledWindow1->SetScrollRate( 5, 5 );
    bSizer13 = new wxBoxSizer( wxVERTICAL );

    gbSizer3 = new wxGridBagSizer( 0, 0 );
    gbSizer3->SetFlexibleDirection( wxBOTH );
    gbSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

    m_BtnAssign = new wxButton( m_scrolledWindow1, wxID_ANY, wxT("zuweisen"), wxDefaultPosition, wxDefaultSize, 0 );
    gbSizer3->Add( m_BtnAssign, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

    m_datePicker = new wxDatePickerCtrl( m_scrolledWindow1, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_DROPDOWN );
    gbSizer3->Add( m_datePicker, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

    m_BtnUnassign = new wxButton( m_scrolledWindow1, wxID_ANY, wxT("Zuweisung aufheben"), wxDefaultPosition, wxDefaultSize, 0 );
    gbSizer3->Add( m_BtnUnassign, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

    m_BtnTransfer = new wxButton( m_scrolledWindow1, wxID_ANY, wxT("übertragen"), wxDefaultPosition, wxDefaultSize, 0 );
    gbSizer3->Add( m_BtnTransfer, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

    m_STComment = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Kommentar:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_STComment->Wrap( -1 );
    gbSizer3->Add( m_STComment, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_BOTTOM|wxLEFT, 5 );

    m_TCComment = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
    gbSizer3->Add( m_TCComment, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

    m_BtnProcessed = new wxButton( m_scrolledWindow1, wxID_ANY, wxT("bearbeitet"), wxDefaultPosition, wxDefaultSize, 0 );
    gbSizer3->Add( m_BtnProcessed, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

    m_BtnProcessedUnassign = new wxButton( m_scrolledWindow1, wxID_ANY, wxT("bearbeitet\n&&\nZuweisung aufheben"), wxDefaultPosition, wxDefaultSize, 0 );
    gbSizer3->Add( m_BtnProcessedUnassign, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

    m_GHistory = new wxGrid( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

    // Grid
    m_GHistory->CreateGrid( 1, 4 );
    m_GHistory->EnableEditing( false );
    m_GHistory->EnableGridLines( true );
    m_GHistory->EnableDragGridSize( false );
    m_GHistory->SetMargins( 0, 0 );

    // Columns
    m_GHistory->EnableDragColMove( false );
    m_GHistory->EnableDragColSize( true );
    m_GHistory->SetColLabelSize( 20 );
    m_GHistory->SetColLabelValue( 0, wxEmptyString );
    m_GHistory->SetColLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTER );

    // Rows
    m_GHistory->EnableDragRowSize( true );
    m_GHistory->SetRowLabelSize( 80 );
    m_GHistory->SetRowLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTER );

    // Label Appearance

    // Cell Defaults
    m_GHistory->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
    gbSizer3->Add( m_GHistory, wxGBPosition( 0, 2 ), wxGBSpan( 5, 1 ), wxALL|wxEXPAND|wxFIXED_MINSIZE, 5 );

    wxBoxSizer* bSizer4;
    bSizer4 = new wxBoxSizer( wxHORIZONTAL );

    m_button_Comment_CLR = new wxButton( m_scrolledWindow1, wxID_ANY, wxT("CLR"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    bSizer4->Add( m_button_Comment_CLR, 1, wxBOTTOM|wxLEFT|wxTOP, 5 );

    m_button_Comment_GDM = new wxButton( m_scrolledWindow1, wxID_ANY, wxT("GDM"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    bSizer4->Add( m_button_Comment_GDM, 1, wxBOTTOM|wxTOP, 5 );

    m_button_Comment_RKG = new wxButton( m_scrolledWindow1, wxID_ANY, wxT("RKG"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    bSizer4->Add( m_button_Comment_RKG, 1, wxBOTTOM|wxRIGHT|wxTOP, 5 );


    gbSizer3->Add( bSizer4, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

    m_CBAnnouncer = new wxComboBox( m_scrolledWindow1, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER );
    gbSizer3->Add( m_CBAnnouncer, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );


    gbSizer3->AddGrowableCol( 2 );

    bSizer13->Add( gbSizer3, 1, wxEXPAND, 5 );


    m_scrolledWindow1->SetSizer( bSizer13 );
    m_scrolledWindow1->Layout();
    bSizer13->Fit( m_scrolledWindow1 );
    bSizer11->Add( m_scrolledWindow1, 1, wxEXPAND, 5 );


    this->SetSizer( bSizer11 );
    this->Layout();

    // Connect Events
    m_BtnAssign->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnAssignClick ), NULL, this );
    m_BtnUnassign->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnUnassignClick ), NULL, this );
    m_BtnTransfer->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnTransferClick ), NULL, this );
    m_BtnProcessed->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnProcessedClick ), NULL, this );
    m_BtnProcessedUnassign->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnProcessedUnassignClick ), NULL, this );
    m_button_Comment_CLR->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnCommentCLR ), NULL, this );
    m_button_Comment_GDM->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnCommentGDM ), NULL, this );
    m_button_Comment_RKG->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnCommentRKG ), NULL, this );
}

C_wxActions::~C_wxActions()
{
    // Disconnect Events
    m_BtnAssign->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnAssignClick ), NULL, this );
    m_BtnUnassign->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnUnassignClick ), NULL, this );
    m_BtnTransfer->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnTransferClick ), NULL, this );
    m_BtnProcessed->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnProcessedClick ), NULL, this );
    m_BtnProcessedUnassign->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnProcessedUnassignClick ), NULL, this );
    m_button_Comment_CLR->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnCommentCLR ), NULL, this );
    m_button_Comment_GDM->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnCommentGDM ), NULL, this );
    m_button_Comment_RKG->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxActions::OnBtnCommentRKG ), NULL, this );

}

MyPanel2::MyPanel2( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxVERTICAL );

    m_CBAnnouncer = new wxComboBox( this, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER );
    bSizer3->Add( m_CBAnnouncer, 0, wxALL, 5 );


    this->SetSizer( bSizer3 );
    this->Layout();
}

MyPanel2::~MyPanel2()
{
}
