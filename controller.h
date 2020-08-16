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
    int framesSinceLastPick;
    QGraphicsScene * scene;
    QTimer * ctimer;
    QGraphicsRectItem * holder;
    QGraphicsRectItem * seasonItemsHolder;
    QList<Zombie*> zombieList;
    QList<Sun*> sunList;
    QGraphicsPixmapItem *scoreBoard;
    Score *controllerScore;
    PlantSlot *** slotArray;
    PlantPreview* currentPlantSelected;
    void SetupSeason(int seasonNum);
    Plant* addPlant(QString plant ,const int& slotX, const int& slotY);
public:
    static Controller * instance;
    bool deselectCurrentObjectSelected();
    bool isAnthingSelected();
    void selectPlant(QString plant);
    void addZombie(const float& moveSpeed, const int& HP);
    void addSun();
    explicit Controller(QObject *parent = nullptr);
    void slotClickedOn(const int& x,const int& y);

    ~Controller();

signals:
    void plantAPlant();
    void selectedPlantDeselected();

public slots:
    void update();
};

#endif // CONTROLLER_H
