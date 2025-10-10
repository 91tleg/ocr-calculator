#include "log.h"
#include <cstring>
#include <cstdio>

namespace sys {

__attribute__((weak)) void log_default_write(const char* str)
{
    std::printf("%s\n", str);
}

void log::init(log_level level, write_func_t writer)
{
    _level = level;
    _writer = writer;
}

void log::write(log_level lvl, const char* fmt, va_list args)
{
    if (static_cast<uint8_t>(lvl) > static_cast<uint8_t>(_level)) {
        return;
    }

    char buf[128];
    int len = std::snprintf(buf, sizeof(buf), "[%s] ", level_to_str(lvl));
    std::vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    _writer ? _writer(buf) : log_default_write(buf);
}

void log::error(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    write(log_level::error, fmt, args);
    va_end(args);
}

void log::warn(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    write(log_level::warn, fmt, args);
    va_end(args);
}

void log::info(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    write(log_level::info, fmt, args);
    va_end(args);
}

void log::debug(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    write(log_level::debug, fmt, args);
    va_end(args);
}

const char* log::level_to_str(log_level lvl)
{
    switch (lvl) {
        case log_level::error: return "ERR";
        case log_level::warn:  return "WRN";
        case log_level::info:  return "INF";
        case log_level::debug: return "DBG";
        default:               return "";
    }
}

} // namespace sys