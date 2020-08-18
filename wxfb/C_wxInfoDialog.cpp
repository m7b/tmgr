///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "C_wxInfoDialog.h"

///////////////////////////////////////////////////////////////////////////

InfoDialog::InfoDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
    this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );

    m_bSizer = new wxBoxSizer( wxVERTICAL );

    m_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxVERTICAL );

    m_gbSizer = new wxGridBagSizer( 0, 0 );
    m_gbSizer->SetFlexibleDirection( wxBOTH );
    m_gbSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

    m_bitmap = new wxStaticBitmap( m_panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
    m_gbSizer->Add( m_bitmap, wxGBPosition( 0, 0 ), wxGBSpan( 2, 1 ), wxALL|wxEXPAND, 5 );

    m_staticTextName = new wxStaticText( m_panel, wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextName->Wrap( -1 );
    m_staticTextName->SetFont( wxFont( 16, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Times New Roman") ) );

    m_gbSizer->Add( m_staticTextName, wxGBPosition( 0, 1 ), wxGBSpan( 1, 3 ), wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );

    m_staticTextFileDescription = new wxStaticText( m_panel, wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextFileDescription->Wrap( -1 );
    m_staticTextFileDescription->SetFont( wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );

    m_gbSizer->Add( m_staticTextFileDescription, wxGBPosition( 2, 2 ), wxGBSpan( 1, 2 ), wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxTOP, 5 );

    m_staticTextAuthor = new wxStaticText( m_panel, wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextAuthor->Wrap( -1 );
    m_staticTextAuthor->SetFont( wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );

    m_gbSizer->Add( m_staticTextAuthor, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP, 5 );

    m_button1 = new wxButton( m_panel, wxID_ANY, _("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
    m_gbSizer->Add( m_button1, wxGBPosition( 5, 0 ), wxGBSpan( 1, 4 ), wxALIGN_CENTER|wxALL, 5 );

    m_auinotebook1 = new wxAuiNotebook( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
    m_panel2 = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxVERTICAL );

    m_richTextDescription = new wxRichTextCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxWANTS_CHARS|wxBORDER_NONE );
    bSizer3->Add( m_richTextDescription, 1, wxEXPAND | wxALL, 5 );


    m_panel2->SetSizer( bSizer3 );
    m_panel2->Layout();
    bSizer3->Fit( m_panel2 );
    m_auinotebook1->AddPage( m_panel2, _("Description"), true, wxNullBitmap );
    m_panel3 = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer4;
    bSizer4 = new wxBoxSizer( wxVERTICAL );

    m_richTextInfo = new wxRichTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxWANTS_CHARS|wxBORDER_NONE );
    bSizer4->Add( m_richTextInfo, 1, wxEXPAND | wxALL, 5 );


    m_panel3->SetSizer( bSizer4 );
    m_panel3->Layout();
    bSizer4->Fit( m_panel3 );
    m_auinotebook1->AddPage( m_panel3, _("Info"), false, wxNullBitmap );
    m_panel4 = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer5;
    bSizer5 = new wxBoxSizer( wxVERTICAL );

    m_htmlWinChangelog = new wxHtmlWindow( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
    bSizer5->Add( m_htmlWinChangelog, 1, wxALL|wxEXPAND, 5 );


    m_panel4->SetSizer( bSizer5 );
    m_panel4->Layout();
    bSizer5->Fit( m_panel4 );
    m_auinotebook1->AddPage( m_panel4, _("Changelog"), false, wxNullBitmap );
    m_panel5 = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer6;
    bSizer6 = new wxBoxSizer( wxVERTICAL );

    m_richTextSVNLog = new wxRichTextCtrl( m_panel5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxWANTS_CHARS|wxBORDER_NONE );
    bSizer6->Add( m_richTextSVNLog, 1, wxEXPAND | wxALL, 5 );


    m_panel5->SetSizer( bSizer6 );
    m_panel5->Layout();
    bSizer6->Fit( m_panel5 );
    m_auinotebook1->AddPage( m_panel5, _("SVN Log"), false, wxNullBitmap );
    m_panel6 = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer7;
    bSizer7 = new wxBoxSizer( wxVERTICAL );

    m_htmlWinToolchain = new wxHtmlWindow( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
    bSizer7->Add( m_htmlWinToolchain, 1, wxALL|wxEXPAND, 5 );


    m_panel6->SetSizer( bSizer7 );
    m_panel6->Layout();
    bSizer7->Fit( m_panel6 );
    m_auinotebook1->AddPage( m_panel6, _("Toolchain"), false, wxNullBitmap );

    m_gbSizer->Add( m_auinotebook1, wxGBPosition( 4, 0 ), wxGBSpan( 1, 4 ), wxALL|wxEXPAND, 5 );

    m_staticTextFileVersion = new wxStaticText( m_panel, wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextFileVersion->Wrap( -1 );
    m_gbSizer->Add( m_staticTextFileVersion, wxGBPosition( 1, 1 ), wxGBSpan( 1, 3 ), wxBOTTOM|wxLEFT|wxRIGHT, 5 );

    m_staticline1 = new wxStaticLine( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    m_gbSizer->Add( m_staticline1, wxGBPosition( 3, 0 ), wxGBSpan( 1, 4 ), wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );


    m_gbSizer->AddGrowableCol( 0 );
    m_gbSizer->AddGrowableCol( 1 );
    m_gbSizer->AddGrowableCol( 2 );
    m_gbSizer->AddGrowableCol( 3 );
    m_gbSizer->AddGrowableRow( 4 );

    bSizer2->Add( m_gbSizer, 1, wxEXPAND, 5 );


    m_panel->SetSizer( bSizer2 );
    m_panel->Layout();
    bSizer2->Fit( m_panel );
    m_bSizer->Add( m_panel, 1, wxEXPAND | wxALL, 5 );


    this->SetSizer( m_bSizer );
    this->Layout();

    this->Centre( wxBOTH );

    // Connect Events
    m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InfoDialog::OnOk ), NULL, this );
    m_htmlWinChangelog->Connect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( InfoDialog::OnHtmlLinkClickedChangelog ), NULL, this );
    m_htmlWinToolchain->Connect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( InfoDialog::OnHtmlLinkClickedChangelog ), NULL, this );
}

InfoDialog::~InfoDialog()
{
    // Disconnect Events
    m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InfoDialog::OnOk ), NULL, this );
    m_htmlWinChangelog->Disconnect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( InfoDialog::OnHtmlLinkClickedChangelog ), NULL, this );
    m_htmlWinToolchain->Disconnect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( InfoDialog::OnHtmlLinkClickedChangelog ), NULL, this );

}
