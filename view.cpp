#include "view.h"
#include "zombie.h"
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>

View* View::instance = nullptr;

int View::frameRate = 60;

View::View() : QGraphicsView()
{
    if(instance == nullptr)
        instance = this;

    viewController = new Controller();

    setScene(viewController->scene);

    setBackgroundBrush(QBrush(QImage(":/Sprites/Background.png")));

    setFixedSize(800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    playList = new QMediaPlaylist();
    playList->addMedia(QUrl("qrc:/Sounds/BackgroundMusic.mp3"));
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    musicPlayer = new QMediaPlayer();
    musicPlayer->setPlaylist(playList);
    musicPlayer->play();

    qInfo() <<musicPlayer->state();

    viewTimer = new QTimer();
    viewTimer->start(1000);
    connect(viewTimer,SIGNAL(timeout()),this,SLOT(incrementTime()));
}

QPoint View::getMousePos()
{
    QPoint p = mapFromGlobal(QCursor::pos());
    return p;
}

View::~View()
{
    delete viewTimer;
    delete musicPlayer;
    delete viewController;
    delete playList;
}

void View::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    emit mouseLeftClicked();
}

void View::incrementTime()
{
    ++seconds;
    if(seconds == 1)
    {
        viewController->addZombie(pixelPerSecondsToPixelPerFrame(90),10);
    }

    if(seconds % 2 == 0)
    {
        viewController->addSun();
    }
}
