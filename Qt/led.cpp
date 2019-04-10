#include "led.h"

#include <QPainter>

Led::Led(QWidget *parent)
    : QWidget(parent)
{
    color = QColor(3,1,0);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}


QSize Led::minimumSizeHint() const
{
    return QSize(10, 10);
}
//! [1]

//! [2]
QSize Led::sizeHint() const
{
    return QSize(10, 10);
}

QColor Led::getColor()
{
    return this->color;
}

void Led::setColor(QColor color)
{
    this->color = color;
    update();
}


void Led::paintEvent(QPaintEvent * /* event */)
{
    QRect rect(2, 2, 6, 6);
    QPainter painter(this);
    painter.save();
    painter.setPen(Qt::black);
    painter.setBrush(this->color);
    painter.drawEllipse(rect);
    painter.restore();
}
