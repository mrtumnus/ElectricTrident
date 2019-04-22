#include "tridentanimation.h"
#include "trident.h"

#include <stdlib.h>

extern long random(long);

TridentAnimationBase::~TridentAnimationBase()
{
}

TridentAnimation::TridentAnimation(Trident *trident) :
    trident(trident)
{
    for (int i = 0; i < Trident::NUM_LEDS; i++)
    {
        trident->setPixelHsv(i, random(MAX_HUE - MIN_HUE + 1) + MIN_HUE, MIN_SAT, MIN_LUM);
    }
    counter = Trident::NUM_LEDS + BOLT_OUTER_RADIUS;
}

void TridentAnimation::step()
{
    bool animationActive = counter < Trident::NUM_LEDS + BOLT_OUTER_RADIUS;

    // Update color(s)
    for (int i = 0; i < Trident::NUM_LEDS; i++)
    {
        int h,s,v,index,anim_index;
        Trident::PixelType type;

        trident->getPixelLocation(i, type, index);
        anim_index = type == Trident::SHAFT ? index : Trident::NUM_LEDS_SHAFT + index;
        trident->getPixelHsv(i, h, s, v);

        // Blend with energy bolt effect based on distance from it
        int bolt_dist = abs(anim_index - counter);

        bool randomizeHsv = false;

        // Is the animation running?
        if (animationActive)
        {
            // Is this tine a tip?
            if ((type == Trident::LEFT && index >= Trident::NUM_LEDS_TINE_LEFT-1) ||
                (type == Trident::CENTER && index >= Trident::NUM_LEDS_TINE_CENTER-2) ||
                (type == Trident::RIGHT && index >= Trident::NUM_LEDS_TINE_RIGHT-1))
            {
                // Converge to the glow color
                h = (h * 7 + GLOW_H * 1) / 8;
                s = (s * 7 + GLOW_S * 1) / 8;
                v = (v * 7 + GLOW_V * 1) / 8;
            }
            else if (bolt_dist <= BOLT_INNER_RADIUS)
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
                // Do nothing (other than randomization)
                randomizeHsv = true;
            }
        }
        else
        {
            randomizeHsv = true;
        }

        if (randomizeHsv)
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

    if (animationActive)
    {
        counter++;
    }
}

void TridentAnimation::reset()
{
    counter = -BOLT_OUTER_RADIUS;
}
