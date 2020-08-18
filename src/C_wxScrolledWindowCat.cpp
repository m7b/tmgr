#include "C_wxScrolledWindowCat.h"

// this is a definition so can't be in a header
wxDEFINE_EVENT(EVT_ELEMENT_CLICK, MyFooEvent);


/// Constructor
C_wxScrolledWindowCat::C_wxScrolledWindowCat(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxScrolledWindow(parent, id, pos, size, style, name), C_DbHandle(0), ad(0), se(0)
{
    //ctor
    BoxSizerMain = new wxBoxSizer(wxVERTICAL);

    SetSizer(BoxSizerMain);
    FitInside();
    SetScrollRate(1, 1);

    Connect(wxEVT_SIZE,(wxObjectEventFunction)&C_wxScrolledWindowCat::OnResize);
}


/// Destructor
C_wxScrolledWindowCat::~C_wxScrolledWindowCat()
{
    //dtor
}


/// Set adresses of application data and settings
void C_wxScrolledWindowCat::set_settings(const ApplicationData *appl_data, const C_Settings *settings)
{
    this->ad = appl_data;
    this->se = settings;

    set_db_file(&ad->db_file);

    wxCOLOUR_Header = wxSystemSettings::GetColour(wxSYS_COLOUR_MENU);
    ButtonSize = wxSize(this->se->m_appear.m_square_size_x, this->se->m_appear.m_square_size_y);
    HeaderFieldHeight = this->se->m_appear.m_square_size_y * 2/3; //35;

    get_colours_from_settings();

    AmountCols = CalcOptimalCols();
}



/// Load elements from db
void C_wxScrolledWindowCat::load_elements_from_db(void)
{
    // Assigned territories
    vElements.clear();
    Stat.reset();

    // Use new territory numbering
    std::string NbField = "tGebiet.Nr";
    if (se->m_general.m_use_new_territory_numbers_in_maps)
        NbField = "tGebiet.NNr";


    set_db_file(&ad->db_file);
    int rc = open_db();

    //Assigned territories
    std::string query = "";
    query += "SELECT tGebiet.Id, tAktion.Id, " + NbField + ", tGebiet.Bez, tGebiet.WEinh, Name, Ausgabe as 'last upd' ";
    query += "FROM tAktion ";
    query += "INNER JOIN tGebiet ON tGebiet.Id = tAktion.GebietId ";
    query += "WHERE tAktion.Zurueck IS NULL OR tAktion.Zurueck = '' ";
    query += "ORDER BY tGebiet.Id ASC";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            Element tmp;
            tmp.geb_id      = get_int(COL_0);
            tmp.act_id      = get_int(COL_1);
            tmp.geb_nr      = get_text(COL_2);
            tmp.geb_bez     = get_text(COL_3);
            tmp.families    = get_int(COL_4);
            tmp.assigned_to = get_text(COL_5);
            tmp.last_update = get_text(COL_6);
            vElements.push_back(tmp);
            Stat.assigned++;
        }

        if(done_or_error(rc))
            break;
    }
    rc = close_db();



    //Unassigned territories
    rc = open_db();

    query = "";
    query += "SELECT tGebiet.Id, " + NbField + ", tGebiet.Bez, tGebiet.WEinh, t2.Zurueck as 'last upd', t2.Kommentar ";
    query += "FROM (SELECT * FROM ( ";
    query += "SELECT Id, GebietId, Name, MAX(Ausgabe), Zurueck, Kommentar FROM tAktion GROUP BY GebietId ";
    query += ") WHERE Zurueck IS NOT NULL AND Zurueck <> '') AS t2 ";
    query += "INNER JOIN tGebiet ON tGebiet.Id = t2.GebietId";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            Element tmp;
            tmp.geb_id      = get_int(COL_0);
            tmp.act_id      = -1;
            tmp.geb_nr      = get_text(COL_1);
            tmp.geb_bez     = get_text(COL_2);
            tmp.families    = get_int(COL_3);
            tmp.last_update = get_text(COL_4);
            tmp.comment     = get_text(COL_5);
            vElements.push_back(tmp);
            Stat.unassigned++;
        }

        if(done_or_error(rc))
            break;
    }
    rc = close_db();

    calc_stats();

    load_history_of_unassigned_territories();
}



