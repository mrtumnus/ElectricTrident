#include "trident.h"

#include <FastLED.h>

Trident::Trident(CRGB * leds)
{
    this->leds = leds;
}


void Trident::setPixelHsv(int index, int h, int s, int v)
{
    if (index < NUM_LEDS)
    {
        leds[index] = CHSV(h, s, v);
    }
}
void Trident::getPixelHsv(int index, int &h, int &s, int &v)
{
    if (index < NUM_LEDS)
    {
        CHSV color = rgb2hsv_approximate(leds[index]);
        h = color.h;
        s = color.s;
        v = color.v;
    }
}
