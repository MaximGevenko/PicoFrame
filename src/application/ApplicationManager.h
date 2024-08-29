#ifndef _APPLICATION_MANAGER_H
#define _APPLICATION_MANAGER_H

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "Application.h"
#include "ClockApp.h"

// !!!
// ApplicationManager is fully static but relies on constructor parameter of conrete object


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class ApplicationManager {
public:
    ApplicationManager(const QueueHandle_t* receiverQueue);
    ~ApplicationManager();
    static void managerTask(void * args);
    static void nextApp();
private:
    const static QueueHandle_t* _receiverQueue;
    static BaseType_t _currentTask;
    static Application* _currentApp;
    static void switchApplication(Application* newApp) {
        _currentApp = newApp;
    }
};

#endif /* _APPLICATION_MANAGER_H */