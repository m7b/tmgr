#include "C_wxDecorator.h"

C_wxDecorator::C_wxDecorator(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
: wxFrame(parent, id, title, pos, size, style)
{
    //ctor

    //Init logging functionality
    init_logging();

    //Set main application icon
    SetIcon( wxICON(MAINICON) );

    //Set main application title
    m_title = title;

    //Load Settings.xml
    ad.settings_file = "Settings.xml";
    settings.load(ad.settings_file);
    settings.save(ad.settings_file); //Save settings one time for adding eventually new properties

    //Where is the work dir?
    ad.work_dir = boost::filesystem::initial_path().string();

    //Set last used db
    ad.db_file = settings.m_general.m_last_used_db;

    //Change main font
    wxFont thisFont = GetFont();
    thisFont.SetPointSize(settings.m_appear.font_size);
    SetFont(thisFont);
}

C_wxDecorator::~C_wxDecorator()
{
    //dtor
}
