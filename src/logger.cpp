#include "logger.h"

void init_logging()
{
    auto rotating_logger = spdlog::rotating_logger_mt(SPDLOG_NAME, SPDLOG_FILENAME, 262144, 1);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e UTC%z] [%l] [thread %t] [process %P] %v");
    spdlog::flush_on(spdlog::level::info);
    LOG->info("spdlog initialized");
    //TODO(mjb): logging: functionality to add __FILE__ , __FUNCTION__, __LINE__
}




fct_dbg::fct_dbg(const std::string &text)
{
    m_text = text;
    LOG->info("{}: entry", m_text);
}

fct_dbg::~fct_dbg()
{
    LOG->info("{}: out", m_text);
}
