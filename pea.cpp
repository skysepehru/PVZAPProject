#include "pea.h"
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

Pea::Pea(QTimer *peaTimer, const int &velocity, QGraphicsScene * sceneRef, QGraphicsItem *parent) :QObject(),QGraphicsPixmapItem(parent),velocity(velocity) , sceneRef(sceneRef)
{
    setPixmap(QPixmap(":Sprites/Pea.png"));

    connect(peaTimer,SIGNAL(timeout()),this,SLOT(move()));
}

void Pea::move()
{
    setPos(x() + velocity , y());
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
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

}
