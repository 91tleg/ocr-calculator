#include "assert.h"
#include <cstdio>
#include <cinttypes>
#include "../log/log.h"

namespace sys {

[[noreturn]] void assert_handler(const char* expr, const char* file, const int line)
{
    char buf[256];
    uint32_t pc = reinterpret_cast<uint32_t>(__builtin_return_address(0));
    uint32_t lr;
    uint32_t sp;
    __asm__ volatile(
        "mov %[lr_out], lr\n"
        "mov %[sp_out], sp\n"
        : [lr_out] "=r" (lr), [sp_out] "=r" (sp)
    );

    std::snprintf(buf, sizeof(buf),
        "expr %s file %s line %d pc 0x%08" PRIX32
        " lr 0x%08" PRIX32 " sp 0x%08" PRIX32,
        expr, file, line, pc, lr, sp);
    LOG_E("assert failed at %s", buf);

    for ( ;; ) {
        __asm__ volatile("bkpt #0");
    }
}

} // namespace sys