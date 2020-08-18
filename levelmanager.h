#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QObject>
#include <QTimer>
#include "level.h"

class LevelManager : public QObject
{
    Q_OBJECT
public:
    explicit LevelManager(QTimer * timer , QObject *parent = nullptr);
    QTimer * timer;
    void startLevel(Level level);
signals:
    void levelFinished();

public slots:
    void update();
};

#endif // LEVELMANAGER_H
