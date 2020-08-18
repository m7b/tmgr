#include "C_wxTmgrMainFrameManager.h"

C_wxTmgrMainFrameManager::C_wxTmgrMainFrameManager(C_wxTmgrMainFrame *frm) :
    m_items_in_toolbox(0),
    m_sash_pos_horizontally(0),
    m_sash_pos_vertically(0),
    m_focus_mode(0),
    m_orientation(0),
    ONE_COLUMN(1)
{
    //ctor
    this->frm = frm;

    //Count Items in Custom ToolBar
    m_items_in_toolbox = frm->m_gSizer1->GetItemCount();
    frm->m_gSizer1->SetCols(m_items_in_toolbox);

    //Set view options
    set_view_options();

    //Dynamic labeling of statistic items
    frm->m_pgiIntLastWorked->SetLabel(wxT("├► davon seit vorletztem Dienstjahr (vor ") + start_date_pre_current_yos() + ")");
    frm->m_pgiIntLastWorked0->SetLabel(wxT("├► davon seit letztem Dienstjahr (vor ") + start_date_current_yos() + ")");
    frm->m_pgiIntLastWorked1->SetLabel(wxT("└► davon seit letztem Jahr (vor ") + start_date_current_year() + ")");

    //Set PropertyGridItems for Statistics to ReadOnly
    frm->m_pgStatistic->SetPropertyReadOnly(frm->m_pgiIntAmountTerritories, true);
    frm->m_pgStatistic->SetPropertyReadOnly(frm->m_pgiIntAssignedTerritories, true);
    frm->m_pgStatistic->SetPropertyReadOnly(frm->m_pgiIntAssignedDuration0, true);
    frm->m_pgStatistic->SetPropertyReadOnly(frm->m_pgiIntAssignedDuration1, true);
    frm->m_pgStatistic->SetPropertyReadOnly(frm->m_pgiIntAssignedDuration2, true);
    frm->m_pgStatistic->SetPropertyReadOnly(frm->m_pgiIntUnassignedTerritories, true);
    frm->m_pgStatistic->SetPropertyReadOnly(frm->m_pgiIntLastWorked, true);
    frm->m_pgStatistic->SetPropertyReadOnly(frm->m_pgiIntLastWorked0, true);
    frm->m_pgStatistic->SetPropertyReadOnly(frm->m_pgiIntLastWorked1, true);

    frm->m_pgStatistic->SetSplitterLeft(true);

    load_aui_perspective();
}

C_wxTmgrMainFrameManager::~C_wxTmgrMainFrameManager()
{
    //dtor
}

void C_wxTmgrMainFrameManager::check_orientation(void)
{
    int w, h;
    bool change_detect = false;

    frm->GetSize(&w, &h);

    // 1=portrait; 2=landscape
    if (w > h && m_orientation != 2)
    {
        m_orientation = 2;
        change_detect = true;
    }

    if (w <= h && m_orientation != 1)
    {
        m_orientation = 1;
        change_detect = true;
    }

    if (!change_detect)
        return;

    if (m_orientation == 2)
    {
        make_landscape_gui();

        if (!m_dock_conf_landscape.IsEmpty())
            frm->m_mgr.LoadPerspective(m_dock_conf_landscape);
        else
            frm->m_mgr.Update();
    }

    if (m_orientation == 1)
    {
        make_portrait_gui();

        if (!m_dock_conf_portrait.IsEmpty())
            frm->m_mgr.LoadPerspective(m_dock_conf_portrait);
        else
            frm->m_mgr.Update();
    }
}

void C_wxTmgrMainFrameManager::save_aui_perspective(void)
{
    //Save settings because of aui pane positions aren't saved yet.
    frm->settings.m_general.m_aui_setting_portrait = m_dock_conf_portrait.ToStdString();
    frm->settings.m_general.m_aui_setting_landscape = m_dock_conf_landscape.ToStdString();
    frm->settings.save(frm->ad.settings_file);
}

void C_wxTmgrMainFrameManager::make_landscape_gui(void)
{
    frm->m_mgr.GetPane(frm->m_panel41).Left();
    frm->m_mgr.GetPane(frm->m_CategoryPanel).Left();
    frm->m_mgr.GetPane(frm->m_panel41).dock_proportion = 1;
}

void C_wxTmgrMainFrameManager::make_portrait_gui(void)
{
    frm->m_mgr.GetPane(frm->m_panel41).Top();
    frm->m_mgr.GetPane(frm->m_panel41).Fixed();
    frm->m_mgr.GetPane(frm->m_CategoryPanel).Center();
}

