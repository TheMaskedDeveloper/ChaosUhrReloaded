#ifndef OverlayClockFire_h
#define OverlayClockFire_h

#include <OverlayClock.h>
#include <FastLED.h>

class OverlayClockFire: public OverlayClock
{
public:
    OverlayClockFire();
    void renderFrame(tm localtime);
private:
    uint8_t noise[MATRIX_WIDTH][MATRIX_HEIGHT];
    uint8_t heat[MATRIX_WIDTH][MATRIX_HEIGHT];
    CRGBPalette16 _colorPalette;
};

#endif