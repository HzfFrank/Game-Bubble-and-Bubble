#include "wall.h"
#include "gamescene.h"
#include "health.h"
#include "hitable.h"
#include "transformbuilder.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

Wall::Wall(int x, int y) : Component(), x(x), y(y) {}

void Wall::onAttach()
{
    this->transform = this->gameObject->getComponent<Transform>();
    Q_ASSERT(this->transform != nullptr);
}