void C_wxTmgrMainFrameManager::set_view_options(void)
{
    //Clear choices
    frm->m_ChoiceCategoryView->Clear();

    //Get available views
    std::vector<std::pair<int, std::string>> options = frm->m_CategoryWindow->get_view_options();

    //Push views to Combox
    for (auto &opt : options)
        frm->m_ChoiceCategoryView->Append(opt.second);

    frm->m_ChoiceCategoryView->SetSelection(0);
}

void C_wxTmgrMainFrameManager::update_aui_perspective(void)
{
    if (m_orientation == 1) //portrait
            m_dock_conf_portrait = frm->m_mgr.SavePerspective();

    if (m_orientation == 2) //landscape
            m_dock_conf_landscape = frm->m_mgr.SavePerspective();
}

void C_wxTmgrMainFrameManager::load_aui_perspective(void)
{
    frm->settings.load(frm->ad.settings_file);
    m_dock_conf_portrait  = wxString(frm->settings.m_general.m_aui_setting_portrait);
    m_dock_conf_landscape = wxString(frm->settings.m_general.m_aui_setting_landscape);

    if (m_orientation == 1)
        frm->m_mgr.LoadPerspective(m_dock_conf_portrait);

    if (m_orientation == 2)
        frm->m_mgr.LoadPerspective(m_dock_conf_landscape);
}

void C_wxTmgrMainFrameManager::focus_reset(void)
{
    m_focus_mode = 0;
}

void C_wxTmgrMainFrameManager::update_title(const C_wxScrolledWindowCat::Element *el)
{
    std::string sInfo = frm->m_title.ToStdString();

    sInfo += " <> ";
    sInfo += wxString::Format("%s | ",      el->geb_nr).c_str();
    sInfo += wxString::Format("%s | ",      wxString::FromUTF8(safe_wx_str(el->geb_bez))).c_str();
    sInfo += wxString::Format("Fam: %d | ", el->families).c_str();

    if (el->act_id != -1)
    {
        sInfo += wxString::Format("%s | ", wxString::FromUTF8(safe_wx_str(el->assigned_to))).c_str();
        sInfo += wxString::Format("letzter Eintrag: %s", el->last_update).c_str();
    }
    else
    {
        sInfo += wxString::Format("letzte Bearbeitung: %s", el->last_update).c_str();
        if (el->comment.size())
            sInfo += wxString::Format(" | %s", wxString::FromUTF8(safe_wx_str(el->comment))).c_str();
    }

    frm->SetTitle(sInfo);
}

void C_wxTmgrMainFrameManager::update_element_properties(const C_wxScrolledWindowCat::Element *el)
{
    frm->m_TerritoryProperties->show(el->geb_id);
}

void C_wxTmgrMainFrameManager::update_element_no_visits(const C_wxScrolledWindowCat::Element *el)
{
    frm->m_NoVisits->show(el->geb_id);
}

void C_wxTmgrMainFrameManager::update_element_tips(const C_wxScrolledWindowCat::Element *el)
{
    frm->m_Tips->show(el->geb_id);
}

void C_wxTmgrMainFrameManager::update_statistics(void)
{
    frm->m_pgiIntAmountTerritories->SetValueFromInt(frm->m_CategoryWindow->Stat.assigned + frm->m_CategoryWindow->Stat.unassigned);
    frm->m_pgiIntAssignedTerritories->SetValueFromInt(frm->m_CategoryWindow->Stat.assigned);

    C_ReportAssignementDuration rep(&frm->ad, &frm->settings);
    auto durations = rep.get_stat();
    frm->m_pgiIntAssignedDuration0->SetValueFromInt(std::get<0>(durations));
    frm->m_pgiIntAssignedDuration1->SetValueFromInt(std::get<1>(durations));
    frm->m_pgiIntAssignedDuration2->SetValueFromInt(std::get<2>(durations));

    frm->m_pgiIntUnassignedTerritories->SetValueFromInt(frm->m_CategoryWindow->Stat.unassigned);
    frm->m_pgiIntLastWorked->SetValueFromInt(frm->m_CategoryWindow->Stat.unassignd_before_last_yos);
    frm->m_pgiIntLastWorked0->SetValueFromInt(frm->m_CategoryWindow->Stat.unassignd_last_yos);
    frm->m_pgiIntLastWorked1->SetValueFromInt(frm->m_CategoryWindow->Stat.unassignd_last_year);

    frm->m_pgStatistic->SetSplitterLeft(true);
}
