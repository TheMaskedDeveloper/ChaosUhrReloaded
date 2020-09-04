#include "Arduino.h"
#include "OverlayClock.h"

#include <FastLED.h>

OverlayClock::OverlayClock()
{

};

void OverlayClock::init(CRGB *leds)
{
    _leds = leds;
};


// uint16_t OverlayClock::XY(uint8_t x, uint8_t y)
// {
//     if (y & 0x01) return (y * MATRIX_WIDTH) + (MATRIX_WIDTH - 1) - x;
//     return (y * MATRIX_WIDTH) + x;
// }


uint16_t OverlayClock::XY(uint8_t x, uint8_t y) {
  if ( (x >= MATRIX_WIDTH) ||
       (y >= MATRIX_HEIGHT)
     ) {
    return 256;
  }

  const uint8_t XYTable[] = {
     7, 15, 23, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  
     6, 14, 22, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  
     5, 13, 21, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  
     4, 12, 20, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  
     3, 11, 19, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  
     2, 10, 18, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  
     1,  9, 17, 25, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  
     0,  8, 16, 24, 32, 40, 48, 56, 64, 72, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  
  };

// y+ 8* y

  uint8_t i = (y * MATRIX_WIDTH) + x;
  return 7-y + 8* x;
}











boolean OverlayClock::toSet(uint8_t x, uint8_t y) {
    return (overlay[y * MATRIX_WIDTH + x] != invert);
}

boolean OverlayClock::bXY(uint8_t x, uint8_t y, CRGB value) {
    if (toSet(x, y)) return _leds[XY(x, y)] = value;
    return _leds[XY(x, y)] =  value.nscale8(scaleBackground);
}

void OverlayClock::renderTime(tm localtime) {
    byte second = localtime.tm_sec;
    if(lastRenderTimeSecond == second) return;
    
    renderDigit(localtime.tm_hour / 10, 1, 2);
    renderDigit(localtime.tm_hour % 10, 5, 2);
    
    renderDigit(localtime.tm_min / 10, 13, 2);
    renderDigit(localtime.tm_min % 10, 17, 2);
    
    renderDigit(second / 10, 24, 2);
    renderDigit(second % 10, 28, 2);
    
    lastRenderTimeSecond = second;

}

void OverlayClock::renderDigit(byte digit, byte x, byte y) {
    overlay[x + 0 + y * MATRIX_WIDTH] = true;
    overlay[x + 1 + y * MATRIX_WIDTH] = true;
    overlay[x + 2 + y * MATRIX_WIDTH] = true;
    overlay[x + 0 + (y + 1) * MATRIX_WIDTH] = true;
    overlay[x + 2 + (y + 1) * MATRIX_WIDTH] = true;
    overlay[x + 0 + (y + 2) * MATRIX_WIDTH] = true;
    overlay[x + 1 + (y + 2) * MATRIX_WIDTH] = true;
    overlay[x + 2 + (y + 2) * MATRIX_WIDTH] = true;
    overlay[x + 0 + (y + 3) * MATRIX_WIDTH] = true;
    overlay[x + 2 + (y + 3) * MATRIX_WIDTH] = true;
    overlay[x + 0 + (y + 4) * MATRIX_WIDTH] = true;
    overlay[x + 1 + (y + 4) * MATRIX_WIDTH] = true;
    overlay[x + 2 + (y + 4) * MATRIX_WIDTH] = true;
    switch (digit) {
    case 1:
        overlay[x + 1 + y * MATRIX_WIDTH] = false;
        overlay[x + 0 + y * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 1) * MATRIX_WIDTH] = false;
        overlay[x + 1 + (y + 2) * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 2) * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 3) * MATRIX_WIDTH] = false;
        overlay[x + 1 + (y + 4) * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 4) * MATRIX_WIDTH] = false;
        break;
    case 2:
        overlay[x + 0 + (y + 1) * MATRIX_WIDTH] = false;
        overlay[x + 2 + (y + 3) * MATRIX_WIDTH] = false;
        break;
    case 3:
        overlay[x + 0 + (y + 1) * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 3) * MATRIX_WIDTH] = false;
        break;
    case 4:
        overlay[x + 1 + y * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 3) * MATRIX_WIDTH] = false;
        overlay[x + 1 + (y + 4) * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 4) * MATRIX_WIDTH] = false;
        break;
    case 5:
        overlay[x + 2 + (y + 1) * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 3) * MATRIX_WIDTH] = false;
        break;
    case 6:
        overlay[x + 2 + (y + 1) * MATRIX_WIDTH] = false;
        break;
    case 7:
        overlay[x + 0 + (y + 1) * MATRIX_WIDTH] = false;
        overlay[x + 1 + (y + 2) * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 2) * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 3) * MATRIX_WIDTH] = false;
        overlay[x + 1 + (y + 4) * MATRIX_WIDTH] = false;
        overlay[x + 0 + (y + 4) * MATRIX_WIDTH] = false;
        break;
    case 9:
        overlay[x + 0 + (y + 3) * MATRIX_WIDTH] = false;
        break;
    case 0:
        overlay[x + 1 + (y + 2) * MATRIX_WIDTH] = false;
        break;
    }
}

