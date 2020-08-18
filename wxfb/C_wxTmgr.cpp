///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "C_wxTmgr.h"

///////////////////////////////////////////////////////////////////////////

C_wxTmgr::C_wxTmgr( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : C_wxDecorator( parent, id, title, pos, size, style )
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
    m_mgr.SetManagedWindow(this);
    m_mgr.SetFlags(wxAUI_MGR_DEFAULT|wxAUI_MGR_LIVE_RESIZE);

    m_panel41 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_mgr.AddPane( m_panel41, wxAuiPaneInfo() .Name( wxT("MenuPanel") ).Top() .CaptionVisible( false ).PinButton( true ).Movable( false ).Dock().Fixed().MinSize( wxSize( -1,65 ) ) );

    bSizer36 = new wxBoxSizer( wxHORIZONTAL );

    m_gSizer1 = new wxGridSizer( 0, 4, 0, 0 );

    m_bpButton1 = new wxBitmapButton( m_panel41, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 65,65 ), wxBU_AUTODRAW|0 );

    m_bpButton1->SetBitmap( wxArtProvider::GetBitmap( wxART_UNDO, wxART_OTHER ) );
    m_gSizer1->Add( m_bpButton1, 0, 0, 5 );

    m_bpButton2 = new wxBitmapButton( m_panel41, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 65,65 ), wxBU_AUTODRAW|0 );

    m_bpButton2->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_OTHER ) );
    m_gSizer1->Add( m_bpButton2, 0, 0, 5 );

    m_bpButton3 = new wxBitmapButton( m_panel41, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 65,65 ), wxBU_AUTODRAW|0 );

    m_bpButton3->SetBitmap( wxArtProvider::GetBitmap( wxART_GO_HOME, wxART_OTHER ) );
    m_gSizer1->Add( m_bpButton3, 0, 0, 5 );

    m_bpButton4 = new wxBitmapButton( m_panel41, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 65,65 ), wxBU_AUTODRAW|0 );

    m_bpButton4->SetBitmap( wxArtProvider::GetBitmap( wxART_INFORMATION, wxART_OTHER ) );
    m_gSizer1->Add( m_bpButton4, 0, 0, 5 );


    bSizer36->Add( m_gSizer1, 0, 0, 5 );


    m_panel41->SetSizer( bSizer36 );
    m_panel41->Layout();
    bSizer36->Fit( m_panel41 );
    m_auinbOperatings = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_BOTTOM|wxAUI_NB_SCROLL_BUTTONS|wxAUI_NB_WINDOWLIST_BUTTON );
    m_auinbOperatings->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

    m_mgr.AddPane( m_auinbOperatings, wxAuiPaneInfo() .Name( wxT("OperatingPanel") ).Center() .CaptionVisible( false ).CloseButton( false ).PinButton( true ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ) );

    m_PanelStatistic = new wxPanel( m_auinbOperatings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_bSizerScrollWinReports = new wxBoxSizer( wxHORIZONTAL );

    bSizer21 = new wxBoxSizer( wxVERTICAL );

    m_pgStatistic = new wxPropertyGrid(m_PanelStatistic, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxPG_DEFAULT_STYLE|wxPG_SPLITTER_AUTO_CENTER);
    m_pgiIntAmountTerritories = m_pgStatistic->Append( new wxIntProperty( wxT("Gesamtzahl Gebiete"), wxT("Gesamtzahl Gebiete") ) );
    m_pgiCategoryAssigned = m_pgStatistic->Append( new wxPropertyCategory( wxT("In Bearbeitung"), wxT("In Bearbeitung") ) );
    m_pgiIntAssignedTerritories = m_pgStatistic->Append( new wxIntProperty( wxT("Gebiete in Bearbeitung"), wxT("Gebiete in Bearbeitung") ) );
    m_pgiIntAssignedDuration0 = m_pgStatistic->Append( new wxIntProperty( wxT("├► über 4 Jahre gleiche Zuteilung"), wxT("├► über 4 Jahre gleiche Zuteilung") ) );
    m_pgiIntAssignedDuration1 = m_pgStatistic->Append( new wxIntProperty( wxT("├► über 3 Jahre gleiche Zuteilung"), wxT("├► über 3 Jahre gleiche Zuteilung") ) );
    m_pgiIntAssignedDuration2 = m_pgStatistic->Append( new wxIntProperty( wxT("└► über 2 Jahre gleiche Zuteilung"), wxT("└► über 2 Jahre gleiche Zuteilung") ) );
    m_pgiCategoryUnassigned = m_pgStatistic->Append( new wxPropertyCategory( wxT("Nicht in Bearbeitung"), wxT("Nicht in Bearbeitung") ) );
    m_pgiIntUnassignedTerritories = m_pgStatistic->Append( new wxIntProperty( wxT("Nicht zugeteilte Gebiete"), wxT("Nicht zugeteilte Gebiete") ) );
    m_pgiIntLastWorked = m_pgStatistic->Append( new wxIntProperty( wxT("├► davon seit letztem Dienstjahr (vor Sep. 2015)"), wxT("├► davon seit letztem Dienstjahr (vor Sep. 2015)") ) );
    m_pgiIntLastWorked0 = m_pgStatistic->Append( new wxIntProperty( wxT("├► davon seit letztem Dienstjahr (vor Sep. 2016)"), wxT("├► davon seit letztem Dienstjahr (vor Sep. 2016)") ) );
    m_pgiIntLastWorked1 = m_pgStatistic->Append( new wxIntProperty( wxT("└► davon seit letztem Jahr (vor Jan. 2016)"), wxT("└► davon seit letztem Jahr (vor Jan. 2016)") ) );
    bSizer21->Add( m_pgStatistic, 1, wxALL|wxEXPAND, 5 );


    m_bSizerScrollWinReports->Add( bSizer21, 2, wxEXPAND, 5 );

    bSizer20 = new wxBoxSizer( wxVERTICAL );

    bSizer20->SetMinSize( wxSize( 250,-1 ) );
    m_scrolledWindow3 = new wxScrolledWindow( m_PanelStatistic, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxHSCROLL|wxVSCROLL );
    m_scrolledWindow3->SetScrollRate( 5, 5 );
    m_bSizerReports = new wxBoxSizer( wxVERTICAL );

    m_staticTextReport = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Berichtserstellung:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextReport->Wrap( -1 );
    m_bSizerReports->Add( m_staticTextReport, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, 5 );

    m_StaticLineReport = new wxStaticLine( m_scrolledWindow3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    m_bSizerReports->Add( m_StaticLineReport, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, 5 );

    m_BtnRepOverview = new wxButton( m_scrolledWindow3, wxID_LATEX_REP_OVERVIEW, wxT("Zuteilungskarte"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerReports->Add( m_BtnRepOverview, 0, wxALL|wxEXPAND, 5 );

    m_BtnRepNoVisits = new wxButton( m_scrolledWindow3, wxID_LATEX_REP_NOVISITS, wxT("Nichtbesuche"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerReports->Add( m_BtnRepNoVisits, 0, wxALL|wxEXPAND, 5 );

    m_BtnRepNotAssigned = new wxButton( m_scrolledWindow3, wxID_LATEX_REP_NOT_ASSIGNED, wxT("Nicht zugeteilt"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerReports->Add( m_BtnRepNotAssigned, 0, wxALL|wxEXPAND, 5 );

    m_BtnRepAssigned = new wxButton( m_scrolledWindow3, wxID_LATEX_REP_ASSIGNED, wxT("Zugeteilt"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerReports->Add( m_BtnRepAssigned, 0, wxALL|wxEXPAND, 5 );

    m_BtnAssignmentDuration = new wxButton( m_scrolledWindow3, wxID_LATEX_REP_ASSIGNMENT_DURATION, wxT("Zuteilungsdauer"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerReports->Add( m_BtnAssignmentDuration, 0, wxALL|wxEXPAND, 5 );

    m_staticTextMaps = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Gebietskarten:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticTextMaps->Wrap( -1 );
    m_bSizerReports->Add( m_staticTextMaps, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, 5 );

    m_staticline2 = new wxStaticLine( m_scrolledWindow3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    m_bSizerReports->Add( m_staticline2, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, 5 );

    m_BtnRepCreateSet = new wxButton( m_scrolledWindow3, wxID_MAP_REP_CREATE_SET, wxT("Set erstellen"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerReports->Add( m_BtnRepCreateSet, 0, wxALL|wxEXPAND, 5 );

    m_BtnRepPrintoutSet = new wxButton( m_scrolledWindow3, wxID_MAP_REP_PRINTOUT_SET, wxT("Set Druckvorlage"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerReports->Add( m_BtnRepPrintoutSet, 0, wxALL|wxEXPAND, 5 );


    m_scrolledWindow3->SetSizer( m_bSizerReports );
    m_scrolledWindow3->Layout();
    m_bSizerReports->Fit( m_scrolledWindow3 );
    bSizer20->Add( m_scrolledWindow3, 1, wxEXPAND, 5 );


    m_bSizerScrollWinReports->Add( bSizer20, 1, wxEXPAND, 5 );


    m_PanelStatistic->SetSizer( m_bSizerScrollWinReports );
    m_PanelStatistic->Layout();
    m_bSizerScrollWinReports->Fit( m_PanelStatistic );
    m_auinbOperatings->AddPage( m_PanelStatistic, wxT("Statistik"), true, wxNullBitmap );
    m_PanelCard = new wxPanel( m_auinbOperatings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_SizerCard = new wxBoxSizer( wxVERTICAL );

    m_bSizerCardActions = new wxBoxSizer( wxHORIZONTAL );

    m_btnRenderCard = new wxButton( m_PanelCard, wxID_CARD_RENDER, wxT("Karte neu generieren"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerCardActions->Add( m_btnRenderCard, 1, 0, 5 );

    m_btnPrintInlet = new wxButton( m_PanelCard, wxID_LATEX_REP_INLET, wxT("Inlet drucken"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerCardActions->Add( m_btnPrintInlet, 1, 0, 5 );

    m_btnPrintInfopage = new wxButton( m_PanelCard, wxID_LATEX_REP_INFOPAGE, wxT("Infoseite drucken"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerCardActions->Add( m_btnPrintInfopage, 1, 0, 5 );

    m_btnPrintBooklet = new wxButton( m_PanelCard, wxID_LATEX_REP_BOOKLET, wxT("Booklet drucken"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bSizerCardActions->Add( m_btnPrintBooklet, 1, 0, 5 );


    m_SizerCard->Add( m_bSizerCardActions, 0, wxEXPAND, 5 );

    m_CardWindow = new C_wxScrolledImageComponent(m_PanelCard, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB);
    m_CardWindow->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
    m_CardWindow->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVECAPTION ) );

    m_SizerCard->Add( m_CardWindow, 1, wxEXPAND, 5 );


    m_PanelCard->SetSizer( m_SizerCard );
    m_PanelCard->Layout();
    m_SizerCard->Fit( m_PanelCard );
    m_auinbOperatings->AddPage( m_PanelCard, wxT("Karte"), false, wxNullBitmap );
    m_PanelActions = new wxPanel( m_auinbOperatings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_SizerActions = new wxBoxSizer( wxHORIZONTAL );

    m_Actions = new C_wxPanelActions(m_PanelActions);
    m_SizerActions->Add( m_Actions, 1, wxALL|wxEXPAND, 5 );


    m_PanelActions->SetSizer( m_SizerActions );
    m_PanelActions->Layout();
    m_SizerActions->Fit( m_PanelActions );
    m_auinbOperatings->AddPage( m_PanelActions, wxT("Aktionen"), false, wxNullBitmap );
    m_PanelProperties = new wxPanel( m_auinbOperatings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_SizerProperties = new wxBoxSizer( wxVERTICAL );

    m_TerritoryProperties = new C_wxPanelTerritoryProperties(m_PanelProperties);
    m_SizerProperties->Add( m_TerritoryProperties, 1, wxALL|wxEXPAND, 5 );


    m_PanelProperties->SetSizer( m_SizerProperties );
    m_PanelProperties->Layout();
    m_SizerProperties->Fit( m_PanelProperties );
    m_auinbOperatings->AddPage( m_PanelProperties, wxT("Eigenschaft"), false, wxNullBitmap );
    m_PanelNoVisits = new wxPanel( m_auinbOperatings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_SizerNoVisits = new wxBoxSizer( wxHORIZONTAL );

    m_NoVisits = new C_wxDataListPanel_NoVisits(m_PanelNoVisits);
    m_SizerNoVisits->Add( m_NoVisits, 1, wxALL|wxEXPAND, 5 );


    m_PanelNoVisits->SetSizer( m_SizerNoVisits );
    m_PanelNoVisits->Layout();
    m_SizerNoVisits->Fit( m_PanelNoVisits );
    m_auinbOperatings->AddPage( m_PanelNoVisits, wxT("Nichtbesuche"), false, wxNullBitmap );
    m_PanelTips = new wxPanel( m_auinbOperatings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_SizerTips = new wxBoxSizer( wxHORIZONTAL );

    m_Tips = new C_wxDataListPanel_Tips(m_PanelTips);
    m_SizerTips->Add( m_Tips, 1, wxALL|wxEXPAND, 5 );


    m_PanelTips->SetSizer( m_SizerTips );
    m_PanelTips->Layout();
    m_SizerTips->Fit( m_PanelTips );
    m_auinbOperatings->AddPage( m_PanelTips, wxT("Zusatzhinweise"), false, wxNullBitmap );
    m_PanelApplSettings = new wxPanel( m_auinbOperatings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    bSizer17 = new wxBoxSizer( wxHORIZONTAL );

    bSizer18 = new wxBoxSizer( wxVERTICAL );

    m_ApplSettings = new C_wxPanelProperties(m_PanelApplSettings);
    bSizer18->Add( m_ApplSettings, 1, wxALL|wxEXPAND, 5 );


    bSizer17->Add( bSizer18, 2, wxEXPAND, 5 );

    bSizer19 = new wxBoxSizer( wxVERTICAL );

    m_swApplActions = new wxScrolledWindow( m_PanelApplSettings, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxHSCROLL|wxVSCROLL );
    m_swApplActions->SetScrollRate( 5, 5 );
    m_bsApplActions = new wxBoxSizer( wxVERTICAL );

    m_BtnDownloadOsmData = new wxButton( m_swApplActions, wxID_MAPERITIVE_DL_OSM_DATA, wxT("Download\nOSM Daten"), wxDefaultPosition, wxDefaultSize, 0 );
    m_bsApplActions->Add( m_BtnDownloadOsmData, 0, wxALL|wxEXPAND, 5 );


    m_swApplActions->SetSizer( m_bsApplActions );
    m_swApplActions->Layout();
    m_bsApplActions->Fit( m_swApplActions );
    bSizer19->Add( m_swApplActions, 1, wxEXPAND, 5 );


    bSizer17->Add( bSizer19, 1, wxEXPAND, 5 );


    m_PanelApplSettings->SetSizer( bSizer17 );
    m_PanelApplSettings->Layout();
    bSizer17->Fit( m_PanelApplSettings );
    m_auinbOperatings->AddPage( m_PanelApplSettings, wxT("tMGR Einstellungen"), false, wxNullBitmap );
    m_PanelConsoleOutputs = new wxPanel( m_auinbOperatings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_SizerConsoleOutputs = new wxBoxSizer( wxVERTICAL );

    m_ConsoleOutputsTextCtrl = new wxTextCtrl( m_PanelConsoleOutputs, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE|wxTE_READONLY );
    m_SizerConsoleOutputs->Add( m_ConsoleOutputsTextCtrl, 1, wxALL|wxEXPAND, 5 );


    m_PanelConsoleOutputs->SetSizer( m_SizerConsoleOutputs );
    m_PanelConsoleOutputs->Layout();
    m_SizerConsoleOutputs->Fit( m_PanelConsoleOutputs );
    m_auinbOperatings->AddPage( m_PanelConsoleOutputs, wxT("Console Outputs"), false, wxNullBitmap );

    m_CategoryPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_mgr.AddPane( m_CategoryPanel, wxAuiPaneInfo() .Name( wxT("CategoryPanel") ).Center() .CaptionVisible( false ).PinButton( true ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ) );

    m_CategoryPanelSizer = new wxBoxSizer( wxVERTICAL );

    m_CategoryChoiceSizer = new wxBoxSizer( wxHORIZONTAL );

    wxArrayString m_ChoiceCategoryViewChoices;
    m_ChoiceCategoryView = new wxChoice( m_CategoryPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_ChoiceCategoryViewChoices, 0 );
    m_ChoiceCategoryView->SetSelection( 0 );
    m_CategoryChoiceSizer->Add( m_ChoiceCategoryView, 1, wxALL, 5 );


    m_CategoryPanelSizer->Add( m_CategoryChoiceSizer, 0, wxEXPAND, 5 );

    m_CategoryWindow = new C_wxScrolledWindowCat(m_CategoryPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    m_CategoryWindow->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
    m_CategoryWindow->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVECAPTION ) );

    m_CategoryPanelSizer->Add( m_CategoryWindow, 1, wxALL|wxEXPAND, 5 );


    m_CategoryPanel->SetSizer( m_CategoryPanelSizer );
    m_CategoryPanel->Layout();
    m_CategoryPanelSizer->Fit( m_CategoryPanel );
    m_statusBar = this->CreateStatusBar( 1, 0, wxID_ANY );

    m_mgr.Update();
    this->Centre( wxBOTH );

    // Connect Events
    this->Connect( wxEVT_SIZE, wxSizeEventHandler( C_wxTmgr::OntMGRResize ) );
    m_bpButton1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnClose ), NULL, this );
    m_bpButton2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnOpenDb ), NULL, this );
    m_bpButton3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnSetAssignee ), NULL, this );
    m_bpButton4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnAbout ), NULL, this );
    m_BtnRepOverview->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnRepNoVisits->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnRepNotAssigned->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnRepAssigned->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnAssignmentDuration->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnRepCreateSet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnRepPrintoutSet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_btnRenderCard->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_btnPrintInlet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_btnPrintInfopage->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_btnPrintBooklet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnDownloadOsmData->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_CategoryPanel->Connect( wxEVT_SIZE, wxSizeEventHandler( C_wxTmgr::OnSizeCategory ), NULL, this );
    m_ChoiceCategoryView->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( C_wxTmgr::OnChoiceView ), NULL, this );
}

C_wxTmgr::~C_wxTmgr()
{
    // Disconnect Events
    this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( C_wxTmgr::OntMGRResize ) );
    m_bpButton1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnClose ), NULL, this );
    m_bpButton2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnOpenDb ), NULL, this );
    m_bpButton3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnSetAssignee ), NULL, this );
    m_bpButton4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnAbout ), NULL, this );
    m_BtnRepOverview->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnRepNoVisits->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnRepNotAssigned->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnRepAssigned->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnAssignmentDuration->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnRepCreateSet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnRepPrintoutSet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_btnRenderCard->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_btnPrintInlet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_btnPrintInfopage->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_btnPrintBooklet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_BtnDownloadOsmData->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( C_wxTmgr::OnStartJob ), NULL, this );
    m_CategoryPanel->Disconnect( wxEVT_SIZE, wxSizeEventHandler( C_wxTmgr::OnSizeCategory ), NULL, this );
    m_ChoiceCategoryView->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( C_wxTmgr::OnChoiceView ), NULL, this );

    m_mgr.UnInit();

}
