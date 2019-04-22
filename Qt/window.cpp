#include "window.h"
#include "trident.h"
#include "tridentanimation.h"
#include "tridentanimationtest.h"

#include <QtWidgets>

Window::Window()
{
    trident = new Trident;
    ta = new TridentAnimation(trident);

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
    delete ta;
    // Don't delete trident - it's owned by the layout
}


void Window::animate()
{
    ta->step();
    trident->update();
}

void Window::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        ta->reset();
    }
}
