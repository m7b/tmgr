/***************************************************************
 * Name:      SortingListCtrlMain.h
 * Purpose:   Defines Application Frame
 * Author:    mbuttig ()
 * Created:   2016-06-09
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#ifndef SORTINGLISTCTRLMAIN_H
#define SORTINGLISTCTRLMAIN_H

//(*Headers(SortingListCtrlFrame)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/splitter.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include "C_wxLCtrlExtended.h"

class SortingListCtrlFrame: public wxFrame
{
    public:

        SortingListCtrlFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~SortingListCtrlFrame();

    private:

        //(*Handlers(SortingListCtrlFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnListCtrlColumnClick(wxListEvent& event);
        void OnFillLists(wxCommandEvent& event);
        //*)

        //(*Identifiers(SortingListCtrlFrame)
        static const long ID_LISTCTRL1;
        static const long ID_PANEL1;
        static const long ID_LISTCTRL2;
        static const long ID_PANEL2;
        static const long ID_SPLITTERWINDOW1;
        static const long idLoadLists;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(SortingListCtrlFrame)
        C_wxLCtrlExtended* ListCtrl1;
        wxPanel* Panel1;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        wxBoxSizer* BoxSizer1;
        wxPanel* Panel2;
        C_wxLCtrlExtended* ListCtrl2;
        wxSplitterWindow* SplitterWindow1;
        //*)

        DECLARE_EVENT_TABLE()

        void FillList1(void);
        void FillList2(void);
};

#endif // SORTINGLISTCTRLMAIN_H
