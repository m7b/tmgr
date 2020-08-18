#include "C_wxTmgrMainFrame.h"

wxDEFINE_EVENT(EVT_ELEMENT_UPDATED, MyFooEvent);
wxDEFINE_EVENT(EVT_ELEMENT_PROP_UPDATED, MyFooEvent);

C_wxTmgrMainFrame::C_wxTmgrMainFrame( wxWindow* parent )
:
C_wxTmgr(parent)
{
    //Init MainFrameManager
    MainFrameManager = new C_wxTmgrMainFrameManager(this);

    //Settingspanel needs settings
    m_ApplSettings->set_settings(&settings, &ad);

    //Category viewer needs settings
    m_CategoryWindow->set_settings(&ad, &settings);

    //Imageviewer needs app.data -> path entries for card images
    m_CardWindow->set_data(&ad);

    //PanelActions need app.data
    m_Actions->set_data(&ad);

    //PanelNoVisits need app.data
    m_NoVisits->set_settings(&ad, &settings);

    //Panel Tips/Hints need app.data
    m_Tips->set_settings(&ad, &settings);

    //Properties Panel for Territories
    m_TerritoryProperties->set_settings(&settings, &ad);

    //Change aplication font
    DoFontChange();

    //Change AUI dock sash size
    wxAuiDockArt* art = m_mgr.GetArtProvider();
    art->SetMetric(wxAUI_DOCKART_SASH_SIZE, settings.m_appear.m_sash_size);
    m_mgr.Update();

    //Try open last used db
    DoOpenDb();

    //Bind app events
    Bind(EVT_ELEMENT_CLICK,        &C_wxTmgrMainFrame::OnElementClick,       this);
    Bind(EVT_ELEMENT_UPDATED,      &C_wxTmgrMainFrame::OnElementUpdated,     this);
    Bind(EVT_ELEMENT_PROP_UPDATED, &C_wxTmgrMainFrame::OnElementPropUpdated, this);
}

C_wxTmgrMainFrame::~C_wxTmgrMainFrame()
{
    MainFrameManager->save_aui_perspective();
    delete MainFrameManager;
}

void C_wxTmgrMainFrame::OnClose( wxCommandEvent& event )
{
    // important: before terminating, we _must_ wait for our joinable
    // thread to end, if it's running; in fact it uses variables of this
    // instance and posts events to *this event handler
    if (GetThread() &&      // DoStartALongTask() may have not been called
        GetThread()->IsRunning())
    {
        GetThread()->Wait();
    }

    Close();
}

void C_wxTmgrMainFrame::OntMGRResize( wxSizeEvent& event )
{
    MainFrameManager->check_orientation();
    event.Skip();
}

