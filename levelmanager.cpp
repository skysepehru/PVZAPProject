#include "levelmanager.h"
#include "controller.h"
#include <cstdlib>
#include<QDebug>

LevelManager::LevelManager(QTimer* myCtimer,QGraphicsScene* scene, QObject *parent) : QObject(parent) , levelTimer(levelTimer),myCtimer(myCtimer)
  ,scene(scene)
{
    levelTimer= new QTimer();
    connect(levelTimer,SIGNAL(timeout()),this,SLOT(update()));


}

void LevelManager::addZombie(const float& moveSpeed , const int& HP,int lane,bool isConeZombie)
{
    int x=800,y=0;
    Zombie* temp = new Zombie(moveSpeed,myCtimer,HP,isConeZombie);
    scene->addItem(temp);
    if(lane==1)
        y=125;
    else if(lane==2)
        y=245;
    else if(lane==3)
        y=365;
    zombieCount++;
    connect(temp,SIGNAL(onDestroy()),this,SLOT(onZombieDeath()));
    connect(temp,SIGNAL(lost()),Controller::instance,SLOT(lostLevel()));
    connect(this,SIGNAL(levelFinished()),temp,SLOT(levelEnd()));
    connect(Controller::instance,SIGNAL(lostLevelController()),temp,SLOT(levelEnd()));
    temp->setPos(x,y+25);
}
void LevelManager::startLevel(Level* level)
{
    mode=rand()%2;
    currentLevel= level;
    Controller::instance->SetupSeason(level->seasonNum);
    zombieCount=0;
    timeIntervals=0;
    counter =0;
    Controller::instance->controllerScore->resetSunCount();
    levelTimer->start(1000);
}

LevelManager::~LevelManager()
{
    delete  levelTimer;
}

void LevelManager::update()
{
    ++timeIntervals;

    if(timeIntervals% 10 == 0){
        Controller::instance->addSun();
    }
    if(counter<currentLevel->levelData.length()){
        if(timeIntervals== currentLevel->levelData[counter]->enterTime ){
            if(currentLevel->areLanesRandomized){

                if(mode==1){
                    addZombie(currentLevel->levelData[counter]->moveSpeed,
                                            currentLevel->levelData[counter]->HP,currentLevel->levelData[counter]->laneNumber,currentLevel->levelData[counter]->isConeZombie);
                }
                else if(mode==0){
                    if(currentLevel->levelData[counter]->laneNumber==2){
                        addZombie(currentLevel->levelData[counter]->moveSpeed,
                                                    currentLevel->levelData[counter]->HP,3,currentLevel->levelData[counter]->isConeZombie);
                    }
                    else if(currentLevel->levelData[counter]->laneNumber==3){
                        addZombie(currentLevel->levelData[counter]->moveSpeed,
                                                    currentLevel->levelData[counter]->HP,2,currentLevel->levelData[counter]->isConeZombie);
                    }
                }
            }
            else{
                addZombie(currentLevel->levelData[counter]->moveSpeed,
                                        currentLevel->levelData[counter]->HP,currentLevel->levelData[counter]->laneNumber,currentLevel->levelData[counter]->isConeZombie);
            }

        ++counter;
        }

    }
    else{
        if (zombieCount == 0)
            emit levelFinished();
    }
}

void LevelManager::onZombieDeath()
{
    zombieCount--;
}
