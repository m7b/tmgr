/***************************************************************
 * Name:      TerritoryMgrApp.h
 * Purpose:   Defines Application Class
 * Author:    mbuttig ()
 * Created:   2016-02-17
 * Copyright: mbuttig ()
 * License:
 **************************************************************/

#ifndef TERRITORYMGRAPP_H
#define TERRITORYMGRAPP_H

// workaround for a boost bug..
#ifndef __kernel_entry
#define __kernel_entry
#endif

#include <boost/process.hpp>

#include <wx/app.h>

class TerritoryMgrApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // TERRITORYMGRAPP_H
