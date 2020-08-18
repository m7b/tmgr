/***************************************************************
 * Name:      ButtonArrayMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    mbuttig ()
 * Created:   2016-09-20
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#include "ButtonArrayMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(ButtonArrayFrame)
#include <wx/font.h>
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

//(*IdInit(ButtonArrayFrame)
const long ButtonArrayFrame::ID_CHOICE1 = wxNewId();
const long ButtonArrayFrame::ID_CUSTOM1 = wxNewId();
const long ButtonArrayFrame::ID_MENUITEM1 = wxNewId();
const long ButtonArrayFrame::idMenuQuit = wxNewId();
const long ButtonArrayFrame::ID_MENUITEM2 = wxNewId();
const long ButtonArrayFrame::ID_MENUITEM3 = wxNewId();
const long ButtonArrayFrame::ID_MENUITEM4 = wxNewId();
const long ButtonArrayFrame::idMenuAbout = wxNewId();
const long ButtonArrayFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ButtonArrayFrame,wxFrame)
    //(*EventTable(ButtonArrayFrame)
    //*)
END_EVENT_TABLE()

ButtonArrayFrame::ButtonArrayFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ButtonArrayFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(-1,-1));
    SetMinSize(wxSize(-1,-1));
    SetMaxSize(wxSize(-1,-1));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    Choice1 = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->Append(_("Gebietsbezeichnung unsortiert"));
    Choice1->SetSelection( Choice1->Append(_("Gebietsbezeichnung sortiert")) );
    Choice1->Append(_("Zugeteilt"));
    wxFont Choice1Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    Choice1->SetFont(Choice1Font);
    BoxSizer1->Add(Choice1, 0, wxALL|wxEXPAND, wxDLG_UNIT(this,wxSize(5,0)).GetWidth());
    ScrolledWindow1 = new C_wxScrolledWindowCat(this,ID_CUSTOM1,wxDefaultPosition,wxDefaultSize);
    BoxSizer1->Add(ScrolledWindow1, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, wxDLG_UNIT(this,wxSize(5,0)).GetWidth());
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Add Category"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    MenuItem4 = new wxMenu();
    MenuItem5 = new wxMenuItem(MenuItem4, ID_MENUITEM2, _("Geb. Bez. unsortiert"), wxEmptyString, wxITEM_NORMAL);
    MenuItem4->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(MenuItem4, ID_MENUITEM3, _("Geb. Bez. sortiert"), wxEmptyString, wxITEM_NORMAL);
    MenuItem4->Append(MenuItem6);
    MenuItem7 = new wxMenuItem(MenuItem4, ID_MENUITEM4, _("Zugeteilt"), wxEmptyString, wxITEM_NORMAL);
    MenuItem4->Append(MenuItem7);
    MenuBar1->Append(MenuItem4, _("Change View"));
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
    SetSizer(BoxSizer1);
    Layout();

    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ButtonArrayFrame::OnChoiceSelectChangeView);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ButtonArrayFrame::OnMenuItemAddCategory);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ButtonArrayFrame::OnQuit);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ButtonArrayFrame::OnMenuItemChangeView);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ButtonArrayFrame::OnMenuItemChangeView);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ButtonArrayFrame::OnMenuItemChangeView);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ButtonArrayFrame::OnAbout);
    //*)
}

ButtonArrayFrame::~ButtonArrayFrame()
{
    //(*Destroy(ButtonArrayFrame)
    //*)
}

void ButtonArrayFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ButtonArrayFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void ButtonArrayFrame::OnMenuItemAddCategory(wxCommandEvent& event)
{
    C_wxScrolledWindowCat::Element el;

    //Testdaten
    for (int i=100; i<=219; i++){el.geb_bez = "Reutlingen";      el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=220; i<=379; i++){el.geb_bez = "Pfullingen";      el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=380; i<=459; i++){el.geb_bez = "Unterhausen";     el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=460; i<=479; i++){el.geb_bez = "Göllesberg";      el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=480; i<=499; i++){el.geb_bez = "Holzelfingen";    el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=500; i<=519; i++){el.geb_bez = "Honau";           el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=520; i<=539; i++){el.geb_bez = "Traifelberg";     el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=540; i<=559; i++){el.geb_bez = "Ohnastetten";     el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=560; i<=599; i++){el.geb_bez = "Genkingen";       el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=600; i<=619; i++){el.geb_bez = "Willmandingen";   el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=620; i<=659; i++){el.geb_bez = "Undingen";        el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=660; i<=679; i++){el.geb_bez = "Erpfingen";       el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=680; i<=699; i++){el.geb_bez = "Ödenwaldstetten"; el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=700; i<=719; i++){el.geb_bez = "Meidelstetten";   el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=720; i<=759; i++){el.geb_bez = "Oberstetten";     el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=760; i<=779; i++){el.geb_bez = "Bernloch";        el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=780; i<=799; i++){el.geb_bez = "Haid";            el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=800; i<=839; i++){el.geb_bez = "Großengstingen";  el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=840; i<=879; i++){el.geb_bez = "Kleinengstingen"; el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}
    for (int i=880; i<=899; i++){el.geb_bez = "Kohlstetten";     el.geb_nr = boost::lexical_cast<std::string>(i); ScrolledWindow1->AddElement(el);}

    el.geb_bez = "Kohlstetten"; el.assigned_to = "Buttig,Mark"; el.geb_nr = "900"; el.last_update = "2016-05-12"; ScrolledWindow1->AddElement(el);
    el.geb_bez = "Kohlstetten"; el.assigned_to = "Buttig,Mark"; el.geb_nr = "901"; el.last_update = "2016-08-12"; ScrolledWindow1->AddElement(el);
    el.geb_bez = "Kohlstetten"; el.assigned_to = "Buttig,Mark"; el.geb_nr = "902"; el.last_update = "2015-08-12"; ScrolledWindow1->AddElement(el);

    ScrolledWindow1->BuildView(C_wxScrolledWindowCat::VIEW_GEB_BEZ_U);

    Bind(EVT_ELEMENT_CLICK, &ButtonArrayFrame::OnElementClick, this);

}

void ButtonArrayFrame::OnElementClick(wxCommandEvent &event) {
    int id = event.GetInt();
    wxMessageBox(wxString::Format("Button pressed with ID %d, Geb Nr. %d", id, id-wxID_HIGHEST));
}

void ButtonArrayFrame::OnMenuItemChangeView(wxCommandEvent& event) {
    int slected_view = event.GetId();

    if (slected_view == ID_MENUITEM2)
        ScrolledWindow1->BuildView(C_wxScrolledWindowCat::VIEW_GEB_BEZ_U);

    if (slected_view == ID_MENUITEM3)
        ScrolledWindow1->BuildView(C_wxScrolledWindowCat::VIEW_GEB_BEZ);

    if (slected_view == ID_MENUITEM4)
        ScrolledWindow1->BuildView(C_wxScrolledWindowCat::VIEW_GEB_ASSIGNED_TO);
}

void ButtonArrayFrame::OnChoiceSelectChangeView(wxCommandEvent& event) {
    int slected_view = event.GetSelection();

    if (slected_view == 0)
        ScrolledWindow1->BuildView(C_wxScrolledWindowCat::VIEW_GEB_BEZ_U);

    if (slected_view == 1)
        ScrolledWindow1->BuildView(C_wxScrolledWindowCat::VIEW_GEB_BEZ);

    if (slected_view == 2)
        ScrolledWindow1->BuildView(C_wxScrolledWindowCat::VIEW_GEB_ASSIGNED_TO);
}
