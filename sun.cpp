#include "sun.h"
#include <cstdlib>
#include <QDebug>
#include <QMediaPlayer>
Sun::Sun(QGraphicsScene *sunScene, Score *sunScore, QGraphicsItem *parent, QTimer *timer):
    QObject(),QGraphicsPixmapItem(parent),sunScene(sunScene),sunScore(sunScore)
{
    setPixmap(QPixmap(":/Sprites/Sun.png"));

    sunScene->addItem(this);
    setPos(rand()%600 + 100,0);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    sunScore->addToSunCount(25);
    sunScore->scorePlayer->setMedia(QUrl("qrc:/Sounds/SunPick.ogg"));
    sunScore->scorePlayer->play();
    sunScene->removeItem(this);
    delete (this);
}

void Sun::move()
{
    ++timeIntervals;

    setPos(x(),y()+3);

    if(timeIntervals == 120 || y()>700){
        sunScene->removeItem(this);
        delete this;
    }
}
