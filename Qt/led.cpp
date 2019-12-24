#include "led.h"

#include <QPainter>

Led::Led(QWidget *parent)
    : QWidget(parent)
{
    color = Qt::black;
//    setBackgroundRole(QPalette::Base);
//    setAutoFillBackground(true);
}


QSize Led::minimumSizeHint() const
{
    return QSize(DEFAULT_DIAMETER, DEFAULT_DIAMETER);
}
//! [1]

//! [2]
QSize Led::sizeHint() const
{
    return QSize(DEFAULT_DIAMETER, DEFAULT_DIAMETER);
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
    QRect rect(0, 0, DEFAULT_DIAMETER, DEFAULT_DIAMETER);
    QPainter painter(this);
    painter.save();
    painter.setPen(Qt::black);
    painter.setBrush(this->color);
    painter.drawEllipse(rect);
    painter.restore();
}
