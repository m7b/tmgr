#ifndef C_WXDECORATOR_H
#define C_WXDECORATOR_H

#include <wx/frame.h>

#include "logger.h"
#include <wx/msw/winundef.h>

#include "appl_data.h"
#include "C_Settings.h"

class C_wxDecorator : public wxFrame
{
    public:
        C_wxDecorator(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style);
        virtual ~C_wxDecorator();

    protected:
        ApplicationData ad;
        C_Settings settings;

        wxString m_title;
};

#endif // C_WXDECORATOR_H
