#include "shovel.h"
#include "view.h"
Shovel::Shovel(int initialX,int initialY, QTimer* timer, QGraphicsItem *parent) : QObject() , QGraphicsPixmapItem(parent) ,initialX(initialX),initialY(initialY)
{
    setPixmap(QPixmap(":/Sprites/Shovel.png"));
    setPos(initialX,initialY);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    player = new QMediaPlayer();
    player->setMedia(QUrl("qrc:/Sounds/Plant.mp3"));
}

void Shovel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelected)
    {
        QList<QGraphicsItem *> collidingList = collidingItems();
        for(int i=0; i<collidingList.size() ; ++i)
        {
            if(typeid(*(collidingList[i])) == typeid(PlantSlot))
            {
                PlantSlot * temp = dynamic_cast<PlantSlot*>(collidingList[i]);
                Controller::instance->slotClickedOn(temp->slotX,temp->slotY);
                return;
            }
        }
        isSelected = false;
        Controller::instance->deselectCurrentObjectSelected();
    }
    else if(Controller::instance->selectShovel())
        isSelected = true;
}

Shovel::~Shovel()
{
    delete player;
}

void Shovel::update()
{
    if(isSelected)
    {
        QPoint p = View::instance->getMousePos();
        setPos(p.x()-30,p.y() - 30);
    }
    else
    {
        setPos(initialX,initialY);
    }
}

void Shovel::deselected()
{
    isSelected = false;
}

void Shovel::used()
{
    player->play();
}
