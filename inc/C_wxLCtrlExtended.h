#ifndef C_WXLCTRLEXTENDED_H
#define C_WXLCTRLEXTENDED_H

#include <wx/listctrl.h>
#include <wx/dataview.h>
#include <map>

class C_wxLCtrlExtended : public wxListCtrl
{
    public:
        enum col_type_for_sorting
        {
            stNULL = 0,
            stSTRING,
            stNUMBER,
            stDATE
        };

    public:
        C_wxLCtrlExtended(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxLC_ICON, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxListCtrlNameStr);
        virtual ~C_wxLCtrlExtended();

        void AddColumn(std::string text, col_type_for_sorting st, int col_width);
        void ClearAllExtended(void);
        void AdjustAllColWidth(void);

        bool SortItemsByColumn(int column);
        bool SortAscending;
        int SortedColumn;

        col_type_for_sorting GetTypeForSorting(int col);

        wxString GetTextByColumn(long index, int col);

        void add_insertion_line(void);
        void remove_insertion_line(void);

    protected:


    private:
        std::map <int, col_type_for_sorting> sort_list;
        std::map <int, int> m_col_width;                //first->column, second->width

        int m_col;

        void SetColTypeForSorting(int col, col_type_for_sorting st);
        void SetColWidth(int col, int col_width);

        void OnColumnHeadClick(wxListEvent &event);
};

#endif // C_WXLCTRLEXTENDED_H

