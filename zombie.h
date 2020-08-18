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
    //QMediaPlayer * groanPlayer;
public:
    Zombie(const float& moveSpeed , QTimer *timer,const int& HP, bool isConeZombie, QGraphicsItem * parent = nullptr);
    void decreaseHP();
    void destroy();
    ~Zombie();
signals:
    void onDestroy();
    void lost();
public slots:
    void moveToLeft();
    void levelEnd();
};

#endif // ZOMBIE_H
