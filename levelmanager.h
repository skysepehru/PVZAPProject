#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QObject>
#include <QTimer>
#include "level.h"
#include <QGraphicsRectItem>
#include<zombie.h>
#include <QGraphicsScene>
#include <QMediaPlayer>

class LevelManager : public QObject
{
    Q_OBJECT
private:
    Level *currentLevel;
    QGraphicsScene* scene;
public:
    explicit LevelManager(QTimer* myCtimer,QGraphicsScene* scene,QObject *parent = nullptr);
    QMediaPlayer * zombiesComingPlayer;
    int counter=0;
    int timeIntervals=0;
    int mode;
    int zombieCount=0;
    QTimer * levelTimer;
    QTimer * myCtimer;
    int seconds=0;
    void startLevel(Level* level);
    void addZombie(const float& moveSpeed , const int& HP,int lane,bool isConeZombie);
    ~LevelManager();
signals:
    void levelFinished();

public slots:
    void update();
    void onZombieDeath();
};

#endif // LEVELMANAGER_H
