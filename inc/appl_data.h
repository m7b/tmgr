#ifndef APPL_DATA_H_INCLUDED
#define APPL_DATA_H_INCLUDED

#include <string>

// DSGVO Setting of the app:
//   true:  All reports are without names
//   false: All reports are with names
#define DSGVO false

const std::string sCR_LF     = "\n";
const std::string sBLANK     = " ";

struct ApplicationData
{
    std::string work_dir;
    std::string db_file;
    std::string settings_file;
};

#endif // APPL_DATA_H_INCLUDED
