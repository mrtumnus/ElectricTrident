#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE
class Trident;
class TridentAnimation;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();

public slots:
    void animate();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QTimer *timer;
    Trident *trident;
    TridentAnimation *ta;
};

#endif // WINDOW_H
