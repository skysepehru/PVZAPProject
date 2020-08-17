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
    CherryBomb(QTimer *bombTimer,QGraphicsItem * parent , QMediaPlayer* bombPlayer );
    static int getCooldown();
    static int getPrice();
public slots:
   void enfejar();

};

#endif // CHERRYBOMB_H
