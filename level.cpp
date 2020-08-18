#include "level.h"

Level::Level(const int& seasonNum,QVector<LevelData*> levelData , bool areLanesRandomized):
    levelData(levelData),seasonNum(seasonNum), areLanesRandomized(areLanesRandomized)
{

}
