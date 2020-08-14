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
};

#endif // SCORE_H