/// Event executes on resize
void C_wxScrolledWindowCat::OnResize(wxSizeEvent& event)
{
    if (AdjustColCnt()) {
        SetSizer(BoxSizerMain);
        FitInside();
        SetScrollRate(1, 1);
    }
    event.Skip();
}



/// Get element
void C_wxScrolledWindowCat::get_element(Element *el)
{
    for (auto e : vElements)
        if (e.geb_id == el->geb_id)
        {
            *el = e;
            break;
        }
}



/// Build specific view
void C_wxScrolledWindowCat::build_view(enView view)
{
    wxWindowUpdateLocker noUpdates(this);

    BoxSizerMain->Clear(true);
    v_ref_grdsizers.clear();

    switch (view) {

    case VIEW_GEB_BEZ_U:
    case VIEW_GEB_BEZ:
    case VIEW_GEB_BEZ_SORT_BY_DATE:
    case VIEW_GEB_ASSIGNED_TO:
    case VIEW_GEB_ASSIGNED_TO_SORT_BY_DATE:
        build_tiles(view); break;
    case VIEW_LIST:
        build_list(view); break;
    default:
        build_tiles(VIEW_GEB_BEZ_U); break;
    }
}


bool C_wxScrolledWindowCat::SetFont(const wxFont &font)
{
    return true;
}


void C_wxScrolledWindowCat::SetAssignee(std::string assignee)
{
    m_assignee = assignee;
    std::transform(m_assignee.begin(), m_assignee.end(), m_assignee.begin(), std::ptr_fun<int, int>(std::toupper));
}


/// Get available view options
std::vector<std::pair<int, std::string>> C_wxScrolledWindowCat::get_view_options(void)
{
    std::vector<std::pair<int, std::string>> tmp;
    std::pair<int, std::string> opt;

    opt.first  = VIEW_GEB_BEZ_U;
    opt.second = "Gebietsbezeichnung unsortiert";
    tmp.push_back(opt);

    opt.first  = VIEW_GEB_BEZ;
    opt.second = "Gebietsbezeichnung sortiert";
    tmp.push_back(opt);

    opt.first  = VIEW_GEB_BEZ_SORT_BY_DATE;
    opt.second = "Gebietsbezeichnung sortiert nach Datum / Status Zuweisung";
    tmp.push_back(opt);

    opt.first  = VIEW_GEB_ASSIGNED_TO;
    opt.second = "Zugewiesen";
    tmp.push_back(opt);

    opt.first  = VIEW_GEB_ASSIGNED_TO_SORT_BY_DATE;
    opt.second = "Zugewiesen sortiert nach Datum";
    tmp.push_back(opt);

    opt.first  = VIEW_LIST;
    opt.second = "Listenansicht";
    tmp.push_back(opt);

    return tmp;
}



/// build tiles
void C_wxScrolledWindowCat::build_tiles(enView view)
{
    //Kategorien ermitteln
    std::vector<std::string> cat = getCategories(view);
    //Elemente sortieren
    sortElements(view);

    //Elemente je Kategorie einfügen
    for (auto category : cat){
        //Header
        AddCategory(category);

        //Add Buttons in GridSizer
        for (auto el : vElements)
            switch (view) {

            case VIEW_GEB_BEZ_U:
            case VIEW_GEB_BEZ:
                if (category == el.geb_bez){AddButton(el, v_ref_grdsizers.back());} break;

            case VIEW_GEB_BEZ_SORT_BY_DATE:
                if (category == el.geb_bez){AddButton(el, v_ref_grdsizers.back());} break;

            case VIEW_GEB_ASSIGNED_TO:
                if (category == el.assigned_to){AddButton(el, v_ref_grdsizers.back());} break;

            case VIEW_GEB_ASSIGNED_TO_SORT_BY_DATE:
                if (category == el.assigned_to){AddButton(el, v_ref_grdsizers.back());} break;

            default:
                if (category == el.geb_bez){AddButton(el, v_ref_grdsizers.back());} break;
            }
    }
    GetParent()->Layout();
}



