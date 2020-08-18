///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/dataview.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class C_wxDataListPanel
///////////////////////////////////////////////////////////////////////////////
class C_wxDataListPanel : public wxPanel
{
    private:

    protected:
        wxDataViewListCtrl* m_dataViewListCtrl;
        wxDataViewColumn* m_dataViewListColumn;
        wxButton* m_button_add;
        wxButton* m_button_remove;

        // Virtual event handlers, overide them in your derived class
        virtual void OnEditingDone( wxDataViewEvent& event ) { event.Skip(); }
        virtual void OnClickAdd( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnClickRemove( wxCommandEvent& event ) { event.Skip(); }


    public:

        C_wxDataListPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
        ~C_wxDataListPanel();

};

