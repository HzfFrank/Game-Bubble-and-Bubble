#ifndef WALL_H
#define WALL_H

#include <component.h>
#include <gameobject.h>
#include <transform.h>

class Wall : public Component
{
private:
    int x, y;

public:
    explicit Wall(int x, int y);
    void onAttach() override;

protected:
    Transform *transform = nullptr;
};

#endif // WALL_H
