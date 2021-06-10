#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsView>

class Game : public QGraphicsView
{
public:
    Game(QWidget *parent = nullptr);

    void start();

    QGraphicsScene *scene;

private:
    void create_Block_Columns(double x);


};
#endif // GAME_H
