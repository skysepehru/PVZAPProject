#include "sun.h"
#include <cstdlib>
#include <QDebug>
#include <QMediaPlayer>
#include "view.h"
#include <QtMath>

Sun::Sun(QGraphicsScene *sunScene, Score *sunScore, QGraphicsItem *parent, QTimer *timer,bool flag):
    QObject(),QGraphicsPixmapItem(parent),sunScene(sunScene),sunScore(sunScore),flag(flag)
{
    setPixmap(QPixmap(":/Sprites/Sun.png"));

    sunScene->addItem(this);
    setPos(rand()%600 + 100,0);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    moveSpeed = View::pixelPerSecondsToPixelPerFrame(120);
    threshold = 0;
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    sunScore->addToSunCount(25);
    sunScore->scorePlayer->setPosition(0);
    sunScore->scorePlayer->play();
    sunScene->removeItem(this);
    delete (this);
}

void Sun::move()
{
    ++timeIntervals;
    if(flag){
        threshold += moveSpeed;
        temp = qFloor(threshold);
        threshold -=temp;
        setPos(x(),y()+temp);
    }
    if(timeIntervals == View::instance->secondsToFrameCount(2) || y()>800){
        sunScene->removeItem(this);
        delete this;
    }
}
