#ifndef PLANTSLOT_H
#define PLANTSLOT_H

#include <QObject>
#include <QGraphicsRectItem>
#include "plant.h"
class PlantSlot : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit PlantSlot(const int& x,const int& y, QGraphicsItem *parent = nullptr);
    bool isPlantable;
    Plant * currentPlant;
    int slotX;
    int slotY;

signals:

};

#endif // PLANTSLOT_H
