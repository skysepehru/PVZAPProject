#include "sunflower.h"
#include"view.h"
#include"sun.h"

SunFlower::SunFlower(QTimer *sunFlowerTimer, Score *scoreCount, QGraphicsItem *parent):
Plant(parent),sunFlowerTimer(sunFlowerTimer),scoreCount(scoreCount),sunFlowerPlayer(sunFlowerPlayer)
{
    setPixmap(QPixmap(":/Sprites/SunFlower.png"));

    sunFlowerPlayer=new QMediaPlayer();
    sunFlowerPlayer->setMedia(QUrl("qrc:/Sounds/SunThrow.mp3"));
    connect(sunFlowerTimer,SIGNAL(timeout()),this,SLOT(update()));
}
int SunFlower::cooldown = View::instance->secondsToFrameCount(3);
int SunFlower::price= 0;
int SunFlower::getCooldown()
{
    return cooldown;
}

int SunFlower::getPrice()
{
    return price;
}

void SunFlower::update()
{
    ++timeIntervals;
    if(timeIntervals%View::instance->secondsToFrameCount(15)==0){
        auto temp=new Sun(scene(),scoreCount,this,sunFlowerTimer,false);
        scene()->addItem(temp);
        sunFlowerPlayer->setPosition(0);
        sunFlowerPlayer->play();
        temp->setPos(0,0);
    }

}

void SunFlower::levelEnded()
{
    scene()->removeItem(this);
    delete this;
}

SunFlower::~SunFlower()
{
   delete sunFlowerPlayer;
}
