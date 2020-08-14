#include "view.h"
#include "zombie.h"
#include <QDebug>
#include <QMediaPlayer>

View::View() : QGraphicsView()
{
    viewController = new Controller();

    setScene(viewController->scene);

    setBackgroundBrush(QBrush(QImage(":/Sprites/Background.png")));

    setFixedSize(800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    musicPlayer = new QMediaPlayer();
    musicPlayer->setMedia(QUrl("qrc:/Sounds/BackgroundMusic.mp3"));
    musicPlayer->setVolume(100);
    musicPlayer->play();
    qInfo() <<musicPlayer->state();

    viewTimer = new QTimer();
    viewTimer->start(1000);
    connect(viewTimer,SIGNAL(timeout()),this,SLOT(incrementTime()));
}

View::~View()
{
    delete viewTimer;
    delete musicPlayer;
    delete viewController;
}

void View::incrementTime()
{
    ++seconds;
    if(seconds == 10 ||seconds == 15)
    {
        viewController->addZombie(3,10);
    }

    if(seconds % 2 == 0)
    {
        viewController->addSun();
    }
}
