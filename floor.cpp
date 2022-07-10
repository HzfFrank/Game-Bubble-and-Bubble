#include "floor.h"
#include "gamescene.h"
#include "hitable.h"
#include "transformbuilder.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

Floor::Floor(int x, int y) : Component(), x(x), y(y) {}

void Floor::onAttach()
{
    this->transform = this->gameObject->getComponent<Transform>();
    //Q_ASSERT(this->transform != nullptr);
}
