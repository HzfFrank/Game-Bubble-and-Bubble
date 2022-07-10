#include "gamewindow.h"
#include "numbomb.h"
#include "ui_gamewindow.h"
#include <iostream>
using namespace std;

#include <gameobject.h>
#include <imagetransform.h>
#include <transformbuilder.h>

#include "floor.h"
#include "gamescene.h"
#include "player.h"
#include "wall.h"
#include "core.h"
#include "pausebutton.h"

void loadScene(GameScene *gameScene) {
    auto map = new Core;

    //炸弹数量
    auto player1_bomb_num = new GameObject();
    player1_bomb_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 0))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player1_bomb_num);
    gameScene->attachGameObject(player1_bomb_num);
    auto player2_bomb_num = new GameObject();
    player2_bomb_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 90))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player2_bomb_num);
    gameScene->attachGameObject(player2_bomb_num);
    auto robot1_bomb_num = new GameObject();
    robot1_bomb_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 180))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot1_bomb_num);
    gameScene->attachGameObject(robot1_bomb_num);
    auto robot2_bomb_num = new GameObject();
    robot2_bomb_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 270))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot2_bomb_num);
    gameScene->attachGameObject(robot2_bomb_num);

    //速度
    auto player1_speed_num = new GameObject();
    player1_speed_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 30))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player1_speed_num);
    gameScene->attachGameObject(player1_speed_num);
    auto player2_speed_num = new GameObject();
    player2_speed_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 120))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player2_speed_num);
    gameScene->attachGameObject(player2_speed_num);
    auto robot1_speed_num = new GameObject();
    robot1_speed_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 210))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot1_speed_num);
    gameScene->attachGameObject(robot1_speed_num);
    auto robot2_speed_num = new GameObject();
    robot2_speed_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 300))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot2_speed_num);
    gameScene->attachGameObject(robot2_speed_num);

    //范围
    auto player1_range_num = new GameObject();
    player1_range_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 60))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player1_range_num);
    gameScene->attachGameObject(player1_range_num);
    auto player2_range_num = new GameObject();
    player2_range_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 150))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player2_range_num);
    gameScene->attachGameObject(player2_range_num);
    auto robot1_range_num = new GameObject();
    robot1_range_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 240))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot1_range_num);
    gameScene->attachGameObject(robot1_range_num);
    auto robot2_range_num = new GameObject();
    robot2_range_num->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(720, 330))
      .setImage(":/images/Image/pic_1.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot2_range_num);
    gameScene->attachGameObject(robot2_range_num);

    //分数
    auto player1_score = new GameObject();
    player1_score->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(630, 390))
      .setImage(":/images/Image/0.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player1_score);
    gameScene->attachGameObject(player1_score);
    auto player2_score = new GameObject();
    player2_score->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(705, 390))
      .setImage(":/images/Image/0.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player2_score);
    gameScene->attachGameObject(player2_score);
    auto robot1_score = new GameObject();
    robot1_score->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(630, 420))
      .setImage(":/images/Image/0.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot1_score);
    gameScene->attachGameObject(robot1_score);
    auto robot2_score = new GameObject();
    robot2_score->addComponent(new Num());
    ImageTransformBuilder()
      .setPos(QPointF(705, 420))
      .setImage(":/images/Image/0.png")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot2_score);
    gameScene->attachGameObject(robot2_score);

    //小头像
    auto face1 = new GameObject();
    face1->addComponent(new Floor(20, 0));
    ImageTransformBuilder()
      .setPos(QPointF(600, 390))
      .setImage(":/images/Image/p1.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(face1);
    gameScene->attachGameObject(face1);
    auto face2 = new GameObject();
    face2->addComponent(new Floor(20, 3));
    ImageTransformBuilder()
      .setPos(QPointF(675, 390))
      .setImage(":/images/Image/p2.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(face2);
    gameScene->attachGameObject(face2);
    auto face3 = new GameObject();
    face3->addComponent(new Floor(20, 6));
    ImageTransformBuilder()
      .setPos(QPointF(600, 420))
      .setImage(":/images/Image/p3.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(face3);
    gameScene->attachGameObject(face3);
    auto face4 = new GameObject();
    face4->addComponent(new Floor(20, 9));
    ImageTransformBuilder()
      .setPos(QPointF(675, 420))
      .setImage(":/images/Image/p4.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(face4);
    gameScene->attachGameObject(face4);


    //暂停按钮
    auto pausebutton = new GameObject();
    pausebutton->addComponent(new PauseButton());
    ImageTransformBuilder()
      .setPos(QPointF(600, 360))
      .setImage(":/images/Image/pic_pause.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(pausebutton);
    gameScene->attachGameObject(pausebutton);

    //人物头像
    auto face_player1 = new GameObject();
    face_player1->addComponent(new Floor(20, 0));
    ImageTransformBuilder()
      .setPos(QPointF(600, 0))
      .setImage(":/images/Image/pic_player1.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(face_player1);
    gameScene->attachGameObject(face_player1);
    auto face_player2 = new GameObject();
    face_player2->addComponent(new Floor(20, 3));
    ImageTransformBuilder()
      .setPos(QPointF(600, 90))
      .setImage(":/images/Image/pic_player2.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(face_player2);
    gameScene->attachGameObject(face_player2);
    auto face_robot1 = new GameObject();
    face_robot1->addComponent(new Floor(20, 6));
    ImageTransformBuilder()
      .setPos(QPointF(600, 180))
      .setImage(":/images/Image/pic_robot1.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(face_robot1);
    gameScene->attachGameObject(face_robot1);
    auto face_robot2 = new GameObject();
    face_robot2->addComponent(new Floor(20, 9));
    ImageTransformBuilder()
      .setPos(QPointF(600, 270))
      .setImage(":/images/Image/pic_robot2.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(face_robot2);
    gameScene->attachGameObject(face_robot2);

    //炸弹数量图标
    auto player1_bomb = new GameObject();
    player1_bomb->addComponent(new Floor(22, 0));
    ImageTransformBuilder()
      .setPos(QPointF(690, 0))
      .setImage(":/images/Image/pic_num_bomb.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player1_bomb);
    gameScene->attachGameObject(player1_bomb);
    auto player2_bomb = new GameObject();
    player2_bomb->addComponent(new Floor(22, 3));
    ImageTransformBuilder()
      .setPos(QPointF(690, 90))
      .setImage(":/images/Image/pic_num_bomb.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player2_bomb);
    gameScene->attachGameObject(player2_bomb);
    auto robot1_bomb = new GameObject();
    robot1_bomb->addComponent(new Floor(22, 7));
    ImageTransformBuilder()
      .setPos(QPointF(690, 180))
      .setImage(":/images/Image/pic_num_bomb.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot1_bomb);
    gameScene->attachGameObject(robot1_bomb);
    auto robot2_bomb = new GameObject();
    robot2_bomb->addComponent(new Floor(22, 10));
    ImageTransformBuilder()
      .setPos(QPointF(690, 270))
      .setImage(":/images/Image/pic_num_bomb.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot2_bomb);
    gameScene->attachGameObject(robot2_bomb);

    //速度图标
    auto player1_speed = new GameObject();
    player1_speed->addComponent(new Floor(22, 2));
    ImageTransformBuilder()
      .setPos(QPointF(690, 30))
      .setImage(":/images/Image/pic_num_speed.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player1_speed);
    gameScene->attachGameObject(player1_speed);
    auto player2_speed = new GameObject();
    player2_speed->addComponent(new Floor(22, 5));
    ImageTransformBuilder()
      .setPos(QPointF(690, 120))
      .setImage(":/images/Image/pic_num_speed.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player2_speed);
    gameScene->attachGameObject(player2_speed);
    auto robot1_speed = new GameObject();
    robot1_speed->addComponent(new Floor(22, 8));
    ImageTransformBuilder()
      .setPos(QPointF(690, 210))
      .setImage(":/images/Image/pic_num_speed.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot1_speed);
    gameScene->attachGameObject(robot1_speed);
    auto robot2_speed = new GameObject();
    robot2_speed->addComponent(new Floor(22, 11));
    ImageTransformBuilder()
      .setPos(QPointF(690, 300))
      .setImage(":/images/Image/pic_num_speed.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot2_speed);
    gameScene->attachGameObject(robot2_speed);

    //炸弹范围图标
    auto player1_range = new GameObject();
    player1_range->addComponent(new Floor(22, 0));
    ImageTransformBuilder()
      .setPos(QPointF(690, 60))
      .setImage(":/images/Image/pic_num_range.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player1_range);
    gameScene->attachGameObject(player1_range);
    auto player2_range = new GameObject();
    player2_range->addComponent(new Floor(22, 3));
    ImageTransformBuilder()
      .setPos(QPointF(690, 150))
      .setImage(":/images/Image/pic_num_range.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player2_range);
    gameScene->attachGameObject(player2_range);
    auto robot1_range = new GameObject();
    robot1_range->addComponent(new Floor(22, 6));
    ImageTransformBuilder()
      .setPos(QPointF(690, 240))
      .setImage(":/images/Image/pic_num_range.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot1_range);
    gameScene->attachGameObject(robot1_range);
    auto robot2_range = new GameObject();
    robot2_range->addComponent(new Floor(22, 9));
    ImageTransformBuilder()
      .setPos(QPointF(690, 330))
      .setImage(":/images/Image/pic_num_range.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(robot2_range);
    gameScene->attachGameObject(robot2_range);

    //人物图标
    auto player1 = new GameObject();
    player1->addComponent(new Player(1, 1, 1, map));
    ImageTransformBuilder()
      .setPos(QPointF(1 * 30, 1 * 30))
      .setImage(":/images/Image/pic_player1_2.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(player1);
    player1->setParentGameScene(gameScene);
    gameScene->attachGameObject(player1);
    auto player2 = new GameObject();
    player2->addComponent(new Player(18, 13, 2, map));
    ImageTransformBuilder()
        .setPos(QPointF(18 * 30, 13 * 30))
        .setImage(":/images/Image/pic_player2_2.jpg")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(player2);
    player2->setParentGameScene(gameScene);
    gameScene->attachGameObject(player2);
    auto robot1 = new GameObject();
    robot1->addComponent(new Player(18, 1, 3, map));
    ImageTransformBuilder()
        .setPos(QPointF(18 * 30, 1 * 30))
        .setImage(":/images/Image/pic_robot1_2.jpg")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(robot1);
    robot1->setParentGameScene(gameScene);
    gameScene->attachGameObject(robot1);
    auto robot2 = new GameObject();
    robot2->addComponent(new Player(1, 13, 4, map));
    ImageTransformBuilder()
        .setPos(QPointF(1 * 30, 13 * 30))
        .setImage(":/images/Image/pic_robot2_2.jpg")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(robot2);
    robot2->setParentGameScene(gameScene);
    gameScene->attachGameObject(robot2);

    //地图
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 20; j++)
        {
            if (map->ask(i, j) == 0)
            {
                auto floor = new GameObject();
                floor->addComponent(new Floor(j, i));
                ImageTransformBuilder()
                  .setPos(QPointF(j * 30, i * 30))
                  .setImage(":/images/Image/pic_floor.jpg")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(floor);
                gameScene->attachGameObject(floor);
            }
            if (map->ask(i, j) == 1)
            {
                auto hardwall = new GameObject();
                hardwall->addComponent(new Wall(j, i));
                ImageTransformBuilder()
                  .setPos(QPointF(j * 30, i * 30))
                  .setImage(":/images/Image/pic_hardwall.jpg")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(hardwall);
                gameScene->attachGameObject(hardwall);
            }
            if (map->ask(i, j) == 2)
            {
                auto hardwall = new GameObject();
                hardwall->addComponent(new Wall(j, i));
                ImageTransformBuilder()
                  .setPos(QPointF(j * 30, i * 30))
                  .setImage(":/images/Image/pic_hardwall_chair.jpg")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(hardwall);
                gameScene->attachGameObject(hardwall);
            }
            if (map->ask(i, j) == 3)
            {
                auto softwall = new GameObject();
                softwall->addComponent(new Wall(j, i));
                ImageTransformBuilder()
                  .setPos(QPointF(j * 30, i * 30))
                  .setImage(":/images/Image/pic_softwall_popcorn.jpg")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(softwall);
                gameScene->attachGameObject(softwall);
            }
            if (map->ask(i, j) == 4)
            {
                auto softwall = new GameObject();
                softwall->addComponent(new Wall(j, i));
                ImageTransformBuilder()
                  .setPos(QPointF(j * 30, i * 30))
                  .setImage(":/images/Image/pic_softwall_glass.jpg")
                  .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                  .addToGameObject(softwall);
                gameScene->attachGameObject(softwall);
            }
        }
    auto midwall = new GameObject();
    midwall->addComponent(new Wall(8, 6));
    ImageTransformBuilder()
      .setPos(QPointF(8 * 30, 6 * 30))
      .setImage(":/images/Image/PIC.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(midwall);
    gameScene->attachGameObject(midwall);
}

gamewindow::gamewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    gameScene = new GameScene();
    gameScene->setParent(this);
    auto view = new QGraphicsView(gameScene, this);
    view->setFrameStyle(QFrame::NoFrame);
    view->resize(this->size());
    view->setSceneRect(QRect(0, 0, this->width(), this->height()));
    loadScene(gameScene);
}

gamewindow::~gamewindow()
{
    delete ui;
}

