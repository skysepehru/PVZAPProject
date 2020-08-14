#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Zombie: public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    int HP;
    int moveSpeed;
public:
    Zombie(const int& moveSpeed , QTimer *timer,const int& HP, QGraphicsItem * parent);
    void decreaseHP();

public slots:
    void moveToLeft();
};

#endif // ZOMBIE_H
