#include "light.h"
#include "floor.h"
#include "gamescene.h"
#include "transformbuilder.h"
#include <QDebug>

Light::Light(int x, int y, Bomb *bomb) : x(x), y(y), bomb(bomb) {}

void Light::onAttach()
{
    this->transform = this->gameObject->getComponent<Transform>();
    this->gameScene = this->gameObject->getGameScene();
    Q_ASSERT(this->transform != nullptr);
}

void Light::onUpdate(float deltaTime)
{
    cd -= deltaTime;
    if (cd <= 0)
    {
        this->bomb->GetPlayer()->GetMap()->change(y, x, 0);
        if (this->bomb->GetPlayer()->GetMap()->PropAsk(y, x) == 7)
        {
            auto floor = new GameObject();
            floor->addComponent(new Floor(x, y));
            ImageTransformBuilder()
              .setPos(QPointF(x * 30, y * 30))
              .setImage(":/images/Image/pic_speed.jpg")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(floor);
            gameScene->attachGameObject(floor);
            destory(this->gameObject);
        }
        else if (this->bomb->GetPlayer()->GetMap()->PropAsk(y, x) == 8)
        {
            auto floor = new GameObject();
            floor->addComponent(new Floor(x, y));
            ImageTransformBuilder()
              .setPos(QPointF(x * 30, y * 30))
              .setImage(":/images/Image/pic_range.jpg")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(floor);
            gameScene->attachGameObject(floor);
            destory(this->gameObject);
        }
        else if (this->bomb->GetPlayer()->GetMap()->PropAsk(y, x) == 9)
        {
            auto floor = new GameObject();
            floor->addComponent(new Floor(x, y));
            ImageTransformBuilder()
              .setPos(QPointF(x * 30, y * 30))
              .setImage(":/images/Image/pic_mutibomb.jpg")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(floor);
            gameScene->attachGameObject(floor);
            destory(this->gameObject);
        }
        else if (this->bomb->GetPlayer()->GetMap()->PropAsk(y, x) == 10)
        {
            auto floor = new GameObject();
            floor->addComponent(new Floor(x, y));
            ImageTransformBuilder()
              .setPos(QPointF(x * 30, y * 30))
              .setImage(":/images/Image/pic_move.jpg")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(floor);
            gameScene->attachGameObject(floor);
            destory(this->gameObject);
        }
        else
        {
            auto floor = new GameObject();
            floor->addComponent(new Floor(x, y));
            ImageTransformBuilder()
              .setPos(QPointF(x * 30, y * 30))
              .setImage(":/images/Image/pic_floor.jpg")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(floor);
            gameScene->attachGameObject(floor);
            destory(this->gameObject);
        }
    }
}
