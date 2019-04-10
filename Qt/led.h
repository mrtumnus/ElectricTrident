#ifndef LED_H
#define LED_H

#include <QWidget>

class Led : public QWidget
{
    Q_OBJECT
public:
    explicit Led(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    QColor getColor();

public slots:
    void setColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor color;
};

#endif // LED_H