/// build list
void C_wxScrolledWindowCat::build_list(enView view)
{

    wxGrid *grid = new wxGrid( this, -1, wxDefaultPosition, wxDefaultSize );

    int rows = vElements.size();
    int cols = 7;

    grid->CreateGrid(rows, cols);
    grid->EnableEditing(false);
    grid->EnableGridLines(true);
    grid->EnableDragGridSize(false);
    grid->SetMargins(0, 0);

    //Set grid label font and height
    wxFont font = GetFont();
    font.SetPointSize(se->m_appear.font_size);
    grid->SetLabelFont(font.Bold());
    int y;
    GetTextExtent("H", nullptr, &y, nullptr, nullptr, &font);
    grid->SetColLabelSize(y*1.5);

    int i_row = 0;
    for(auto& el : vElements)
    {
        grid->SetCellValue(i_row, COL_0, wxString::Format("%d", el.geb_id));
        grid->SetCellValue(i_row, COL_1, wxString::FromUTF8(safe_wx_str(el.geb_nr)));
        grid->SetCellValue(i_row, COL_2, wxString::FromUTF8(safe_wx_str(el.geb_bez)));
        grid->SetCellValue(i_row, COL_3, wxString::Format("%d", el.families));
        grid->SetCellValue(i_row, COL_4, wxString::FromUTF8(safe_wx_str(el.assigned_to)));
        grid->SetCellValue(i_row, COL_5, wxString::FromUTF8(safe_wx_str(el.last_update)));
        grid->SetCellValue(i_row, COL_6, wxString::FromUTF8(safe_wx_str(el.comment)));

        i_row++;
    }

    grid->SetColLabelValue(COL_0, wxT("Geb.-Id"));
    grid->SetColLabelValue(COL_1, wxT("Nr."));
    grid->SetColLabelValue(COL_2, wxT("Bezeichnung"));
    grid->SetColLabelValue(COL_3, wxT("Familien"));
    grid->SetColLabelValue(COL_4, wxT("Zugeteilt"));
    grid->SetColLabelValue(COL_5, wxT("Aktualisierung"));
    grid->SetColLabelValue(COL_6, wxT("Kommentar"));

    grid->HideCol(COL_0);

    grid->SetRowLabelSize(1);
    grid->AutoSize();

    grid->Connect(wxEVT_GRID_SELECT_CELL, wxGridEventHandler( C_wxScrolledWindowCat::OnGridSelectCell ), NULL, this );

    BoxSizerMain->Add(grid, 0, wxALL|wxEXPAND, 0);

    GetParent()->Layout();
}



/// Get categories
std::vector<std::string> C_wxScrolledWindowCat::getCategories(enView view)
{
    std::vector<std::string> uniques;

    switch (view) {

        case VIEW_GEB_BEZ_U: //Gebietsbezeichnung in der Reihenfolge des Vorkommens
            {
                for (auto el : vElements)
                    if (std::find(uniques.begin(), uniques.end(), el.geb_bez) == uniques.end())
                        uniques.push_back(el.geb_bez);
                break;
            }

        case VIEW_GEB_BEZ: //Gebietsbezeichnung sortiert alphabetisch
            {
                std::set<std::string> cat;
                for (auto el : vElements)
                    cat.insert(el.geb_bez);
                for (auto el : cat)
                    uniques.push_back(el);
                break;
            }

        case VIEW_GEB_BEZ_SORT_BY_DATE: //Gebietsbezeichnung sortiert alphabetisch mit Datum
            {
                std::set<std::string> cat;
                for (auto el : vElements)
                    cat.insert(el.geb_bez);
                for (auto el : cat)
                    uniques.push_back(el);
                break;
            }

        case VIEW_GEB_ASSIGNED_TO: //Zugeteilt alphabetisch
            {
                std::set<std::string> cat;
                for (auto el : vElements)
                    cat.insert(el.assigned_to);
                for (auto el : cat)
                    uniques.push_back(el);
                break;
            }

        case VIEW_GEB_ASSIGNED_TO_SORT_BY_DATE: //Zugeteilt alphabetisch nach Datum sortiert
            {
                std::set<std::string> cat;
                for (auto el : vElements)
                    cat.insert(el.assigned_to);
                for (auto el : cat)
                    uniques.push_back(el);
                break;
            }

        default: //VIEW_GEB_BEZ_U Gebietsbezeichnung in der Reihenfolge des Vorkommens
            {
                for (auto el : vElements)
                    if (std::find(uniques.begin(), uniques.end(), el.geb_bez) == uniques.end())
                        uniques.push_back(el.geb_bez);
                break;
            }
    }

    return uniques;
}



