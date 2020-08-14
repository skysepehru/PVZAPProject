#include "zombie.h"
#include "plant.h"
#include <QGraphicsScene>
Zombie::Zombie(const int& moveSpeed , QTimer * timer,const int& HP,QGraphicsItem * parent) :QObject(),QGraphicsPixmapItem(parent) ,HP(HP), moveSpeed(moveSpeed)
{
    setPixmap(QPixmap(":/Sprites/Zombie.png"));
    connect(timer,SIGNAL(timeout()),this,SLOT(moveToLeft()));
}

void Zombie::decreaseHP()
{
    --HP;
    if(HP<=0)
    {
        scene()->removeItem(this);
        delete this;
    }
}

void Zombie::moveToLeft()
{
    QList<QGraphicsItem *> collidingObjects = collidingItems();

    for(int i =0;i<collidingObjects.length();++i)
    {
        Plant* plant = dynamic_cast<Plant *>(collidingObjects[i]);
        if(plant)
        {
            scene()->removeItem(collidingObjects[i]);
            delete collidingObjects[i];
            return;
        }
    }
    setPos(x() - moveSpeed,y());

    if(x() <= 0 )
        exit(1);
}
