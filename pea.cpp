#include "pea.h"
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QtMath>

Pea::Pea(QTimer *peaTimer,QMediaPlayer * player, const float &velocity, QGraphicsScene * sceneRef, QGraphicsItem *parent) :QObject()
  ,QGraphicsPixmapItem(parent),velocity(velocity) , sceneRef(sceneRef) , player(player)

{
    setPixmap(QPixmap(":Sprites/Pea.png"));

    connect(peaTimer,SIGNAL(timeout()),this,SLOT(move()));
    threshold = 0;
}

void Pea::move()
{
    threshold += velocity;
    temp = qFloor(threshold);
    threshold -= temp;
    setPos(x() + temp , y());
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
            dynamic_cast<Zombie *>(collidingList[i])->decreaseHP();
            player->setPosition(0);
            player->play();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

}
