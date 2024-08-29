
#include "ClockApp.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"
#include "utils/font8x8_basic.h"

static void alarm_callback();

void ClockApp::setup() {
    std::cout << "Setup for ClockApp" << std::endl;

    /* setup datetime */
    datetime_t default_time = {
        .year  = 2024,
        .month = 8,
        .day   = 28,
        .dotw  = 3, // 0 is Sunday, so 3 is Wednesday
        .hour  = 16,
        .min   = 52,
        .sec   = 30
    };
    rtc_init();
    rtc_set_datetime(&default_time);

    std::cout << "[CLOCK_APP] Set default time to: " << default_time.hour << ":" << default_time.min << std::endl;

    /* setup alarm */
    /* datetime_t alarm_time = {
        .year  = -1,
        .month = -1,
        .day   = -1,
        .dotw  = -1, // 0 is Sunday, so 3 is Wednesday
        .hour  = -1,
        .min   = -1,
        .sec   = 00
    };
    rtc_set_alarm(&alarm_time, &alarm_callback); */

}

static void alarm_callback() {
    //_led_matrix.drawChar(Vector2D{1,4}, font8x8_basic['1']);
}

void ClockApp::loop() {
    std::cout << "Loop for ClockApp" << std::endl;


    //_led_matrix.fillRect(1,1,6,6);

    //_led_matrix.drawPoint(Vector2D{(int8_t)(counter % 16), (int8_t)(counter / 16)});


    _led_matrix.clear();
    /* ---Drawing--- */
    _led_matrix.setColor(15, 15, 15);
    _led_matrix.fillRect(Vector2D{0,0}, 16, 16);

    datetime_t current_time;
    rtc_get_datetime(&current_time);

    std::cout << "[CLOCK_APP] current time: " << current_time.hour << ":" << current_time.min << std::endl;

    int hour = current_time.hour;
    int min = current_time.min;

    _led_matrix.setColor(0, 0, 0);
    _led_matrix.drawChar(Vector2D{0,0}, font8x8_basic[(hour/10)+48]);
    _led_matrix.drawChar(Vector2D{8,0}, font8x8_basic[(hour%10)+48]);

    _led_matrix.setColor(0, 0, 0);
    _led_matrix.drawChar(Vector2D{0,8}, font8x8_basic[(min/10)+48]);
    _led_matrix.drawChar(Vector2D{8,8}, font8x8_basic[(min%10)+48]);
 
    //_led_matrix.drawChar(Vector2D{1,4}, font8x8_basic['1']);


    _led_matrix.update();
    APP_SLEEP(1000);
}