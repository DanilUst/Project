#include "paddle.h"
#include <QBrush>
#include "game.h"

extern Game *game;

Paddle::Paddle(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    // Рисуем ракетку
    setRect(0,0,100,20);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);
}

void Paddle::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    // Устанавливаем позицию  элемента
    // в сцене, транслируя координаты
    // курсора внутри элемента
    // в координатную систему сцены
    // координату Y делаем константой
    setPos(mapToScene(event->pos()).x(),560);

    // Ограничиваем передвижение ракетки в пределах окна
    double screen_width = game->width();

    if(pos().x() > screen_width - rect().width()){
        setPos(screen_width - rect().width(), 560);
    }
    if(pos().x() < 0){
        setPos(0, 560);
    }
}
