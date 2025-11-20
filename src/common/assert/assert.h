#ifndef ASSERT_H
#define ASSERT_H

#include <cstdint>

#ifndef NDEBUG

namespace sys {

[[noreturn]] void assert_handler(const char* expr, const char* file, const int line);

} //namespace sys

#define ASSERT(expr)                                        \
    do {                                                    \
        if (!(expr)) {                                      \
            sys::assert_handler(#expr, __FILE__, __LINE__); \
        }                                                   \
    } while(0)

#else 
#define ASSERT(expr) ( (void)0 )
#endif // NDEBUG

#endif // ASSERT_H