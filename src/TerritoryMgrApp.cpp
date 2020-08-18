/***************************************************************
 * Name:      TerritoryMgrApp.cpp
 * Purpose:   Code for Application Class
 * Author:    mbuttig ()
 * Created:   2016-02-17
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#include "TerritoryMgrApp.h"

//(*AppHeaders
#include "C_wxTmgrMainFrame.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(TerritoryMgrApp);

bool TerritoryMgrApp::OnInit()
{

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        C_wxTmgrMainFrame* Frame = new C_wxTmgrMainFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)

    return wxsOK;

}
