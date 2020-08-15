#include "controller.h"
#include "peashooter.h"
#include <QDebug>
void Controller::SetupSeason(int seasonNum)
{
    if(seasonItemsHolder != nullptr)
        delete seasonItemsHolder;
    seasonItemsHolder = new QGraphicsRectItem();
    seasonItemsHolder->setRect(0,0,800,600);
    QString address;
    int x=0;
    int y=0;
    if(seasonNum == 1)
    {
        address ="One";
        x=22;
        y=260;
    }
    else if(seasonNum ==2)
    {
        address ="Two";
        x=22;
        y=260;
    }
    else if(seasonNum ==3)
    {
        x=16;
        y=130;
        address ="Three";
    }
    QGraphicsPixmapItem * lanes = new QGraphicsPixmapItem(seasonItemsHolder);
    lanes->setPixmap(QPixmap(":/Sprites/" + address + "Lane.png"));
    lanes->setPos(x,y);
    scene->addItem(lanes);
}

void Controller::addZombie(const int& moveSpeed , const int& HP)
{
    zombieList.push_back(new Zombie{moveSpeed,ctimer,HP,holder,});
    scene->addItem(zombieList.last());
    zombieList.last()->setPos(800,300);
}

void Controller::addSun()
{
    sunList.push_back(new Sun(scene,controllerScore,holder,ctimer));
}

Controller::Controller(QObject *parent) : QObject(parent)
{
    seasonItemsHolder = new QGraphicsRectItem();
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);

    holder = new QGraphicsRectItem();
    holder->setRect(0,0,800,600);

    ctimer = new QTimer();
    ctimer->start(16);

    scoreBoard = new QGraphicsPixmapItem();
    scoreBoard->setPixmap(QPixmap(":/Sprites/UpperPannel.png"));
    scene->addItem(scoreBoard);
    scoreBoard->setPos(20,0);

    controllerScore = new Score(holder);
    scene->addItem(controllerScore);
    controllerScore->setPos(40,58);


    SetupSeason(1);


    slotArray = new PlantSlot**[3];
    for(int i= 0;i<3;i++)
    {
        slotArray[i] = new PlantSlot*[8];
        for(int j =0;j<8;j++)
        {
            slotArray[i][j] = new PlantSlot(38 + (j*90),145 + (i * 120),holder);
            scene->addItem(slotArray[i][j]);
        }
    }

//    auto myPeaShooter = new PeaShooter(ctimer,scene ,holder);
//    scene->addItem(myPeaShooter);
//    myPeaShooter->setPos(50,300);
}

Controller::~Controller()
{
    for(int i =0;i<3;i++)
    {
        for(int j=0;j<8;j++)
        {
            delete[] slotArray[i][j];
        }
        delete [] slotArray[i];
    }
    delete slotArray;
    delete holder;
    delete ctimer;
    delete seasonItemsHolder;
}
