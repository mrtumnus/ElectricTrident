#include "trident.h"
#include "led.h"

#include <QtWidgets>

Trident::Trident(QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout();
    int i,x,y;
    QColor color;

    // Allocate all LEDs
    for (i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = new Led;
    }

    // Place shaft LEDs
    i = 0;
    x = 3;
    y = NUM_LEDS_SHAFT + NUM_LEDS_TINE-1;
    for (int j = 0; j < NUM_LEDS_SHAFT; i++, j++, y--)
    {
        mainLayout->addWidget(leds[i], y, x, Qt::AlignCenter);
    }

    // Place tine LEDs
    for (int xdir = -1; xdir <= 1; xdir++)
    {
        x = 3;
        y = NUM_LEDS_TINE;
        for (int j = 0; j < NUM_LEDS_TINE; i++, j++)
        {
            // Pre-inc/decrement the row/column
            if (j < 3)
            {
                x += xdir;
            }
            if (j >= 2 || xdir == 0)
            {
                y--;
            }

            mainLayout->addWidget(leds[i], y, x, Qt::AlignCenter);
        }
    }

    setLayout(mainLayout);
}


void Trident::setPixelHsv(int index, int h, int s, int v)
{
    if (index < NUM_LEDS)
    {
        // h range for FastLED is 0-255, but Qt uses standard 0-359 range
        h = (h * 360 + 128)/256;
        leds[index]->setColor(QColor::fromHsv(h, s, v));
    }
}
void Trident::getPixelHsv(int index, int &h, int &s, int &v)
{
    if (index < NUM_LEDS)
    {
        leds[index]->getColor().getHsv(&h, &s, &v);
        // h range for FastLED is 0-255, but Qt uses standard 0-359 range
        h = (h * 256 + 180)/360;
    }
}

long random(long max)
{
    return rand() % max;
}
