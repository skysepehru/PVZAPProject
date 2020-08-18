#include "wallnut.h"
#include "view.h"
#include <QtMath>

Wallnut::Wallnut(QTimer *wallnutTimer,float velocity, QGraphicsItem *parent):
Plant(parent),wallnutTimer(wallnutTimer),velocity(velocity)
    {
        setPixmap(QPixmap(":/Sprites/Wallnut.png"));

        wallnutPlayList = new QMediaPlaylist();
        wallnutPlayList->addMedia(QUrl("qrc:/Sounds/WallnutMoving.mp3"));
        wallnutPlayList->setPlaybackMode(QMediaPlaylist::Loop);

        hitPlayer = new QMediaPlayer();
        hitPlayer->setMedia(QUrl("qrc:/Sounds/WallnutHit.mp3"));

        movingPlayer=new QMediaPlayer();
        movingPlayer->setPlaylist(wallnutPlayList);
        movingPlayer->play();




        connect(wallnutTimer,SIGNAL(timeout()),this,SLOT(update()));
    }
int Wallnut::cooldown = View::instance->secondsToFrameCount(0);
int Wallnut::price = 0;
int Wallnut::getCooldown()
{
        return cooldown;
}
int Wallnut::getPrice()
{
    return price;
}

Wallnut::~Wallnut()
{
    delete hitPlayer;
    delete movingPlayer;
    delete wallnutPlayList;
}

void Wallnut::update()
{
    ++timeIntervals;
    threshold += velocity;
    temp = qFloor(threshold);
    threshold -= temp;
    setPos(x() + temp , y());

    setTransformOriginPoint(25,30);
    setRotation(timeIntervals*5);

    if(x() > 800){
        scene()->removeItem(this);
        delete this;
        return;
    }
    QList<QGraphicsItem *> collidingList = collidingItems();
    for(int i=0; i<collidingList.size() ; ++i)
    {
        if(typeid(*(collidingList[i])) == typeid(Zombie))
        {
            dynamic_cast<Zombie*>(collidingList[i])->destroy();
            hitPlayer->setPosition(0);
            hitPlayer->play();
        }
    }

}
