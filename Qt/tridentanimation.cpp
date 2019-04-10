#include "tridentanimation.h"
#include "trident.h"

#define RAND_HUE        (rand() % (MAX_HUE - MIN_HUE) + MIN_HUE)

TridentAnimation::TridentAnimation(Trident *trident) :
    trident(trident),
    counter(0)
{
    ledDirs = new int[Trident::NUM_LEDS];

    for (int i = 0; i < Trident::NUM_LEDS; i++)
    {
        trident->setPixelHsv(i, RAND_HUE, MIN_SAT, MIN_LUM);
        ledDirs[i] = 1;
    }
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
        int h,s,v;
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
        trident->setPixelHsv(i, h, s, v);
    }

    counter++;
}

void TridentAnimation::reset()
{
    counter = 0;
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
        loc = static_cast<PixelType>(index / Trident::NUM_LEDS_TINE);
        locIndex = index - loc * Trident::NUM_LEDS_TINE;
    }
}
