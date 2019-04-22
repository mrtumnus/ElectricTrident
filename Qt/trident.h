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

    static const int NUM_LEDS = 60;
    static const int NUM_LEDS_TINE = 7;
    static const int NUM_TINES = 3;
    static const int NUM_LEDS_SHAFT = NUM_LEDS - (NUM_TINES * NUM_LEDS_TINE);

    void setPixelHsv(int index, int h, int s, int v);
    void getPixelHsv(int index, int &h, int &s, int &v);

signals:

public slots:

private:
    Led *leds[NUM_LEDS];
};

#endif // TRIDENT_H
