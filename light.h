#ifndef LIGHT_H
#define LIGHT_H

#include "bomb.h"
#include <component.h>
#include <gameobject.h>
#include <transform.h>

class Light : public Component
{
private:
    int x, y;
    int cd = 50;
    Bomb *bomb;

public:
    Light(int x, int y, Bomb *bomb);
    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    Transform *transform = nullptr;
};

#endif // LIGHT_H
