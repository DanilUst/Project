#include "block.h"
#include <QBrush>
Block::Block(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    // Рисуем блок
    setRect(0, 0, 25, 25);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}
