#ifndef OverlayClockPlasma_h
#define OverlayClockPlasma_h

#include <OverlayClock.h>
#include <FastLED.h>

class OverlayClockPlasma: public OverlayClock
{
public:
    OverlayClockPlasma();
    void renderFrame(tm localtime);
private:
    uint16_t time;
    uint16_t shift;
};

#endif