void C_wxTmgrMainFrame::OnOpenDb( wxCommandEvent& event )
{
    int ret_val;

    wxFileDialog fd(this, _("Auswahl Datenbankdatei ..."), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    //fd.SetDirectory(ad.work_dir);
    fd.CentreOnParent();
    ret_val = fd.ShowModal();
    if (ret_val == wxID_CANCEL)
        return;

    ad.db_file = fd.GetPath().c_str();

    //Save last opened db
    settings.m_general.m_last_used_db = ad.db_file;
    settings.save(ad.settings_file);

    //Open Database
    DoOpenDb();
}

void C_wxTmgrMainFrame::DoFontChange(void)
{
    //Change main font
    wxFont thisFont = GetFont();
    thisFont.SetPointSize(settings.m_appear.font_size);
    SetFont(thisFont);

    //   --> AuiNotebookTab
    int y;
    m_auinbOperatings->SetFont(thisFont);
    GetTextExtent("H", nullptr, &y, nullptr, nullptr, &thisFont);
      m_auinbOperatings->SetTabCtrlHeight(y*2.0);

    //   --> Panel Statistic
    m_pgStatistic->SetFont(thisFont);
    m_staticTextReport->SetFont(thisFont);
    m_BtnRepOverview->SetFont(thisFont);
    m_BtnRepNoVisits->SetFont(thisFont);
    m_BtnRepNotAssigned->SetFont(thisFont);
    m_BtnRepAssigned->SetFont(thisFont);
    m_BtnAssignmentDuration->SetFont(thisFont);
    m_staticTextMaps->SetFont(thisFont);
    m_BtnRepCreateSet->SetFont(thisFont);
    m_BtnRepPrintoutSet->SetFont(thisFont);

    //   --> Panel Card
    m_btnRenderCard->SetFont(thisFont);
    m_btnPrintInlet->SetFont(thisFont);
    m_btnPrintInfopage->SetFont(thisFont);
    m_btnPrintBooklet->SetFont(thisFont);

    //   --> Panel Actions
    m_Actions->SetFont(thisFont);

    //   --> Panel Territory Properties
    m_TerritoryProperties->SetFont(thisFont);

    //   --> Panel No Visits
    m_NoVisits->SetFont(thisFont);

    //   --> Panel Hints
    m_Tips->SetFont(thisFont);

    //   --> Panel Appl Settings
    m_ApplSettings->SetFont(thisFont);
    m_BtnDownloadOsmData->SetFont(thisFont);

    //   --> Category Window
    m_ChoiceCategoryView->SetFont(thisFont.Larger().Larger());
    m_CategoryWindow->SetFont(thisFont);
}

void C_wxTmgrMainFrame::DoOpenDb(void)
{
    //Check file variable empty
    if (ad.db_file == "")
    {
        LOG->info("No db opened last time.");
        return;
    }

    //Check file does not exist
    if (!check_file_present(ad.db_file))
    {
        LOG->info("Last opened db does not exist anymore ({}). Forget last db.", ad.db_file);
        ad.db_file = "";
        settings.m_general.m_last_used_db = ad.db_file;
        settings.save(ad.settings_file);
        return;
    }

    LOG->info("Try loading last opened db ({}).", ad.db_file);

    m_CategoryWindow->load_elements_from_db();
    m_CategoryWindow->build_view((C_wxScrolledWindowCat::enView) m_ChoiceCategoryView->GetSelection());

    m_statusBar->SetStatusText(wxString::Format("%s", ad.db_file));

    //Update statistics
    MainFrameManager->update_statistics();

    //PanelActions need app.data new set -> db file
    m_Actions->set_data(&ad);
}

void C_wxTmgrMainFrame::OnElementClick(MyFooEvent &event)
{
    C_wxScrolledWindowCat::Element el = event.GetElement();

    //Save actual geb id in member
    ActGebId = el.geb_id;

    //Update Information title
    MainFrameManager->update_title(&el);

    //Show card
    m_CardWindow->show_card(el.geb_nr);

    //Prepare Actions Panel
    m_Actions->prepare_actions(el);

    //Update Information Table on top
    MainFrameManager->update_element_properties(&el);

    //Update no visits
    MainFrameManager->update_element_no_visits(&el);

    //Update tips
    MainFrameManager->update_element_tips(&el);
}

void C_wxTmgrMainFrame::OnElementUpdated(MyFooEvent &event)
{
    C_wxScrolledWindowCat::Element el = event.GetElement();

    //Save Scrollbar position
    int x = m_CategoryWindow->GetScrollPos(wxHORIZONTAL);
    int y = m_CategoryWindow->GetScrollPos(wxVERTICAL);

    //Reopen DB;
    DoOpenDb();

    //Scroll to saved position
    m_CategoryWindow->Scroll(x,y);

    //Update title
    m_CategoryWindow->get_element(&el);
    MainFrameManager->update_title(&el);

    //Prepare Actions Panel
    m_Actions->prepare_actions(el);
}

void C_wxTmgrMainFrame::OnElementPropUpdated(MyFooEvent &event)
{
    C_wxScrolledWindowCat::Element el = event.GetElement();

    //Reopen DB;
    DoOpenDb();

    //Update title
    m_CategoryWindow->get_element(&el);
    MainFrameManager->update_title(&el);
}

void C_wxTmgrMainFrame::OnStartJob(wxCommandEvent &event)
{
    ProcessType = event.GetId();

    //Check Job has choices and user select a valid choice
    if (check_sorting() == wxID_NONE)
        return;

    // Check if thread is already running and prevent invoking a second thread
    if (GetThread())
    {
        bool alive   = GetThread()->IsAlive();
        bool running = GetThread()->IsRunning();
        if (alive || running)
        {
            LOG->info("An order is still active or running");
            return;
        }
    }

    // we want to start a long task, but we don't want our GUI to block
    // while it's executed, so we use a thread to do it.
    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        LOG->info("Could not create the worker thread!");
        return;
    }
    // go!
    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        LOG->info("Could not create the worker thread!");
        return;
    }
}