/// Sort elements
void C_wxScrolledWindowCat::sortElements(enView view)
{
    switch (view) {

        case VIEW_GEB_BEZ_U:
            std::sort(vElements.begin(), vElements.end(), C_wxScrolledWindowCat::SortBy_geb_nr);
            break;

        case VIEW_GEB_BEZ:
            std::sort(vElements.begin(), vElements.end(), C_wxScrolledWindowCat::SortBy_geb_nr);
            break;

        case VIEW_GEB_BEZ_SORT_BY_DATE:
            std::sort(vElements.begin(), vElements.end(), C_wxScrolledWindowCat::SortBy_last_update_unassigned);
            break;

        case VIEW_GEB_ASSIGNED_TO:
            std::sort(vElements.begin(), vElements.end(), C_wxScrolledWindowCat::SortBy_geb_nr);
            break;

        case VIEW_GEB_ASSIGNED_TO_SORT_BY_DATE:
            std::sort(vElements.begin(), vElements.end(), C_wxScrolledWindowCat::SortBy_last_update);
            break;

        default:
            std::sort(vElements.begin(), vElements.end(), C_wxScrolledWindowCat::SortBy_geb_nr);
            break;
    }
}



/// Add category
void C_wxScrolledWindowCat::AddCategory(std::string category)
{
    wxString Label = wxString::FromUTF8(safe_wx_str(category));
    wxBoxSizer *HeadSizer = new wxBoxSizer(wxHORIZONTAL);
    wxRichTextCtrl *CategoryText = new wxRichTextCtrl(this, wxID_ANY, Label, wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE|wxRE_READONLY|wxNO_BORDER, wxDefaultValidator, _T("wxID_ANY"));
    CategoryText->SetMinSize(wxSize(0, HeaderFieldHeight));
    CategoryText->Disable();
    CategoryText->SetBackgroundColour(wxCOLOUR_Header);
    HeadSizer->Add(CategoryText, 1, wxTOP|wxBOTTOM|wxEXPAND, 5);
    BoxSizerMain->Add(HeadSizer, 0, wxALL|wxEXPAND, 0);

    //Add GridSizer for it's elements
    wxGridSizer *ContainerGridSizer = new wxGridSizer(0, AmountCols, 0, 0);
    v_ref_grdsizers.push_back(ContainerGridSizer);
    BoxSizerMain->Add(ContainerGridSizer, 0, wxLEFT, 5);
}



