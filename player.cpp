#include "player.h"
#include "bomb.h"
#include "floor.h"
#include "gamescene.h"
#include "health.h"
#include "hitable.h"
#include "qfontmetrics.h"
#include "qpainter.h"
#include "transformbuilder.h"
#include <transform.h>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include "core.h"
#include <string.h>
#include "numbomb.h"
#include <queue>
#include <vector>

typedef std::pair<int, int> pii;

int cal(int x1, int y1, int x2, int y2)
{
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

Player::Player(int x, int y, int id, Core *map) : Component(), x(x), y(y), id(id), map(map)
{
    speed = 15;
    cd = speed;
    score = 0;
    TotalNumberOfBombs = 1;
    NumberOfBombs = 1;
    lastX = -1;
    lastY = -1;
    lock_status = false;
    aim = std::make_pair(-1, -1);
    de = 0;
    lastdir = 0;
}

//operation
void Player::LayBomb()
{
    if (map->checkX(this->id) >= 0 && this->NumberOfBombs > 0 && this->x != this->lastX && this->y != this->lastY)
    {
        this->GetMap()->change(this->y, this->x, -1);
        this->NumberOfBombs--;
        lastX = this->x;
        lastY = this->y;
        auto bomb = new GameObject();
        bomb->addComponent(new Bomb(this->x, this->y, this));
        ImageTransformBuilder()
          .setPos(QPointF((this->x) * 30, (this->y) * 30))
          .setImage(":/images/Image/pic_boom.jpg")
          .setAlignment(Qt::AlignLeft | Qt::AlignTop)
          .addToGameObject(bomb);
        bomb->setParentGameScene(gameScene);
        this->gameScene->attachGameObject(bomb);
        for (int i = 1; i <= range; i++)
        {
            if (this->GetMap()->ask(this->y, this->x - i) != 0)
                break;
            else
                this->GetMap()->change(this->y, this->x - i, 11);
        }
        for (int i = 1; i <= range; i++)
        {
            if (this->GetMap()->ask(this->y, this->x + i) != 0)
                break;
            else
                this->GetMap()->change(this->y, this->x + i, 11);
        }
        for (int i = 1; i <= range; i++)
        {
            if (this->GetMap()->ask(this->y - i, this->x) != 0)
                break;
            else
                this->GetMap()->change(this->y - i, this->x, 11);
        }
        for (int i = 1; i <= range; i++)
        {
            if (this->GetMap()->ask(this->y + i, this->x) != 0)
                break;
            else
                this->GetMap()->change(this->y + i, this->x, 11);
        }
    }
}

void Player::ChangRoute()
{
    /*while (!route.empty())
        route.pop();*/
    aim = std::make_pair(-1, -1);
    lastdir = 0;
}

//move
void Player::MoveUp()//强制上行
{
    if (map->checkX(this->id) >= 0)
    {
        if (this->id == 1)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_player1_8.jpg");
        else if (this->id == 2)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_player2_8.jpg");
        else if (this->id == 3)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_robot1_8.jpg");
        else
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_robot2_8.jpg");
        if (map->current(this->y - 1, this->x))
        {
            this->transform->moveBy(0, -30);
            this->y--;
            if (lastX != -1 && lastY != -1)
            {
                lastX = -1;
                lastY = -1;
            }
            map->UpdateLocation(this->id, this->x, this->y);
        }
    }
}
void Player::MoveDown()//强制上下行
{
    if (map->checkX(this->id) >= 0)
    {
        if (this->id == 1)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_player1_2.jpg");
        else if (this->id == 2)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_player2_2.jpg");
        else if (this->id == 3)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_robot1_2.jpg");
        else
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_robot2_2.jpg");
        if (map->current(this->y + 1, this->x))
        {
            this->transform->moveBy(0, 30);
            this->y++;
            if (lastX != -1 && lastY != -1)
            {
                lastX = -1;
                lastY = -1;
            }
            map->UpdateLocation(this->id, this->x, this->y);
        }
    }
}
void Player::MoveLeft()//强制左行
{
    if (map->checkX(this->id) >= 0)
    {
        if (this->id == 1)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_player1_4.jpg");
        else if (this->id == 2)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_player2_4.jpg");
        else if (this->id == 3)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_robot1_4.jpg");
        else
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_robot2_4.jpg");
        if (map->current(this->y, this->x - 1))
        {
            this->transform->moveBy(-30, 0);
            this->x--;
            if (lastX != -1 && lastY != -1)
            {
                lastX = -1;
                lastY = -1;
            }
            map->UpdateLocation(this->id, this->x, this->y);
        }
    }
}
void Player::MoveRight()//强制右行
{
    if (map->checkX(this->id) >= 0)
    {
        if (this->id == 1)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_player1_6.jpg");
        else if (this->id == 2)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_player2_6.jpg");
        else if (this->id == 3)
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_robot1_6.jpg");
        else
            this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/pic_robot2_6.jpg");
        if (map->current(this->y, this->x + 1))
        {
            this->transform->moveBy(30, 0);
            this->x++;
            if (lastX != -1 && lastY != -1)
            {
                lastX = -1;
                lastY = -1;
            }
            map->UpdateLocation(this->id, this->x, this->y);
        }
    }
}

void Player::Search(int nowX, int nowY)//以数组位置为准
{
    if (lastdir == 0)
    {
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY - i, nowX))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY - i + 1, nowX);
                    lastdir = 8;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY, nowX - i))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY, nowX - i + 1);
                    lastdir = 4;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY + i, nowX))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY + i - 1, nowX);
                    lastdir = 2;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY, nowX + i))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY, nowX + i - 1);
                    lastdir = 6;
                    return;
                }
                break;
            }
        }
    }
    else if (lastdir == 8)
    {
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY - i, nowX))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY - i + 1, nowX);
                    lastdir = 8;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY, nowX - i))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY, nowX - i + 1);
                    lastdir = 4;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY, nowX + i))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY, nowX + i - 1);
                    lastdir = 6;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY + i, nowX))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY + i - 1, nowX);
                    lastdir = 2;
                    return;
                }
                break;
            }
        }
    }
    else if (lastdir == 2)
    {
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY + i, nowX))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY + i - 1, nowX);
                    lastdir = 2;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY, nowX - i))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY, nowX - i + 1);
                    lastdir = 4;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY, nowX + i))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY, nowX + i - 1);
                    lastdir = 6;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY - i, nowX))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY - i + 1, nowX);
                    lastdir = 8;
                    return;
                }
                break;
            }
        }
    }
    else if (lastdir == 4)
    {
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY, nowX - i))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY, nowX - i + 1);
                    lastdir = 4;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY + i, nowX))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY + i - 1, nowX);
                    lastdir = 2;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY - i, nowX))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY - i + 1, nowX);
                    lastdir = 8;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY, nowX + i))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY, nowX + i - 1);
                    lastdir = 6;
                    return;
                }
                break;
            }
        }
    }
    else if (lastdir == 6)
    {
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY, nowX + i))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY, nowX + i - 1);
                    lastdir = 6;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY + i, nowX))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY + i - 1, nowX);
                    lastdir = 2;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY - i, nowX))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY - i + 1, nowX);
                    lastdir = 8;
                    return;
                }
                break;
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            if (!map->SafePassage(nowY, nowX - i))
            {
                if (i != 1)
                {
                    aim = std::make_pair(nowY, nowX - i + 1);
                    lastdir = 4;
                    return;
                }
                break;
            }
        }
    }
    else
        qDebug() << "NO LASTDIR";
}

