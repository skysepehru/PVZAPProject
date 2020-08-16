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
    int price;
    int cooldown; // in miliseconds
    int timeSinceLastUse; // in miliseconds
    Score * scoreRef;
    static QMediaPlayer * cardPlayer;
    QGraphicsRectItem * mask;
    QGraphicsRectItem * mask2;
    QString plantType;
    bool isSelected;
    CardState state;
    void setState(CardState state);

public:
    ~PlantCard();
    explicit PlantCard(QString  plant, QTimer * timer , Score * scoreRef ,   QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
    void update();
    void unselected();
    void used();
};

#endif // PLANTCARD_H