/// Take button colours from settings
void C_wxScrolledWindowCat::get_colours_from_settings(void)
{
    /// Colour definitions
    wxColour tmp_colour;

    m_v_col_a.clear();
    tmp_colour.Set(se->m_appear.assigned.colour_1.r, se->m_appear.assigned.colour_1.g, se->m_appear.assigned.colour_1.b, wxALPHA_OPAQUE);
    m_v_col_a.push_back(tmp_colour);
    tmp_colour.Set(se->m_appear.assigned.colour_2.r, se->m_appear.assigned.colour_2.g, se->m_appear.assigned.colour_2.b, wxALPHA_OPAQUE);
    m_v_col_a.push_back(tmp_colour);
    tmp_colour.Set(se->m_appear.assigned.colour_3.r, se->m_appear.assigned.colour_3.g, se->m_appear.assigned.colour_3.b, wxALPHA_OPAQUE);
    m_v_col_a.push_back(tmp_colour);
    tmp_colour.Set(se->m_appear.assigned.colour_4.r, se->m_appear.assigned.colour_4.g, se->m_appear.assigned.colour_4.b, wxALPHA_OPAQUE);
    m_v_col_a.push_back(tmp_colour);
    tmp_colour.Set(se->m_appear.assigned.colour_5.r, se->m_appear.assigned.colour_5.g, se->m_appear.assigned.colour_5.b, wxALPHA_OPAQUE);
    m_v_col_a.push_back(tmp_colour);

    m_v_col_ua.clear();
    tmp_colour.Set(se->m_appear.unassigned.colour_1.r, se->m_appear.unassigned.colour_1.g, se->m_appear.unassigned.colour_1.b, wxALPHA_OPAQUE);
    m_v_col_ua.push_back(tmp_colour);
    tmp_colour.Set(se->m_appear.unassigned.colour_2.r, se->m_appear.unassigned.colour_2.g, se->m_appear.unassigned.colour_2.b, wxALPHA_OPAQUE);
    m_v_col_ua.push_back(tmp_colour);
    tmp_colour.Set(se->m_appear.unassigned.colour_3.r, se->m_appear.unassigned.colour_3.g, se->m_appear.unassigned.colour_3.b, wxALPHA_OPAQUE);
    m_v_col_ua.push_back(tmp_colour);
    tmp_colour.Set(se->m_appear.unassigned.colour_4.r, se->m_appear.unassigned.colour_4.g, se->m_appear.unassigned.colour_4.b, wxALPHA_OPAQUE);
    m_v_col_ua.push_back(tmp_colour);
    tmp_colour.Set(se->m_appear.unassigned.colour_5.r, se->m_appear.unassigned.colour_5.g, se->m_appear.unassigned.colour_5.b, wxALPHA_OPAQUE);
    m_v_col_ua.push_back(tmp_colour);
}



/// Get colour of button
void C_wxScrolledWindowCat::getBtnColour(Element el, BtnColour* col)
{
    int i  = calc_days(el.last_update);

    std::vector<wxColour> bg_col;
    int days_1, days_2, days_3, days_4;
    if(el.assigned_to.size() == 0)
    {
        bg_col = m_v_col_ua;
        days_1 = se->m_appear.unassigned.days_1;
        days_2 = se->m_appear.unassigned.days_2;
        days_3 = se->m_appear.unassigned.days_3;
        days_4 = se->m_appear.unassigned.days_4;
    }
    else
    {
        bg_col = m_v_col_a;
        days_1 = se->m_appear.assigned.days_1;
        days_2 = se->m_appear.assigned.days_2;
        days_3 = se->m_appear.assigned.days_3;
        days_4 = se->m_appear.assigned.days_4;
    }


    if(i < 0)
    {
        col->BtnBack = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);
        col->BtnFront = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT);
    }
    else if(i <= days_1)
    {
        col->BtnBack = bg_col[0];
        col->BtnFront = wxColour(0,0,0);
    }
    else if(i <= days_2)
    {
        col->BtnBack = bg_col[1];
        col->BtnFront = wxColour(0,0,0);
    }
    else if(i <= days_3)
    {
        col->BtnBack = bg_col[2];
        col->BtnFront = wxColour(0,0,0);
    }
    else if(i < days_4)
    {
        col->BtnBack = bg_col[3];
        col->BtnFront = wxColour(0,0,0);
    }
    else
    {
        col->BtnBack = bg_col[4];
        col->BtnFront = wxColour(255,255,255);
    }
}


//Check element was assiggned already some time ago and change colour
void C_wxScrolledWindowCat::fadeBtnColour(Element el, BtnColour* col)
{
    // - get history data of element
    // - check assignees of element last time
    // - if element was assigned to same assignee last x days without interruption
    //   - fade colours

    //Only fading if assignee was set
    if (m_assignee.empty())
        return;

    //fade only actual unassigned territories
    if (!el.assigned_to.empty())
        return;

    for (auto &history_item : vHistory)
    {
        if (el.geb_id == history_item.geb_id)
        {
            std::string name = history_item.assignee;
            std::transform(name.begin(), name.end(), name.begin(), std::ptr_fun<int, int>(std::toupper));
            if (name.find(m_assignee) != std::string::npos)
            {
                // Fading (BtnFront / BtnBack)
                col->BtnBack = col->BtnBack.ChangeLightness(175);
                return;
            }
        }
    }
}


