#include "pausebutton.h"
#include "qtimer.h"
#include "transformbuilder.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include "gamescene.h"

PauseButton::PauseButton() {}

void PauseButton::onAttach() {
  auto transform = this->gameObject->getComponent<Transform>();
  this->gameScene = this->gameObject->getGameScene();
  Q_ASSERT(transform != nullptr);
}

void PauseButton::onClick(QGraphicsSceneMouseEvent *ev) {
    Q_ASSERT(this->gameScene != nullptr);
    this->gameScene->Pause();
}
