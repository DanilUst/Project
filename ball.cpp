#include "ball.h"
#include "game.h"
#include "paddle.h"
#include "block.h"
#include <QBrush>
#include <QTimer>
#include <QMessageBox>

extern Game *game;

Ball::Ball(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    //Рисуем мяч
    setRect(0, 0, 25, 25);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);
    setBrush(brush);

    // Счётчик для проверки, сколько уничтоженно блоков
    count = 0;

    // Задаем начальное движение мяча
    xSpeed = 1;
    ySpeed = 3;

    // Таймер для вызова функции move каждые 20 миллисекунд
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(20);
}

void Ball::Sides_Collision(){

    double screen_width = game->width();
    double screen_height = game->height();

    // Проверка на выход за пределы экрана слева
    if (pos().x() <= 0){
        xSpeed = -1 * xSpeed;
    }

    // Проверка на выход за пределы экрана справа
    if (pos().x() >= screen_width - rect().width()){
        xSpeed = -1 * xSpeed;
    }

    // Проверка на выход за пределы экрана сверху
    if (pos().y() <= 0){
        ySpeed = -1 * ySpeed;
    }
    // Проверка на выход за пределы экрана снизу(конец игры)
    if(pos().y() >= screen_height - rect().height()){
        QMessageBox msgBox;
        msgBox.setWindowTitle("GG");
        msgBox.setText("You lose");
        msgBox.exec();

        game->scene->clear();
    }
}
void Ball::Paddle_Collision(){
    // Возвращает список элементов, которые сталкиваются с мячом.
    QList<QGraphicsItem*> collPaddle = collidingItems();
    size_t n = collPaddle.size();
    for (size_t i = 0; i < n; i++){
        Paddle* paddle = dynamic_cast<Paddle*>(collPaddle[i]);
        if (paddle){
            // Изменяю направление мяча
            ySpeed = -1 * ySpeed;

            double xBall = pos().x();
            double xPaddle = paddle->pos().x();

            double dx = xBall - xPaddle;

            // Изменяю скорость полета мяча, в зависимости от того, где он был отбит ракеткой
            if(dx < 25){
                xSpeed = (xSpeed + (4*dx))/20;
            }
            if(dx > 25 && dx < 75){
                xSpeed = (xSpeed + dx)/20;
            }
            if(dx > 75){
                xSpeed = (xSpeed + (1.5*dx))/20;
            }

            return;
        }
    }
}
void Ball::Block_Collision(){
    // Возвращает список элементов, которые сталкиваются с мячом.
    QList<QGraphicsItem*> collBlocks = collidingItems();
    size_t n = collBlocks.size();
    for (size_t i = 0; i < n; i++){
        Block* block = dynamic_cast<Block*>(collBlocks[i]);
        // Коллизия с блоками
        if (block){
            // Позиция мяча
            double xBall = pos().x();
            double yBall = pos().y();

            // Позиция блока
            double xBlock = block->pos().x();
            double yBlock = block->pos().y();

            // Проверка снизу
            if (yBall > yBlock  && ySpeed < 0){
                ySpeed = -1 * ySpeed;
            }

            // Проверка сверху
            if (yBlock > yBall  && ySpeed > 0 ){
                ySpeed = -1 * ySpeed;
            }

            // Проверка справа
            if (xBall > xBlock  && xSpeed < 0){
                xSpeed = -1 * xSpeed;
            }

            // Проверка слева
            if (xBlock > xBall  && xSpeed > 0){
                xSpeed = -1 * xSpeed;
            }
            // Удаляем блок со сцены
            game->scene->removeItem(block);

            // Проверка на победу
            count++;

            if(count == 100){
                QMessageBox msgBox;
                msgBox.setWindowTitle("GG");
                msgBox.setText("You won");
                msgBox.exec();

                game->scene->clear();
            }
        }
    }
}
void Ball::move(){

    Sides_Collision();

    Paddle_Collision();

    Block_Collision();

    moveBy(xSpeed, ySpeed);
}
