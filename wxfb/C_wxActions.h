///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 13 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/combobox.h>
#include <wx/gbsizer.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class C_wxActions
///////////////////////////////////////////////////////////////////////////////
class C_wxActions : public wxPanel
{
    private:

    protected:
        wxBoxSizer* bSizer11;
        wxScrolledWindow* m_scrolledWindow1;
        wxBoxSizer* bSizer13;
        wxGridBagSizer* gbSizer3;
        wxButton* m_BtnAssign;
        wxDatePickerCtrl* m_datePicker;
        wxButton* m_BtnUnassign;
        wxButton* m_BtnTransfer;
        wxStaticText* m_STComment;
        wxTextCtrl* m_TCComment;
        wxButton* m_BtnProcessed;
        wxButton* m_BtnProcessedUnassign;
        wxGrid* m_GHistory;
        wxButton* m_button_Comment_CLR;
        wxButton* m_button_Comment_GDM;
        wxButton* m_button_Comment_RKG;

        // Virtual event handlers, overide them in your derived class
        virtual void OnBtnAssignClick( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnBtnUnassignClick( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnBtnTransferClick( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnBtnProcessedClick( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnBtnProcessedUnassignClick( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnBtnCommentCLR( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnBtnCommentGDM( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnBtnCommentRKG( wxCommandEvent& event ) { event.Skip(); }


    public:
        wxComboBox* m_CBAnnouncer;

        C_wxActions( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 409,338 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
        ~C_wxActions();

};

///////////////////////////////////////////////////////////////////////////////
/// Class MyPanel2
///////////////////////////////////////////////////////////////////////////////
class MyPanel2 : public wxPanel
{
    private:

    protected:

    public:
        wxComboBox* m_CBAnnouncer;

        MyPanel2( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
        ~MyPanel2();

};

