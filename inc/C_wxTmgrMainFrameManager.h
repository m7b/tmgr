#ifndef C_WXTMGRMAINFRAMEMANAGER_H
#define C_WXTMGRMAINFRAMEMANAGER_H

#include "C_wxTmgrMainFrame.h"

class C_wxTmgrMainFrame;

class C_wxTmgrMainFrameManager
{
    friend C_wxTmgrMainFrame;
    public:
        C_wxTmgrMainFrameManager(C_wxTmgrMainFrame *frm);
        virtual ~C_wxTmgrMainFrameManager();

        void check_orientation(void);
        void update_aui_perspective(void);
        void save_aui_perspective(void);
        void load_aui_perspective(void);
        void focus_reset(void);
        void update_title(const C_wxScrolledWindowCat::Element *el);
        void update_element_properties(const C_wxScrolledWindowCat::Element *el);
        void update_element_no_visits(const C_wxScrolledWindowCat::Element *el);
        void update_element_tips(const C_wxScrolledWindowCat::Element *el);

        void update_statistics(void);

    protected:

    private:
        C_wxTmgrMainFrame *frm;

        int m_items_in_toolbox;
        int m_sash_pos_horizontally;
        int m_sash_pos_vertically;

        int m_focus_mode;
        int m_orientation; // 1=portrait; 2=landscape

        wxString m_dock_conf_landscape;
        wxString m_dock_conf_portrait;

        //Konstanten
        const int ONE_COLUMN;

        void make_landscape_gui(void);
        void make_portrait_gui(void);

        void set_view_options(void);
};

#endif // C_WXTMGRMAINFRAMEMANAGER_H
