/***************************************************************
 * Name:      SortingListCtrlApp.cpp
 * Purpose:   Code for Application Class
 * Author:    mbuttig ()
 * Created:   2016-06-09
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#include "SortingListCtrlApp.h"

//(*AppHeaders
#include "SortingListCtrlMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SortingListCtrlApp);

bool SortingListCtrlApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        SortingListCtrlFrame* Frame = new SortingListCtrlFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
