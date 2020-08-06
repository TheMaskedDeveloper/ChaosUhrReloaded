#include "Arduino.h"
#include "OverlayClockFire.h"

#include <FastLED.h>

OverlayClockFire::OverlayClockFire()
{
    scaleBackground = 8;
    _colorPalette = HeatColors_p;
};

void OverlayClockFire::renderFrame(tm localtime)
{
  renderTime(localtime);
  uint16_t c1 = inoise16(11 * millis(), 0, 0);
  uint16_t c2 = inoise16(13 * millis(), 100000, 100000);
  uint16_t  c3 = ((c1 + c2) / 2);
  uint8_t s = 20;

  uint32_t x1 = 3 * c3 * s;
  uint32_t y1 = 15 * millis() * s;
  uint32_t z1 = 3 * millis() * s ;
  uint32_t sx = c1 / 2;
  uint32_t sy = c2 / 2;

  for (uint8_t i = 0; i < MATRIX_WIDTH; i++) {
    uint32_t io = sx * (i - (MATRIX_WIDTH / 2) - 1);
    for (uint8_t j = 0; j < MATRIX_HEIGHT; j++) {
      uint32_t jio = sy * (j - (MATRIX_HEIGHT / 2) - 1);
      uint16_t d = ((inoise16(x1 + io, y1 + jio, z1)) + 1);
      noise[i][j] = d >> 8;
    }
  }

  for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
    bXY(x, MATRIX_HEIGHT - 1, ColorFromPalette( _colorPalette, noise[x][0]));
    heat[x][MATRIX_HEIGHT - 1] = noise[x][0];
  }

  for (uint8_t y = 0; y < MATRIX_HEIGHT - 1; y++)
    for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
      heat[x][y] = heat[x][y+1];
    }

  for (uint8_t y = 0; y < MATRIX_HEIGHT - 1; y++)
    for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
      uint8_t dim = noise[x][y];
      dim = 255 - dim / 1.8;
      heat[x][y] = scale8(heat[x][y] , dim);
    }

  for (uint8_t y = 0; y < MATRIX_HEIGHT - 1; y++)
    for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
      bXY(x, y, ColorFromPalette( _colorPalette, heat[x][y]));
    }
};