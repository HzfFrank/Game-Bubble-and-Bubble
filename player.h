#ifndef PLAYER_H
#define PLAYER_H

#include <component.h>
#include <gameobject.h>
#include <transform.h>
#include "core.h"
#include "numbomb.h"
#include <queue>
#include <utility>
typedef std::pair<int, int> pii;

class Player : public Component
{
private:
    int id;
    int speed;
    int cd;
    bool lock_status;
    int score;
    int NumberOfBombs;
    int TotalNumberOfBombs;
    int range = 1;
    int x, y;
    int lastX, lastY;
    bool moveable = false;
    std::queue<std::pair<int, int>> route;
    pii aim;
    int de;
    int lastdir;

    Core *map;

public:
    Player(int x, int y, int id, Core *map);
    void onAttach() override;
    void onUpdate(float deltaTime) override;

    //get information
    int GetPlayerX() const { return x; }
    int GetPlayerY() const { return y; }
    int GetId() const { return id; }
    int GetSpeed() const { return speed; }
    int GetNumberOfBombs() const { return NumberOfBombs; }
    int GetRange() const { return range; }
    Core *GetMap() const { return map; }

    //orperation
    void LayBomb();
    void IncreaseRange() { range++; }
    void Counting(float deltatime) { cd -= deltatime; }
    void RenewNumberOfBombs() { NumberOfBombs++; }
    void lock() { lock_status = true; }
    void unlock() { lock_status = false; }
    void RenewCd() { if (!lock_status) cd = speed; }
    void ChangRoute();

    //move
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    int BFS_SearchProp();
    void Search(int nowX, int nowY);
    void Moveto(int tx, int ty);

    //eat
    void EatSpeed() { speed--; }
    void EatRange() { range++; }
    void EatBomb() { TotalNumberOfBombs++; NumberOfBombs++;}
    void EatMove() { moveable = true; }
protected:
    Transform *transform = nullptr;
    QGraphicsItem *collider = nullptr;
    GameObject *showBomb = nullptr;
    Num *num_of_bomb = nullptr;
};

#endif // PLAYER_H
