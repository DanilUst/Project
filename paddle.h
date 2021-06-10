#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Paddle : public QGraphicsRectItem
{
public:
    explicit Paddle(QGraphicsItem *parent = nullptr);

private:
    void mouseMoveEvent (QGraphicsSceneMouseEvent *event);

};

#endif // PADDLE_H
