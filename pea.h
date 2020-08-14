#ifndef PEA_H
#define PEA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "zombie.h"

class Pea : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int velocity;
    QGraphicsScene * sceneRef;
public:
    explicit Pea(QTimer *peaTimer , const int& velocity, QGraphicsScene * sceneRef, QGraphicsItem *parent = nullptr);

signals:

public slots:
    void move();

};

#endif // PEA_H
