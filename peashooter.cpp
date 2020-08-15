#include "peashooter.h"
#include <QDebug>
#include <QGraphicsScene>
PeaShooter::PeaShooter(QTimer *shooterTimer, QGraphicsScene * sceneRef, QGraphicsItem *parent): QObject() , QGraphicsPixmapItem(parent) , sceneRef(sceneRef)
  ,Plant() , shooterTimer(shooterTimer)
{
    setPixmap(QPixmap(":/Sprites/PeaShooter"));

    shooterPlayer = new QMediaPlayer();
    shooterPlayer->setMedia(QUrl("qrc:/Sounds/Shoot.ogg"));

    connect(shooterTimer,SIGNAL(timeout()),this,SLOT(shoot()));
}

void PeaShooter::shoot()
{
    ++timeIntervals;
    if(timeIntervals%24 == 0)
    {
        auto pea = new Pea(shooterTimer,12,sceneRef);
        scene()->addItem(pea);
        pea->setPos(x()+100,y()+10);
        shooterPlayer->stop();
        shooterPlayer->setMedia(QUrl("qrc:/Sounds/Shoot.ogg"));
        shooterPlayer->play();
    }
}
