#include <iostream>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <vector>
#include "MatrixConfig.h"
#include "middleware/dispatcher.h"
#include "application/context.h"
#include "application/ApplicationManager.h"
#include "HAL/gpio_control.h"
#include "HAL/led_matrix.h"
#include "middleware/events.h"

extern uint8_t __flash_binary_end;

using namespace std;

int main() {

    stdio_init_all();
    cout << "____________________________\nled-matrix boot up..." << endl;
    // Print binary flash information
    uint8_t* binary_end = &__flash_binary_end;
    uint32_t binary_size = (uint32_t)(binary_end - XIP_BASE);
    cout << "Binary end at: " << (void *)binary_end << " with " << binary_size << " bytes in size." << endl;


    // Resources
    uint32_t* frame_buffer = (uint32_t*) malloc(sizeof(uint32_t) * MATRIX_WIDTH * MATRIX_HEIGHT);
    //uint32_t frame_buffer[MATRIX_WIDTH][MATRIX_HEIGHT];

    QueueHandle_t appManagerQueue = xQueueCreate(DISPATCHER_QUEUE_SIZE, sizeof(Event));


    Dispatcher* dispatcher = Dispatcher::getInstance();
    GPIO_Control gpio;
    gpio.init();
    LED_Matrix ledMatrix(frame_buffer);
    ClockApp clockApp(ledMatrix);
    
    BaseType_t dispatcherTask = xTaskCreate(Dispatcher::dispatchTask, "DISPATCH_TASK", 128, NULL, 3, NULL);
    BaseType_t clockAppTask = xTaskCreate(Application::run, "CLOCK_APP_TASK", 128, (void *) &clockApp, 3, NULL);

    vTaskStartScheduler();
    
    return 0;
}