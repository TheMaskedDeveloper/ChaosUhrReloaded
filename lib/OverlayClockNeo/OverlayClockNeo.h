#ifndef OverlayClockNeo_h
#define OverlayClockNeo_h

#include <OverlayClock.h>
#include <FastLED.h>

class OverlayClockNeo: public OverlayClock
{
public:
    OverlayClockNeo();
    void renderFrame(tm localtime);
private:
    CRGB pane[MATRIX_WIDTH][MATRIX_HEIGHT];
    byte dotsPerColoumn[MATRIX_WIDTH];;
    byte scaleTrail;
};

#endif