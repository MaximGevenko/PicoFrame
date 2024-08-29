#include <iostream>
#include "HAL/led_matrix.h"
#include "Application.h"

class ClockApp : public Application {
public:
    ClockApp (LED_Matrix& led_matrix) : _led_matrix(led_matrix) {

    }
private:
    LED_Matrix& _led_matrix;

    void setup() override;
    void loop() override;
};