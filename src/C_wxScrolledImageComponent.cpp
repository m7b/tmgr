#include "C_wxScrolledImageComponent.h"

C_wxScrolledImageComponent::C_wxScrolledImageComponent(wxWindow* parent, wxWindowID id, wxString image_path)
: wxScrolledWindow(parent, id)
{
    //ctor
}

C_wxScrolledImageComponent::C_wxScrolledImageComponent(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxScrolledWindow(parent, id, pos, size, style, name)
{
    //ctor

    sizer = new wxBoxSizer(wxHORIZONTAL);
    ImagePanel1 = new C_wxImagePanel(this, wxBITMAP_TYPE_PNG);
    sizer->Add(ImagePanel1, 1, wxEXPAND);

    SetSizer(sizer);
    //sizer->Fit(this);
    //sizer->SetSizeHints(this);

    Bind(EVT_IMG_RESIZED, &C_wxScrolledImageComponent::OnImgResized, this);
}

C_wxScrolledImageComponent::~C_wxScrolledImageComponent()
{
    //dtor
}

void C_wxScrolledImageComponent::OnImgResized(wxCommandEvent &event)
{
    wxSize tmp = ImagePanel1->get_image_size();
    SetScrollRate(1,1);
    SetVirtualSize(tmp.x,tmp.y);
}

void C_wxScrolledImageComponent::OnDraw(wxDC& dc)
{
    /* render the image - in a real app, if your scrolled area
       is somewhat big, you will want to draw only visible parts,
       not everything like below */
    //dc.DrawBitmap(*bitmap, 0, 0, false);


/*  wxSize tmp = ImagePanel1->get_image_size();
    SetScrollRate(1,1);
    SetVirtualSize(tmp.x,tmp.y); */

/*  if (tmp.x > 0)
        SetScrollbars(1,1, tmp.x, tmp.y, 0, 0);
*/

}

void C_wxScrolledImageComponent::set_data(const ApplicationData *ad)
{
    this->ad = ad;
}

void C_wxScrolledImageComponent::show_card(std::string GebietNr)
{
    std::string card_to_load = ad->work_dir + "\\maperitive\\" + GebietNr + ".png";

    if (!check_file_present(card_to_load))
    {
        card_to_load = ad->work_dir + "\\maperitive\\templates\\no_map.png";
    }

    ImagePanel1->load_card(card_to_load);
}

