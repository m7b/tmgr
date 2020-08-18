/***************************************************************
 * Name:      ScrolledImageComponentMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    mbuttig ()
 * Created:   2016-10-18
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#include "ScrolledImageComponentMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(ScrolledImageComponentFrame)
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

//(*IdInit(ScrolledImageComponentFrame)
const long ScrolledImageComponentFrame::ID_CUSTOM1 = wxNewId();
const long ScrolledImageComponentFrame::ID_PANEL1 = wxNewId();
const long ScrolledImageComponentFrame::ID_MENUITEM1 = wxNewId();
const long ScrolledImageComponentFrame::idMenuQuit = wxNewId();
const long ScrolledImageComponentFrame::idMenuAbout = wxNewId();
const long ScrolledImageComponentFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ScrolledImageComponentFrame,wxFrame)
    //(*EventTable(ScrolledImageComponentFrame)
    //*)
END_EVENT_TABLE()

ScrolledImageComponentFrame::ScrolledImageComponentFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ScrolledImageComponentFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Custom1 = new C_wxScrolledImageComponent(Panel1,ID_CUSTOM1,wxDefaultPosition,wxDefaultSize, wxALWAYS_SHOW_SB);
    BoxSizer2->Add(Custom1, 1, wxALL|wxEXPAND, wxDLG_UNIT(Panel1,wxSize(5,0)).GetWidth());
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND, wxDLG_UNIT(this,wxSize(5,0)).GetWidth());
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Add Picture"), wxEmptyString, wxITEM_NORMAL);
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

    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ScrolledImageComponentFrame::OnAddPicture);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ScrolledImageComponentFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ScrolledImageComponentFrame::OnAbout);
    //*)

    //Where is the work dir?
    boost::filesystem::path Pfad(boost::filesystem::initial_path());
    ad.work_dir = Pfad.generic_string();

    Custom1->set_data(&ad);
}

ScrolledImageComponentFrame::~ScrolledImageComponentFrame()
{
    //(*Destroy(ScrolledImageComponentFrame)
    //*)
}

void ScrolledImageComponentFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ScrolledImageComponentFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void ScrolledImageComponentFrame::OnAddPicture(wxCommandEvent& event)
{
    Custom1->show_card("1");
}
