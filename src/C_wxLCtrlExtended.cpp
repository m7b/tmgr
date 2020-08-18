#include "C_wxLCtrlExtended.h"

int wxCALLBACK ListCompareFunction(wxIntPtr  item1, wxIntPtr  item2, long long sortData);
bool Is1GreaterThan2( wxString &lsDate1, wxString &lsDate2 );

C_wxLCtrlExtended::C_wxLCtrlExtended(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
: wxListCtrl(parent, id, pos, size, style, validator, name)
{
    //ctor
    SortAscending = false;
    SortedColumn = -1;
    m_col = -1;

    Connect(id ,wxEVT_COMMAND_LIST_COL_CLICK,(wxObjectEventFunction)&C_wxLCtrlExtended::OnColumnHeadClick);
}

C_wxLCtrlExtended::~C_wxLCtrlExtended()
{
    //dtor
}

void C_wxLCtrlExtended::AddColumn(std::string text, col_type_for_sorting st, int col_width)
{
    wxListItem tmp_col;

    m_col++;
    tmp_col.SetId(m_col);
    tmp_col.SetText(text);
    InsertColumn(m_col, tmp_col);
    SetColTypeForSorting(m_col, st);
    SetColWidth(m_col, col_width);
}

void C_wxLCtrlExtended::ClearAllExtended(void)
{
    ClearAll();
    m_col = -1;
}

void C_wxLCtrlExtended::AdjustAllColWidth(void)
{
    for (std::map<int, int>::iterator it = m_col_width.begin(); it != m_col_width.end(); ++it)
        SetColumnWidth(it->first, it->second);
}

bool C_wxLCtrlExtended::SortItemsByColumn(int column)
{
    if(column == SortedColumn) // user clicked same column as last time, change the sorting order
        SortAscending = SortAscending ? FALSE : TRUE;
    else                 // user clicked new column, sort ascending
        SortAscending = TRUE;

    SortedColumn = column;

    return SortItems(&ListCompareFunction, (long long int)this);
}

void C_wxLCtrlExtended::SetColTypeForSorting(int col, col_type_for_sorting st)
{
    sort_list[col] = st;
}

void C_wxLCtrlExtended::SetColWidth(int col, int col_width)
{
    m_col_width[col] = col_width;
}

C_wxLCtrlExtended::col_type_for_sorting C_wxLCtrlExtended::GetTypeForSorting(int col)
{
    return sort_list[col];
}

wxString C_wxLCtrlExtended::GetTextByColumn(long index, int col)
{
    wxListItem Item;                // the item whose text we want
    Item.SetId(index);              // set the index
    Item.SetColumn(col);            // set the column
    Item.SetMask(wxLIST_MASK_TEXT); // enable GetText()
    GetItem(Item);                  // get the item
    return Item.GetText();          // get and return its text
}

void C_wxLCtrlExtended::OnColumnHeadClick( wxListEvent& event )
{
    remove_insertion_line();

    int col = event.GetColumn();
    SortItemsByColumn(col);

    add_insertion_line();
}

void C_wxLCtrlExtended::add_insertion_line(void)
{
    wxListItem NewItem;

    int ItemId = GetItemCount();

    NewItem.SetMask(wxLIST_MASK_TEXT);
    NewItem.SetId(ItemId);
    NewItem.SetText("hinzufügen");
    NewItem.SetFont(*wxITALIC_FONT);
    NewItem.SetTextColour(wxColour(*wxRED));
    NewItem.SetBackgroundColour(wxColour(235, 235, 235));

    InsertItem(NewItem);
    this->SetItem(ItemId, 0, "hinzufügen");
}

void C_wxLCtrlExtended::remove_insertion_line(void)
{
    long pos = this->FindItem(0, "hinzufügen");

    if (pos == wxNOT_FOUND)
        return;

    this->DeleteItem(pos);
}

// #################################################################################
// Helper Functions
// #################################################################################


int wxCALLBACK ListCompareFunction(wxIntPtr  item1, wxIntPtr  item2, long long sortData)
{

    int rc = 0;
    C_wxLCtrlExtended *pListCtrl = (C_wxLCtrlExtended*) sortData;

    int index1 = pListCtrl->FindItem(-1, item1); // get the index of the first item
    int index2 = pListCtrl->FindItem(-1, item2); // get the index of the second item

    int col = pListCtrl->SortedColumn;

    wxString string1 = pListCtrl->GetTextByColumn(index1, col); // get the text of the first item
    wxString string2 = pListCtrl->GetTextByColumn(index2, col); // get the text of the second item

    C_wxLCtrlExtended::col_type_for_sorting st = pListCtrl->GetTypeForSorting(col);
    switch(st)
    {
        case C_wxLCtrlExtended::stNUMBER:

            long long1, long2;
            string1.ToLong(&long1);
            string2.ToLong(&long2);
            if (long1 < long2)
                rc = pListCtrl->SortAscending ? -1 : 1;
            if (long1 > long2)
                rc = pListCtrl->SortAscending ? 1 : -1;
            break;

        case C_wxLCtrlExtended::stDATE:

            if( Is1GreaterThan2(string1,string2))
                rc = pListCtrl->SortAscending ? -1 : 1;
            else
                rc = pListCtrl->SortAscending ? 1 : -1;
            break;

        case C_wxLCtrlExtended::stSTRING:

            if(string1.Cmp(string2) < 0)
                rc = pListCtrl->SortAscending ? -1 : 1;
            else
            if(string1.Cmp(string2) > 0)
                rc = pListCtrl->SortAscending ? 1 : -1;
            break;

        case C_wxLCtrlExtended::stNULL:
            break;

        default:
            break;
    }

    return rc;
}

bool Is1GreaterThan2( wxString &lsDate1, wxString &lsDate2 )      // Should come in as DD.MM.YYYY
{
    wxDateTime ldDate1, ldDate2;
    bool lbRetVal = false;

    if (!ldDate1.ParseFormat( lsDate1, "%d.%m.%Y" ))
        return true;

    if (!ldDate2.ParseFormat( lsDate2, "%d.%m.%Y" ))
        return true;

    if ( ldDate2.IsEarlierThan( ldDate1 ) )
       lbRetVal = true;

    return lbRetVal;
}
