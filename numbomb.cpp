#include "numbomb.h"
#include "gamescene.h"
#include "transformbuilder.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QDebug>

Num::Num() {}

void Num::onAttach()
{
    this->transform = this->gameObject->getComponent<Transform>();
    this->gameScene = this->gameObject->getGameScene();
    Q_ASSERT(this->transform != nullptr);
}

void Num::onUpdate(float deltaTime)
{
}
