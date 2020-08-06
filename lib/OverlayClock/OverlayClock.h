#ifndef OverlayClock_h
#define OverlayClock_h
#define MATRIX_WIDTH 20
#define MATRIX_HEIGHT 15

#include <FastLED.h>

class OverlayClock
{
public:
    OverlayClock();
    void init(CRGB *leds);
    virtual void renderFrame(tm localtime) {};
protected:
    uint16_t XY(uint8_t x, uint8_t y);
    boolean toSet(uint8_t x, uint8_t y);
    boolean bXY(uint8_t x, uint8_t y, CRGB value);
    void renderTime(tm localtime);
    void renderDigit(byte digit, byte x, byte y);
    CRGB *_leds;
    boolean overlay[MATRIX_WIDTH * MATRIX_HEIGHT];
    boolean invert = false;
    byte scaleBackground;
private:
    byte lastRenderTimeSecond = 255;
};

#endif