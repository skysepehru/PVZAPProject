#include "controller.h"
#include "peashooter.h"

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

    auto myPeaShooter = new PeaShooter(ctimer,scene ,holder);
    scene->addItem(myPeaShooter);
    myPeaShooter->setPos(50,300);
}

Controller::~Controller()
{
    delete holder;
    delete ctimer;
}
