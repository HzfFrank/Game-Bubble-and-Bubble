#include "instructionwindow.h"
#include "gamescene.h"
#include "qgraphicsview.h"
#include "ui_instructionwindow.h"

#include <gameobject.h>
#include <imagetransform.h>
#include <transformbuilder.h>
#include "floor.h"

void loadInstruction(GameScene *gameScene) {
    auto floor = new GameObject();
    floor->addComponent(new Floor(0, 0));
    ImageTransformBuilder()
      .setPos(QPointF(0, 0))
      .setImage(":/images/Image/pic_reference.jpg")
      .setAlignment(Qt::AlignLeft | Qt::AlignTop)
      .addToGameObject(floor);
    gameScene->attachGameObject(floor);
}

instructionwindow::instructionwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::instructionwindow)
{
    ui->setupUi(this);
    gameScene = new GameScene();
    gameScene->setParent(this);
    auto view = new QGraphicsView(gameScene, this);
    view->setFrameStyle(QFrame::NoFrame);
    view->resize(this->size());
    view->setSceneRect(QRect(0, 0, this->width(), this->height()));

    loadInstruction(gameScene);
}

instructionwindow::~instructionwindow()
{
    delete ui;
}

void instructionwindow::on_pushButton_clicked()
{
    exit(0);
}

