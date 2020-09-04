#include "Arduino.h"
#include "OverlayClockNeo.h"

#include <FastLED.h>

OverlayClockNeo::OverlayClockNeo()
{
    scaleBackground = 8;
    scaleTrail = 192;
    scaleTrail = 150;

};

void OverlayClockNeo::renderFrame(tm localtime)
{
    renderTime(localtime);
    for (int8_t row = MATRIX_HEIGHT - 1; row >= 0; row--)
        for (int8_t col = 0; col < MATRIX_WIDTH; col++)
            if (pane[col][row].r == 255 || pane[col][row].g == 255 || pane[col][row].b == 255)
            {
                if (row < MATRIX_HEIGHT - 1)
                    pane[col][row + 1] = pane[col][row];
                else
                    dotsPerColoumn[col]--;
                pane[col][row] = CRGB(27, 130, 39);
            }

    for (int8_t row = MATRIX_HEIGHT - 1; row >= 0; row--)
        for (int8_t col = 0; col < MATRIX_WIDTH; col++) {
            if (pane[col][row].r != 255 && pane[col][row].g != 255 && pane[col][row].b != 255) pane[col][row].nscale8(scaleTrail);
        }

    if (random8(2) == 0)
    {
        int8_t spawnX = random8(MATRIX_WIDTH);
        if (dotsPerColoumn[spawnX] < 3) {
            pane[spawnX][0] = CRGB(175, 255, 175);
            dotsPerColoumn[spawnX] = dotsPerColoumn[spawnX] + 1;
        }
    }
    for (int8_t col = 0; col < MATRIX_WIDTH; col++)
        if (dotsPerColoumn[col] < 1) {
            pane[col][0] = CRGB(175, 255, 175);
            dotsPerColoumn[col]++;
        }

    for (int8_t row = MATRIX_HEIGHT - 1; row >= 0; row--)
        for (int8_t col = 0; col < MATRIX_WIDTH; col++)
            bXY(col, row, pane[col][row]);
    FastLED.delay(50);

};