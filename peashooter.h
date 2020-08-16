#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <QObject>
#include "plant.h"
#include "pea.h"
#include <QMediaPlayer>
#include <QTimer>
#include <QGraphicsPixmapItem>

class PeaShooter : public Plant
{
    Q_OBJECT

private:
    QMediaPlayer * shooterPlayer;
    QMediaPlayer * zombieHitPlayer;

    QTimer *shooterTimer;
    int timeIntervals = 0;
    QGraphicsScene * sceneRef;
    static int cooldown;
    static int price;
public:
    static int getCooldown();
    static int getPrice();
    explicit PeaShooter(){}
    explicit PeaShooter(QTimer *shooterTimer , QGraphicsScene * sceneRef , QGraphicsItem *parent = nullptr);
signals:

public slots:
    void shoot();


};

#endif // PEASHOOTER_H
