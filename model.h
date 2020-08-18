#ifndef MODEL_H
#define MODEL_H

#include "level.h"
#include "leveldata.h"
#include <QList>
class Model
{
private:
    QVector<Level*> levels;
    int progress;
public:
    Model();
    Level* getCurrentLevel();
    void goToNextLevel();
};

#endif // MODEL_H
