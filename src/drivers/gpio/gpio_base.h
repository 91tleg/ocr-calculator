#ifndef GPIO_BASE_H
#define GPIO_BASE_H

namespace drv {

class gpio_base
{
public:
    virtual void init() = 0;
    virtual void set() = 0;
    virtual void clear() = 0;
    virtual bool read() const = 0;
    virtual ~gpio_base() = default;
};

} //namespace drv

#endif // GPIO_BASE_H