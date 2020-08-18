#include "C_wxDataListPanel_NoVisits.h"

C_wxDataListPanel_NoVisits::C_wxDataListPanel_NoVisits( wxWindow* parent )
:
C_wxDataListPanel( parent ), C_DbHandle(0), ad(nullptr), s(nullptr)
{
    m_DSGVO = DSGVO;
    
    m_dataViewListCtrl->AppendTextColumn( wxT("Adresse"),   wxDATAVIEW_CELL_EDITABLE, wxCOL_WIDTH_AUTOSIZE, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );
    if (!m_DSGVO)
        m_dataViewListCtrl->AppendTextColumn( wxT("Name"),      wxDATAVIEW_CELL_EDITABLE, wxCOL_WIDTH_AUTOSIZE, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );
    m_dataViewListCtrl->AppendTextColumn( wxT("Datum"),     wxDATAVIEW_CELL_EDITABLE, wxCOL_WIDTH_AUTOSIZE, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );
    m_dataViewListCtrl->AppendTextColumn( wxT("Kommentar"), wxDATAVIEW_CELL_EDITABLE, wxCOL_WIDTH_AUTOSIZE, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );

}

void C_wxDataListPanel_NoVisits::set_settings(ApplicationData* appl_data, C_Settings* settings)
{
    s = settings;
    ad = appl_data;
    set_db_file(&ad->db_file);
}

void C_wxDataListPanel_NoVisits::show(int geb_id)
{
    m_geb_id      = geb_id;
    m_last_row_id = 0;
    m_dataViewListCtrl->DeleteAllItems();

    int rc = open_db();

    std::string query = "";
    query += "SELECT Id, GebietId, Name, Adresse, Datum, Kommentar ";
    query += "FROM tNichtbesuche ";
    query += "WHERE GebietId=" + std::to_string(m_geb_id);

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            wxVector<wxVariant> data;
            data.push_back( wxVariant(get_int(COL_0)) );                                   //ID
            data.push_back( wxVariant(wxString::FromUTF8(safe_wx_str(get_text(COL_3)))));  //Adresse
            if (!m_DSGVO)
                data.push_back( wxVariant(wxString::FromUTF8(safe_wx_str(get_text(COL_2)))));  //Name
            data.push_back( wxVariant(wxString::FromUTF8(safe_wx_str(get_text(COL_4)))));  //Datum
            data.push_back( wxVariant(wxString::FromUTF8(safe_wx_str(get_text(COL_5)))));  //Kommentar


            m_dataViewListCtrl->AppendItem(data);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();

}

bool C_wxDataListPanel_NoVisits::SetFont(const wxFont &font)
{
    m_dataViewListCtrl->SetFont(font);
    return true;
}

wxVariant C_wxDataListPanel_NoVisits::get_value(int col, int row)
{
    wxVariant val;
    m_dataViewListCtrl->GetValue(val, row, col);
    return val;
}

void C_wxDataListPanel_NoVisits::set_value(wxVariant val, int col, int row)
{
    m_dataViewListCtrl->SetValue(val, row, col);
}

void C_wxDataListPanel_NoVisits::OnClickAdd( wxCommandEvent& event )
{
    wxVector<wxVariant> data;
    data.push_back( "<neu>" );
    data.push_back( "<Adresse>");
    if (!m_DSGVO)
        data.push_back( "<Name>");

    wxDateTime today = wxDateTime::Today();
    wxString str = today.Format(wxT("%Y-%m-%d"), wxDateTime::CET);
    data.push_back( str );

    data.push_back( ""); //Comment

    m_dataViewListCtrl->InsertItem(0, data);

    wxDataViewItem item = m_dataViewListCtrl->RowToItem(0);
    wxDataViewColumn *col = m_dataViewListCtrl->GetColumn(1);
    m_dataViewListCtrl->EditItem(item, col);
}