void Player::Moveto(int tx, int ty)
{
    if (tx == this->y && ty == this->x)
    {
        this->Search(this->x, this->y);
        return;
    }
    if (ty < this->x && map->SafePassage(this->y, this->x - 1))
    {
        this->MoveLeft();
    }
    else if (ty > this->x && map->SafePassage(this->y, this->x + 1))
    {
        this->MoveRight();
    }
    else if (tx < this->y && map->SafePassage(this->y - 1, this->x))
    {
        this->MoveUp();
    }
    else if (tx > this->y && map->SafePassage(this->y + 1, this->x))
    {
        this->MoveDown();
    }
    else
    {
        this->ChangRoute();
    }
}

int Player::BFS_SearchProp()
{
    if (cal(this->x, this->y, map->checkX(1), map->checkY(1)) <= 1 || cal(this->x, this->y, map->checkX(2), map->checkY(2)) <= 1)
    {
        this->LayBomb();
        return 0;
    }
    std::queue<std::vector<int>> storage;
    while (!storage.empty())
        storage.pop();
    std::vector<std::vector<int>> visit;
    visit.push_back({this->x, this->y, -1});
    if (map->SafePassage(this->y - 1, this->x))
        storage.push({this->y - 1, this->x, 1});
    if (map->SafePassage(this->y + 1, this->x))
        storage.push({this->y + 1, this->x, 2});
    if (map->SafePassage(this->y, this->x - 1))
        storage.push({this->y, this->x - 1, 3});
    if (map->SafePassage(this->y, this->x + 1))
        storage.push({this->y, this->x + 1, 4});
    while(!storage.empty())
    {
        std::vector<int> head = storage.front();
        storage.pop();
        visit.push_back(head);
        if (cal(head[0], head[1], map->checkX(1), map->checkY(1)) <= 1)
        {
            qDebug() << "FIND 1";
            if (head[2] == 1)
                return 1;
            else if (head[2] == 2)
                return 2;
            else if (head[2] == 3)
                return 3;
            else if (head[2] == 4)
                return 4;
            else
                qDebug() << "CAN'T MOVE";
        }
        else if (cal(head[0], head[1], map->checkX(2), map->checkY(2)) <= 1)
        {
            qDebug() << "FIND 2";
            if (head[2] == 1)
                return 1;
            else if (head[2] == 2)
                return 2;
            else if (head[2] == 3)
                return 3;
            else if (head[2] == 4)
                return 4;
            else
                qDebug() << "CAN'T MOVE";
        }
        else if (map->eatable(head[0], head[1]))
        {
            if (head[2] == 1)
                return 1;
            else if (head[2] == 2)
                return 2;
            else if (head[2] == 3)
                return 3;
            else if (head[2] == 4)
                return 4;
            else
                qDebug() << "CAN'T MOVE";
        }
        std::vector<int> dir[5];
        dir[1].push_back(head[0]);
        dir[1].push_back(head[1] - 1);
        dir[1].push_back(head[2]);
        dir[2].push_back(head[0]);
        dir[2].push_back(head[1] + 1);
        dir[2].push_back(head[2]);
        dir[3].push_back(head[0] - 1);
        dir[3].push_back(head[1]);
        dir[3].push_back(head[2]);
        dir[4].push_back(head[0] + 1);
        dir[4].push_back(head[1]);
        dir[4].push_back(head[2]);
        for (int i = 1; i <= 4; i++)
        {
            bool flag = true;
            if (!map->SafePassage(dir[i][0], dir[i][1]))
                continue;
            for (int j = 0; j < visit.size(); j++)
            {
                if (visit[j][0] == dir[i][0] && visit[j][1] == dir[i][1])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                storage.push(dir[i]);
            }
        }
    }
    return 0;
}

