#ifndef PLANTCARD_H
#define PLANTCARD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "plant.h"
#include <QTimer>
#include "score.h"
#include <QGraphicsSceneMouseEvent>
#include <QMediaPlayer>
#include "controller.h"

//states a card can be in
enum CardState
{
    Selectable,
    Selected,
    NotEnoughSun,
    OnCooldown
};

class PlantCard : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    //initialized with plant data
    int price;
    int cooldown;
    //used for cooldown
    int timeSinceLastUse;
    //used for getting sun count
    Score * scoreRef;
    //it can be static, so why not
    static QMediaPlayer * cardPlayer;
    //masks for showing card state
    QGraphicsRectItem * mask;
    QGraphicsRectItem * mask2;
    //name of the plant being represented
    QString plantType;
    //assists the state system
    bool isSelected;
    //current state of card
    CardState state;
    void setState(CardState state);

public:
    ~PlantCard();
    explicit PlantCard(QString  plant, QTimer * timer , Score * scoreRef ,   QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
    //main loop
    void update();
    void unselected();
    void used();
};

#endif // PLANTCARD_H
