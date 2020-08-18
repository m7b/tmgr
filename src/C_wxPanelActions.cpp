#include "C_wxPanelActions.h"

C_wxPanelActions::C_wxPanelActions( wxWindow* parent )
:C_wxActions(parent), C_DbHandle(0)
{
    //ctor
}

void C_wxPanelActions::set_data(const ApplicationData *ad)
{
    this->ad = ad;
    set_db_file(&this->ad->db_file);

    if(check_file_present(this->ad->db_file))
        populate_names();
}

void C_wxPanelActions::populate_names(void)
{
    wxArrayString wxa_Names;

    int rc = open_db();

    std::string query = "SELECT Name FROM tAktion WHERE Zurueck IS NULL OR Zurueck='' GROUP BY Name";

    rc = query_db(&query);
    if (is_error(rc))
        return;

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
            wxa_Names.Add(wxString::FromUTF8(get_text(COL_0).c_str()));

        if(done_or_error(rc))
            break;
    }
    rc = close_db();

    m_CBAnnouncer->Clear();
    m_CBAnnouncer->Append(wxa_Names);
    m_CBAnnouncer->AutoComplete(wxa_Names);
}

void C_wxPanelActions::populate_history(int geb_id)
{
    m_GHistory->DeleteCols(0, m_GHistory->GetNumberCols(), true);
    m_GHistory->DeleteRows(0, m_GHistory->GetNumberRows(), true);

    m_GHistory->AppendCols(4, true);

    int rc = open_db();

    std::string query = "SELECT Ausgabe, Zurueck, Name, Kommentar FROM tAktion WHERE GebietId=" + std::to_string(geb_id) + " ORDER BY Ausgabe DESC";

    rc = query_db(&query);

    int row = 0;
    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            m_GHistory->AppendRows(1, true);
            m_GHistory->SetCellValue(row, COL_0, wxString::FromUTF8(get_text(COL_0).c_str()));
            m_GHistory->SetCellValue(row, COL_1, wxString::FromUTF8(get_text(COL_1).c_str()));
            m_GHistory->SetCellValue(row, COL_2, wxString::FromUTF8(get_text(COL_2).c_str()));
            m_GHistory->SetCellValue(row, COL_3, wxString::FromUTF8(get_text(COL_3).c_str()));
            row++;
        }

        if(done_or_error(rc))
            break;
    }
    rc = close_db();

    m_GHistory->SetColLabelValue(COL_0, wxT("Ausgabe"));
    m_GHistory->SetColLabelValue(COL_1, wxT("Zurück"));
    m_GHistory->SetColLabelValue(COL_2, wxT("Verkündiger"));
    m_GHistory->SetColLabelValue(COL_3, wxT("Kommentar"));
    m_GHistory->SetRowLabelSize(1);
    m_GHistory->AutoSize();

    Layout();
}

void C_wxPanelActions::prepare_actions(const C_wxScrolledWindowCat::Element el)
{
    this->el = el;

    m_TCComment->Clear();
    m_datePicker->SetValue(wxDateTime::Today());

    if (this->el.act_id == -1)
    {
        m_BtnAssign->Enable(true);
        m_BtnUnassign->Enable(false);
        m_BtnTransfer->Enable(false);
        m_BtnProcessed->Enable(false);
        m_BtnProcessedUnassign->Enable(false);
    }
    else
    {
        m_BtnAssign->Enable(false);
        m_BtnUnassign->Enable(true);
        m_BtnTransfer->Enable(true);
        m_BtnProcessed->Enable(true);
        m_BtnProcessedUnassign->Enable(true);
    }

    populate_history(this->el.geb_id);
}


bool C_wxPanelActions::SetFont(const wxFont &font)
{
    m_CBAnnouncer->SetFont(font.Larger());
    m_BtnAssign->SetFont(font);
    m_datePicker->SetFont(font);
    m_BtnUnassign->SetFont(font);
    m_BtnTransfer->SetFont(font);
    m_STComment->SetFont(font);
    m_TCComment->SetFont(font);
    m_BtnProcessed->SetFont(font);
    m_BtnProcessedUnassign->SetFont(font);
    m_GHistory->SetDefaultCellFont(font);
    m_GHistory->SetLabelFont(font.Bold());

    int y;
    GetTextExtent("H", nullptr, &y, nullptr, nullptr, &font);
    m_GHistory->SetColLabelSize(y*1.5);

    return true;
}

