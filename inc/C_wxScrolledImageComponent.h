#ifndef C_WXSCROLLEDIMAGECOMPONENT_H
#define C_WXSCROLLEDIMAGECOMPONENT_H

#include "helpers.h"
#include "appl_data.h"

#include "wx/wx.h"
#include "C_wxImagePanel.h"

/* Evtl ist diese Methode besser
https://wiki.wxwidgets.org/An_image_panel
*/

class C_wxScrolledImageComponent : public wxScrolledWindow
{
    public:
        C_wxScrolledImageComponent(wxWindow* parent, wxWindowID id, wxString image_path);
        C_wxScrolledImageComponent(wxWindow* parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxHSCROLL | wxVSCROLL, const wxString& name = "scrolledWindow");
        virtual ~C_wxScrolledImageComponent();

        void set_data(const ApplicationData *ad);
        void show_card(std::string GebietNr);

    protected:

    private:
        const ApplicationData *ad;

        C_wxImagePanel* ImagePanel1;
        wxBoxSizer* sizer;

        //Events
        void OnDraw(wxDC& dc);
        void OnImgResized(wxCommandEvent &event);
};

#endif // C_WXSCROLLEDIMAGECOMPONENT_H
