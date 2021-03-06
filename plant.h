#ifndef PLANT_H
#define PLANT_H

#include <QString>
#include <QGraphicsPixmapItem>
#include "plantslot.h"

class PlantSlot;

class Plant : public QObject , public QGraphicsPixmapItem
{

public:
    Plant(QGraphicsItem *parent = nullptr);
    PlantSlot* slot;
    ~Plant();
public slots:
    void levelEnded();
};
#endif // PLANT_H
