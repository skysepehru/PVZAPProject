#ifndef WALLNUT_H
#define WALLNUT_H
#include "plant.h"
#include "QTimer"
#include "QMediaplayer"
#include <QMediaPlaylist>

class Wallnut : public Plant
{
        Q_OBJECT
private:
    QTimer* wallnutTimer;
    QMediaPlayer * movingPlayer;
    QMediaPlayer * hitPlayer;
    QMediaPlaylist *wallnutPlayList;
    int timeIntervals=0;
    static int price;
    static int cooldown;
    float velocity;
    float threshold;
    int temp;

public:
    Wallnut(QTimer* wallnutTimer,float velocity, QGraphicsItem * parent);
    static int getCooldown();
    static int getPrice();
    ~Wallnut();
public slots:
    void update();
};

#endif // WALLNUT_H