void C_wxPanelActions::OnBtnAssignClick(wxCommandEvent& event)
{
    wxString text("");// = "";
    text += wxT("Möchtest du folgende Zuweisung durchführen?\n\n");
    text += wxString::Format(wxT("Gebiet:      %s - %s\n"), el.geb_nr, wxString::FromUTF8(safe_wx_str(el.geb_bez)));
    text += wxString::Format(wxT("Datum:       %s\n"), m_datePicker->GetValue().Format(wxT("%d.%m.%Y"), wxDateTime::CET));
    text += wxString::Format(wxT("Verkündiger: %s\n"), m_CBAnnouncer->GetValue());

    int answer = wxMessageBox(text, wxT("Zuweisung"),  wxOK|wxCANCEL|wxICON_QUESTION);
    if (answer != wxOK)
        return;

    el.assigned_to = m_CBAnnouncer->GetValue().ToUTF8();
    el.last_update = m_datePicker->GetValue().Format(wxT("%Y-%m-%d"), wxDateTime::CET).c_str();

    do_assign();

    post_element_updated();
}

void C_wxPanelActions::OnBtnUnassignClick(wxCommandEvent& event)
{
    wxString text = "";
    text += wxT("Möchtest du folgende Zuweisung aufheben?\n\n");
    text += wxString::Format(wxT("Act.-Id:      %s\n"), std::to_string(el.act_id));
    text += wxString::Format(wxT("Gebiet:       %s - %s\n"), el.geb_nr, wxString::FromUTF8(safe_wx_str(el.geb_bez)));
    text += wxString::Format(wxT("Ausgabedatum: %s\n"), el.last_update);
    text += wxString::Format(wxT("Verkündiger:  %s\n"), wxString::FromUTF8(safe_wx_str(el.assigned_to)));

    int answer = wxMessageBox(text, wxT("Zuweisung aufheben"),  wxOK|wxCANCEL|wxICON_QUESTION);
    if (answer != wxOK)
        return;

    do_unassign();

    post_element_updated();
}

void C_wxPanelActions::OnBtnTransferClick(wxCommandEvent& event)
{
    wxString text = "";
    text += wxT("Möchtest du folgende Zuweisung ändern?\n\n");
    text += wxString::Format(wxT("Act.-Id:                %s\n"), std::to_string(el.act_id));
    text += wxString::Format(wxT("Gebiet:                 %s - %s\n"), el.geb_nr, wxString::FromUTF8(safe_wx_str(el.geb_bez)));
    text += wxString::Format(wxT("Ausgabedatum:           %s\n"), el.last_update);
    text += wxString::Format(wxT("Bisheriger Verkündiger: %s\n"), wxString::FromUTF8(safe_wx_str(el.assigned_to)));
    text += wxString::Format(wxT("Datum:                  %s\n"), m_datePicker->GetValue().Format(wxT("%d.%m.%Y"), wxDateTime::CET));
    text += wxString::Format(wxT("Neuer Verkündiger:      %s\n"), m_CBAnnouncer->GetValue());
    text += wxString::Format(wxT("Kommentar:              %s\n"), m_TCComment->GetValue());

    int answer = wxMessageBox(text, wxT("Zuweisung ändern"),  wxOK|wxCANCEL|wxICON_QUESTION);
    if (answer != wxOK)
        return;

    el.last_update = m_datePicker->GetValue().Format(wxT("%Y-%m-%d"), wxDateTime::CET).c_str();
    el.comment     = m_TCComment->GetValue().ToUTF8();
    el.assigned_to = m_CBAnnouncer->GetValue().ToUTF8();

    do_transfer();

    post_element_updated();
}

