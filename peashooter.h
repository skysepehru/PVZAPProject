#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <QObject>
#include "plant.h"
#include "pea.h"
#include <QMediaPlayer>
#include <QTimer>
#include <QGraphicsPixmapItem>

class PeaShooter : public QObject , public QGraphicsPixmapItem, public Plant
{
    Q_OBJECT

private:
    QMediaPlayer * shooterPlayer;
    QTimer *shooterTimer;
    int timeIntervals = 0;
    QGraphicsScene * sceneRef;

public:
    explicit PeaShooter(QTimer *shooterTimer  , QGraphicsScene * sceneRef ,QGraphicsItem *parent = nullptr);

signals:

public slots:
    void shoot();


};

#endif // PEASHOOTER_H
