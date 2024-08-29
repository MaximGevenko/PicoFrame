#ifndef _GPIO_CONTROL_H
#define _GPIO_CONTROL_H

class GPIO_Control {
public:
    void init();
private:
    static void button_ISR(uint gpio, uint32_t events);
};

#endif /*_GPIO_CONTROL_H*/