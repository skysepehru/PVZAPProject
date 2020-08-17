#ifndef SUN_H
#define SUN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "score.h"
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
class Sun : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    bool flag=true;
    QGraphicsScene * sunScene;
    float moveSpeed;
    float threshold;
    int temp;
    Score * sunScore;
    int timeIntervals = 0;
public:
    Sun(QGraphicsScene * sunScene,Score* sunScore, QGraphicsItem *parent , QTimer *timer,bool flag);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void move();
};

#endif // SUN_H
