#include <iostream>
#include <FreeRTOS.h>
#include <queue.h>
#include <functional>
#include "pico/stdlib.h"
#include "gpio_control.h"
#include "middleware/dispatcher.h"
#include "middleware/events.h"

using namespace std;

void GPIO_Control::init() {
    gpio_init(15);
    gpio_set_dir(15, GPIO_IN);
    
    gpio_set_irq_enabled_with_callback(15, GPIO_IRQ_EDGE_RISE, 1, button_ISR);
    gpio_set_irq_enabled(14, GPIO_IRQ_EDGE_RISE, 1);
}

void GPIO_Control::button_ISR(uint gpio, uint32_t events) {
    QueueHandle_t* eventQueue = Dispatcher::getInstance()->getEventQueue();
    if (gpio == 14)
        cout << "Wire bridged !!!" << endl;
    else if(gpio == 15)
        cout << "BUTTON PRESSED !!!" << endl;
        Event event;
        event.data = 0;
        event.type = EventType::BUTTON_DOWN;
        xQueueSendFromISR(*eventQueue, &event, NULL);
}