/// Calculate days between date and today
int C_wxScrolledWindowCat::calc_days(std::string date) {

    int ret_val = -1;

    if (date.length() < 10)
        return ret_val;
    if (date.length() > 10)
        return ret_val;

    /* char chars_to_remove[] = "-";
    for (unsigned int i = 0; i < strlen(chars_to_remove); ++i)
        date.erase (std::remove(date.begin(), date.end(), chars_to_remove[i]), date.end()); */

    std::string now = build_date();

    try {
        boost::gregorian::date d(boost::gregorian::from_simple_string(date));
        boost::gregorian::date n(boost::gregorian::from_simple_string(now));
        boost::gregorian::days amount = n - d;
        ret_val = amount.days();
    }
    catch(const bad_lexical_cast ) {
        ret_val = -1;
    }

    return ret_val;
}



/// Add button
void C_wxScrolledWindowCat::AddButton(Element el, wxGridSizer* cgs)
{
    int btn_id = get_btn_id(el.geb_id);
    wxButton *Button = new wxButton(this, btn_id, el.geb_nr, wxDefaultPosition, ButtonSize, 0, wxDefaultValidator, _T("wxID_ANY"));
    BtnColour col;
    getBtnColour(el, &col);
    fadeBtnColour(el, &col);
    Button->SetBackgroundColour(col.BtnBack);
    Button->SetForegroundColour(col.BtnFront);
    if (se->m_general.m_use_tooltip_on_territory_tile)
        Button->SetToolTip(wxString::FromUTF8(safe_wx_str(CreateToolTipOfElement(el))));
    Button->Connect(wxEVT_BUTTON,(wxObjectEventFunction)&C_wxScrolledWindowCat::OnElementClicked);

    cgs->Add(Button, 0, wxALL, 0);
}



/// Adjust amount of columns
bool C_wxScrolledWindowCat::AdjustColCnt(void)
{
    bool ret_val = false;

    int btn_per_row = CalcOptimalCols();
    if (btn_per_row == 0)
        return ret_val;

    for (auto a : v_ref_grdsizers)
        if ((btn_per_row < a->GetEffectiveColsCount()) || (a->GetEffectiveRowsCount() > 1))
            a->SetCols(btn_per_row);

    if (AmountCols != btn_per_row) {
        AmountCols = btn_per_row;
        ret_val = true;
    }

    return ret_val;
}



/// Calculate optimal columns
int C_wxScrolledWindowCat::CalcOptimalCols(void)
{
    if (ButtonSize.x == 0)
        return 0;

    int w, h, border_grid_sizer = 5;
    GetClientSize(&w, &h);
    return (w-border_grid_sizer)/ButtonSize.x;
}



/// Trigger event on element clicked
void C_wxScrolledWindowCat::OnElementClicked(wxCommandEvent &event)
{

    wxButton *btn = dynamic_cast<wxButton*>(event.GetEventObject());
    C_wxScrolledWindowCat *swc = dynamic_cast<C_wxScrolledWindowCat*>(btn->GetParent());
    int geb_id = get_geb_id(event.GetId());

    MyFooEvent e(EVT_ELEMENT_CLICK);

    for (auto el : swc->vElements)
        if (el.geb_id == geb_id)
        {
            e.SetElement(el);
            break;
        }

    wxPostEvent(this, e); // to ourselves
}



/// Create tool tip of element
std::string C_wxScrolledWindowCat::CreateToolTipOfElement(Element el) {
    std::string tmp = "";

    tmp += el.geb_bez + " Nr. " + el.geb_nr + " (ID: " + std::to_string(el.geb_id) + ")\n";
    tmp += wxString::Format("Familien: %d\n",  el.families).c_str();
    if (el.act_id != -1)
    {
        tmp += wxString::Format("Zugeteilt: %s\n",                el.assigned_to).c_str();
        tmp += wxString::Format("Ausgabe/letzte Bearbeitung: %s", el.last_update).c_str();
    }
    else
        tmp += wxString::Format("letzte Bearbeitung: %s", el.last_update).c_str();

    return tmp;
}



