///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/html/htmlwin.h>
#include <wx/aui/auibook.h>
#include <wx/statline.h>
#include <wx/gbsizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class InfoDialog
///////////////////////////////////////////////////////////////////////////////
class InfoDialog : public wxDialog
{
    private:

    protected:
        wxBoxSizer* m_bSizer;
        wxPanel* m_panel;
        wxGridBagSizer* m_gbSizer;
        wxStaticBitmap* m_bitmap;
        wxStaticText* m_staticTextName;
        wxStaticText* m_staticTextFileDescription;
        wxStaticText* m_staticTextAuthor;
        wxButton* m_button1;
        wxAuiNotebook* m_auinotebook1;
        wxPanel* m_panel2;
        wxRichTextCtrl* m_richTextDescription;
        wxPanel* m_panel3;
        wxRichTextCtrl* m_richTextInfo;
        wxPanel* m_panel4;
        wxHtmlWindow* m_htmlWinChangelog;
        wxPanel* m_panel5;
        wxRichTextCtrl* m_richTextSVNLog;
        wxPanel* m_panel6;
        wxHtmlWindow* m_htmlWinToolchain;
        wxStaticText* m_staticTextFileVersion;
        wxStaticLine* m_staticline1;

        // Virtual event handlers, overide them in your derived class
        virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnHtmlLinkClickedChangelog( wxHtmlLinkEvent& event ) { event.Skip(); }


    public:

        InfoDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Information"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 570,500 ), long style = wxDEFAULT_DIALOG_STYLE );
        ~InfoDialog();

};