void Player::onAttach()
{
    this->transform = this->gameObject->getComponent<Transform>();
    this->transform->setZValue(1);
    this->gameScene = this->gameObject->getGameScene();
    gameObject->addComponent(new Health(1));
}

void Player::onUpdate(float deltaTime)
{
    srand(time(0));
    Counting(deltaTime);
    if (map->ask(y, x) == 6)
    {
        map->UpdateLocation(this->id, -1, -1);
        if (id == 1)
        {
            auto face_player1 = new GameObject();
            face_player1->addComponent(new Floor(20, 0));
            ImageTransformBuilder()
              .setPos(QPointF(600, 0))
              .setImage(":/images/Image/pic_player1_dead.jpg")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(face_player1);
            gameScene->attachGameObject(face_player1);
        }
        else if (id == 2)
        {
            auto face_player2 = new GameObject();
            face_player2->addComponent(new Floor(20, 3));
            ImageTransformBuilder()
              .setPos(QPointF(600, 90))
              .setImage(":/images/Image/pic_player2_dead.jpg")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(face_player2);
            gameScene->attachGameObject(face_player2);
        }
        else if (id == 3)
        {
            auto face_robot1 = new GameObject();
            face_robot1->addComponent(new Floor(20, 6));
            ImageTransformBuilder()
              .setPos(QPointF(600, 180))
              .setImage(":/images/Image/pic_robot1_dead.jpg")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(face_robot1);
            gameScene->attachGameObject(face_robot1);
        }
        else
        {
            auto face_robot2 = new GameObject();
            face_robot2->addComponent(new Floor(20, 9));
            ImageTransformBuilder()
              .setPos(QPointF(600, 270))
              .setImage(":/images/Image/pic_robot2_dead.jpg")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(face_robot2);
            gameScene->attachGameObject(face_robot2);
        }
        this->gameObject->getComponent<ImageTransform>()->setImage(":/images/Image/floor.jpg");
        this->gameScene->Pause();
        int times = 100;
        while (times) {
            times--;
        }
        this->gameScene->Pause();
        //destory(this->gameObject);
    }
    if (map->PropAsk(y, x) == 7)
    {
        score ++;
        EatSpeed();
        map->eat(y, x);
        auto floor = new GameObject();
        floor->addComponent(new Floor(x, y));
        ImageTransformBuilder()
          .setPos(QPointF(x * 30, y * 30))
          .setImage(":/images/Image/pic_floor.jpg")
          .setAlignment(Qt::AlignLeft | Qt::AlignTop)
          .addToGameObject(floor);
        gameScene->attachGameObject(floor);
        if (score == 0)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 1)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 2)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 3)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 4)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 5)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 6)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 7)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 8)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 9)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 10)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        if (speed == 15)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, (id - 1) * 90 + 30))
              .setImage(":/images/Image/pic_1.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else if (speed == 14)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, (id - 1) * 90 + 30))
              .setImage(":/images/Image/pic_2.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else if (speed == 13)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, (id - 1) * 90 + 30))
              .setImage(":/images/Image/pic_3.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else if (speed == 12)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, (id - 1) * 90 + 30))
              .setImage(":/images/Image/pic_4.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, (id - 1) * 90 + 30))
              .setImage(":/images/Image/pic_5.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
    }
    if (map->PropAsk(y, x) == 8)
    {
        score ++;
        EatRange();
        map->eat(y, x);
        auto floor = new GameObject();
        floor->addComponent(new Floor(x, y));
        ImageTransformBuilder()
          .setPos(QPointF(x * 30, y * 30))
          .setImage(":/images/Image/pic_floor.jpg")
          .setAlignment(Qt::AlignLeft | Qt::AlignTop)
          .addToGameObject(floor);
        gameScene->attachGameObject(floor);
        if (score == 0)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 1)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 2)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 3)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 4)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 5)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 6)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 7)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 8)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 9)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 10)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        if (range == 1)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, id * 90 - 30))
              .setImage(":/images/Image/pic_1.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else if (range == 2)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, id * 90 - 30))
              .setImage(":/images/Image/pic_2.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else if (range == 3)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, id * 90 - 30))
              .setImage(":/images/Image/pic_3.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else if (range == 4)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, id * 90 - 30))
              .setImage(":/images/Image/pic_4.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, id * 90 - 30))
              .setImage(":/images/Image/pic_5.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
    }
    if (map->PropAsk(y, x) == 9)
    {
        score ++;
        EatBomb();
        map->eat(y, x);
        auto floor = new GameObject();
        floor->addComponent(new Floor(x, y));
        ImageTransformBuilder()
          .setPos(QPointF(x * 30, y * 30))
          .setImage(":/images/Image/pic_floor.jpg")
          .setAlignment(Qt::AlignLeft | Qt::AlignTop)
          .addToGameObject(floor);
        gameScene->attachGameObject(floor);
        if (score == 0)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 1)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 2)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 3)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 4)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 5)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 6)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 7)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 8)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 9)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 10)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        if (TotalNumberOfBombs == 1)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, (id - 1) * 90))
              .setImage(":/images/Image/pic_1.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else if (TotalNumberOfBombs == 2)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, (id - 1) * 90))
              .setImage(":/images/Image/pic_2.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else if (TotalNumberOfBombs == 3)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, (id - 1) * 90))
              .setImage(":/images/Image/pic_3.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else if (TotalNumberOfBombs == 4)
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, (id - 1) * 90))
              .setImage(":/images/Image/pic_4.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
        else
        {
            auto num = new GameObject();
            num->addComponent(new Num());
            ImageTransformBuilder()
              .setPos(QPointF(720, (id - 1) * 90))
              .setImage(":/images/Image/pic_5.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(num);
            gameScene->attachGameObject(num);
        }
    }
    if (map->PropAsk(y, x) == 10)
    {
        score ++;
        EatMove();
        map->eat(y, x);
        auto floor = new GameObject();
        floor->addComponent(new Floor(x, y));
        ImageTransformBuilder()
          .setPos(QPointF(x * 30, y * 30))
          .setImage(":/images/Image/pic_floor.jpg")
          .setAlignment(Qt::AlignLeft | Qt::AlignTop)
          .addToGameObject(floor);
        gameScene->attachGameObject(floor);
        if (score == 0)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/0.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 1)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/1.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 2)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/2.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 3)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/3.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 4)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/4.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 5)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/5.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 6)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/6.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 7)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/7.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 8)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/8.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 9)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/9.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else if (score == 10)
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/10.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
        else
        {
            auto score = new GameObject();
            score->addComponent(new Num());
            if (id == 1)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 390))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 2)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 390))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else if (id == 3)
            {
                ImageTransformBuilder()
                  .setPos(QPointF(630, 420))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
            else
            {
                ImageTransformBuilder()
                  .setPos(QPointF(705, 420))
                  .setImage(":/images/Image/11.png")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(score);
                gameScene->attachGameObject(score);
            }
        }
    }
    if (getKey(Qt::Key_Space) && id == 1)
    {
        this->LayBomb();
    }
    if ((getKey(Qt::Key_Enter) || getKey(Qt::Key_Return)) && id == 2)
    {
        this->LayBomb();
    }
    if (map->checkX(1) < 0 && map->checkX(2) < 0 && map->checkX(3) < 0 && map->checkX(4) > 0)
    {
        auto win_4 = new GameObject();
        win_4->addComponent(new Floor(20, 9));
        ImageTransformBuilder()
          .setPos(QPointF(240, 180))
          .setImage(":/images/Image/pic_robot2_win.png")
          .setAlignment(Qt::AlignLeft | Qt::AlignTop)
          .addToGameObject(win_4);
        gameScene->attachGameObject(win_4);
        map->UpdateLocation(4, -1, -1);
    }
    if (map->checkX(1) < 0 && map->checkX(2) < 0 && map->checkX(3) > 0 && map->checkX(4) < 0)
    {
        auto win_3 = new GameObject();
        win_3->addComponent(new Floor(20, 9));
        ImageTransformBuilder()
          .setPos(QPointF(240, 180))
          .setImage(":/images/Image/pic_robot1_win.png")
          .setAlignment(Qt::AlignLeft | Qt::AlignTop)
          .addToGameObject(win_3);
        gameScene->attachGameObject(win_3);
        map->UpdateLocation(3, -1, -1);
    }
    if (map->checkX(1) < 0 && map->checkX(2) > 0 && map->checkX(3) < 0 && map->checkX(4) < 0)
    {
        auto win_2 = new GameObject();
        win_2->addComponent(new Floor(20, 9));
        ImageTransformBuilder()
          .setPos(QPointF(240, 180))
          .setImage(":/images/Image/pic_player2_win.png")
          .setAlignment(Qt::AlignLeft | Qt::AlignTop)
          .addToGameObject(win_2);
        gameScene->attachGameObject(win_2);
        map->UpdateLocation(2, -1, -1);
    }
    if (map->checkX(1) > 0 && map->checkX(2) < 0 && map->checkX(3) < 0 && map->checkX(4) < 0)
    {
        auto win_1 = new GameObject();
        win_1->addComponent(new Floor(20, 9));
        ImageTransformBuilder()
          .setPos(QPointF(240, 180))
          .setImage(":/images/Image/pic_player1_win.png")
          .setAlignment(Qt::AlignLeft | Qt::AlignTop)
          .addToGameObject(win_1);
        gameScene->attachGameObject(win_1);
        map->UpdateLocation(1, -1, -1);
    }
    if (cd <= 0)
    {
        if (id == 3)
        {
            if (map->ask(this->y, this->x) == -1)
            {
                this->ChangRoute();
                if (map->current(this->y - 1, this->x) &&
                    map->ask(this->y - 1, this->x) != 6 &&
                   (map->current(this->y - 1, this->x - 1) || map->current(this->y - 1, this->x + 1) || map->current(this->y - 2, this->x)))
                {
                    this->MoveUp();
                    this->unlock();
                }
                else if (map->current(this->y + 1, this->x) &&
                         map->ask(this->y + 1, this->x) != 6 &&
                        (map->current(this->y + 1, this->x - 1) || map->current(this->y + 1, this->x + 1) || map->current(this->y + 2, this->x)))
                {
                    this->MoveDown();
                    this->unlock();
                }
                else if (map->current(this->y, this->x - 1) &&
                         map->ask(this->y, this->x - 1) != 6 &&
                        (map->current(this->y - 1, this->x - 1) || map->current(this->y + 1, this->x - 1) || map->current(this->y, this->x - 2)))
                {
                    this->MoveLeft();
                    this->unlock();
                }
                else if (map->current(this->y, this->x + 1) &&
                         map->ask(this->y, this->x + 1) != 6 &&
                        (map->current(this->y - 1, this->x + 1) || map->current(this->y + 1, this->x + 1) || map->current(this->y, this->x + 2)))
                {
                    this->MoveRight();
                    this->unlock();
                }
                else if (map->current(this->y - 1, this->x) && map->ask(this->y - 1, this->x) != 6)
                {
                    this->MoveUp();
                    this->unlock();
                }
                else if (map->current(this->y + 1, this->x) && map->ask(this->y + 1, this->x) != 6)
                {
                    this->MoveDown();
                    this->unlock();
                }
                else if (map->current(this->y, this->x - 1) && map->ask(this->y, this->x - 1) != 6)
                {
                    this->MoveLeft();
                    this->unlock();
                }
                else if (map->current(this->y, this->x + 1) && map->ask(this->y, this->x + 1) != 6)
                {
                    this->MoveRight();
                    this->unlock();
                }
                else
                {
                    this->lock();
                }
            }
            else if (map->dangerous(this->y, this->x))
            {
                this->ChangRoute();
                if (map->SafePassage(this->y - 1, this->x))
                {
                    this->MoveUp();
                    this->unlock();
                }
                else if (map->SafePassage(this->y + 1, this->x))
                {
                    this->MoveDown();
                    this->unlock();
                }
                else if (map->SafePassage(this->y, this->x - 1))
                {
                    this->MoveLeft();
                    this->unlock();
                }
                else if (map->SafePassage(this->y, this->x + 1))
                {
                    this->MoveRight();
                    this->unlock();
                }
                else if (map->current(this->y - 1, this->x) &&
                    map->ask(this->y - 1, this->x) != 6 &&
                   (map->current(this->y - 1, this->x - 1) || map->current(this->y - 1, this->x + 1) || map->current(this->y - 2, this->x)))
                {
                    this->MoveUp();
                    this->unlock();
                }
                else if (map->current(this->y + 1, this->x) &&
                         map->ask(this->y + 1, this->x) != 6 &&
                        (map->current(this->y + 1, this->x - 1) || map->current(this->y + 1, this->x + 1) || map->current(this->y + 2, this->x)))
                {
                    this->MoveDown();
                    this->unlock();
                }
                else if (map->current(this->y, this->x - 1) &&
                         map->ask(this->y, this->x - 1) != 6 &&
                        (map->current(this->y - 1, this->x - 1) || map->current(this->y + 1, this->x - 1) || map->current(this->y, this->x - 2)))
                {
                    this->MoveLeft();
                    this->unlock();
                }
                else if (map->current(this->y, this->x + 1) &&
                         map->ask(this->y, this->x + 1) != 6 &&
                        (map->current(this->y - 1, this->x + 1) || map->current(this->y + 1, this->x + 1) || map->current(this->y, this->x + 2)))
                {
                    this->MoveRight();
                    this->unlock();
                }
                else if (map->current(this->y - 1, this->x) && map->ask(this->y - 1, this->x) != 6)
                {
                    this->MoveUp();
                    this->unlock();
                }
                else if (map->current(this->y + 1, this->x) && map->ask(this->y + 1, this->x) != 6)
                {
                    this->MoveDown();
                    this->unlock();
                }
                else if (map->current(this->y, this->x - 1) && map->ask(this->y, this->x - 1) != 6)
                {
                    this->MoveLeft();
                    this->unlock();
                }
                else if (map->current(this->y, this->x + 1) && map->ask(this->y, this->x + 1) != 6)
                {
                    this->MoveRight();
                    this->unlock();
                }
                else
                {
                    this->lock();
                }
            }
            else
            {
                int BFS = this->BFS_SearchProp();
                if (BFS == 0)
                {
                    if (cal(this->x, this->y, map->checkX(1), map->checkY(1)) <= 1 || cal(this->x, this->y, map->checkX(2), map->checkY(2)) <= 1)
                    {
                        if (this->NumberOfBombs > 0 && this->x != this->lastX && this->y != this->lastY)
                            this->LayBomb();
                    }
                    if (map->fireable(this->y + 1, this->x)
                            || map->fireable(this->y - 1, this->x)
                            || map->fireable(this->y, this->x - 1)
                            || map->fireable(this->y, this->x + 1))
                    {
                        if (this->NumberOfBombs > 0 && this->x != this->lastX && this->y != this->lastY)
                            this->LayBomb();
                    }
                    if (aim.first < 0)
                    {
                        this->Search(this->x, this->y);
                    }
                    if (aim.first > 0)
                    {
                        this->Moveto(aim.first, aim.second);
                    }
                }
                else if (BFS == 1)
                {
                    this->MoveUp();
                    this->unlock();
                    this->ChangRoute();
                }
                else if (BFS == 2)
                {
                    this->MoveDown();
                    this->unlock();
                    this->ChangRoute();
                }
                else if (BFS == 3)
                {
                    this->MoveLeft();
                    this->unlock();
                    this->ChangRoute();
                }
                else
                {
                    this->MoveRight();
                    this->unlock();
                    this->ChangRoute();
                }
            }
        }
        else if (id == 4)
        {
            if (map->ask(this->y, this->x) == -1)
            {
                this->ChangRoute();
                if (map->current(this->y - 1, this->x) &&
                    map->ask(this->y - 1, this->x) != 6 &&
                   (map->current(this->y - 1, this->x - 1) || map->current(this->y - 1, this->x + 1) || map->current(this->y - 2, this->x)))
                {
                    this->MoveUp();
                    this->unlock();
                }
                else if (map->current(this->y + 1, this->x) &&
                         map->ask(this->y + 1, this->x) != 6 &&
                        (map->current(this->y + 1, this->x - 1) || map->current(this->y + 1, this->x + 1) || map->current(this->y + 2, this->x)))
                {
                    this->MoveDown();
                    this->unlock();
                }
                else if (map->current(this->y, this->x - 1) &&
                         map->ask(this->y, this->x - 1) != 6 &&
                        (map->current(this->y - 1, this->x - 1) || map->current(this->y + 1, this->x - 1) || map->current(this->y, this->x - 2)))
                {
                    this->MoveLeft();
                    this->unlock();
                }
                else if (map->current(this->y, this->x + 1) &&
                         map->ask(this->y, this->x + 1) != 6 &&
                        (map->current(this->y - 1, this->x + 1) || map->current(this->y + 1, this->x + 1) || map->current(this->y, this->x + 2)))
                {
                    this->MoveRight();
                    this->unlock();
                }
                else if (map->current(this->y - 1, this->x) && map->ask(this->y - 1, this->x) != 6)
                {
                    this->MoveUp();
                    this->unlock();
                }
                else if (map->current(this->y + 1, this->x) && map->ask(this->y + 1, this->x) != 6)
                {
                    this->MoveDown();
                    this->unlock();
                }
                else if (map->current(this->y, this->x - 1) && map->ask(this->y, this->x - 1) != 6)
                {
                    this->MoveLeft();
                    this->unlock();
                }
                else if (map->current(this->y, this->x + 1) && map->ask(this->y, this->x + 1) != 6)
                {
                    this->MoveRight();
                    this->unlock();
                }
                else
                {
                    this->lock();
                }
            }
            else if (map->dangerous(this->y, this->x))
            {
                this->ChangRoute();
                if (map->SafePassage(this->y - 1, this->x))
                {
                    this->MoveUp();
                    this->unlock();
                }
                else if (map->SafePassage(this->y + 1, this->x))
                {
                    this->MoveDown();
                    this->unlock();
                }
                else if (map->SafePassage(this->y, this->x - 1))
                {
                    this->MoveLeft();
                    this->unlock();
                }
                else if (map->SafePassage(this->y, this->x + 1))
                {
                    this->MoveRight();
                    this->unlock();
                }
                else if (map->current(this->y - 1, this->x) &&
                    map->ask(this->y - 1, this->x) != 6 &&
                   (map->current(this->y - 1, this->x - 1) || map->current(this->y - 1, this->x + 1) || map->current(this->y - 2, this->x)))
                {
                    this->MoveUp();
                    this->unlock();
                }
                else if (map->current(this->y + 1, this->x) &&
                         map->ask(this->y + 1, this->x) != 6 &&
                        (map->current(this->y + 1, this->x - 1) || map->current(this->y + 1, this->x + 1) || map->current(this->y + 2, this->x)))
                {
                    this->MoveDown();
                    this->unlock();
                }
                else if (map->current(this->y, this->x - 1) &&
                         map->ask(this->y, this->x - 1) != 6 &&
                        (map->current(this->y - 1, this->x - 1) || map->current(this->y + 1, this->x - 1) || map->current(this->y, this->x - 2)))
                {
                    this->MoveLeft();
                    this->unlock();
                }
                else if (map->current(this->y, this->x + 1) &&
                         map->ask(this->y, this->x + 1) != 6 &&
                        (map->current(this->y - 1, this->x + 1) || map->current(this->y + 1, this->x + 1) || map->current(this->y, this->x + 2)))
                {
                    this->MoveRight();
                    this->unlock();
                }
                else if (map->current(this->y - 1, this->x) && map->ask(this->y - 1, this->x) != 6)
                {
                    this->MoveUp();
                    this->unlock();
                }
                else if (map->current(this->y + 1, this->x) && map->ask(this->y + 1, this->x) != 6)
                {
                    this->MoveDown();
                    this->unlock();
                }
                else if (map->current(this->y, this->x - 1) && map->ask(this->y, this->x - 1) != 6)
                {
                    this->MoveLeft();
                    this->unlock();
                }
                else if (map->current(this->y, this->x + 1) && map->ask(this->y, this->x + 1) != 6)
                {
                    this->MoveRight();
                    this->unlock();
                }
                else
                {
                    this->lock();
                }
            }
            else
            {
                int BFS = this->BFS_SearchProp();
                if (BFS == 0)
                {
                    if (cal(this->x, this->y, map->checkX(1), map->checkY(1)) <= 1 || cal(this->x, this->y, map->checkX(2), map->checkY(2)) <= 1)
                    {
                        if (this->NumberOfBombs > 0 && this->x != this->lastX && this->y != this->lastY)
                            this->LayBomb();
                    }
                    if (map->fireable(this->y + 1, this->x)
                            || map->fireable(this->y - 1, this->x)
                            || map->fireable(this->y, this->x - 1)
                            || map->fireable(this->y, this->x + 1))
                    {
                        if (this->NumberOfBombs > 0 && this->x != this->lastX && this->y != this->lastY)
                            this->LayBomb();
                    }
                    if (aim.first < 0)
                    {
                        this->Search(this->x, this->y);
                    }
                    if (aim.first > 0)
                    {
                        this->Moveto(aim.first, aim.second);
                    }
                }
                else if (BFS == 1)
                {
                    this->MoveUp();
                    this->unlock();
                    this->ChangRoute();
                }
                else if (BFS == 2)
                {
                    this->MoveDown();
                    this->unlock();
                    this->ChangRoute();
                }
                else if (BFS == 3)
                {
                    this->MoveLeft();
                    this->unlock();
                    this->ChangRoute();
                }
                else
                {
                    this->MoveRight();
                    this->unlock();
                    this->ChangRoute();
                }
            }
        }
        if (getKey(Qt::Key_A) && id == 1)
        {
            this->MoveLeft();
        }
        if (getKey(Qt::Key_D) && id == 1)
        {
            this->MoveRight();
        }
        if (getKey(Qt::Key_W) && id == 1)
        {
            this->MoveUp();
        }
        if (getKey(Qt::Key_S) && id == 1)
        {
            this->MoveDown();
        }
        if (getKey(Qt::Key_J) && id == 2)
        {
            this->MoveLeft();
        }
        if (getKey(Qt::Key_L) && id == 2)
        {
            this->MoveRight();
        }
        if (getKey(Qt::Key_I) && id == 2)
        {
            this->MoveUp();
        }
        if (getKey(Qt::Key_K) && id == 2)
        {
            this->MoveDown();
        }
        RenewCd();
    }
}
