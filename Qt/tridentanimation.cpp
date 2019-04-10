#include "tridentanimation.h"
#include "trident.h"

#include <algorithm>

#define RAND_HUE        (rand() % (MAX_HUE - MIN_HUE) + MIN_HUE)

TridentAnimation::TridentAnimation(Trident *trident) :
    trident(trident),
    speed_div(10)
{
    ledDirs = new int[Trident::NUM_LEDS];

    for (int i = 0; i < Trident::NUM_LEDS; i++)
    {
        trident->setPixelHsv(i, RAND_HUE, MIN_SAT, MIN_LUM);
        ledDirs[i] = 1;
    }

    reset();
}

TridentAnimation::~TridentAnimation()
{
    delete ledDirs;
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

        h = h + ledDirs[i];

        if (h > MAX_HUE)
        {
            h = MAX_HUE;
            ledDirs[i] = -1;
        }
        if (h < MIN_HUE)
        {
            h = MIN_HUE;
            ledDirs[i] = 1;
        }

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
            // Don't touch the color
        }

        trident->setPixelHsv(i, h, s, v);
    }

    counter++;
    if (counter/speed_div >= 2*Trident::NUM_LEDS)
    {
        reset();
    }
}

void TridentAnimation::reset()
{
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
