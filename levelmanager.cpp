#include "levelmanager.h"

LevelManager::LevelManager(QTimer * timer , QObject *parent) : QObject(parent) , timer(timer)
{
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
}

void LevelManager::startLevel(Level level)
{

}

void LevelManager::update()
{

}
