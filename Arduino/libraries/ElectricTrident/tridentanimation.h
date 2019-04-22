#ifndef TRIDENTANIMATION_H
#define TRIDENTANIMATION_H

class Trident;

#define HUE_RED     0
#define HUE_ORANGE  32
#define HUE_YELLOW  64
#define HUE_GREEN   96
#define HUE_AQUA    128
#define HUE_PURPLE  192
#define HUE_BLUE    160
#define HUE_PINK    224

class TridentAnimationBase
{
public:
    virtual ~TridentAnimationBase();
    virtual void step() = 0;
    virtual void reset() = 0;
};

class TridentAnimation : public TridentAnimationBase
{
public:
    TridentAnimation(Trident *trident);

    void step();
    void reset();

protected:
     const int MIN_HUE = (HUE_RED + HUE_ORANGE)/2;
     const int MAX_HUE = HUE_YELLOW;//(HUE_ORANGE + HUE_YELLOW)/2;
//    const int MIN_HUE = 0;
//    const int MAX_HUE = 253;
    const int MIN_SAT = 200;
    const int MAX_SAT = 240;
    const int MIN_LUM = 20;
    const int MAX_LUM = 80;
    const int BOLT_INNER_RADIUS = 3;
    const int BOLT_OUTER_RADIUS = 6;
    const int BOLT_H = HUE_AQUA;
    const int BOLT_S = 255;
    const int BOLT_V = 255;
    const int GLOW_H = HUE_BLUE;
    const int GLOW_S = 200;
    const int GLOW_V = 255;

private:
    Trident *trident;
    int counter;
};

#endif // TRIDENTANIMATION_H
