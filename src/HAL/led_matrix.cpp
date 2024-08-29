
#include <iostream>
#include <hardware/pio.h>
#include <string.h>
#include <cmath>
#include "led_matrix.h"
#include "ws2812.pio.h"
#include "middleware/events.h"
#include "utils/font8x8_basic.h"

LED_Matrix::LED_Matrix(uint32_t* frameBuffer) : _FRAME_BUFFER(frameBuffer) {

    memset(_FRAME_BUFFER, 0, 4*MATRIX_HEIGHT*MATRIX_WIDTH);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, 2, 800000, false);

    //fillFrameBufferExample(false);
    //update();

}

void LED_Matrix::fillRect(Vector2D pos, int width, int height) {
    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {
            drawPoint(Vector2D{(int8_t)(pos.x + x), (int8_t)(pos.y + y)});
        }
    }
}

void LED_Matrix::clear() {
    memset(_FRAME_BUFFER, 0, 4*MATRIX_HEIGHT*MATRIX_WIDTH);
}

void LED_Matrix::drawPoint(Vector2D pos) {
    _FRAME_BUFFER[pos.x + MATRIX_WIDTH * pos.y] = _currentColor;
    //_FRAME_BUFFER[pos_x][pos_y] = 0x00111111;
}

void LED_Matrix::drawCircle(Vector2D middle, uint8_t radius) {

    uint8_t xc = middle.x;
    uint8_t yc = middle.y;

    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    drawPoint(Vector2D{(int8_t)(xc + x), (int8_t)(yc + y)});
    drawPoint(Vector2D{(int8_t)(xc - x), (int8_t)(yc + y)});
    drawPoint(Vector2D{(int8_t)(xc + x), (int8_t)(yc - y)});
    drawPoint(Vector2D{(int8_t)(xc - x), (int8_t)(yc - y)});
    drawPoint(Vector2D{(int8_t)(xc + y), (int8_t)(yc + x)});
    drawPoint(Vector2D{(int8_t)(xc - y), (int8_t)(yc + x)});
    drawPoint(Vector2D{(int8_t)(xc + y), (int8_t)(yc - x)});
    drawPoint(Vector2D{(int8_t)(xc - y), (int8_t)(yc - x)});

    while (y >= x) {
        x++;

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }

        drawPoint(Vector2D{(int8_t)(xc + x), (int8_t)(yc + y)});
        drawPoint(Vector2D{(int8_t)(xc - x), (int8_t)(yc + y)});
        drawPoint(Vector2D{(int8_t)(xc + x), (int8_t)(yc - y)});
        drawPoint(Vector2D{(int8_t)(xc - x), (int8_t)(yc - y)});
        drawPoint(Vector2D{(int8_t)(xc + y), (int8_t)(yc + x)});
        drawPoint(Vector2D{(int8_t)(xc - y), (int8_t)(yc + x)});
        drawPoint(Vector2D{(int8_t)(xc + y), (int8_t)(yc - x)});
        drawPoint(Vector2D{(int8_t)(xc - y), (int8_t)(yc - x)});
    }

    /* float PI = 3.14159265;
    //TODO: reduce delta-steps for efficiency
    float param;
    int8_t x;
    int8_t y;
    for (int omega = 0; omega<360; omega++) {
        param = omega*PI/180;
        x = radius*(cos(param) - sin(param)) + middle.x;
        y = radius*(sin(param) + cos(param)) + middle.y;
        drawPoint(Vector2D{x,y});
    } */
}



void LED_Matrix::drawLine(Vector2D startPos, Vector2D endPos) {
    int8_t x0 = startPos.x;
    int8_t y0 = startPos.y;
    int8_t x1 = endPos.x;
    int8_t y1 = endPos.y;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        drawPoint(Vector2D{x0, y0});
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { 
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void LED_Matrix::drawChar(Vector2D pos, char *bitmap) {


    int x,y;
    int set;
    for (x=0; x < 8; x++) {
        for (y=0; y < 8; y++) {
            set = bitmap[x] & 1 << y;
            //printf("%c", set ? 'X' : ' ');
            if(set)
                drawPoint(vectorAdd(pos, Vector2D{(int8_t)y,(int8_t)x}));
        }
    }

    /* Vector2D letter[] = {                   Vector2D{1,0},
                            Vector2D{0,1},                  Vector2D{2,1},
                            Vector2D{0,2},  Vector2D{1,2},  Vector2D{2,2},
                            Vector2D{0,3},                  Vector2D{2,3},
                            Vector2D{0,4},                  Vector2D{2,4}};

    for(int i=0; i<10; i++) {
        drawPoint(vectorAdd(pos, letter[i]));
    } */
}


void LED_Matrix::setColor(uint8_t r, uint8_t g, uint8_t b) {
    _currentColor = (g << 16) | (r << 8) | b;
}

void LED_Matrix::update() {
    for(int y=0; y< MATRIX_HEIGHT; y++) {
        for(int x=0; x< MATRIX_WIDTH; x++) {
            if(y % 2 != 0) {
                put_pixel(_FRAME_BUFFER[x + MATRIX_WIDTH*y]);
            }
            else {
                put_pixel(_FRAME_BUFFER[(MATRIX_WIDTH-1 - x) + MATRIX_WIDTH*y]);
            }
            //put_pixel(_FRAME_BUFFER[x][y]);
        }
    }
}

void LED_Matrix::put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}



void LED_Matrix::fillFrameBufferExample(bool inverse) {
    /* for(int x=0; x<SCREEN_WIDTH; x++) {
        for(int y=0; y<SCREEN_HEIGHT; y++) {
            if(x % 2 == 0 && inverse) {
                frameBuffer[x][y] = 0x00110000;
            }
            else {
                frameBuffer[x][y] = 0x00001100;
            }
        }
    } */

}