#include "plantcard.h"
#include "peashooter.h"
#include <QDebug>
#include <QGraphicsRectItem>

void PlantCard::setState(CardState state)
{
    this->state = state;
    if(state == CardState::Selected)
    {
        mask->setOpacity(0.7);
        mask2->setOpacity(0.7);
    }
    else if(state == CardState ::OnCooldown)
    {
        mask->setOpacity(0.7);
        mask2->setOpacity(0.5);
        mask->setRect(0,0,50,70 -(70*((float)timeSinceLastUse/cooldown)));
    }
    else if(state == CardState::Selectable)
    {
        mask->setOpacity(0);
        mask2->setOpacity(0);
    }
    else if(state == CardState::NotEnoughSun)
    {
        mask->setOpacity(0.5);
        mask2->setOpacity(0.5);
    }
}

PlantCard::~PlantCard()
{
    delete cardPlayer;
}

QMediaPlayer* PlantCard::cardPlayer = new QMediaPlayer();

PlantCard::PlantCard(QString plant,QTimer * timer, Score * scoreRef ,QGraphicsItem *parent) : QObject() , QGraphicsPixmapItem(parent)
   , scoreRef(scoreRef),isSelected{false}
{
    mask = new QGraphicsRectItem(this);
    mask2 = new QGraphicsRectItem(this);
    mask->setRect(x(),y(),50,70);
    mask2->setRect(x(),y(),50,70);
    mask->setBrush(QBrush(Qt::black));
    mask2->setBrush(QBrush(Qt::black));
    mask->setOpacity(0.5);
    mask2->setOpacity(0);
    plantType = plant;
    if( plant == "PeaShooter")
    {
        cooldown = PeaShooter::getCooldown();
        price = PeaShooter::getPrice();
    }
    timeSinceLastUse = cooldown;

    setPixmap(QPixmap(":/Sprites/" + plant + "Card.png"));

    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
}

void PlantCard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(state == CardState::Selectable)
    {

            cardPlayer->setMedia(QUrl("qrc:/Sounds/Seedlift.mp3"));
            cardPlayer->play();
            isSelected = true;
            Controller::instance->selectPlant(plantType);
    }
}

void PlantCard::update()
{
    ++timeSinceLastUse;
    if(isSelected)
    {
        setState(CardState::Selected);
        return;
    }
    if(timeSinceLastUse > cooldown)
    {
        if(scoreRef->getSunCount() >= price)
        {
            setState(CardState::Selectable);
        }
        else
        {
            setState(CardState::NotEnoughSun);
        }
    }
    else
        setState(CardState::OnCooldown);
}

void PlantCard::unselected()
{
    isSelected = false;
}

void PlantCard::used()
{
    cardPlayer->setMedia(QUrl("qrc:/Sounds/Plant.mp3"));
    cardPlayer->play();
    if(!isSelected)
        return;
    isSelected = false;
    setState(CardState::OnCooldown);
    timeSinceLastUse = 0;
}


















