#include "controller.h"
#include "peashooter.h"
#include "plantcard.h"
#include <QDebug>
#include <QGraphicsView>
#include "view.h"
#include "sunflower.h"
#include"cherrybomb.h"
#include "wallnut.h"


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

void Controller::addCard(int x, int y, QString cardName)
{
    PlantCard* plantCard = new PlantCard( cardName,ctimer,controllerScore);
    seasonItemsHolder.push_back(plantCard);
    connect(this,SIGNAL ( selectedPlantDeselected()),plantCard,SLOT(unselected()));
    connect(this,SIGNAL ( plantAPlant()),plantCard,SLOT(used()));
    scene->addItem(plantCard);
    plantCard->setPos(x,y);
}

void Controller::SetupSeason(int seasonNum)
{
    QGraphicsItem* item;
    for(int i = seasonItemsHolder.length() - 1;i>=0;i--)
    {
        item = seasonItemsHolder[i];
        seasonItemsHolder.removeAt(i);
        delete item;
    }

    framesSinceLastPick = 6;
    deselectCurrentObjectSelected();


    //initializing season objects and setting correct plantslot settings
    QString address;
    int x=0;
    int y=0;

    if(seasonNum == 1)
    {
        addCard(105,7,"PeaShooter");
        addCard(160,7,"SunFlower");

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
        addCard(105,7,"PeaShooter");
        addCard(160,7,"SunFlower");
        addCard(215,7,"Wallnut");
        //addCard(270,7,"CherryBomb");

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
        addCard(105,7,"PeaShooter");
        addCard(160,7,"SunFlower");
        addCard(215,7,"Wallnut");
        addCard(270,7,"CherryBomb");

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
    QGraphicsPixmapItem * lanes = new QGraphicsPixmapItem();
    seasonItemsHolder.push_back(lanes);
    lanes->setPixmap(QPixmap(":/Sprites/" + address + "Lane.png"));
    lanes->setPos(x,y);
    scene->addItem(lanes);
}

Plant* Controller::addPlant(QString plant,const int& slotX, const int& slotY)
{
    //adding plant with the name given.
    Plant * temp = nullptr;
    if(plant == "PeaShooter"){
        temp = new PeaShooter(ctimer, scene);
        controllerScore->decreaseSunCount(PeaShooter::getPrice());
    }
    else if(plant=="SunFlower"){
        temp=new SunFlower(ctimer,controllerScore);
        controllerScore->decreaseSunCount(SunFlower::getPrice());
    }
    else if(plant=="CherryBomb"){
        temp=new CherryBomb(ctimer,bombPlayer);
        controllerScore->decreaseSunCount(CherryBomb::getPrice());
    }
    else if(plant=="Wallnut"){
        temp=new Wallnut(ctimer, View::instance->pixelPerSecondsToPixelPerFrame(180));
        controllerScore->decreaseSunCount(Wallnut::getPrice());
    }
    connect(myLevelManager,SIGNAL(levelFinished()),temp,SLOT(levelEnded()));
    connect(this,SIGNAL(lostLevelController()),temp,SLOT(levelEnded()));
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

    bombPlayer = new QMediaPlayer();
    bombPlayer->setMedia(QUrl("qrc:/Sounds/CherryBombExplosion.mp3"));

    losePlayer = new QMediaPlayer();
    losePlayer->setMedia(QUrl("qrc:/Sounds/LoseMusic.mp3"));

    winPlayer = new QMediaPlayer();
    winPlayer->setMedia(QUrl("qrc:/Sounds/WinMusic.mp3"));

    myModel=new Model();
    myLevelManager = new LevelManager(ctimer,scene);
    connect(myLevelManager,SIGNAL(levelFinished()),this,SLOT(wonLevel()));
    myLevelManager->startLevel(myModel->getCurrentLevel());



}

void Controller::slotClickedOn(const int &x, const int &y)
{
    //if a plant is selected , the slot clicked on is plantable and it is emply, a plant will be planted.
    if(isAnthingSelected())
    {
        if(slotArray[x][y]->isPlantable && slotArray[x][y]->currentPlant == nullptr){
            slotArray[x][y]->currentPlant = addPlant(currentPlantSelected->getPlant(),x,y);
            if(currentPlantSelected->getPlant() == "Wallnut"){
                slotArray[x][y]->currentPlant=nullptr;

            }
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
    delete bombPlayer;
    delete myLevelManager;
    delete myModel;
    delete winPlayer;
    delete losePlayer;
}

void Controller::update()
{
    framesSinceLastPick++;
}

void Controller::wonLevel()
{
    winPlayer->setPosition(0);
    winPlayer->play();
    if(myModel->isGameFinished())
    {
        exit(1);
    }
    myModel->goToNextLevel();
    myLevelManager->startLevel(myModel->getCurrentLevel());
}

void Controller::lostLevel()
{
    losePlayer->setPosition(0);
    losePlayer->play();
    emit lostLevelController();
    myLevelManager->startLevel(myModel->getCurrentLevel());
}
