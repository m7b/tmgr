#ifndef C_WXPOPUPMENU_H
#define C_WXPOPUPMENU_H

#include "C_Settings.h"
#include <wx/menu.h>
#include <wx/artprov.h>

#include "safe_wx_str.h"

class C_wxPopupMenu : public wxMenu
{
    public:
        C_wxPopupMenu(const std::string &titel, std::vector<std::pair<int, std::string>> *choices, const C_Settings *s);
        virtual ~C_wxPopupMenu();

    private:
        const C_Settings *setting;
        wxMenuItem *entry;
};

#endif // C_WXPOPUPMENU_H
