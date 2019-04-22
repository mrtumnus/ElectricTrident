#ifndef TRIDENTANIMATIONTEST_H
#define TRIDENTANIMATIONTEST_H

#include "tridentanimation.h"

class Trident;

class TridentAnimationTest : public TridentAnimationBase
{
public:
    TridentAnimationTest(Trident *trident);

    void step();
    void reset();

private:
    Trident *trident;
    int counter;
};

#endif // TRIDENTANIMATIONTEST_H
