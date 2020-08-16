#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QMediaPlayer>

class Zombie: public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    int HP;
    float moveSpeed;
    float threshold;
    int temp;
    QMediaPlayer * zombiePlayer;
public:
    Zombie(const float& moveSpeed , QTimer *timer,const int& HP, QGraphicsItem * parent);
    void decreaseHP();
    ~Zombie();

public slots:
    void moveToLeft();
};

#endif // ZOMBIE_H
