#include "zombie.h"
#include "plant.h"
#include <QGraphicsScene>
#include <QtMath>
#include "wallnut.h"

Zombie::Zombie(const float& moveSpeed , QTimer * timer,const int& HP,QGraphicsItem * parent) :QObject(),QGraphicsPixmapItem(parent) ,HP(HP), moveSpeed(moveSpeed)
{
    setPixmap(QPixmap(":/Sprites/Zombie.png"));
    connect(timer,SIGNAL(timeout()),this,SLOT(moveToLeft()));
    zombiePlayer = new QMediaPlayer();
    zombiePlayer->setMedia(QUrl("qrc:/Sounds/Gulp.mp3"));
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

    //if(x() <= 0 )
        //exit(1);
}
