/***************************************************************
 * Name:      ScrolledImageComponentMain.h
 * Purpose:   Defines Application Frame
 * Author:    mbuttig ()
 * Created:   2016-10-18
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#ifndef SCROLLEDIMAGECOMPONENTMAIN_H
#define SCROLLEDIMAGECOMPONENTMAIN_H

//(*Headers(ScrolledImageComponentFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include "../../include/C_wxScrolledImageComponent.h"
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)


#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

class ScrolledImageComponentFrame: public wxFrame
{
    public:

        ScrolledImageComponentFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ScrolledImageComponentFrame();

    private:

        ApplicationData ad;

        //(*Handlers(ScrolledImageComponentFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnAddPicture(wxCommandEvent& event);
        //*)

        //(*Identifiers(ScrolledImageComponentFrame)
        static const long ID_CUSTOM1;
        static const long ID_PANEL1;
        static const long ID_MENUITEM1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ScrolledImageComponentFrame)
        C_wxScrolledImageComponent* Custom1;
        wxPanel* Panel1;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SCROLLEDIMAGECOMPONENTMAIN_H
