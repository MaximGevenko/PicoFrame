#ifndef _LED_MATRIX_H
#define _LED_MATRIX_H

#include <FreeRTOS.h>
#include <queue.h>
#include "utils/Vector2DUtil.h"
#include "MatrixConfig.h"

using namespace Vector2DUtil;

class LED_Matrix {
public:
    LED_Matrix(uint32_t* frameBuffer);
    ~LED_Matrix() {
        
    }
    void clear();
    void fillRect(Vector2D pos, int width, int height);
    void drawLine(Vector2D startPos, Vector2D endPos);
    void drawPoint(Vector2D pos);
    void drawCircle(Vector2D middle, uint8_t radius);
    void drawChar(Vector2D pos, char *c);
    void setColor(uint8_t r, uint8_t g, uint8_t b);

    void update();

private:
    uint32_t _currentColor = 0x11111111;
    uint32_t* _FRAME_BUFFER;
    void put_pixel(uint32_t pixel_grb);


    // Just for demo
    void fillFrameBufferExample(bool inverse);
};

#endif /*_LED_MATRIX_H*/