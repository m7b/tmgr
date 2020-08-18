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
 * @file C_DbHandle.h
 * @author Mark Buttig
 * @date 11.01.2019
 * @brief Database handling
 */

#ifndef C_DBHANDLE_H
#define C_DBHANDLE_H

#include <string>
#include "sqlite3.h"

class C_DbHandle
{
    public:

        enum ColumnColumn
        {
          COL_0 = 0,
          COL_1,
          COL_2,
          COL_3,
          COL_4,
          COL_5,
          COL_6,
          COL_7,
          COL_8,
          COL_9
        };

        //C_DbHandle();
        C_DbHandle(const std::string *db_file);
        virtual ~C_DbHandle();

        void set_db_file(const std::string *db_file);
        std::string get_db_file(void);
        std::string get_last_query(void);

        int open_db(void);
        int close_db(void);
        int close_no_finalize_db(void);
        int query_db(const std::string *query);
        int step_db(void);
        int exec_db(const std::string *query);

        bool is_error(int rc);
        bool done_or_error(int rc);

        int get_int(int col);
        std::string get_text(int col);
        int last_insert_rowid(void);

        const char *get_errormsg(void);

    protected:

    private:

        std::string db_file;
        sqlite3 *db;
        sqlite3_stmt *db_stmt;

        std::string query;

};

#endif // C_DBHANDLE_H
