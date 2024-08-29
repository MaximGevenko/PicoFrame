
#include "middleware/events.h"
#include "ApplicationManager.h"

ApplicationManager::ApplicationManager(const QueueHandle_t* receiverQueue) {
    _receiverQueue = receiverQueue;
    //TODO: make task pointer class global
    BaseType_t managerTask = xTaskCreate(ApplicationManager::managerTask, "DISPATCH_TASK", 128, (void *)_receiverQueue, 3, NULL);
}

ApplicationManager::~ApplicationManager() {

}

void ApplicationManager::managerTask(void * args) {

    void * eventBuf = malloc(sizeof(Event));
    while(1) {
        if(xQueueReceive(*_receiverQueue, eventBuf, portMAX_DELAY) == pdTRUE) {
            Event receivedEvent = * (Event*) eventBuf;
            std::cout << "AppManager received: " << receivedEvent.data << std::endl;
        }
        else {
            // TODO: Log Entry
            // Should not happen with xQueueReceive being blocked until receiving an event.
            configASSERT(pdFALSE);
        }
    }
    free(eventBuf);
}

void ApplicationManager::nextApp() {
    //IApplication* app = new ClockApp();
    //switchApplication(app);
}