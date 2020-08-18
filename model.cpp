#include "model.h"
#include "view.h"
#include <vector>

Model::Model()
{
    progress = 0;

    //Season 1 Level 1
    QVector <LevelData*> levelData;
    float moveSpeed;
    moveSpeed = View::instance->pixelPerSecondsToPixelPerFrame(90);
    levelData  = {new LevelData{50,false,4,moveSpeed,2},
                  new LevelData{54,false,4,moveSpeed,2},
                  new LevelData{57,false,4,moveSpeed,2},
                  new LevelData{59,false,4,moveSpeed,2},
                  new LevelData{60,false,4,moveSpeed,2},
                  };


    levels.push_back(new Level(1,levelData,false));

    //Season 2 Level 1

    moveSpeed = View::instance->pixelPerSecondsToPixelPerFrame(90);
    levelData  = {new LevelData{50,false,4,moveSpeed,2},
                  new LevelData{55,false,4,moveSpeed,3},
                  new LevelData{58,false,4,moveSpeed,2},
                  new LevelData{60,false,4,moveSpeed,3},
                  new LevelData{62,false,4,moveSpeed,2},
                  new LevelData{63,false,4,moveSpeed,2},
                  new LevelData{63,false,4,moveSpeed,3},
                  new LevelData{64,false,4,moveSpeed,3}
                  };

    levels.push_back(new Level(2,levelData,true));

    //Season 2 Level 2

    moveSpeed = View::instance->pixelPerSecondsToPixelPerFrame(90);
    levelData  = {new LevelData{45,false,4,moveSpeed,2},
                  new LevelData{48,false,4,moveSpeed,3},
                  new LevelData{48,false,4,moveSpeed,2},
                  new LevelData{49,false,4,moveSpeed,3},
                  new LevelData{50,false,4,moveSpeed,2},
                  new LevelData{50,false,4,moveSpeed,3},
                  new LevelData{51,false,4,moveSpeed,2},
                  new LevelData{51,false,4,moveSpeed,3},
                  new LevelData{52,false,4,moveSpeed,2},
                  new LevelData{52,false,4,moveSpeed,3}
                  };

    levels.push_back(new Level(2,levelData,false));

    //Season 3 Level 1

    moveSpeed = View::instance->pixelPerSecondsToPixelPerFrame(90);
    levelData  = {new LevelData{40,false,4,moveSpeed,1},
                  new LevelData{44,false,4,moveSpeed,2},
                  new LevelData{46,false,4,moveSpeed,3},
                  new LevelData{47,false,4,moveSpeed,1},
                  new LevelData{47,false,4,moveSpeed,2},
                  new LevelData{48,false,4,moveSpeed,3},
                  new LevelData{48,false,4,moveSpeed,1},
                  new LevelData{50,false,4,moveSpeed,2},
                  new LevelData{50,false,4,moveSpeed,3},
                  new LevelData{50,false,4,moveSpeed,1},
                  new LevelData{51,false,4,moveSpeed,2},
                  new LevelData{51,false,4,moveSpeed,3},
                  new LevelData{53,true,10,moveSpeed,1},
                  new LevelData{53,true,10,moveSpeed,2},
                  new LevelData{53,true,10,moveSpeed,3}
                  };

    levels.push_back(new Level(3,levelData,false));

    //Season 3 Level 2

    moveSpeed = View::instance->pixelPerSecondsToPixelPerFrame(90);
    levelData  = {new LevelData{40,false,4,moveSpeed,1},
                  new LevelData{44,false,4,moveSpeed,2},
                  new LevelData{46,false,4,moveSpeed,3},
                  new LevelData{47,false,4,moveSpeed,1},
                  new LevelData{47,false,4,moveSpeed,2},
                  new LevelData{48,false,4,moveSpeed,3},
                  new LevelData{48,false,4,moveSpeed,1},
                  new LevelData{50,false,4,moveSpeed,2},
                  new LevelData{50,false,4,moveSpeed,3},
                  new LevelData{50,false,4,moveSpeed,1},
                  new LevelData{51,false,4,moveSpeed,2},
                  new LevelData{51,false,4,moveSpeed,3},
                  new LevelData{53,true,12,moveSpeed,1},
                  new LevelData{53,true,12,moveSpeed,2},
                  new LevelData{53,true,12,moveSpeed,3}
                  };

    levels.push_back(new Level(3,levelData,false));

    //Season 3 Level 3

    moveSpeed = View::instance->pixelPerSecondsToPixelPerFrame(180);
    levelData  = {new LevelData{40,true,15,moveSpeed,1},
                  new LevelData{44,true,15,moveSpeed,2},
                  new LevelData{46,true,15,moveSpeed,3},
                  new LevelData{47,true,15,moveSpeed,1},
                  new LevelData{47,true,15,moveSpeed,2},
                  new LevelData{48,true,15,moveSpeed,3},
                  new LevelData{48,true,15,moveSpeed,1},
                  new LevelData{50,true,15,moveSpeed,2},
                  new LevelData{50,true,15,moveSpeed,3},
                  new LevelData{50,true,15,moveSpeed,1},
                  new LevelData{51,true,15,moveSpeed,2},
                  new LevelData{51,true,15,moveSpeed,3},
                  new LevelData{53,true,15,moveSpeed,1},
                  new LevelData{53,true,15,moveSpeed,2},
                  new LevelData{53,true,15,moveSpeed,3}
                  };

    levels.push_back(new Level(3,levelData,false));

}

bool Model::isGameFinished()
{
    if(levels.length() == progress+1)
        return true;
    return  false;
}

Level* Model::getCurrentLevel()
{
    return levels[progress];
}

void Model::goToNextLevel()
{
    progress++;
}
