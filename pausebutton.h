#ifndef PAUSEBUTTON_H
#define PAUSEBUTTON_H

#include <component.h>
#include <gameobject.h>
#include <transform.h>

class PauseButton : public Component
{
public:
    PauseButton();

    void onAttach() override;
    void onClick(QGraphicsSceneMouseEvent *ev) override;
};

#endif // PAUSEBUTTON_H
