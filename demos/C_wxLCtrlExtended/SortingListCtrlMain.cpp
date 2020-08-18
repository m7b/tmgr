/***************************************************************
 * Name:      SortingListCtrlMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    mbuttig ()
 * Created:   2016-06-09
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#include "SortingListCtrlMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(SortingListCtrlFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(SortingListCtrlFrame)
const long SortingListCtrlFrame::ID_LISTCTRL1 = wxNewId();
const long SortingListCtrlFrame::ID_PANEL1 = wxNewId();
const long SortingListCtrlFrame::ID_LISTCTRL2 = wxNewId();
const long SortingListCtrlFrame::ID_PANEL2 = wxNewId();
const long SortingListCtrlFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long SortingListCtrlFrame::idLoadLists = wxNewId();
const long SortingListCtrlFrame::idMenuQuit = wxNewId();
const long SortingListCtrlFrame::idMenuAbout = wxNewId();
const long SortingListCtrlFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SortingListCtrlFrame,wxFrame)
    //(*EventTable(SortingListCtrlFrame)
    //*)
END_EVENT_TABLE()

SortingListCtrlFrame::SortingListCtrlFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SortingListCtrlFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    SplitterWindow1 = new wxSplitterWindow(this, ID_SPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(10,10));
    SplitterWindow1->SetMinimumPaneSize(10);
    SplitterWindow1->SetSashGravity(0.5);
    Panel1 = new wxPanel(SplitterWindow1, ID_PANEL1, wxPoint(7,16), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    ListCtrl1 = new C_wxLCtrlExtended(Panel1, ID_LISTCTRL1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL1"));
    BoxSizer2->Add(ListCtrl1, 1, wxALL|wxEXPAND, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    Panel2 = new wxPanel(SplitterWindow1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    ListCtrl2 = new C_wxLCtrlExtended(Panel2, ID_LISTCTRL2, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL2"));
    BoxSizer3->Add(ListCtrl2, 1, wxALL|wxEXPAND, 5);
    Panel2->SetSizer(BoxSizer3);
    BoxSizer3->Fit(Panel2);
    BoxSizer3->SetSizeHints(Panel2);
    SplitterWindow1->SplitVertically(Panel1, Panel2);
    BoxSizer1->Add(SplitterWindow1, 1, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idLoadLists, _("Load Lists\tAlt-F2"), _("Fülle Listen mit Daten"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_COL_CLICK,(wxObjectEventFunction)&SortingListCtrlFrame::OnListCtrlColumnClick);
    Connect(ID_LISTCTRL2,wxEVT_COMMAND_LIST_COL_CLICK,(wxObjectEventFunction)&SortingListCtrlFrame::OnListCtrlColumnClick);
    Connect(idLoadLists,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SortingListCtrlFrame::OnFillLists);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SortingListCtrlFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SortingListCtrlFrame::OnAbout);
    //*)

/*
    GridBagSizer1->AddGrowableCol(0);
    GridBagSizer1->AddGrowableCol(1);
    GridBagSizer1->AddGrowableRow(1);
*/
}

SortingListCtrlFrame::~SortingListCtrlFrame()
{
    //(*Destroy(SortingListCtrlFrame)
    //*)
}

void SortingListCtrlFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void SortingListCtrlFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void SortingListCtrlFrame::OnListCtrlColumnClick(wxListEvent& event)
{
    int id = event.GetId();

    if ( id == ID_LISTCTRL1)
        ListCtrl1->SortItemsByColumn(event.GetColumn());

    if ( id == ID_LISTCTRL2)
        ListCtrl2->SortItemsByColumn(event.GetColumn());
}

void SortingListCtrlFrame::OnFillLists(wxCommandEvent& event)
{
    FillList1();
    FillList2();
}


