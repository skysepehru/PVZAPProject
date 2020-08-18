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
class Controller : public QObject
{
    Q_OBJECT
    friend class View;

private:
    //used to prevent instantly deselecting after selecting an object
    int framesSinceLastPick;
    QGraphicsScene * scene;
    QTimer * ctimer;
    QGraphicsRectItem * holder;
    //parent for items that are specefic to a season
    QGraphicsRectItem * seasonItemsHolder;
    QList<Zombie*> zombieList;
    QList<Sun*> sunList;
    //The Scoreboard Graphic Item
    QGraphicsPixmapItem *scoreBoard;
    //Sun Count Text On the Scoreboard
    Score *controllerScore;
    //array holding the plant Slot refrences
    PlantSlot *** slotArray;
    //if it is null, no plant is selected
    PlantPreview* currentPlantSelected;
    //takes 1,2,3 and initializes the scene based on the number
    void SetupSeason(int seasonNum);
    //Adds plant on a certain plant slot
    Plant* addPlant(QString plant ,const int& slotX, const int& slotY);

    void  addCard(int x,int y , QString cardName);

    QMediaPlayer* bombPlayer;
public:
    //Singleton
    static Controller * instance;
    //deselects the selected object ,returns false if the program tries to instantly deselect after selecting
    void deselectCurrentObjectSelected();
    //the name says it all
    bool isAnthingSelected();
    //if no other plant is allready selected,select plant with the name given
    void selectPlant(QString plant);
    void addZombie(const float& moveSpeed, const int& HP);
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

public slots:
    void update();
};

#endif // CONTROLLER_H
