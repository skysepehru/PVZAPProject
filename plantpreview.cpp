#include "plantpreview.h"
#include <QCursor>
#include <QWidget>
#include <QApplication>
#include "view.h"

PlantPreview::PlantPreview(QString plant ,QTimer* timer , QGraphicsItem *parent) : QObject() , QGraphicsPixmapItem(parent) ,plant(plant)
{
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    setPixmap(QPixmap(":/Sprites/" + plant));
    setPos(QCursor::pos());
    connect(View::instance,SIGNAL(mouseLeftClicked()),this,SLOT(mouseLeftClicked()));

}

QString PlantPreview::getPlant()
{
    return plant;
}

void PlantPreview::update()
{
    QPoint p = View::instance->getMousePos();
    setPos(p.x()-28,p.y() - 30);
}

void PlantPreview::mouseLeftClicked()
{
    if(!Controller::instance->isAnthingSelected())
        return;
    QList<QGraphicsItem *> collidingList = collidingItems();
    for(int i=0; i<collidingList.size() ; ++i)
    {
        if(typeid(*(collidingList[i])) == typeid(PlantSlot))
        {
            return;
        }
    }
    Controller::instance->deselectCurrentObjectSelected();
}
