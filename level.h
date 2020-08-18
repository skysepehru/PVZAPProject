#ifndef LEVEL_H
#define LEVEL_H

#include <QList>
#include "leveldata.h"

class Level
{
public:
    Level(const int& seasonNum,QVector<LevelData*> levelData , bool areLanesRandomized);
    QVector<LevelData*> levelData;
    int seasonNum;
    bool areLanesRandomized;
};

#endif // LEVEL_H
