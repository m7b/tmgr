#ifndef SAFE_WX_STR_H
#define SAFE_WX_STR_H

#include <string>

#ifdef wxNO_UNSAFE_WXSTRING_CONV
std::string safe_wx_str(std::string str);
#else /* wxNO_UNSAFE_WXSTRING_CONV */
const char* safe_wx_str(std::string str);
#endif /* wxNO_UNSAFE_WXSTRING_CONV */

#endif // SAFE_WX_STR_H
