#ifndef TRIDENT_H
#define TRIDENT_H

struct CRGB;

class Trident
{
public:
    explicit Trident(CRGB * leds);

    static const int NUM_LEDS = 60;
    static const int NUM_LEDS_TINE_LEFT = 4;
    static const int NUM_LEDS_TINE_CENTER = 7;
    static const int NUM_LEDS_TINE_RIGHT = 5;
    static const int NUM_LEDS_SHAFT = NUM_LEDS -
        (NUM_LEDS_TINE_LEFT + NUM_LEDS_TINE_CENTER + NUM_LEDS_TINE_RIGHT);

    void setPixelHsv(int index, int h, int s, int v);
    void getPixelHsv(int index, int &h, int &s, int &v);

    typedef enum {SHAFT, LEFT, CENTER, RIGHT} PixelType;
    int getPixelIndex(PixelType loc, int locIndex);
    void getPixelLocation(int index, PixelType &loc, int &locIndex);

private:
    CRGB *leds;
};

#endif // TRIDENT_H
