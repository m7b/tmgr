#include "C_wxPopupMenu.h"

C_wxPopupMenu::C_wxPopupMenu(const std::string &titel, std::vector<std::pair<int, std::string>> *choices, const C_Settings *s)
: wxMenu(titel), setting(s)
{
    //ctor

    //Build different font for menu
    wxMenuItem test(this, 0, wxT("Text"), wxT("Help Text"), wxITEM_NORMAL, 0);
    wxFont font = test.GetFont();
    font.SetPointSize(setting->m_appear.font_size);

    //Icon for entries
    wxBitmap icon = wxArtProvider::GetBitmap(wxART_GO_FORWARD, wxART_OTHER); // wxART_GO_FORWARD, wxART_MENU )

    for(auto el : *choices)
    {
        entry = new wxMenuItem(this, el.first, wxString::FromUTF8(safe_wx_str(el.second)), wxT("Help Text"), wxITEM_NORMAL, 0);
        entry->SetBitmap(icon);
        entry->SetFont(font.Larger());
        Append(entry);
    }
}

C_wxPopupMenu::~C_wxPopupMenu()
{
    //dtor
}
