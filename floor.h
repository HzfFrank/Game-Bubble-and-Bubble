#ifndef FLOOR_H
#define FLOOR_H

#include <component.h>
#include <gameobject.h>
#include <transform.h>

class Floor : public Component
{
private:
    int x, y;

public:
    explicit Floor(int x, int y);

    void onAttach() override;
    //void onUpdate(float deltaTime) override;

protected:
    Transform *transform = nullptr;
    QGraphicsItem *collider = nullptr;
};

#endif // FLOOR_H
