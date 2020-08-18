#ifndef MODEL_H
#define MODEL_H

#include "level.h"
#include "leveldata.h"
#include <QList>
class Model
{
private:
    QVector<Level*> levels;
    static int progress;
public:
    Model();
    bool isGameFinished();
    Level* getCurrentLevel();
    void goToNextLevel();
    static int getProgress();
};

#endif // MODEL_H
