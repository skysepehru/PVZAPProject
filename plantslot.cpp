#include "plantslot.h"
#include <QGraphicsScene>
PlantSlot::PlantSlot(const int& x,const int& y ,QGraphicsItem *parent) : QObject() , QGraphicsRectItem(parent)
{
    setRect(x,y,90,120);
}
