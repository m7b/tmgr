#include "C_wxImagePanel.h"

// some useful events
/*
 void C_wxImagePanel::mouseMoved(wxMouseEvent& event) {}
 void C_wxImagePanel::mouseDown(wxMouseEvent& event) {}
 void C_wxImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
 void C_wxImagePanel::mouseReleased(wxMouseEvent& event) {}
 void C_wxImagePanel::rightClick(wxMouseEvent& event) {}
 void C_wxImagePanel::mouseLeftWindow(wxMouseEvent& event) {}
 void C_wxImagePanel::keyPressed(wxKeyEvent& event) {}
 void C_wxImagePanel::keyReleased(wxKeyEvent& event) {}
 */



// this is a definition so can't be in a header
wxDEFINE_EVENT(EVT_IMG_RESIZED, wxCommandEvent);

C_wxImagePanel::C_wxImagePanel(wxWindow* parent, std::string file, wxBitmapType format) :
wxPanel(parent)
{
    // load the file... ideally add a check to see if loading was successful
    if (check_file_present(file))
        image.LoadFile(file, format);

    panel_w = -1;
    panel_h = -1;
    this->format = format;
}

C_wxImagePanel::C_wxImagePanel(wxWindow* parent, wxBitmapType format) :
wxPanel(parent)
{
    panel_w = -1;
    panel_h = -1;
    this->format = format;

    wxClientDC dc(this);
    dc.GetSize( &panel_w, &panel_h );
}

C_wxImagePanel::~C_wxImagePanel()
{
    //dtor
}

void C_wxImagePanel::load_card(std::string card_to_load)
{
    //wxClientDC dc(this);
    //dc.GetSize( &w, &h );

    panel_w = -1;
    panel_h = -1;

    if (check_file_present(card_to_load))
    {
        m_new_img = true;
        image.LoadFile(card_to_load, format);
        Refresh();
    }
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void C_wxImagePanel::paintEvent(wxPaintEvent & evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void C_wxImagePanel::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void C_wxImagePanel::render(wxDC&  dc)
{
    int panel_new_w, panel_new_h;
    dc.GetSize( &panel_new_w, &panel_new_h );

    if (!image.IsOk())
        return;

    if(panel_new_w != panel_w || panel_new_h != panel_h || !resized.IsOk() || m_new_img)
    {
        m_new_img = false;
        panel_w = panel_new_w;
        panel_h = panel_new_h;

        double fc_w = (double) panel_new_w / (double) image.GetWidth();
        int img_new_w = image.GetWidth()  * fc_w;
        int img_new_h = image.GetHeight() * fc_w;

        resized = wxBitmap( image.Scale( img_new_w, img_new_h, wxIMAGE_QUALITY_HIGH ) );
        dc.DrawBitmap( resized, 0, 0, false );

        wxCommandEvent e(EVT_IMG_RESIZED);
        wxPostEvent(this, e); // to ourselves
    }
    else
    {
        dc.DrawBitmap( resized, 0, 0, false );
    }
}

wxSize C_wxImagePanel::get_image_size(void)
{
    return resized.GetSize();
}

/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void C_wxImagePanel::OnSize(wxSizeEvent& event){
    Refresh();

    //skip the event.
    event.Skip();
}




BEGIN_EVENT_TABLE(C_wxImagePanel, wxPanel)
// some useful events
/*
 EVT_MOTION(C_wxImagePanel::mouseMoved)
 EVT_LEFT_DOWN(C_wxImagePanel::mouseDown)
 EVT_LEFT_UP(C_wxImagePanel::mouseReleased)
 EVT_RIGHT_DOWN(C_wxImagePanel::rightClick)
 EVT_LEAVE_WINDOW(C_wxImagePanel::mouseLeftWindow)
 EVT_KEY_DOWN(C_wxImagePanel::keyPressed)
 EVT_KEY_UP(C_wxImagePanel::keyReleased)
 EVT_MOUSEWHEEL(C_wxImagePanel::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(C_wxImagePanel::paintEvent)
//Size event
EVT_SIZE(C_wxImagePanel::OnSize)

END_EVENT_TABLE()
