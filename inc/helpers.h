#ifndef HELPERS_H
#define HELPERS_H

#include <windows.h>
#include <string>
#include <fstream>
#include "ctime"

#include "boost/date_time/gregorian/gregorian.hpp"
#include <boost/algorithm/string/replace.hpp>

bool check_file_present(const std::string &file);
std::string build_timestamp(void);
std::string build_date(void);

int days_passed(const std::string &str_date);
boost::gregorian::date boost_date_from_string(std::string str_date);
int is_date_in_current_yos(const std::string &str_date);
bool is_date_in_last_year(const std::string &str_date);
std::string start_date_pre_current_yos(void);
std::string start_date_current_yos(void);
std::string start_date_current_year(void);

void replace_all(std::string &content, const std::string &to_replace, const std::string &replacement);
void get_resource_file(std::string &content, const wchar_t *identifier);

#endif // HELPERS_H