void C_wxTmgrMainFrame::OnChoiceView( wxCommandEvent& event )
{
    wxChoice* choice = dynamic_cast<wxChoice*>(event.GetEventObject());
    C_wxScrolledWindowCat::enView view = (C_wxScrolledWindowCat::enView) choice->GetSelection();
    m_CategoryWindow->build_view(view);
}

void C_wxTmgrMainFrame::OnSetAssignee( wxCommandEvent& event )
{
    std::string assignee(m_Actions->m_CBAnnouncer->GetValue().ToUTF8());
    m_CategoryWindow->SetAssignee(assignee);

    //Force load elements for also reloading history data and element fading in case of
    //parameter (settings) changed
    m_CategoryWindow->load_elements_from_db();

    //Rebuild view
    C_wxScrolledWindowCat::enView view = (C_wxScrolledWindowCat::enView) m_ChoiceCategoryView->GetSelection();
    m_CategoryWindow->build_view(view);
}

void C_wxTmgrMainFrame::OnAbout( wxCommandEvent& event )
{
    C_wxDlgInfo InfoDlg(0);
    InfoDlg.ShowModal();
}

void C_wxTmgrMainFrame::print_console_window(std::string value)
{
    m_ConsoleOutputsTextCtrl->AppendText(value);
}

void C_wxTmgrMainFrame::show_card(std::string value)
{
    m_CardWindow->show_card(value);
    m_auinbOperatings->ChangeSelection(1);
}

void C_wxTmgrMainFrame::monitor_process(void)
{
    m_ConsoleOutputsTextCtrl->Clear();

    //TODO(mjb): Add setting:ng: Create settings flag for switching monitoring process
    if (false)
        m_auinbOperatings->ChangeSelection(7);
}

wxThread::ExitCode C_wxTmgrMainFrame::Entry()
{
    if (ProcessType == wxID_MAPERITIVE_DL_OSM_DATA)
        DoMaperitiveDownloadOsmData();

    if (ProcessType == wxID_LATEX_REP_OVERVIEW)
        DoLaTeXReportOverview();

    if (ProcessType == wxID_LATEX_REP_ASSIGNMENT_DURATION)
        DoLaTeXReportAssignementDuration();

    if (ProcessType == wxID_LATEX_REP_NOVISITS)
        DoLaTeXReportNoVisits();

    if (ProcessType == wxID_LATEX_REP_NOT_ASSIGNED)
        DoLaTeXReportNotAssigned();

    if (ProcessType == wxID_LATEX_REP_ASSIGNED)
        DoLaTeXReportAssigned();

    if (ProcessType == wxID_CARD_RENDER)
        DoCardRender();

    if (ProcessType == wxID_LATEX_REP_INLET)
        DoLaTeXReportInlet();

    if (ProcessType == wxID_MAP_REP_CREATE_SET)
        DoCardCreateSet();

    if (ProcessType == wxID_MAP_REP_PRINTOUT_SET)
        DoLaTeXReportPrintoutSet();

    if (ProcessType == wxID_LATEX_REP_INFOPAGE)
        DoLaTeXReportInfopage();

    if (ProcessType == wxID_LATEX_REP_BOOKLET)
        DoLaTeXReportBooklet();

    return (wxThread::ExitCode)0;
}

void C_wxTmgrMainFrame::DoMaperitiveDownloadOsmData(void)
{
    C_OsmDownloader DownloadOsmFile(&ad, &settings);
    DownloadOsmFile.callback = std::bind(&print_console_window, this, std::placeholders::_1);
    std::string osm_file;

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        DownloadOsmFile.start(&osm_file);
        break;
    }
}

