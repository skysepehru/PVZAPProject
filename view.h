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
    static View* instance;//Singleton
    explicit View();
    QPoint getMousePos();//returns Mouse Position Relative to the View(Application Window)
    static int frameRate;

    //used for getting frame count in a certain time
    static int secondsToFrameCount(int seconds){return seconds * frameRate;}

    //converts speed(must be float for getting thesame speed on different framerates)
    static float pixelPerSecondsToPixelPerFrame(float pixelPerSeconds){return pixelPerSeconds/frameRate;}
    ~View();

private:
    QMediaPlayer * musicPlayer;
    QMediaPlaylist *playList;//used for looping through music
    Controller* viewController;
    void mousePressEvent(QMouseEvent *event) override;


signals:

    void mouseLeftClicked();

};

#endif // VIEW_H
