#include <iostream>
#include "dispatcher.h"

QueueHandle_t Dispatcher::eventQueue = xQueueCreate(DISPATCHER_QUEUE_SIZE, sizeof(Event));

Dispatcher::Dispatcher() {}

void Dispatcher::subscribe(QueueHandle_t receivingQueue, Event topic) {

}

void Dispatcher::dispatchTask(void *pvParameters) {
    void * eventBuf = malloc(sizeof(Event));
    while(1) {
        if(xQueueReceive(eventQueue, eventBuf, portMAX_DELAY) == pdTRUE) {
            Event receivedEvent = * (Event*) eventBuf;
            std::cout << "Dispatcher received: " << receivedEvent.data << std::endl;
        }
        else {
            // TODO: Log Entry
            // Should not happen with xQueueReceive being blocked until receiving an event.
            configASSERT(pdFALSE);
        }
    }
    free(eventBuf);
}

QueueHandle_t* Dispatcher::getEventQueue() {
    return &eventQueue;
}