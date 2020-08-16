#include "sun.h"
#include <cstdlib>
#include <QDebug>
#include <QMediaPlayer>
#include "view.h"
#include <QtMath>

Sun::Sun(QGraphicsScene *sunScene, Score *sunScore, QGraphicsItem *parent, QTimer *timer):
    QObject(),QGraphicsPixmapItem(parent),sunScene(sunScene),sunScore(sunScore)
{
    setPixmap(QPixmap(":/Sprites/Sun.png"));

    sunScene->addItem(this);
    setPos(rand()%600 + 100,0);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    sunScore->scorePlayer->setMedia(QUrl("qrc:/Sounds/SunPick.mp3"));
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
    threshold += moveSpeed;
    temp = qFloor(threshold);
    threshold -=temp;
    setPos(x(),y()+temp);

    if(timeIntervals == 120 || y()>700){
        sunScene->removeItem(this);
        delete this;
    }
}