void SortingListCtrlFrame::FillList1(void)
{
    ListCtrl1->ClearAll();

    // Add first column
    ListCtrl1->AddColumn("Geb. Id", C_wxLCtrlExtended::stNUMBER, wxLIST_AUTOSIZE_USEHEADER);

    // Add second column
    ListCtrl1->AddColumn("Geb. Nr.", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add third column
    ListCtrl1->AddColumn("Bezeichnung", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add fourth column
    ListCtrl1->AddColumn("Aktiv", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add fifth column
    ListCtrl1->AddColumn("Wohnein.", C_wxLCtrlExtended::stNUMBER, wxLIST_AUTOSIZE_USEHEADER);

    // Add sixth column
    ListCtrl1->AddColumn("Stand", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add seventh column
    ListCtrl1->AddColumn("Zuletzt von", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add eight column
    ListCtrl1->AddColumn("Zuletzt am", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add eight column
    ListCtrl1->AddColumn("Letzter Kommentar", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    for (int fake_data = 0; fake_data < 100; fake_data++)
    {
        wxListItem item;
        item.SetId(fake_data);
        item.SetText(wxString::Format("%d",fake_data));

        ListCtrl1->InsertItem(item);

        ListCtrl1->SetItem(fake_data, 0, wxString::Format("%d", fake_data));
        ListCtrl1->SetItem(fake_data, 1, wxString::Format("%d", fake_data));
        ListCtrl1->SetItem(fake_data, 2, wxString::Format("%d", fake_data));
        ListCtrl1->SetItem(fake_data, 3, wxString::Format("%d", fake_data));
        ListCtrl1->SetItem(fake_data, 4, wxString::Format("%d", fake_data));
        ListCtrl1->SetItem(fake_data, 5, wxString::Format("%d", fake_data));
        ListCtrl1->SetItem(fake_data, 6, wxString::Format("%d", fake_data));
        ListCtrl1->SetItem(fake_data, 7, wxString::Format("%d", fake_data));
        ListCtrl1->SetItem(fake_data, 8, wxString::Format("%d", fake_data));

        ListCtrl1->SetItemData(fake_data, fake_data);
    }
}

void SortingListCtrlFrame::FillList2(void)
{
    ListCtrl2->ClearAll();

    // Add first column
    ListCtrl2->AddColumn("Geb. Id", C_wxLCtrlExtended::stNUMBER, wxLIST_AUTOSIZE_USEHEADER);

    // Add second column
    ListCtrl2->AddColumn("Geb. Nr.", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add third column
    ListCtrl2->AddColumn("Bezeichnung", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add fourth column
    ListCtrl2->AddColumn("Aktiv", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add fifth column
    ListCtrl2->AddColumn("Wohnein.", C_wxLCtrlExtended::stNUMBER, wxLIST_AUTOSIZE_USEHEADER);

    // Add sixth column
    ListCtrl2->AddColumn("Stand", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add seventh column
    ListCtrl2->AddColumn("Zuletzt von", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add eight column
    ListCtrl2->AddColumn("Zuletzt am", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    // Add eight column
    ListCtrl2->AddColumn("Letzter Kommentar", C_wxLCtrlExtended::stSTRING, wxLIST_AUTOSIZE_USEHEADER);

    for (int fake_data = 0; fake_data < 100; fake_data++)
    {
        wxListItem item;
        item.SetId(fake_data);
        item.SetText(wxString::Format("%d",fake_data));

        ListCtrl2->InsertItem(item);

        ListCtrl2->SetItem(fake_data, 0, wxString::Format("%d", fake_data));
        ListCtrl2->SetItem(fake_data, 1, wxString::Format("%d", fake_data));
        ListCtrl2->SetItem(fake_data, 2, wxString::Format("%d", fake_data));
        ListCtrl2->SetItem(fake_data, 3, wxString::Format("%d", fake_data));
        ListCtrl2->SetItem(fake_data, 4, wxString::Format("%d", fake_data));
        ListCtrl2->SetItem(fake_data, 5, wxString::Format("%d", fake_data));
        ListCtrl2->SetItem(fake_data, 6, wxString::Format("%d", fake_data));
        ListCtrl2->SetItem(fake_data, 7, wxString::Format("%d", fake_data));
        ListCtrl2->SetItem(fake_data, 8, wxString::Format("%d", fake_data));

        ListCtrl2->SetItemData(fake_data, fake_data);
    }
}