void C_wxPanelActions::OnBtnProcessedClick(wxCommandEvent& event)
{
    wxString text = "";
    text += wxT("Möchtest du folgende Gebietszuteilung\n");
    text += wxT("als bearbeitet kennzeichnen?\n\n");
    text += wxString::Format(wxT("Act.-Id:      %s\n"), std::to_string(el.act_id));
    text += wxString::Format(wxT("Gebiet:       %s - %s\n"), el.geb_nr, wxString::FromUTF8(safe_wx_str(el.geb_bez)));
    text += wxString::Format(wxT("Ausgabedatum: %s\n"), el.last_update);
    text += wxString::Format(wxT("Verkündiger:  %s\n"), wxString::FromUTF8(safe_wx_str(el.assigned_to)));
    text += wxString::Format(wxT("Kommentar:    %s\n"), m_TCComment->GetValue());

    int answer = wxMessageBox(text, "Gebiet als bearbeit eintragen",  wxOK|wxCANCEL|wxICON_QUESTION);
    if (answer != wxOK)
        return;

    el.last_update = m_datePicker->GetValue().Format(wxT("%Y-%m-%d"), wxDateTime::CET).ToUTF8();
    el.comment     = m_TCComment->GetValue().ToUTF8();

    do_processed();

    post_element_updated();
}

void C_wxPanelActions::OnBtnProcessedUnassignClick(wxCommandEvent& event)
{
    wxString text = "";
    text += wxT("Möchtest du folgende Gebietszuteilung als bearbeitet\n");
    text += wxT("kennzeichnen und die Zuteilung aufheben?\n\n");
    text += wxString::Format(wxT("Act.-Id:      %s\n"), std::to_string(el.act_id));
    text += wxString::Format(wxT("Gebiet:       %s - %s\n"), el.geb_nr, wxString::FromUTF8(safe_wx_str(el.geb_bez)));
    text += wxString::Format(wxT("Ausgabedatum: %s\n"), el.last_update);
    text += wxString::Format(wxT("Verkündiger:  %s\n"), wxString::FromUTF8(safe_wx_str(el.assigned_to)));
    text += wxString::Format(wxT("Kommentar:    %s\n"), m_TCComment->GetValue());

    int answer = wxMessageBox(text, wxT("Gebiet als bearbeit eintragen / Zuteilung aufheben"),  wxOK|wxCANCEL|wxICON_QUESTION);
    if (answer != wxOK)
        return;

    el.last_update = m_datePicker->GetValue().Format(wxT("%Y-%m-%d"), wxDateTime::CET).ToUTF8();
    el.comment     = m_TCComment->GetValue().ToUTF8();

    do_processed_unassign();

    post_element_updated();
}

void C_wxPanelActions::OnBtnCommentCLR( wxCommandEvent& event )
{
    //Clear comment field
    m_TCComment->Clear();
}

void C_wxPanelActions::OnBtnCommentGDM( wxCommandEvent& event )
{
    //Set text module "Einladung GDM"
    m_TCComment->SetValue("Einladung GDM");
}

void C_wxPanelActions::OnBtnCommentRKG( wxCommandEvent& event )
{
    //Set text module "Einladung RKG"
    m_TCComment->SetValue("Einladung RKG");
}


void C_wxPanelActions::do_assign(void)
{
    open_db();

    std::string query = "";
    query += "INSERT INTO tAktion (GebietId, Name, Ausgabe) ";
    query += "VALUES (";
    query += std::to_string(el.geb_id) + ",";
    query += "'" + el.assigned_to + "',";
    query += "'" + el.last_update + "');";

    exec_db(&query);
    close_no_finalize_db();
}

void C_wxPanelActions::do_unassign(void)
{
    open_db();

    std::string query = "";
    query += "DELETE FROM tAktion WHERE Id = " + std::to_string(el.act_id);

    exec_db(&query);
    close_no_finalize_db();
}

void C_wxPanelActions::do_transfer(void)
{
    do_processed_unassign();
    do_assign();
}

void C_wxPanelActions::do_processed(void)
{
    do_processed_unassign();
    do_assign();
}

void C_wxPanelActions::do_processed_unassign(void)
{
    open_db();

    std::string query = "";
    query += "UPDATE tAktion ";
    query += "SET ";
    query += "Zurueck = '"   + el.last_update + "', ";
    query += "Kommentar = '" + el.comment     + "' ";
    query += "WHERE Id = "   + std::to_string(el.act_id);

    exec_db(&query);
    close_no_finalize_db();
}

void C_wxPanelActions::post_element_updated(void)
{
    MyFooEvent e(EVT_ELEMENT_UPDATED);
    e.SetElement(el);
    wxPostEvent(this, e); // to ourselves
}
