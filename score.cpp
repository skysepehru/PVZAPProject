#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent) , sunCount{0}
{
    setPlainText(QString::number(sunCount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times",16));

    scorePlayer = new QMediaPlayer();
    scorePlayer->setMedia(QUrl("qrc:/Sounds/SunPick.mp3"));
}

Score::~Score()
{
    delete scorePlayer;
}

void Score::addToSunCount(int amount)
{
    sunCount += amount;
    setPlainText(QString::number(sunCount));
}

void Score::decreaseSunCount(int amount)
{
    sunCount -= amount;
    setPlainText(QString::number(sunCount));
}


int Score::getSunCount()
{
    return sunCount;
}

void Score::resetSunCount()
{
    sunCount = 0;
    setPlainText(QString::number(sunCount));
}
