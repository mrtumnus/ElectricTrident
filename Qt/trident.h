#ifndef TRIDENT_H
#define TRIDENT_H

#include "led.h"

#include <QObject>
#include <QWidget>

class Trident : public QWidget
{
    Q_OBJECT
public:
    explicit Trident(QWidget *parent = nullptr);

    static const int NUM_LEDS = 50;
    static const int NUM_LEDS_TINE = 7;
    static const int NUM_TINES = 3;
    static const int NUM_LEDS_SHAFT = NUM_LEDS - (NUM_TINES * NUM_LEDS_TINE);

signals:

public slots:
    void animate();

private:
    typedef enum {SHAFT, LEFT, CENTER, RIGHT} LedLocation;
    const int MIN_HUE = 20;
    const int MAX_HUE = 40;
    const int MIN_SAT = 200;
    const int MAX_SAT = 240;
    const int MIN_LUM = 240;
    const int MAX_LUM = 180;

    int getLedIndex(LedLocation loc, int locIndex);

    Led *leds[NUM_LEDS];
    Led *tineLeds[NUM_TINES][NUM_LEDS_TINE];
    Led *shaftLeds[NUM_LEDS_SHAFT];
    int ledDirs[NUM_LEDS];
};

#endif // TRIDENT_H
