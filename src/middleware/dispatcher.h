#ifndef _DISPATCHER_H
#define _DISPATCHER_H

#include <FreeRTOS.h>
#include <queue.h>
#include "events.h"

#define DISPATCHER_QUEUE_SIZE 32

/*
Singleton class Dispatcher

*/
class Dispatcher{
public:
    static Dispatcher* getInstance() {
        static Dispatcher instance;
        return &instance;
    }

    QueueHandle_t* getEventQueue();

    static void dispatchTask(void *pvParameters);

    void subscribe(QueueHandle_t receivingQueue, Event topic);
    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

private:
    Dispatcher() = default;
    static QueueHandle_t eventQueue;
};

#endif /*_DISPATCHER_H*/