#include "plantslot.h"
#include "controller.h"
#include <QGraphicsScene>
PlantSlot::PlantSlot(const int& x,const int& y ,const int& slotX,const int& slotY,QGraphicsItem *parent) : QObject() , QGraphicsRectItem(parent) , slotX(slotX),slotY(slotY)
{
    setPen(Qt::NoPen);
    currentPlant = nullptr;
    setRect(x,y,90,120);
}
void PlantSlot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Controller::instance->slotClickedOn(slotX,slotY);
}
