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

#ifndef NDEBUG
#define LOG_E(fmt, ...) sys::log::error(fmt, ##__VA_ARGS__)
#define LOG_W(fmt, ...) sys::log::warn(fmt,  ##__VA_ARGS__)
#define LOG_I(fmt, ...) sys::log::info(fmt,  ##__VA_ARGS__)
#define LOG_D(fmt, ...) sys::log::debug(fmt, ##__VA_ARGS__)
#else
#define LOG_E(fmt, ...) ( (void)0 )
#define LOG_W(fmt, ...) ( (void)0 )
#define LOG_I(fmt, ...) ( (void)0 )
#define LOG_D(fmt, ...) ( (void)0 )
#endif // NDEBUG

#endif // LOG_H