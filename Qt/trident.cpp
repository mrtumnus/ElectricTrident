#include "trident.h"
#include "led.h"

#include <QtWidgets>

Trident::Trident(QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;
    int h,s,v,i,x,y;
    Led *(*pTineLedArr)[NUM_LEDS_TINE];
    QColor color(Qt::blue);
    color.getHsv(&h,&s,&v);

    // Allocate all LEDs
    for (i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = new Led;
        leds[i]->setColor(color);
        h += 256/NUM_LEDS;
        color.setHsv(h,s,v);
    }

    // Place shaft LEDs
    i = 0;
    x = 3;
    y = NUM_LEDS_SHAFT + NUM_LEDS_TINE-1;
    for (int j = 0; j < NUM_LEDS_SHAFT; i++, j++, y--)
    {
        shaftLeds[j] = leds[i];
        mainLayout->addWidget(leds[i], y, x, Qt::AlignCenter);
    }

    // Place tine LEDs
    pTineLedArr = &this->tineLeds[0];
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

            *pTineLedArr[j] = leds[i];
            mainLayout->addWidget(leds[i], y, x, Qt::AlignCenter);
        }
        pTineLedArr++;
    }

    setLayout(mainLayout);
}

Trident::~Trident()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        delete leds[i];
    }
}

void Trident::animate()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        int h,s,v;
        QColor newColor = leds[i]->getColor();
        newColor.getHsv(&h, &s, &v);
        h = (h + 1) % 256;
        newColor.setHsv(h, s, v);
        leds[i]->setColor(newColor);
    }
}

int Trident::getLedIndex(LedLocation loc, int locIndex)
{
    int offset = -1;
    switch (loc)
    {
    case SHAFT:
        if (locIndex < NUM_LEDS_SHAFT)
        {
            offset = 0;
        }
        break;
    case LEFT:
    case CENTER:
    case RIGHT:
        if (locIndex < NUM_LEDS_TINE)
        {
            offset = NUM_LEDS_SHAFT + (loc - 1) * NUM_LEDS_TINE;
        }
        break;
    }

    if (offset >= 0)
    {
        return offset + locIndex;
    }
    else
    {
        return -1;
    }
}
