#ifndef SHOVEL_H
#define SHOVEL_H

#include <QObject>
#include <QGraphicsPathItem>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QMediaPlayer>

class Shovel : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Shovel(int initialX,int initialY,QTimer* timer, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    ~Shovel();
private:
    bool isSelected = false;
    QMediaPlayer * player;
    int initialX;
    int initialY;
signals:

public slots:
    void update();
    void deselected();
    void used();
};

#endif // SHOVEL_H
