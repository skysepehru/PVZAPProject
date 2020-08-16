#ifndef PEA_H
#define PEA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "zombie.h"
#include <QMediaPlayer>

class Pea : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    float velocity;
    float threshold;
    int temp;
    QGraphicsScene * sceneRef;
    QMediaPlayer * player;
public:
    explicit Pea(QTimer *peaTimer , QMediaPlayer * player, const float& velocity, QGraphicsScene * sceneRef, QGraphicsItem *parent = nullptr);

signals:

public slots:
    void move();

};

#endif // PEA_H
