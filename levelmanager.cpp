#include "levelmanager.h"
#include "controller.h"
#include <cstdlib>
#include<QDebug>

LevelManager::LevelManager(QTimer* myCtimer,QGraphicsScene* scene, QObject *parent) : QObject(parent) , levelTimer(levelTimer),myCtimer(myCtimer)
  ,scene(scene)
{
    levelTimer= new QTimer();
    levelHolder = new QGraphicsRectItem();
    connect(levelTimer,SIGNAL(timeout()),this,SLOT(update()));


}

void LevelManager::addZombie(const float& moveSpeed , const int& HP,int lane)
{
    int x=800,y;
    zombieList.push_back(new Zombie{moveSpeed,myCtimer,HP,levelHolder});
    scene->addItem(zombieList.last());
    if(lane==1)
        y=125;
    else if(lane==2)
        y=245;
    else if(lane==3)
        y=365;
    zombieCount++;
    connect(zombieList.last(),SIGNAL(onDestroy()),this,SLOT(onZombieDeath()));
    zombieList.last()->setPos(x,y);
}
void LevelManager::startLevel(Level* level)
{
    mode=rand()%2;
    currentLevel= level;
    delete levelHolder;
    levelHolder = new QGraphicsRectItem();
    levelHolder->setRect(0,0,800,600);
    Controller::instance->SetupSeason(level->seasonNum);
    zombieCount=0;
    timeIntervals=0;
    counter =0;
    levelTimer->start(1000);
}

LevelManager::~LevelManager()
{
    delete  levelTimer;
    delete levelHolder;
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
                                            currentLevel->levelData[counter]->HP,currentLevel->levelData[counter]->laneNumber);
                }
                else if(mode==0){
                    if(currentLevel->levelData[counter]->laneNumber==2){
                        addZombie(currentLevel->levelData[counter]->moveSpeed,
                                                    currentLevel->levelData[counter]->HP,3);
                    }
                    else if(currentLevel->levelData[counter]->laneNumber==3){
                        addZombie(currentLevel->levelData[counter]->moveSpeed,
                                                    currentLevel->levelData[counter]->HP,2);
                    }
                }
            }
            else{
                addZombie(currentLevel->levelData[counter]->moveSpeed,
                                        currentLevel->levelData[counter]->HP,currentLevel->levelData[counter]->laneNumber);
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
