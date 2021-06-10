#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "block.h"

Game::Game(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(0, 0, 400, 600);
    scene->setBackgroundBrush(Qt::lightGray);
    setScene(scene);
}

void Game::start(){
    // Создаем мяч и добавляем его на сцену
    Ball* ball = new Ball();
    ball->setPos(200,500);
    scene->addItem(ball);

    // Создаем ракетку и добавляем на сцену
    Paddle* paddle = new Paddle();
    paddle->setPos(150,560);
    scene->addItem(paddle);
    paddle->grabMouse();

    // Создаем сетку кубиков
    size_t m = 10;
    for (size_t j = 0; j < m; j++){
        create_Block_Columns(j*28);
    }
}

void Game::create_Block_Columns(double x){
    size_t n = 10;
    for (size_t i = 0; i < n; i++){
        Block* block = new Block();
        block->setPos(x+60,i*28);
        scene->addItem(block);
    }
}


