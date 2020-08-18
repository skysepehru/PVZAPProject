#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include<QTimer>
#include<QGraphicsPixmapItem>
#include"score.h"
#include"plant.h"
#include<QMediaPlayer>



class SunFlower:public Plant
{
    Q_OBJECT
private:
    QTimer *sunFlowerTimer;
    QMediaPlayer *sunFlowerPlayer;
    int timeIntervals = 0;
    Score* scoreCount;
    static int cooldown;
    static int price;
public:
    SunFlower(QTimer* sunFlowerTimer,Score* scoreCount,QGraphicsItem *parent=nullptr);
    static int getCooldown();
    static int getPrice();
    ~SunFlower();
public slots:
      void update();
      void levelEnded();

};

#endif // SUNFLOWER_H
