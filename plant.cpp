#include "plant.h"

Plant::Plant(QGraphicsItem *parent) : QObject() , QGraphicsPixmapItem(parent)
{
    slot = nullptr;
}

Plant::~Plant()
{
    slot->currentPlant = nullptr;
}

void Plant::levelEnded()
{
    delete this;
}


