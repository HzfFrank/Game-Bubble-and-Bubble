#ifndef NUMBOMB_H
#define NUMBOMB_H

#include <component.h>
#include <gameobject.h>
#include <transform.h>

class Num : public Component
{
public:
    Num();

    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    Transform *transform = nullptr;
};

#endif // NUMBOMB_H
