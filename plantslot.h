#ifndef PLANTSLOT_H
#define PLANTSLOT_H

#include <QObject>
#include <QGraphicsRectItem>
#include "plant.h"

class Plant;

class PlantSlot : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit PlantSlot(const int& x,const int& y,const int& slotX,const int& slotY, QGraphicsItem *parent = nullptr);
    bool isPlantable;
    Plant * currentPlant;
    int slotX;
    int slotY;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

};

#endif // PLANTSLOT_H
