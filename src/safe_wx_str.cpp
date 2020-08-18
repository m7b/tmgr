/****************************************************************************
 * Copyright (C) 2019 by Mark Buttig                                        *
 *                                                                          *
 * This file is part of tMGR.                                               *
 *                                                                          *
 *   tMGR is free software: you can redistribute it and/or modify it        *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   tMGR is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with tMGR.  If not, see <http://www.gnu.org/licenses/>.  *
 ****************************************************************************/

/**
 * @file safe_wx_str.cpp
 * @author Mark Buttig
 * @date 11.01.2019
 * @brief For safe wxString conversions
 */

#include "safe_wx_str.h"

#ifdef wxNO_UNSAFE_WXSTRING_CONV
std::string safe_wx_str(std::string str){return str;};
#else /* wxNO_UNSAFE_WXSTRING_CONV */
const char* safe_wx_str(std::string str){return str.c_str();};
#endif /* wxNO_UNSAFE_WXSTRING_CONV */
