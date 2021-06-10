#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsItem>

class Ball : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Ball(QGraphicsItem *parent = nullptr);

public slots:
    void move();

private:
    size_t count;
    double xSpeed;
    double ySpeed;

    void Sides_Collision();
    void Paddle_Collision();
    void Block_Collision();

};

#endif // BALL_H
