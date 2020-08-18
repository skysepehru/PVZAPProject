#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>
#include "score.h"
#include "zombie.h"
#include "sun.h"
#include "plantslot.h"
#include "plantpreview.h"
#include "model.h"
#include "levelmanager.h"
#include "shovel.h"

class Controller : public QObject
{
    Q_OBJECT
    friend class View;
    friend class LevelManager;
private:
    //used to prevent instantly deselecting after selecting an object
    bool isShovelSelected = false;
    int framesSinceLastPick;
    QGraphicsScene * scene;
    QTimer * ctimer;
    QGraphicsRectItem * holder;
    //parent for items that are specefic to a season
    //QGraphicsRectItem *   seasonItemsHolder;
    QVector<QGraphicsItem *> seasonItemsHolder;
    QList<Sun*> sunList;
    //The Scoreboard Graphic Item
    QGraphicsPixmapItem *scoreBoard;
    QGraphicsPixmapItem *shovelHolder;
    Shovel* shovel;
    //array holding the plant Slot refrences
    PlantSlot *** slotArray;
    //if it is null, no plant is selected
    PlantPreview* currentPlantSelected;

    //Adds plant on a certain plant slot
    Plant* addPlant(QString plant ,const int& slotX, const int& slotY);

    void  addCard(int x,int y , QString cardName);
    Model *myModel;
    LevelManager *myLevelManager;
    QMediaPlayer* bombPlayer;
    //Sun Count Text On the Scoreboard
    Score *controllerScore;
    QMediaPlayer* losePlayer;
    QMediaPlayer* winPlayer;
public:

    //takes 1,2,3 and initializes the scene based on the number
    void SetupSeason(int seasonNum);
    bool selectShovel();

    //Singleton
    static Controller * instance;
    //deselects the selected object ,returns false if the program tries to instantly deselect after selecting
    void deselectCurrentObjectSelected();
    //the name says it all
    bool isAnthingSelected();
    //if no other plant is allready selected,select plant with the name given
    void selectPlant(QString plant);
    void addSun();
    explicit Controller(QObject *parent = nullptr);
    //gets called by plantslot when it is clicked on
    void slotClickedOn(const int& x,const int& y);

    ~Controller();

signals:
    //sent when a plant is planted,used in plantcard
    void plantAPlant();
    //sent when a plant is deselected,used in plantcard
    void selectedPlantDeselected();
    void lostLevelController();
    void shovelDeselected();
    void shovelUsed();

public slots:
    void update();
    void wonLevel();
    void lostLevel();
};

#endif // CONTROLLER_H
