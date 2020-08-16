#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QTimer>
#include <QMediaPlayer>
#include "controller.h"
#include <QGraphicsSceneMouseEvent>

class View : public QGraphicsView
{
    Q_OBJECT

public:
    static View* instance;
    explicit View();
    QPoint getMousePos();
    static int frameRate;
    static int secondsToFrameCount(int seconds){return seconds * frameRate;}
    static float pixelPerSecondsToPixelPerFrame(float pixelPerSeconds){return pixelPerSeconds/frameRate;}
    ~View();

private:
    QTimer * viewTimer;
    QMediaPlayer * musicPlayer;
    QMediaPlaylist *playList;
    int seconds = 0;
    Controller* viewController;
    void mousePressEvent(QMouseEvent *event) override;

public slots:

    void incrementTime();

signals:

    void mouseLeftClicked();
};

#endif // VIEW_H
