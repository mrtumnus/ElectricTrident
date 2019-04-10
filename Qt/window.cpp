#include "window.h"
#include "trident.h"

#include <QtWidgets>

Window::Window()
{
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start();

    trident = new Trident;

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(trident);
    setLayout(mainLayout);
}

Window::~Window()
{
    delete trident;
    delete timer;
}


void Window::animate()
{
    trident->animate();
    trident->update();
}
