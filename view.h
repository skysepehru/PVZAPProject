#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QTimer>
#include <QMediaPlayer>
#include "controller.h"
class View : public QGraphicsView
{
    Q_OBJECT

public:
    explicit View();
    ~View();

private:
    QTimer * viewTimer;
    QMediaPlayer * musicPlayer;
    int seconds = 0;
    Controller* viewController;

public slots:
    void incrementTime();

};

#endif // VIEW_H
