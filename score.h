#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QMediaPlayer>

class Score : public QGraphicsTextItem
{
    friend class Sun;
private:
    int sunCount;
    QMediaPlayer *scorePlayer;
public:
    Score(QGraphicsItem * parent = nullptr);
    ~Score();
    void addToSunCount(int amount);
    void decreaseSunCount(int amount);
    int getSunCount();
    void resetSunCount();
};

#endif // SCORE_H
