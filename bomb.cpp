#include "bomb.h"
#include "gamescene.h"
#include "hitable.h"
#include "light.h"
#include "transformbuilder.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QDebug>

Bomb::Bomb(int x, int y, Player *player) : Component(), x(x), y(y), player(player){}

void Bomb::onAttach()
{
    this->transform = this->gameObject->getComponent<Transform>();
    this->gameScene = this->gameObject->getGameScene();
    Q_ASSERT(this->transform != nullptr);
}

void Bomb::onUpdate(float deltaTime)
{
    if (exist)
    {
        cd -= deltaTime;
        if (cd <= 0)
        {
            this->player->GetMap()->change(this->y, this->x, 6);
            auto MidLight = new GameObject();
            MidLight->addComponent(new Light(this->x, this->y, this));
            ImageTransformBuilder()
              .setPos(QPointF((this->x) * 30, (this->y) * 30))
              .setImage(":/images/Image/pic_midlight.jpg")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(MidLight);
            MidLight->setParentGameScene(gameScene);
            gameScene->attachGameObject(MidLight);
            for (int i = 1; i <= this->player->GetRange(); i++)
            {
                if (!this->player->GetMap()->breakable(this->y, this->x - i))
                    break;
                bool flag = false;
                if (this->player->GetMap()->ask(this->y, this->x - i) == 0|| this->player->GetMap()->ask(this->y, this->x - i) == 11)
                    flag = true;
                this->player->GetMap()->change(this->y, this->x - i, 6);
                auto RowLight = new GameObject();
                RowLight->addComponent(new Light(this->x - i, this->y, this));
                ImageTransformBuilder()
                  .setPos(QPointF((this->x - i) * 30, (this->y) * 30))
                  .setImage(":/images/Image/pic_rowlight.jpg")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(RowLight);
                RowLight->setParentGameScene(gameScene);
                gameScene->attachGameObject(RowLight);
                if (!flag)
                    break;
            }
            for (int i = 1; i <= this->player->GetRange(); i++)
            {
                if (!this->player->GetMap()->breakable(this->y, this->x + i))
                    break;
                bool flag = false;
                if (this->player->GetMap()->ask(this->y, this->x + i) == 0 || this->player->GetMap()->ask(this->y, this->x + i) == 11)
                    flag = true;
                this->player->GetMap()->change(this->y, this->x + i, 6);
                auto RowLight = new GameObject();
                RowLight->addComponent(new Light(this->x + i, this->y, this));
                ImageTransformBuilder()
                  .setPos(QPointF((this->x + i) * 30, (this->y) * 30))
                  .setImage(":/images/Image/pic_rowlight.jpg")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(RowLight);
                RowLight->setParentGameScene(gameScene);
                gameScene->attachGameObject(RowLight);
                if (!flag)
                    break;
            }
            for (int i = 1; i <= this->player->GetRange(); i++)
            {
                if (!this->player->GetMap()->breakable(this->y - i, this->x))
                    break;
                bool flag = false;
                if (this->player->GetMap()->ask(this->y - i, this->x) == 0 || this->player->GetMap()->ask(this->y - i, this->x) == 11)
                    flag = true;
                this->player->GetMap()->change(this->y - i, this->x, 6);
                auto ColLight = new GameObject();
                ColLight->addComponent(new Light(this->x, this->y - i, this));
                ImageTransformBuilder()
                  .setPos(QPointF((this->x) * 30, (this->y - i) * 30))
                  .setImage(":/images/Image/pic_collight.jpg")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(ColLight);
                ColLight->setParentGameScene(gameScene);
                gameScene->attachGameObject(ColLight);
                if (!flag)
                    break;
            }
            for (int i = 1; i <= this->player->GetRange(); i++)
            {
                if (!this->player->GetMap()->breakable(this->y + i, this->x))
                    break;
                bool flag = false;
                if (this->player->GetMap()->ask(this->y + i, this->x) == 0 || this->player->GetMap()->ask(this->y + i, this->x) ==11)
                    flag = true;
                this->player->GetMap()->change(this->y + i, this->x, 6);
                auto ColLight = new GameObject();
                ColLight->addComponent(new Light(this->x, this->y + i, this));
                ImageTransformBuilder()
                  .setPos(QPointF((this->x) * 30, (this->y + i) * 30))
                  .setImage(":/images/Image/pic_collight.jpg")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(ColLight);
                ColLight->setParentGameScene(gameScene);
                gameScene->attachGameObject(ColLight);
                if (!flag)
                    break;
            }
            this->player->RenewNumberOfBombs();
            this->explode();
        }
    }
}