void C_wxDataListPanel_NoVisits::OnClickRemove( wxCommandEvent& event )
{
    int row = m_dataViewListCtrl->GetSelectedRow();

    if (row == wxNOT_FOUND)
        return;

    int id = get_value(0, row).GetLong();

    wxString text = "";
    text += "Möchtest du folgenden Nichtbesuch löschen?\n\n";
    text += wxString::Format(wxT("Id:            %s\n"), std::to_string(id));
    text += wxString::Format(wxT("Adresse: %s\n"), get_value(1, row).GetString());
    if (!m_DSGVO)
        text += wxString::Format(wxT("Name:    %s\n"), get_value(2, row).GetString());

    int answer = wxMessageBox(text, "Nichtbesuch löschen",  wxOK|wxCANCEL|wxICON_QUESTION);
    if (answer != wxOK)
        return;

    open_db();
    std::string query = "DELETE FROM tNichtbesuche WHERE Id=" + std::to_string(id);
    exec_db(&query);
    close_no_finalize_db();

    m_dataViewListCtrl->DeleteItem(row);
}

void C_wxDataListPanel_NoVisits::OnEditingDone( wxDataViewEvent& event )
{
    int col = event.GetColumn();
    wxDataViewItem item = event.GetItem();
    int row = m_dataViewListCtrl->ItemToRow(item);
    wxString id = get_value(0, row).GetString();

    std::string query = "";

    if (id == "<neu>")
    {
        query += "INSERT INTO tNichtbesuche (GebietId, Adresse, Name, Datum, Kommentar) VALUES (";
        query += "'" + std::to_string(m_geb_id)                           + "', ";
        query += "'" + std::string(event.GetValue().GetString().ToUTF8()) + "', ";
        query += "'" + get_value(2, row).GetString()                      + "', ";
        if (!m_DSGVO)
        {
            query += "'" + get_value(3, row).GetString()                      + "', ";
            query += "'" + get_value(4, row).GetString()                      + "'); ";
        }
        else
        {
            query += "'" + get_value(3, row).GetString()                      + "', ";
        }

        open_db();
        exec_db(&query);
        m_last_row_id = last_insert_rowid();
        set_value(m_last_row_id, 0, row);
        close_no_finalize_db();
    }
    else
    {
        
        if (!m_DSGVO)
        {
            switch(col)
            {
                case 1:
                    query = "UPDATE tNichtbesuche SET Adresse = '" + std::string(event.GetValue().GetString().ToUTF8()) + "' WHERE Id = " + id;
                    break;
                case 2:
                    query = "UPDATE tNichtbesuche SET Name = '" + std::string(event.GetValue().GetString().ToUTF8()) + "' WHERE Id = " + id;
                    break;
                case 3:
                    query = "UPDATE tNichtbesuche SET Datum = '" + std::string(event.GetValue().GetString().ToUTF8()) + "' WHERE Id = " + id;
                    break;
                case 4:
                    query = "UPDATE tNichtbesuche SET Kommentar = '" + std::string(event.GetValue().GetString().ToUTF8()) + "' WHERE Id = " + id;
                    break;
            }
        }
        else
        {
            switch(col)
            {
                case 1:
                    query = "UPDATE tNichtbesuche SET Adresse = '" + std::string(event.GetValue().GetString().ToUTF8()) + "' WHERE Id = " + id;
                    break;
                case 2:
                    query = "UPDATE tNichtbesuche SET Datum = '" + std::string(event.GetValue().GetString().ToUTF8()) + "' WHERE Id = " + id;
                    break;
                case 3:
                    query = "UPDATE tNichtbesuche SET Kommentar = '" + std::string(event.GetValue().GetString().ToUTF8()) + "' WHERE Id = " + id;
                    break;
            }
        }

        open_db();
        exec_db(&query);
        close_no_finalize_db();
    }

/*
    if (col < m_dataViewListCtrl->GetColumnCount()-1)
        col++;
    else
    {
        show(m_geb_id);
        return;
    }

    //Automatically edit next column
    wxDataViewColumn *dvcol = m_dataViewListCtrl->GetColumn(col);
    m_dataViewListCtrl->EditItem(item, dvcol);
*/
}
