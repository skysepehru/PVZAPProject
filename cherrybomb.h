#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H
#include "plant.h"
#include <QMediaPlayer>
#include <QGraphicsRectItem>
#include <QTimer>


class CherryBomb : public Plant
{
    Q_OBJECT
private:

    QMediaPlayer * bombPlayer;
    QTimer * bombTimer;
    int timeIntervals=0;
    static int price;
    static int cooldown;


public:
    CherryBomb(QTimer *bombTimer , QMediaPlayer* bombPlayer ,QGraphicsItem * parent = nullptr);
    static int getCooldown();
    static int getPrice();
public slots:
   void enfejar();
   void levelEnded();

};

#endif // CHERRYBOMB_H
