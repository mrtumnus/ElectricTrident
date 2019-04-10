#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE
class Led;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

    static const int NUM_LEDS = 16;

public slots:
    void animate();

private:
    Led *led[NUM_LEDS];
    QTimer *timer;
};

#endif // WINDOW_H
