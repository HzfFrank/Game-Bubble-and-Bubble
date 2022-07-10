#ifndef BOMB_H
#define BOMB_H

#include <component.h>
#include <gameobject.h>
#include <transform.h>
#include <windows.h>
#include "player.h"

class Bomb : public Component
{
private:
    int x, y;
    int cd = 200;
    // position of the bomb
    // int count_down; // time left before the bomb explodes
    Player *player;
    bool exist = true;

public:
    explicit Bomb(int x, int y, Player *player);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

    int GetBombX() const { return x; }
    int GetBombY() const { return y; }
    void explode() { exist = false; }
    Player *GetPlayer() const { return player; }

    /*int *setter; // who dropped the bomb
    int ShowTime() const { return count_down; }
    int ShowLight() const { return light_time; }
    QPointF ShowLocation() const { return location; }
    void Count();                           // count down
    void Reciprocal();                      // charge the light time
    void DroppedBomb(int x, int y, Map *m); // drop the bomb
    void IncreasePower();
    void Explode(Map *m);
    void Fade(Map *m);
    bool Check(int x, int y, int i);*/

protected:
    Transform *transform = nullptr;
    QGraphicsItem *collider = nullptr;
};

#endif // BOMB_H
