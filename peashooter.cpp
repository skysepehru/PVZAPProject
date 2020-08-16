#include "peashooter.h"
#include <QDebug>
#include <QGraphicsScene>
#include <view.h>

PeaShooter::PeaShooter(QTimer *shooterTimer, QGraphicsScene * sceneRef, QGraphicsItem *parent):Plant(parent) , sceneRef(sceneRef)
  , shooterTimer(shooterTimer)
{

    setPixmap(QPixmap(":/Sprites/PeaShooter"));

    shooterPlayer = new QMediaPlayer();
    shooterPlayer->setMedia(QUrl("qrc:/Sounds/Shoot.mp3"));

    zombieHitPlayer = new QMediaPlayer();
    zombieHitPlayer->setMedia(QUrl("qrc:/Sounds/Splat.mp3"));
    connect(shooterTimer,SIGNAL(timeout()),this,SLOT(shoot()));
}
int PeaShooter::cooldown = View::instance->secondsToFrameCount(5);
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
        auto pea = new Pea(shooterTimer, zombieHitPlayer ,View::pixelPerSecondsToPixelPerFrame(360),sceneRef);
        scene()->addItem(pea);
        pea->setPos(x()+55,y()+2);
        shooterPlayer->setPosition(0);
        shooterPlayer->play();
    }
}
