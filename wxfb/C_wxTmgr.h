///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include "C_wxDecorator.h"
#include <wx/bmpbuttn.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/scrolwin.h>
#include <C_wxScrolledImageComponent.h>
#include <C_wxPanelActions.h>
#include <C_wxPanelTerritoryProperties.h>
#include <C_wxDataListPanel_NoVisits.h>
#include <C_wxDataListPanel_Tips.h>
#include <C_wxPanelProperties.h>
#include <wx/textctrl.h>
#include <wx/aui/auibook.h>
#include <wx/choice.h>
#include <C_wxScrolledWindowCat.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_LATEX_REP_OVERVIEW 1000
#define wxID_LATEX_REP_NOVISITS 1001
#define wxID_LATEX_REP_NOT_ASSIGNED 1002
#define wxID_LATEX_REP_ASSIGNED 1003
#define wxID_LATEX_REP_ASSIGNMENT_DURATION 1004
#define wxID_MAP_REP_CREATE_SET 1005
#define wxID_MAP_REP_PRINTOUT_SET 1006
#define wxID_CARD_RENDER 1007
#define wxID_LATEX_REP_INLET 1008
#define wxID_LATEX_REP_INFOPAGE 1009
#define wxID_LATEX_REP_BOOKLET 1010
#define wxID_MAPERITIVE_DL_OSM_DATA 1011

///////////////////////////////////////////////////////////////////////////////
/// Class C_wxTmgr
///////////////////////////////////////////////////////////////////////////////
class C_wxTmgr : public C_wxDecorator
{
    private:

    protected:
        wxPanel* m_panel41;
        wxBoxSizer* bSizer36;
        wxGridSizer* m_gSizer1;
        wxBitmapButton* m_bpButton1;
        wxBitmapButton* m_bpButton2;
        wxBitmapButton* m_bpButton3;
        wxBitmapButton* m_bpButton4;
        wxAuiNotebook* m_auinbOperatings;
        wxPanel* m_PanelStatistic;
        wxBoxSizer* m_bSizerScrollWinReports;
        wxBoxSizer* bSizer21;
        wxPropertyGrid* m_pgStatistic;
        wxPGProperty* m_pgiIntAmountTerritories;
        wxPGProperty* m_pgiCategoryAssigned;
        wxPGProperty* m_pgiIntAssignedTerritories;
        wxPGProperty* m_pgiIntAssignedDuration0;
        wxPGProperty* m_pgiIntAssignedDuration1;
        wxPGProperty* m_pgiIntAssignedDuration2;
        wxPGProperty* m_pgiCategoryUnassigned;
        wxPGProperty* m_pgiIntUnassignedTerritories;
        wxPGProperty* m_pgiIntLastWorked;
        wxPGProperty* m_pgiIntLastWorked0;
        wxPGProperty* m_pgiIntLastWorked1;
        wxBoxSizer* bSizer20;
        wxScrolledWindow* m_scrolledWindow3;
        wxBoxSizer* m_bSizerReports;
        wxStaticText* m_staticTextReport;
        wxStaticLine* m_StaticLineReport;
        wxButton* m_BtnRepOverview;
        wxButton* m_BtnRepNoVisits;
        wxButton* m_BtnRepNotAssigned;
        wxButton* m_BtnRepAssigned;
        wxButton* m_BtnAssignmentDuration;
        wxStaticText* m_staticTextMaps;
        wxStaticLine* m_staticline2;
        wxButton* m_BtnRepCreateSet;
        wxButton* m_BtnRepPrintoutSet;
        wxPanel* m_PanelCard;
        wxBoxSizer* m_SizerCard;
        wxBoxSizer* m_bSizerCardActions;
        wxButton* m_btnRenderCard;
        wxButton* m_btnPrintInlet;
        wxButton* m_btnPrintInfopage;
        wxButton* m_btnPrintBooklet;
        C_wxScrolledImageComponent* m_CardWindow;
        wxPanel* m_PanelActions;
        wxBoxSizer* m_SizerActions;
        C_wxPanelActions* m_Actions;
        wxPanel* m_PanelProperties;
        wxBoxSizer* m_SizerProperties;
        C_wxPanelTerritoryProperties* m_TerritoryProperties;
        wxPanel* m_PanelNoVisits;
        wxBoxSizer* m_SizerNoVisits;
        C_wxDataListPanel_NoVisits* m_NoVisits;
        wxPanel* m_PanelTips;
        wxBoxSizer* m_SizerTips;
        C_wxDataListPanel_Tips* m_Tips;
        wxPanel* m_PanelApplSettings;
        wxBoxSizer* bSizer17;
        wxBoxSizer* bSizer18;
        C_wxPanelProperties* m_ApplSettings;
        wxBoxSizer* bSizer19;
        wxScrolledWindow* m_swApplActions;
        wxBoxSizer* m_bsApplActions;
        wxButton* m_BtnDownloadOsmData;
        wxPanel* m_PanelConsoleOutputs;
        wxBoxSizer* m_SizerConsoleOutputs;
        wxTextCtrl* m_ConsoleOutputsTextCtrl;
        wxPanel* m_CategoryPanel;
        wxBoxSizer* m_CategoryPanelSizer;
        wxBoxSizer* m_CategoryChoiceSizer;
        wxChoice* m_ChoiceCategoryView;
        C_wxScrolledWindowCat* m_CategoryWindow;
        wxStatusBar* m_statusBar;

        // Virtual event handlers, overide them in your derived class
        virtual void OntMGRResize( wxSizeEvent& event ) { event.Skip(); }
        virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnOpenDb( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnSetAssignee( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnStartJob( wxCommandEvent& event ) { event.Skip(); }
        virtual void OnSizeCategory( wxSizeEvent& event ) { event.Skip(); }
        virtual void OnChoiceView( wxCommandEvent& event ) { event.Skip(); }


    public:

        C_wxTmgr( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("tMGR"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
        wxAuiManager m_mgr;

        ~C_wxTmgr();

};