/// Calculate stats
void C_wxScrolledWindowCat::calc_stats(void)
{
    Stat.unassignd_before_last_yos = 0;
    for (auto e : vElements)
        if (e.assigned_to == "")
            if (is_date_in_current_yos(e.last_update) == -2)
                Stat.unassignd_before_last_yos++;

    Stat.unassignd_last_yos = 0;
    for (auto e : vElements)
        if (e.assigned_to == "")
            if (is_date_in_current_yos(e.last_update) == -1)
                Stat.unassignd_last_yos++;

    Stat.unassignd_last_year = 0;
    for (auto e : vElements)
        if (e.assigned_to == "")
            if (is_date_in_last_year(e.last_update))
                Stat.unassignd_last_year++;
}




void C_wxScrolledWindowCat::load_history_of_unassigned_territories(void)
{
    vHistory.clear();
    unsigned int months = se->m_general.m_assignee_past_months;

    //History of unassigned territories and their past assignees (3 years)
    int rc = open_db();

    std::string query = "";
    query += "SELECT GebietId, Name, Zurueck ";
    query += "FROM tAktion ";
    query += "WHERE Zurueck NOT Null AND Zurueck >= date('now', '-" + std::to_string(months) + " months') ";
    query += "ORDER BY Zurueck";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            History tmp;
            tmp.geb_id   = get_int(COL_0);
            tmp.assignee = get_text(COL_1);
            vHistory.push_back(tmp);
        }

        if(done_or_error(rc))
            break;
    }
    rc = close_db();
}



/// Sort method by geb_id
bool C_wxScrolledWindowCat::SortBy_geb_id(const Element &lhs, const Element &rhs)
{
    return lhs.geb_id < rhs.geb_id;
}



/// Sort method by geb_nr
bool C_wxScrolledWindowCat::SortBy_geb_nr(const Element &lhs, const Element &rhs)
{
    return std::stoi(lhs.geb_nr, nullptr) < std::stoi(rhs.geb_nr, nullptr);
}



/// Sort method by geb_bez
bool C_wxScrolledWindowCat::SortBy_geb_bez(const Element &lhs, const Element &rhs)
{
    return lhs.geb_bez < rhs.geb_bez;
}



/// Sort method by families
bool C_wxScrolledWindowCat::SortBy_families(const Element &lhs, const Element &rhs) {
    return lhs.families < rhs.families;
}



/// Sort method by assigned_to
bool C_wxScrolledWindowCat::SortBy_assigned_to(const Element &lhs, const Element &rhs){
    return lhs.assigned_to < rhs.assigned_to;
}



/// Sort method by last_update
bool C_wxScrolledWindowCat::SortBy_last_update(const Element &lhs, const Element &rhs){
    return lhs.last_update < rhs.last_update;
}



/// Sort method by last_update and assigned status
/// Assigned elements should appear after unassigned ones
bool C_wxScrolledWindowCat::SortBy_last_update_unassigned(const Element &lhs, const Element &rhs){
    std::string c_lhs, c_rhs;

    if (lhs.assigned_to.size() > 0)
        c_lhs = "assigned_" + lhs.last_update;
    else
        c_lhs = lhs.last_update;

    if (rhs.assigned_to.size() > 0)
        c_rhs = "assigned_" + rhs.last_update;
    else
        c_rhs = rhs.last_update;

    return c_lhs < c_rhs;
}

void C_wxScrolledWindowCat::OnGridSelectCell(wxGridEvent& event)
{
    wxGrid *grid = dynamic_cast<wxGrid*>(event.GetEventObject());
    C_wxScrolledWindowCat *swc = dynamic_cast<C_wxScrolledWindowCat*>(grid->GetParent());

    int i = event.GetRow();
    grid->SelectRow(i, false /*don't add to existing selection*/);


    //Get Geb.-Id
    int geb_id = wxAtoi(grid->GetCellValue(i, COL_0));

    MyFooEvent e(EVT_ELEMENT_CLICK);

    for (auto el : swc->vElements)
        if (el.geb_id == geb_id)
        {
            e.SetElement(el);
            break;
        }

    wxPostEvent(this, e); // to ourselves
}
