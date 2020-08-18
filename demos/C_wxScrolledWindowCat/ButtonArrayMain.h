/***************************************************************
 * Name:      ButtonArrayMain.h
 * Purpose:   Defines Application Frame
 * Author:    mbuttig ()
 * Created:   2016-09-20
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#ifndef BUTTONARRAYMAIN_H
#define BUTTONARRAYMAIN_H

//(*Headers(ButtonArrayFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/choice.h>
#include "../../include/C_wxScrolledWindowCat.h"
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class ButtonArrayFrame: public wxFrame
{
    public:

        ButtonArrayFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ButtonArrayFrame();

    private:

        //(*Handlers(ButtonArrayFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnMenuItemAddCategory(wxCommandEvent& event);
        void OnMenuItemChangeView(wxCommandEvent& event);
        void OnChoiceSelectChangeView(wxCommandEvent& event);
        //*)

        //(*Identifiers(ButtonArrayFrame)
        static const long ID_CHOICE1;
        static const long ID_CUSTOM1;
        static const long ID_MENUITEM1;
        static const long idMenuQuit;
        static const long ID_MENUITEM2;
        static const long ID_MENUITEM3;
        static const long ID_MENUITEM4;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ButtonArrayFrame)
        wxMenuItem* MenuItem7;
        C_wxScrolledWindowCat* ScrolledWindow1;
        wxMenuItem* MenuItem5;
        wxMenu* MenuItem4;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        wxMenuItem* MenuItem6;
        wxBoxSizer* BoxSizer1;
        wxChoice* Choice1;
        //*)

        void OnElementClick(wxCommandEvent &event);

        DECLARE_EVENT_TABLE()
};

#endif // BUTTONARRAYMAIN_H
