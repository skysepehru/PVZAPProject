#include "peashooter.h"
#include <QDebug>
#include <QGraphicsScene>
#include <view.h>

PeaShooter::PeaShooter(QTimer *shooterTimer, QGraphicsScene * scenRef, QGraphicsItem *parent):Plant(parent) , sceneRef(sceneRef)
  , shooterTimer(shooterTimer)
{

    setPixmap(QPixmap(":/Sprites/PeaShooter"));

    shooterPlayer = new QMediaPlayer();
    shooterPlayer->setMedia(QUrl("qrc:/Sounds/Shoot.mp3"));

    zombieHitPlayer = new QMediaPlayer();
    zombieHitPlayer->setMedia(QUrl("qrc:/Sounds/Splat.mp3"));
    connect(shooterTimer,SIGNAL(timeout()),this,SLOT(shoot()));
}
int PeaShooter::cooldown = View::instance->secondsToFrameCount(3);
int PeaShooter::price= 100;
int PeaShooter::getCooldown()
{
    return cooldown;
}

int PeaShooter::getPrice()
{
    return price;
}

void PeaShooter::shoot()
{
    ++timeIntervals;
    if(timeIntervals%View::secondsToFrameCount(1) == 0)
    {
        Pea* pea;
        if(Model::getProgress()==5)
         pea = new Pea(shooterTimer, zombieHitPlayer ,View::pixelPerSecondsToPixelPerFrame(450),sceneRef,this);
        else
         pea = new Pea(shooterTimer, zombieHitPlayer ,View::pixelPerSecondsToPixelPerFrame(360),sceneRef,this);
        scene()->addItem(pea);
        pea->setPos(55,2);
        shooterPlayer->setPosition(0);
        shooterPlayer->play();
    }
}

void PeaShooter::levelEnded()
{
    scene()->removeItem(this);
    delete this;
}
