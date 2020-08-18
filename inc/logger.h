#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

#define SPDLOG_NAME     "tmgr_logger"
#define SPDLOG_FILENAME "tmgr.log"
#define                 LOG spdlog::get(SPDLOG_NAME)

void init_logging(void);

//Simplified usage uf function logging:
//LOG_FUNCTION;
#define LOG_FUNCTION fct_dbg a(__func__)

// example for usage: fct_dbg a(__func__); at the beginning of debugged function
class fct_dbg
{
    public:
        fct_dbg(const std::string &text);
        ~fct_dbg();

    private:
        std::string m_text;
};

#endif // LOGGER_H
