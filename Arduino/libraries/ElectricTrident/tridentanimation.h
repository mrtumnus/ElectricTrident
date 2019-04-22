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

class TridentAnimation
{
public:
    TridentAnimation(Trident *trident);
    ~TridentAnimation();

    void step();
    void reset();

protected:
     const int MIN_HUE = (HUE_RED + HUE_ORANGE)/2;
     const int MAX_HUE = (HUE_ORANGE + HUE_YELLOW)/2;
//    const int MIN_HUE = 0;
//    const int MAX_HUE = 253;
    const int MIN_SAT = 200;
    const int MAX_SAT = 240;
    const int MIN_LUM = 64;
    const int MAX_LUM = 120;
    const int BOLT_INNER_RADIUS = 3;
    const int BOLT_OUTER_RADIUS = 6;
    const int BOLT_H = HUE_AQUA;
    const int BOLT_S = 255;
    const int BOLT_V = 255;

    typedef enum {SHAFT, LEFT, CENTER, RIGHT} PixelType;

    int getPixelIndex(PixelType loc, int locIndex);
    void getPixelLocation(int index, PixelType &loc, int &locIndex);

private:
    Trident *trident;
    int counter;
    int *ledDirs;
    int speed_div;
};

#endif // TRIDENTANIMATION_H
