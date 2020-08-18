/***************************************************************
 * Name:      ScrolledImageComponentApp.cpp
 * Purpose:   Code for Application Class
 * Author:    mbuttig ()
 * Created:   2016-10-18
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#include "ScrolledImageComponentApp.h"

//(*AppHeaders
#include "ScrolledImageComponentMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ScrolledImageComponentApp);

bool ScrolledImageComponentApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        ScrolledImageComponentFrame* Frame = new ScrolledImageComponentFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
