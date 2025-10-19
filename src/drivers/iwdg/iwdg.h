#ifndef IWDG_H
#define IWDG_H

#include <cstdint>

namespace drv {

class iwdg
{
public:
    explicit iwdg(uint32_t timeout_ms);

    /**
     * @brief Initialize and start the IWDG
     */
    void init();

    /**
     * @brief Refresh the timer
     */
    void reset();

private:
    uint32_t _timeout_ms;
};

} // namespace drv

#endif // IWDG_H