#include "tridentanimation.h"
#include "trident.h"

#include <stdlib.h>

extern long random(long);

TridentAnimation::TridentAnimation(Trident *trident) :
    trident(trident)
{
    for (int i = 0; i < Trident::NUM_LEDS; i++)
    {
        trident->setPixelHsv(i, random(MAX_HUE - MIN_HUE + 1) + MIN_HUE, MIN_SAT, MIN_LUM);
    }
    speed_div = 1;
    counter = Trident::NUM_LEDS + BOLT_OUTER_RADIUS;
}

TridentAnimation::~TridentAnimation()
{
}

void TridentAnimation::step()
{
    // Update color(s)
    for (int i = 0; i < Trident::NUM_LEDS; i++)
    {
        int h,s,v,index,anim_index;
        PixelType type;

        getPixelLocation(i, type, index);
        anim_index = type == SHAFT ? index : Trident::NUM_LEDS_SHAFT + index;
        trident->getPixelHsv(i, h, s, v);

        // Blend with energy bolt effect based on distance from it
        int bolt_dist = abs(anim_index - counter/speed_div);

        if (bolt_dist <= BOLT_INNER_RADIUS)
        {
            // Override entirely with bolt color
            h = BOLT_H;
            s = BOLT_S;
            v = BOLT_V;
        }
        else if (bolt_dist <= BOLT_OUTER_RADIUS)
        {
            // Blend colors
            const int BLEND_DIST = (BOLT_OUTER_RADIUS - BOLT_INNER_RADIUS);
            bolt_dist -= BLEND_DIST;
            h = (h * bolt_dist + BOLT_H * (BLEND_DIST - bolt_dist)) / BLEND_DIST;
            s = (s * bolt_dist + BOLT_S * (BLEND_DIST - bolt_dist)) / BLEND_DIST;
            v = (v * bolt_dist + BOLT_V * (BLEND_DIST - bolt_dist)) / BLEND_DIST;
        }
        else
        {
            if (h > MAX_HUE)
            {
                h -= 2;
            }
            else if (h < MIN_HUE)
            {
                h += 2;
            }
            else
            {
                // Let the color drift randomly
                h = h + random(5) - 2;
            }

            if (s > MAX_SAT)
            {
                s -= 2;
            }
            else if (v < MIN_SAT)
            {
                s += 2;
            }
            else
            {
                // Let the saturation drift randomly
                s = s + random(5) - 2;
            }

            if (v > MAX_LUM)
            {
                v -= 2;
            }
            else if (v < MIN_LUM)
            {
                v += 2;
            }
            else
            {
                // Let the brightness drift randomly
                v = v + random(5) - 2;
            }
        }

        trident->setPixelHsv(i, h, s, v);
    }

    counter++;
}

void TridentAnimation::reset()
{
    speed_div = 1;
    counter = -BOLT_OUTER_RADIUS * speed_div;
}

int TridentAnimation::getPixelIndex(PixelType loc, int locIndex)
{
    int offset = -1;
    switch (loc)
    {
    case SHAFT:
        if (locIndex < Trident::NUM_LEDS_SHAFT)
        {
            offset = 0;
        }
        break;
    case LEFT:
    case CENTER:
    case RIGHT:
        if (locIndex < Trident::NUM_LEDS_TINE)
        {
            offset = Trident::NUM_LEDS_SHAFT + (loc - 1) * Trident::NUM_LEDS_TINE;
        }
        break;
    }

    if (offset >= 0)
    {
        return offset + locIndex;
    }
    else
    {
        return -1;
    }
}

void TridentAnimation::getPixelLocation(int index, PixelType &loc, int &locIndex)
{
    if (index < Trident::NUM_LEDS_SHAFT)
    {
        loc = SHAFT;
        locIndex = index;
    }
    else
    {
        index -= Trident::NUM_LEDS_SHAFT;
        loc = static_cast<PixelType>(index / Trident::NUM_LEDS_TINE + 1);
        locIndex = index - (loc-1) * Trident::NUM_LEDS_TINE;
    }
}
