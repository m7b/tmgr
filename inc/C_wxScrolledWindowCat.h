#ifndef C_WXSCROLLEDWINDOWCAT_H
#define C_WXSCROLLEDWINDOWCAT_H

#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/wupdlock.h>
#include <wx/grid.h>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <set>
#include <algorithm>
#include <cctype>

#include "helpers.h"
#include "C_Settings.h"
#include "C_DbHandle.h"
#include "appl_data.h"

#include "safe_wx_str.h"

class MyFooEvent;
wxDECLARE_EVENT(EVT_ELEMENT_CLICK, MyFooEvent);

class C_wxScrolledWindowCat : public wxScrolledWindow, C_DbHandle
{
    public:
        struct Element
        {
            int geb_id;
            int act_id;
            std::string geb_nr;
            std::string geb_bez;
            int families;
            std::string assigned_to;
            std::string last_update;
            std::string comment;
            Element() : geb_id(0), act_id(0), geb_nr(""), geb_bez(""), families(0), assigned_to(""), last_update(""){}
        };

        struct Statistic
        {
            int assigned;
            int unassigned;
            int unassignd_before_last_yos;
            int unassignd_last_yos;
            int unassignd_last_year;
            Statistic() : assigned(0), unassigned(0){}
            void reset(void){ assigned=0; unassigned=0; }
        };

        struct History
        {
            int geb_id;
            std::string assignee;
            History() : geb_id(0), assignee(""){}
        };

        enum enView
        {
            VIEW_GEB_BEZ_U = 0,
            VIEW_GEB_BEZ,
            VIEW_GEB_BEZ_SORT_BY_DATE,
            VIEW_GEB_ASSIGNED_TO,
            VIEW_GEB_ASSIGNED_TO_SORT_BY_DATE,
            VIEW_LIST
        };

    private:
        struct BtnColour
        {
            wxColour BtnBack;
            wxColour BtnFront;
        };

    public:
        C_wxScrolledWindowCat(wxWindow* parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxHSCROLL | wxVSCROLL, const wxString& name = "scrolledWindow");
        virtual ~C_wxScrolledWindowCat();

        Statistic Stat;

        void set_settings(const ApplicationData *appl_data, const C_Settings *settings);
        void load_elements_from_db(void);
        void get_element(Element *el);
        void build_view(enView view);
        bool SetFont(const wxFont &font);
        void SetAssignee(std::string assignee);

        std::vector<std::pair<int, std::string>> get_view_options(void);

    protected:

    private:
        const ApplicationData *ad;
        const C_Settings *se;

        wxBoxSizer* BoxSizerMain;
        std::vector<wxGridSizer*> v_ref_grdsizers;
        std::vector<Element>  vElements;
        std::vector<History>  vHistory;

        wxColour wxCOLOUR_Header;
        std::vector<wxColour> m_v_col_a;
        std::vector<wxColour> m_v_col_ua;

        wxSize ButtonSize;
        int AmountCols;
        int HeaderFieldHeight;

        std::string m_assignee;

        int CalcOptimalCols(void);
        bool AdjustColCnt(void);

        void build_tiles(enView view);
        void build_list(enView view);
        std::vector<std::string> getCategories(enView view);
        void sortElements(enView view);
        void AddCategory(std::string category);
        void get_colours_from_settings(void);
        void getBtnColour(Element el, BtnColour* col);
        void fadeBtnColour(Element el, BtnColour* col);
        int calc_days(std::string date);
        void AddButton(Element el, wxGridSizer* cgs);
        std::string CreateToolTipOfElement(Element el);

        int get_btn_id(int geb_id){return geb_id + wxID_HIGHEST;};
        int get_geb_id(int btn_id){return btn_id - wxID_HIGHEST;};

        void calc_stats(void);
        void load_history_of_unassigned_territories(void);

        static bool SortBy_geb_id(const Element &lhs, const Element &rhs);
        static bool SortBy_geb_nr(const Element &lhs, const Element &rhs);
        static bool SortBy_geb_bez(const Element &lhs, const Element &rhs);
        static bool SortBy_families(const Element &lhs, const Element &rhs);
        static bool SortBy_assigned_to(const Element &lhs, const Element &rhs);
        static bool SortBy_last_update(const Element &lhs, const Element &rhs);
        static bool SortBy_last_update_unassigned(const Element &lhs, const Element &rhs);

        //Events
        void OnResize(wxSizeEvent &event);
        void OnElementClicked(wxCommandEvent &event);
        void OnGridSelectCell(wxGridEvent& event);
};



class MyFooEvent: public wxCommandEvent
{
public:
    MyFooEvent(wxEventType commandType = EVT_ELEMENT_CLICK, int id = 0)
                :  wxCommandEvent(commandType, id),
                   m_el()  { }

    // You *must* copy here the data to be transported
    MyFooEvent(const MyFooEvent& event)
                :  wxCommandEvent(event) { this->SetElement(event.GetElement()); }

    // Required for sending with wxPostEvent()
    wxEvent* Clone() const { return new MyFooEvent(*this); }

    C_wxScrolledWindowCat::Element GetElement() const { return m_el; }
    void SetElement(const C_wxScrolledWindowCat::Element& el) { m_el = el; }

private:
    C_wxScrolledWindowCat::Element m_el;
};


#endif // C_WXSCROLLEDWINDOWCAT_H
