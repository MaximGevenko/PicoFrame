#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <FreeRTOS.h>
#include <task.h>

#define APP_SLEEP(x) vTaskDelay(x / portTICK_PERIOD_MS)

class Application {
public:
    static void run(void * args) {
        Application* app = (Application*)args;

        app->setup();
        while(1) app->loop();
    }
    virtual ~Application() {};
private:
    virtual void setup() = 0;
    virtual void loop() = 0;
};

#endif /* _APPLICATION_H */