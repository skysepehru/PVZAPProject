#ifndef LEVELDATA_H
#define LEVELDATA_H


class LevelData
{
public:
    LevelData(const int& enterTimer , bool isConeZombie , const int& HP , const float& moveSpeed, const int& laneNumber);
    int enterTime;
    bool isConeZombie;
    int HP;
    float moveSpeed;
    int laneNumber;
};

#endif // LEVELDATA_H
