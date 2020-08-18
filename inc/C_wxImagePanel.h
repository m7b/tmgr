#ifndef C_WXIMAGEPANEL_H
#define C_WXIMAGEPANEL_H

#include "helpers.h"

#include <wx/wx.h>
#include <wx/sizer.h>


wxDECLARE_EVENT(EVT_IMG_RESIZED, wxCommandEvent);

class C_wxImagePanel : public wxPanel
    {
        wxImage image;
        wxBitmap resized;
        int panel_w, panel_h;
        wxBitmapType format;
        bool m_new_img;

    public:
        C_wxImagePanel(wxWindow* parent, std::string file, wxBitmapType format);
        C_wxImagePanel(wxWindow* parent, wxBitmapType format);
        virtual ~C_wxImagePanel();

        void load_card(std::string card_to_load);

        void paintEvent(wxPaintEvent & evt);
        void paintNow();
        void OnSize(wxSizeEvent& event);
        void render(wxDC& dc);
        wxSize get_image_size(void);

        // some useful events
        /*
         void mouseMoved(wxMouseEvent& event);
         void mouseDown(wxMouseEvent& event);
         void mouseWheelMoved(wxMouseEvent& event);
         void mouseReleased(wxMouseEvent& event);
         void rightClick(wxMouseEvent& event);
         void mouseLeftWindow(wxMouseEvent& event);
         void keyPressed(wxKeyEvent& event);
         void keyReleased(wxKeyEvent& event);
         */

        DECLARE_EVENT_TABLE()
    };




#endif // C_WXIMAGEPANEL_H
