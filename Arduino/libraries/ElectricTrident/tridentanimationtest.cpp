#include "tridentanimationtest.h"
#include "trident.h"

#include <stdlib.h>

extern long random(long);

TridentAnimationTest::TridentAnimationTest(Trident *trident) :
    trident(trident)
{
    for (int i = 0; i < Trident::NUM_LEDS; i++)
    {
        trident->setPixelHsv(i, 0,0,0);
    }
    counter = 0;
}

void TridentAnimationTest::step()
{
    // Update color(s)
    for (int i = 0; i < Trident::NUM_LEDS; i++)
    {
        trident->setPixelHsv(i, 0,0, i==counter ? 255 : 0);
    }
}

void TridentAnimationTest::reset()
{
    counter++;
    if (counter >= Trident::NUM_LEDS)
        counter = 0;
}
