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
 * @file C_DbHandle.cpp
 * @author Mark Buttig
 * @date 11.01.2019
 * @brief Database handling
 */

#include "C_DbHandle.h"
#include <stdio.h>

C_DbHandle::C_DbHandle(const std::string *f)
: /*db_file(*f), */db(0), db_stmt(0), query("")
{
    //ctor
    if (f)
    {
        db_file = *f;
    }
}

C_DbHandle::~C_DbHandle()
{
    //dtor
}

void C_DbHandle::set_db_file(const std::string *file)
{
    db_file = *file;
}

std::string C_DbHandle::get_db_file(void)
{
    return db_file;
}

std::string C_DbHandle::get_last_query(void)
{
    return query;
}

int C_DbHandle::open_db(void)
{
    return sqlite3_open(db_file.c_str(), &db);
    //SQLITE_OK
}

int C_DbHandle::close_db(void)
{
    int rc;
    rc = sqlite3_finalize(db_stmt);
    rc = sqlite3_close(db);
    return rc;
}

int C_DbHandle::close_no_finalize_db(void)
{
    int rc;
    rc = sqlite3_close(db);
    return rc;
}

int C_DbHandle::query_db(const std::string *query)
{
    this->query = *query;
    return sqlite3_prepare_v2(db, query->c_str(), -1, &db_stmt, 0);
    //SQLITE_OK
}

int C_DbHandle::step_db(void)
{
    return sqlite3_step(db_stmt);
}

int C_DbHandle::exec_db(const std::string *query)
{
    int rc;
    char *zErrMsg = 0;

    rc = sqlite3_exec(db, query->c_str(), NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        sqlite3_free(zErrMsg);
    }

    return rc;
}

bool C_DbHandle::is_error(int rc)
{
    bool ret_val = false;

    if (rc >= SQLITE_ERROR && rc <= SQLITE_WARNING)
    {
        ret_val = true;
    }

    return ret_val;
}

bool C_DbHandle::done_or_error(int rc)
{
    bool ret_val = false;

    if (rc == SQLITE_DONE || rc == SQLITE_ERROR || rc == SQLITE_MISUSE)
    {
        ret_val = true;
    }

    return ret_val;
}

int C_DbHandle::get_int(int col)
{
    return sqlite3_column_int (db_stmt, col);
}

std::string C_DbHandle::get_text(int col)
{
    const char* data = reinterpret_cast<const char*>(sqlite3_column_text(db_stmt, col));
    if (data != 0)
    {
        return std::string(data);
    }
    else
    {
        return std::string();
    }
}

int C_DbHandle::last_insert_rowid(void)
{
    return sqlite3_last_insert_rowid(db);
}

const char *C_DbHandle::get_errormsg(void)
{
    return sqlite3_errmsg(db);
}