void C_wxTmgrMainFrame::DoLaTeXReportOverview(void)
{
    C_ReportOverview rep(&ad, &settings);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.rollout();
        break;
    }
}

void C_wxTmgrMainFrame::DoLaTeXReportAssignementDuration(void)
{
    C_ReportAssignementDuration rep(&ad, &settings);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.rollout();
        break;
    }
}

void C_wxTmgrMainFrame::DoLaTeXReportNoVisits(void)
{
    C_ReportNoVisits rep(&ad, &settings);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);
    rep.set_sort_choice(SortType);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.rollout();
        break;
    }
}

void C_wxTmgrMainFrame::DoLaTeXReportNotAssigned(void)
{
    C_ReportNotAssigned rep(&ad, &settings);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);
    rep.set_sort_choice(SortType);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.rollout();
        break;
    }
}

void C_wxTmgrMainFrame::DoLaTeXReportAssigned(void)
{
    C_ReportAssignements rep(&ad, &settings);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);
    rep.set_sort_choice(SortType);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.rollout();
        break;
    }
}

void C_wxTmgrMainFrame::DoCardRender(void)
{
    C_ReportMapCreator rep(&ad, &settings, ActGebId);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);
    rep.push_card = std::bind(&show_card, this, std::placeholders::_1);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.rollout();
        break;
    }
}

void C_wxTmgrMainFrame::DoLaTeXReportInlet(void)
{
    C_ReportMapInlet rep(&ad, &settings, ActGebId);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.rollout();
        break;
    }
}

void C_wxTmgrMainFrame::DoCardCreateSet(void)
{
    C_ReportMapCreatorAll rep(&ad, &settings);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.rollout_all();
        break;
    }
}

void C_wxTmgrMainFrame::DoLaTeXReportPrintoutSet(void)
{
    C_ReportMapCreatorAll rep(&ad, &settings);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.printout_all();
        break;
    }
}

void C_wxTmgrMainFrame::DoLaTeXReportInfopage(void)
{
    C_ReportMapCreator rep(&ad, &settings, ActGebId);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.rollout_description();
        break;
    }
}

void C_wxTmgrMainFrame::DoLaTeXReportBooklet(void)
{
    C_ReportMapCreator rep(&ad, &settings, ActGebId);
    rep.callback = std::bind(&print_console_window, this, std::placeholders::_1);

    monitor_process();

    while (!GetThread()->TestDestroy())
    {
        rep.rollout_booklet();
        break;
    }
}

int C_wxTmgrMainFrame::check_sorting(void)
{
    int ret = 0;

    //Get mouse position for placing the popup nearby
    wxPoint pos = wxGetMousePosition();
    pos.x -= GetScreenPosition().x;
    pos.y -= GetScreenPosition().y;

    if (ProcessType == wxID_LATEX_REP_NOVISITS)
    {
        C_ReportNoVisits rep(&ad, &settings);
        C_wxPopupMenu popup("Nichtbesuche ...", rep.get_sort_choices(), &settings);
        return SortType = GetPopupMenuSelectionFromUser(popup, pos);
    }

    if (ProcessType == wxID_LATEX_REP_NOT_ASSIGNED)
    {
        C_ReportNotAssigned rep(&ad, &settings);
        C_wxPopupMenu popup("Nicht zugeteilte Gebiete ...", rep.get_sort_choices(), &settings);
        return SortType = GetPopupMenuSelectionFromUser(popup, pos);
    }

    if (ProcessType == wxID_LATEX_REP_ASSIGNED)
    {
        C_ReportAssignements rep(&ad, &settings);
        C_wxPopupMenu popup("Zugeteilte Gebiete ...", rep.get_sort_choices(), &settings);
        return SortType = GetPopupMenuSelectionFromUser(popup, pos);
    }

    return ret;
}

void C_wxTmgrMainFrame::OnSizeCategory( wxSizeEvent& event )
{
    MainFrameManager->update_aui_perspective();
    event.Skip();
}
