#include "Arduino.h"
#include "OverlayClockPlasma.h"

#include <FastLED.h>

OverlayClockPlasma::OverlayClockPlasma()
{
    scaleBackground = 4;
    shift = (random8(1, 15) * 32) + 64;
    time = 0;
};

void OverlayClockPlasma::renderFrame(tm localtime)
{
    renderTime(localtime);
    for (int16_t x = 0; x < MATRIX_WIDTH; x++)
    {
        for (int16_t y = 0; y < MATRIX_HEIGHT; y++)
        {
            int16_t r = sin16(time) / 256;
            int16_t h = sin16(x * r * 10 + time) + cos16(y * (-r) * 30 + time) + sin16(y * x * (cos16(-time) / 256) / 2);
            bXY(x, y, CHSV((uint8_t)((h / 256) + 128), 255, 255));
        }
    }
    uint16_t old_plasma_time = time;
    time += shift;
    if (old_plasma_time > time)
        time = (random8(1, 15) * 32) + 64;


};