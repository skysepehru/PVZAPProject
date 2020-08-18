#include "cherrybomb.h"
#include"view.h"

CherryBomb::CherryBomb(QTimer *bombTimer , QMediaPlayer* bombPlayer, QGraphicsItem *parent):
    Plant(parent),bombTimer(bombTimer),bombPlayer(bombPlayer)
{
    setPixmap(QPixmap(":/Sprites/CherryBomb.png"));

    connect(bombTimer,SIGNAL(timeout()),this,SLOT(enfejar()));

}
int CherryBomb ::cooldown = View::instance->secondsToFrameCount(3);
int CherryBomb ::price = 150;
int CherryBomb::getCooldown()
{
    return cooldown;
}

int CherryBomb::getPrice()
{
    return price;
}

void CherryBomb::enfejar()
{

    timeIntervals++;
    if(timeIntervals==View::instance->secondsToFrameCount(1)){

    QGraphicsRectItem* temp=new QGraphicsRectItem(-105,-145,270,360,this);
    temp->setPen(Qt::NoPen);

    bombPlayer->setPosition(0);
    bombPlayer->play();

    QList<QGraphicsItem *> collidingList = temp->collidingItems();
    for(int i=0; i<collidingList.size() ; ++i)
    {
        if(typeid(*(collidingList[i])) == typeid(Zombie))
        {

            dynamic_cast<Zombie*>(collidingList[i])->destroy();
        }
    }
    scene()->removeItem(this);
    delete this;
    }
}

void CherryBomb::levelEnded()
{
    scene()->removeItem(this);
    delete this;
}


