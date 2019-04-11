#ifndef TRIDENT_H
#define TRIDENT_H

struct CRGB;

class Trident
{
public:
    explicit Trident(CRGB * leds);

    static const int NUM_LEDS = 50;
    static const int NUM_LEDS_TINE = 7;
    static const int NUM_TINES = 3;
    static const int NUM_LEDS_SHAFT = NUM_LEDS - (NUM_TINES * NUM_LEDS_TINE);

    void setPixelHsv(int index, int h, int s, int v);
    void getPixelHsv(int index, int &h, int &s, int &v);

private:
    CRGB *leds;
};

#endif // TRIDENT_H
