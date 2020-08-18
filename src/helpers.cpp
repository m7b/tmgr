#include "helpers.h"

bool check_file_present(const std::string &file)
{
    if (file.empty())
        return false;

    std::fstream f;
    f.open(file);
    if (f.is_open())
    {
        f.close();
        return true;
    }
    else
        return false;
}

std::string build_timestamp(void)
{
    time_t sekunden = time(NULL);
    char str[100];
    std::strftime(str, sizeof(str), "%Y%m%d-%H%M%S", localtime(&sekunden));
    return str;
}

/// Returns a string containing the actual date (today) in the form
/// YYYY-mm-dd
std::string build_date(void)
{
    time_t sekunden = time(NULL);
    char str[100];
    std::strftime(str, sizeof(str), "%Y-%m-%d", localtime(&sekunden));
    return str;
}


/// Calculate days between today and a given date in form of
/// yyyy-mm-dd or dd.mm.yyyy.
/// \return
/// - negative values: given date is in future.
/// - positive values: given date is in past
int days_passed(const std::string &str_date)
{
    namespace bd = boost::gregorian;

    bd::date bd_date = boost_date_from_string(str_date);
    bd::date today = bd::day_clock::local_day();
    bd::days bd_days = today - bd_date;

    return bd_days.days();
}

/// Transform a string date in form of YYYY-mm-dd or dd.mm.YYYY
/// to a boost::gregorian::date
boost::gregorian::date boost_date_from_string(std::string str_date)
{
    namespace bd = boost::gregorian;

    bd::date bd_date(0);

    if (str_date.compare(4, 1, "-") == 0)
    {
        // From delimited date string where with order year-month-day 2019-12-31
        try{bd_date = bd::from_simple_string(str_date);}
        catch (std::exception& e){}
    }
    else if (str_date.compare(2, 1, ".") == 0)
    {
        // From delimited date string where with order day-month-year 31.12.2019
        try{bd_date = bd::from_uk_string(str_date);}
        catch (std::exception& e){}
    }

    return bd_date;
}

/// Determin if date is in past/current/future year of service (yos)
/// \return
/// -1: past
///  0: current
///  1: future
int is_date_in_current_yos(const std::string &str_date)
{
    namespace bd = boost::gregorian;

    //get boost date from string date
    bd::date bd_date = boost_date_from_string(str_date);

    //get date of today
    bd::date today = bd::day_clock::local_day();

    bd::date start_yos, end_yos;

    //Zeitpunkt neues Dienstjahr: 1. September
    bd::partial_date new_yos_day(1, bd::Sep);

    //Bestimme Datum Anfang/Ende aktuelles DJ
    if (today < new_yos_day.get_date(today.year()))
    {
        start_yos = new_yos_day.get_date(today.year()) - bd::years(1);
        end_yos   = new_yos_day.get_date(today.year()) - bd::days(1);
    }

    if (today >= new_yos_day.get_date(today.year()))
    {
        start_yos = new_yos_day.get_date(today.year());
        end_yos   = new_yos_day.get_date(today.year()) + bd::years(1) - bd::days(1);
    }

    //Ist Str_Datum kleiner Anfang  vorheriges DJ
    if (bd_date < start_yos - bd::years(1))
    {
        return -2;
    }

    //Ist Str_Datum kleiner Anfang DJ
    if (bd_date < start_yos)
    {
        return -1;
    }

    //Ist Str_Datum zwischen Anfang und Ende DJ
    if ((bd_date >= start_yos) && (bd_date <= end_yos))
    {
        return 0;
    }

    //Ist Str_Datum gr��er Ende DJ
    if (bd_date > end_yos)
    {
        return 1;
    }

    //Irgendein Fehler ist passiert (kann nicht sein ;-)
    return -99;
}

/// Determine if date is in last year
/// \return
/// true: date is in last year
/// false: date is not in last year
bool is_date_in_last_year(const std::string &str_date)
{
    namespace bd = boost::gregorian;

    //get boost date from string date
    bd::date bd_date = boost_date_from_string(str_date);

    //get date of today
    bd::date today = bd::day_clock::local_day();

    //Zeitpunkt neues Hahr: 1. Januar
    bd::partial_date new_year_day(1, bd::Jan);

    //Bestimme Datum kleiner aktuelles Jahr
    if (bd_date < new_year_day.get_date(today.year()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// Determine start date of pre current year of service of today
/// \return Year of yos
std::string start_date_pre_current_yos(void)
{
    namespace bd = boost::gregorian;
    bd::date start_yos, end_yos;

    //get date of today
    bd::date today = bd::day_clock::local_day();

    //Zeitpunkt neues Dienstjahr: 1. September
    bd::partial_date new_yos_day(1, bd::Sep);

    //Bestimme Datum Anfang/Ende aktuelles DJ
    if (today < new_yos_day.get_date(today.year()))
    {
        start_yos = new_yos_day.get_date(today.year()) - bd::years(2);
        end_yos   = new_yos_day.get_date(today.year()) - bd::days(1);
    }

    //Bestimme Datum Anfang/Ende letztes DJ
    if (today >= new_yos_day.get_date(today.year()))
    {
        start_yos = new_yos_day.get_date(today.year()) - bd::years(1);
        end_yos   = new_yos_day.get_date(today.year()) + bd::years(0) - bd::days(1);
    }

    return bd::to_simple_string(start_yos);
}

/// Determine start date of current year of service of today
/// \return Year of yos
std::string start_date_current_yos(void)
{
    namespace bd = boost::gregorian;
    bd::date start_yos, end_yos;

    //get date of today
    bd::date today = bd::day_clock::local_day();

    //Zeitpunkt neues Dienstjahr: 1. September
    bd::partial_date new_yos_day(1, bd::Sep);

    //Bestimme Datum Anfang/Ende aktuelles DJ
    if (today < new_yos_day.get_date(today.year()))
    {
        start_yos = new_yos_day.get_date(today.year()) - bd::years(1);
        end_yos   = new_yos_day.get_date(today.year()) - bd::days(1);
    }

    //Bestimme Datum Anfang/Ende letztes DJ
    if (today >= new_yos_day.get_date(today.year()))
    {
        start_yos = new_yos_day.get_date(today.year());
        end_yos   = new_yos_day.get_date(today.year()) + bd::years(1) - bd::days(1);
    }

    return bd::to_simple_string(start_yos);
}

/// Determine start date of current year
/// \return current year
std::string start_date_current_year(void)
{
    namespace bd = boost::gregorian;
    bd::date start_year;

    //get date of today
    bd::date today = bd::day_clock::local_day();

    //Zeitpunkt neues Dienstjahr: 1. September
    bd::partial_date new_year_day(1, bd::Jan);

    start_year = new_year_day.get_date(today.year());

    return bd::to_simple_string(start_year);
}


void replace_all(std::string &content, const std::string &to_replace,
                 const std::string &replacement)
{
    boost::replace_all(content, to_replace, replacement);
}


void get_resource_file(std::string &content, const wchar_t *identifier)
{
    HRSRC a_resource = FindResource(0, identifier, RT_RCDATA);
    if (a_resource != 0)
    {
        HGLOBAL a_resHandle = LoadResource(NULL, a_resource);
        if (a_resHandle != 0)
        {
            DWORD res_size = SizeofResource(0, a_resource);
            auto firstByte = reinterpret_cast<const char*>(LockResource(a_resHandle));

            std::stringstream ss;
            ss.write(firstByte, res_size);
            content = ss.str();
            replace_all(content, "\r\n", "\n");
        }
    }
}
