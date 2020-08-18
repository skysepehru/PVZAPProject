#include "zombie.h"
#include "plant.h"
#include <QGraphicsScene>
#include <QtMath>
#include <QString>
#include "wallnut.h"

Zombie::Zombie(const float& moveSpeed , QTimer * timer,const int& HP, bool isConeZombie,QGraphicsItem * parent) :QObject(),QGraphicsPixmapItem(parent) ,HP(HP), moveSpeed(moveSpeed)
{
    if(isConeZombie)
    {
        setPixmap(QPixmap(":/Sprites/ZombieCone.png"));
        setScale(0.9);
    }
    else
        setPixmap(QPixmap(":/Sprites/Zombie.png"));
    connect(timer,SIGNAL(timeout()),this,SLOT(moveToLeft()));
    zombiePlayer = new QMediaPlayer();
    zombiePlayer->setMedia(QUrl("qrc:/Sounds/Gulp.mp3"));

    groanPlayer = new QMediaPlayer();
    int a = (rand()%3 )+ 1;
    if(a == 0)
    {
        groanPlayer->setMedia(QUrl("qrc:/Sounds/Groan1.mp3"));
    }
    else if(a==1)
    {
        groanPlayer->setMedia(QUrl("qrc:/Sounds/Groan2.mp3"));
    }
    else if(a==2)
    {
        groanPlayer->setMedia(QUrl("qrc:/Sounds/Groan3.mp3"));
    }
    groanPlayer->play();
    threshold = 0;
}

void Zombie::decreaseHP()
{
    --HP;
    if(HP<=0)
    {
        destroy();
    }
}

void Zombie::destroy()
{
    emit onDestroy();
    scene()->removeItem(this);
    delete this;

}

Zombie::~Zombie()
{
    delete zombiePlayer;
    delete groanPlayer;
}

void Zombie::moveToLeft()
{
    QList<QGraphicsItem *> collidingObjects = collidingItems();

    for(int i =0;i<collidingObjects.length();++i)
    {
        Plant* plant = dynamic_cast<Plant *>(collidingObjects[i]);
        if(plant)
        {
            if(typeid(*plant)!=typeid(Wallnut)){
            scene()->removeItem(collidingObjects[i]);
            delete collidingObjects[i];
            zombiePlayer->setPosition(0);
            zombiePlayer->play();
            return;
            }
        }
    }
    //these calculations are done for a steady speed over various farame rates.
    threshold += moveSpeed;
    temp = qFloor(threshold);
    threshold -=temp;
    setPos(x() - temp,y());

    if(x() <= 0 )
        emit lost();
}

void Zombie::levelEnd()
{
    destroy();
}
