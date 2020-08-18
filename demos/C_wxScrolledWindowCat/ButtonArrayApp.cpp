/***************************************************************
 * Name:      ButtonArrayApp.cpp
 * Purpose:   Code for Application Class
 * Author:    mbuttig ()
 * Created:   2016-09-20
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#include "ButtonArrayApp.h"

//(*AppHeaders
#include "ButtonArrayMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ButtonArrayApp);

bool ButtonArrayApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        ButtonArrayFrame* Frame = new ButtonArrayFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
