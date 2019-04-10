#ifndef TRIDENTANIMATION_H
#define TRIDENTANIMATION_H

class Trident;

class TridentAnimation
{
public:
    TridentAnimation(Trident *trident);
    ~TridentAnimation();

    void step();
    void reset();

protected:
    const int MIN_HUE = 20;
    const int MAX_HUE = 40;
    const int MIN_SAT = 200;
    const int MAX_SAT = 240;
    const int MIN_LUM = 240;
    const int MAX_LUM = 180;
    const int BOLT_INNER_RADIUS = 3;
    const int BOLT_OUTER_RADIUS = 6;
    const int BOLT_H = 60;
    const int BOLT_S = 255;
    const int BOLT_V = 250;

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
