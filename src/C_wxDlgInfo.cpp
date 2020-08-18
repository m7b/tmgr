#include "C_wxDlgInfo.h"


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


C_wxDlgInfo::C_wxDlgInfo(wxWindow* parent)
:
InfoDialog( parent )
{
    SetIcon(wxICON(MAINICON));
    SetImage();

    m_staticTextName->SetLabel(VER_PRODUCTNAME_STR);
    m_staticTextFileVersion->SetLabel(VER_FILE_VERSION_STR);
    m_staticTextFileDescription->SetLabel(VER_FILE_DESCRIPTION_STR);

    m_staticTextAuthor->SetLabel(wxString::Format(_("Author: %s"), AUTHOR));

    CollectComponentVersions();
    SetDescriptionText();
    SetChangelogText();
    SetToolchainText();
    SetSVNLogText();

    bool state = wxGetKeyState(WXK_SHIFT);
    if (!state)
    {
        m_auinotebook1->RemovePage(3);
        m_auinotebook1->RemovePage(3);
    }
}


void C_wxDlgInfo::SetImage(void)
{
    wxIconBundle bundle = LoadwxIconBundleFromWindowsResource("MAINICON");
    unsigned int ico_to_show = 2;
     if (bundle.GetIconCount() >= ico_to_show)
        m_bitmap->SetIcon(bundle.GetIconByIndex(ico_to_show));
    else
        m_bitmap->SetIcon(wxICON(MAINICON));
}



void C_wxDlgInfo::CollectComponentVersions(void)
{
    wxString tmp;

    tmp += "GCC " + wxString(__VERSION__) + "\n";
    tmp += wxbuildinfo(long_f) + "\n";
    tmp += "SQlite " + wxString(SQLITE_VERSION) + "\n";
    tmp += "Boost " + wxString::Format("%d.%d.%d", BOOST_VERSION / 100000, BOOST_VERSION / 100 % 1000, BOOST_VERSION % 100) + "\n";
    tmp += "spdlog " + wxString::Format("%d.%d.%d", SPDLOG_VERSION / 10000, SPDLOG_VERSION / 100 % 100, SPDLOG_VERSION % 100) + "\n";

    m_richTextInfo->SetValue(tmp);
}

void C_wxDlgInfo::SetDescriptionText(void)
{
    wxString tmp;

    tmp += "Gebieteverwaltungsprogramm und Gebietskartenerstellung";

    m_richTextDescription->SetValue(tmp);
}

void C_wxDlgInfo::SetChangelogText(void)
{
    m_htmlWinChangelog->SetStandardFonts(8);
    m_htmlWinChangelog->SetPage(GetResString(L"CHANGELOG"));
}

void C_wxDlgInfo::SetToolchainText(void)
{
    m_htmlWinToolchain->SetStandardFonts(8);
    m_htmlWinToolchain->SetPage(GetResString(L"TOOLCHAIN"));
}

void C_wxDlgInfo::SetSVNLogText(void)
{
    m_richTextSVNLog->SetFont(wxFont(8, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    std::string svn_log;
    get_resource_file(svn_log, L"SVNLOG");
    m_richTextSVNLog->SetValue(svn_log);
}


std::string C_wxDlgInfo::GetResString(const wchar_t *res)
{
    std::string res_string;
    get_resource_file(res_string, res);
    return res_string;
}

void C_wxDlgInfo::OnHtmlLinkClickedChangelog( wxHtmlLinkEvent& event )
{
    wxHtmlLinkInfo LinkInfo = event.GetLinkInfo();
    wxLaunchDefaultBrowser(LinkInfo.GetHref());
}

void C_wxDlgInfo::OnOk(wxCommandEvent &event)
{
    Close();
}
