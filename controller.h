#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>
#include "score.h"
#include "zombie.h"
#include "sun.h"
#include "plantslot.h"
class Controller : public QObject
{
    Q_OBJECT
    friend class View;

private:
    QGraphicsScene * scene;
    QTimer * ctimer;
    QGraphicsRectItem * holder;
    QGraphicsRectItem * seasonItemsHolder;
    QList<Zombie*> zombieList;
    QList<Sun*> sunList;
    QGraphicsPixmapItem *scoreBoard;
    Score *controllerScore;
    PlantSlot *** slotArray;

    void SetupSeason(int seasonNum);
public:
    void addZombie(const int& moveSpeed, const int& HP);
    void addSun();
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

signals:

};

#endif // CONTROLLER_H
