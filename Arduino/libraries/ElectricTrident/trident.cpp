#include "trident.h"

#include <FastLED.h>

Trident::Trident(CRGB * leds)
{
    this->leds = leds;
}

int Trident::getPixelIndex(PixelType loc, int locIndex)
{
    int index = -1;
    switch (loc)
    {
    case SHAFT:
        if (locIndex < NUM_LEDS_SHAFT)
        {
            index = locIndex;
        }
        break;
    case LEFT:
        if (locIndex < NUM_LEDS_TINE_LEFT)
        {
            index = locIndex + NUM_LEDS_SHAFT +
                NUM_LEDS_TINE_CENTER + NUM_LEDS_TINE_RIGHT;
        }
        break;
    case CENTER:
        if (locIndex < NUM_LEDS_TINE_CENTER)
        {
            index = locIndex + NUM_LEDS_SHAFT;
        }
        break;
    case RIGHT:
        if (locIndex < NUM_LEDS_TINE_RIGHT)
        {
            // Right tine is reversed order
            index = (NUM_LEDS_TINE_RIGHT-1 - locIndex) + NUM_LEDS_SHAFT +
                NUM_LEDS_TINE_CENTER;
        }
        break;
    }
    
    return index;
}

void Trident::getPixelLocation(int index, PixelType &loc, int &locIndex)
{
    if (index < NUM_LEDS_SHAFT)
    {
        loc = SHAFT;
        locIndex = index;
    }
    else
    {
        index -= NUM_LEDS_SHAFT;
        
        if (index < NUM_LEDS_TINE_CENTER)
        {
            loc = CENTER;
            locIndex = index;
        }
        else
        {
            index -= NUM_LEDS_TINE_CENTER;

            if (index < NUM_LEDS_TINE_RIGHT)
            {
                loc = RIGHT;
                locIndex = NUM_LEDS_TINE_RIGHT-1 - index;
            }
            else
            {
                index -= NUM_LEDS_TINE_RIGHT;
                
                if (index < NUM_LEDS_TINE_LEFT)
                {
                    loc = LEFT;
                    locIndex = index;
                }
                else
                {
                    // Invalid index
                }
            }
        }
    }
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
