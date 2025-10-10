#ifndef LOG_H
#define LOG_H

#include <cstdint>
#include <cstdarg>

namespace sys {

enum class log_level : uint8_t {
    none  = 0U,
    error = 1U,
    warn  = 2U,
    info  = 3U,
    debug = 4U
};

class log
{
public:
    using write_func_t = void(*)(const char* str);
    static void init(log_level level, write_func_t writer = nullptr);
    static void error(const char* fmt, ...);
    static void warn (const char* fmt, ...);
    static void info (const char* fmt, ...);
    static void debug(const char* fmt, ...);

private:
    static void write(log_level lvl, const char* fmt, va_list args);
    static const char* level_to_str(log_level lvl);

    static inline log_level _level = log_level::info;
    static inline write_func_t _writer = nullptr;
};

} // namespace sys

#endif // LOG_H