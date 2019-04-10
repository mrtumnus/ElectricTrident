#include "window.h"
#include "trident.h"

#include <QtWidgets>

Window::Window()
{
    trident = new Trident;

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(trident);
    setLayout(mainLayout);

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start();
}

Window::~Window()
{
    timer->stop();
    delete timer;
    // Don't delete trident - it's owned by the layout
}


void Window::animate()
{
    trident->animate();
    trident->update();
}
