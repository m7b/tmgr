/****************************************************************************
 * Copyright (C) 2019 by Mark Buttig                                        *
 *                                                                          *
 * This file is part of tMGR.                                               *
 *                                                                          *
 *   tMGR is free software: you can redistribute it and/or modify it        *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   tMGR is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with tMGR.  If not, see <http://www.gnu.org/licenses/>.  *
 ****************************************************************************/

/**
 * @file wxIconBundleResLoader.cpp
 * @author Mark Buttig
 * @date 11.01.2019
 * @brief Loads a bundle of icons from ico file
 */

#include "wxIconBundleResLoader.h"

#ifndef __WXMSW__
// return an empty bundle for non-MSW OSes
wxIconBundle LoadwxIconBundleFromWindowsResource(const wxString& name, WXHINSTANCE module = 0)
{
    return wxIconBundle();
}

#else

#include <wx/msw/wrapwin.h>

// Based on http://stackoverflow.com/a/20731449/7267315

namespace
{

#pragma pack( push )
#pragma pack( 2 )

    typedef struct
    {
        BYTE   bWidth;               // Width, in pixels, of the image
        BYTE   bHeight;              // Height, in pixels, of the image
        BYTE   bColorCount;          // Number of colors in image (0 if >=8bpp)
        BYTE   bReserved;            // Reserved
        WORD   wPlanes;              // Color Planes
        WORD   wBitCount;            // Bits per pixel
        DWORD  dwBytesInRes;         // how many bytes in this resource?
        WORD   nID;                  // the ID
    } GRPICONDIRENTRY, *LPGRPICONDIRENTRY;

    typedef struct
    {
        WORD            idReserved;   // Reserved (must be 0)
        WORD            idType;       // Resource type (1 for icons)
        WORD            idCount;      // How many images?
        GRPICONDIRENTRY idEntries[1]; // The entries for each image
    } GRPICONDIR, *LPGRPICONDIR;

    #pragma pack( pop )


    wxIcon LoadIconFromWindowsResource(WORD Id, WXHINSTANCE module)
    {
        wxIcon icon;

        HRSRC hRsrc = FindResourceW(module, MAKEINTRESOURCE(Id), RT_ICON);
        if ( !hRsrc )
        {
            wxLogDebug("Could not find resource with id %hu (error code %lu).", Id, GetLastError());
            return icon;
        }

        HGLOBAL hGlobal = LoadResource(module, hRsrc);
        if ( !hGlobal )
        {
            wxLogDebug("Could not load resource with id %hu (error code %lu).", Id, GetLastError());
            return icon;
        }

        BYTE* lpData = static_cast<BYTE*>(LockResource(hGlobal));
        if ( !lpData )
        {
            wxLogDebug("Could not lock resource with id %hu (error code %lu).", Id, GetLastError());
            return icon;
        }

        DWORD dwSize = SizeofResource(module, hRsrc);
        HICON hIcon = CreateIconFromResourceEx(lpData, dwSize, TRUE,
                                               0x00030000, 0, 0,
                                               LR_DEFAULTCOLOR );
        if (hIcon)
        {
             icon.CreateFromHICON(hIcon);
        }
        else
        {
            wxLogDebug("Could not create icon from resource with id %hu (error code %lu).", Id, GetLastError());
        }

        return icon;
    }

} // anonymous namespace

wxIconBundle LoadwxIconBundleFromWindowsResource(const wxString& name, WXHINSTANCE module)
{
    wxIconBundle bundle;

    HRSRC hRsrc = FindResource(module, name.t_str(), RT_GROUP_ICON);
    if (!hRsrc)
    {
        wxLogDebug("Could not find resource with name %s (error code %lu).", name, GetLastError());
        return bundle;
    }

    HGLOBAL hGlobal = LoadResource(module, hRsrc);
    if (!hGlobal)
    {
        wxLogDebug("Could not load resource with name %s (error code %lu).", name, GetLastError());
        return bundle;
    }

    GRPICONDIR* lpGrpIconDir = static_cast<GRPICONDIR*>(LockResource(hGlobal));
    if (!lpGrpIconDir)
    {
        wxLogDebug("Could not lock resource with name %s (error code %lu).", name, GetLastError());
        return bundle;
    }

    for ( size_t i = 0; i < lpGrpIconDir->idCount; ++i )
    {
        wxIcon icon = LoadIconFromWindowsResource(lpGrpIconDir->idEntries[i].nID, module);

        if (icon.IsOk())
        {
            bundle.AddIcon(icon);
        }
    }

    return bundle;
}

#endif
