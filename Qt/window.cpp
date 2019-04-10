#include "window.h"
#include "led.h"

#include <QtWidgets>

Window::Window()
{
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start();

    QGridLayout *mainLayout = new QGridLayout;
    int h,s,v;
    QColor color(Qt::blue);
    color.getHsv(&h,&s,&v);
    for (int i = 0; i < NUM_LEDS; i++)
    {
        led[i] = new Led;
        led[i]->setColor(color);
        mainLayout->addWidget(led[i], 0, i, Qt::AlignCenter);

        h += 256/NUM_LEDS;
        color.setHsv(h,s,v);
    }

    setLayout(mainLayout);
}


void Window::animate()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        int h,s,v;
        QColor newColor = led[i]->getColor();
        newColor.getHsv(&h, &s, &v);
        h = (h + 1) % 256;
        newColor.setHsv(h, s, v);
        led[i]->setColor(newColor);
    }
}
