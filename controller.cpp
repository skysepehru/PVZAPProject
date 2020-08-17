#include "controller.h"
#include "peashooter.h"
#include "plantcard.h"
#include <QDebug>
#include <QGraphicsView>
#include "view.h"
#include "sunflower.h"

void Controller::deselectCurrentObjectSelected()
{
    if(currentPlantSelected != nullptr)
    {
        //if less than 5 frames have passed since selection, do not deselect...bug:select bad inselect
        if(framesSinceLastPick < 5)
            return;
        delete  currentPlantSelected;
        currentPlantSelected = nullptr;
        //notifying plantcards of this event
        emit selectedPlantDeselected();
    }
}

void Controller::SetupSeason(int seasonNum)
{
    //seasonItemsHolder barye pak kardan har marhale...
    if(seasonItemsHolder != nullptr)
        delete seasonItemsHolder;

    seasonItemsHolder = new QGraphicsRectItem();
    seasonItemsHolder->setRect(0,0,800,600);

    //initializing plant cards.
    PlantCard* peaShooterCard = new PlantCard( "PeaShooter",ctimer,controllerScore,seasonItemsHolder);
    connect(this,SIGNAL ( selectedPlantDeselected()),peaShooterCard,SLOT(unselected()));
    connect(this,SIGNAL ( plantAPlant()),peaShooterCard,SLOT(used()));
    scene->addItem(peaShooterCard);
    peaShooterCard->setPos(105,7);

    PlantCard* sunFlowerCard = new PlantCard("SunFlower",ctimer,controllerScore,seasonItemsHolder);
    connect(this,SIGNAL ( selectedPlantDeselected()),sunFlowerCard,SLOT(unselected()));
    connect(this,SIGNAL ( plantAPlant()),sunFlowerCard,SLOT(used()));
    scene->addItem(sunFlowerCard);
    sunFlowerCard->setPos(160,7);

    //initializing season objects and setting correct plantslot settings
    QString address;
    int x=0;
    int y=0;

    if(seasonNum == 1)
    {
        address ="One";
        x=22;
        y=260;
        for(int i=0;i<8;i++)
        {
            slotArray[0][i]->isPlantable = false;
            slotArray[1][i]->isPlantable = true;
            slotArray[2][i]->isPlantable = false;
        }
        slotArray[1][7]->isPlantable = false;
    }
    else if(seasonNum ==2)
    {
        address ="Two";
        x=22;
        y=260;
        for(int i=0;i<8;i++)
        {
            slotArray[0][i]->isPlantable = false;
            slotArray[1][i]->isPlantable = true;
            slotArray[2][i]->isPlantable = true;
        }
        slotArray[1][7]->isPlantable = false;
        slotArray[2][7]->isPlantable = false;
    }
    else if(seasonNum ==3)
    {
        x=16;
        y=130;
        address ="Three";
        for(int i=0;i<8;i++)
        {
            slotArray[0][i]->isPlantable = true;
            slotArray[1][i]->isPlantable = true;
            slotArray[2][i]->isPlantable = true;
        }
        slotArray[0][7]->isPlantable = false;
        slotArray[1][7]->isPlantable = false;
        slotArray[2][7]->isPlantable = false;
    }

    //loading lane graphic
    QGraphicsPixmapItem * lanes = new QGraphicsPixmapItem(seasonItemsHolder);
    lanes->setPixmap(QPixmap(":/Sprites/" + address + "Lane.png"));
    lanes->setPos(x,y);
    scene->addItem(lanes);
}

Plant* Controller::addPlant(QString plant,const int& slotX, const int& slotY)
{
    //adding plant with the name given.
    Plant * temp = nullptr;
    if(plant == "PeaShooter"){
        temp = new PeaShooter(ctimer, scene ,holder);
        controllerScore->decreaseSunCount(PeaShooter::getPrice());
    }
    else if(plant=="SunFlower"){
        temp=new SunFlower(ctimer,controllerScore,holder);
        controllerScore->decreaseSunCount(SunFlower::getPrice());
    }
    //set the slot on plant
    temp->slot = slotArray[slotX][slotY];
    scene->addItem(temp);
    temp->setPos(slotArray[slotX][slotY]->rect().x() +15 , slotArray[slotX][slotY]->rect().y() + 25);
    return temp;
}

bool Controller::isAnthingSelected()
{
    if(currentPlantSelected == nullptr)
        return false;
    return true;
}

void Controller::selectPlant(QString plant)
{
    if(isAnthingSelected())
        return;
    framesSinceLastPick = 0;
    currentPlantSelected = new PlantPreview(plant,ctimer,holder);
    scene->addItem(currentPlantSelected);
}

//k
void Controller::addZombie(const float& moveSpeed , const int& HP)
{
    zombieList.push_back(new Zombie{moveSpeed,ctimer,HP,holder,});
    scene->addItem(zombieList.last());
    zombieList.last()->setPos(800,300);
}

void Controller::addSun()
{
    sunList.push_back(new Sun(scene,controllerScore,holder,ctimer,true));
}

Controller * Controller::instance = nullptr;
Controller::Controller(QObject *parent) : QObject(parent) , currentPlantSelected{nullptr}
{
    framesSinceLastPick = 0;

    if(Controller::instance == nullptr)
        Controller::instance = this;

    seasonItemsHolder = new QGraphicsRectItem();
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);

    holder = new QGraphicsRectItem();
    holder->setRect(0,0,800,600);

    ctimer = new QTimer();
    ctimer->start(1000/View::frameRate);

    connect(ctimer,SIGNAL(timeout()),this,SLOT(update()));

    scoreBoard = new QGraphicsPixmapItem();
    scoreBoard->setPixmap(QPixmap(":/Sprites/UpperPannel.png"));
    scene->addItem(scoreBoard);
    scoreBoard->setPos(20,0);

    controllerScore = new Score(holder);
    scene->addItem(controllerScore);
    controllerScore->setPos(40,58);

    //setup plant slots
    slotArray = new PlantSlot**[3];
    for(int i= 0;i<3;i++)
    {
        slotArray[i] = new PlantSlot*[8];
        for(int j =0;j<8;j++)
        {
            slotArray[i][j] = new PlantSlot(38 + (j*90),145 + (i * 120),i,j,holder);
            scene->addItem(slotArray[i][j]);
        }
    }

    SetupSeason(3);
}

void Controller::slotClickedOn(const int &x, const int &y)
{
    //if a plant is selected , the slot clicked on is plantable and it is emply, a plant will be planted.
    if(isAnthingSelected())
    {
        if(slotArray[x][y]->isPlantable && slotArray[x][y]->currentPlant == nullptr){
            slotArray[x][y]->currentPlant = addPlant(currentPlantSelected->getPlant(),x,y);
            emit plantAPlant();
            deselectCurrentObjectSelected();
        }
    }
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

void Controller::update()
{
    framesSinceLastPick++;
}
