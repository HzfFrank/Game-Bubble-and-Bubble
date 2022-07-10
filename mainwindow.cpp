#include "bomb.h"
#include "qurl.h"
#include <iostream>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>
using namespace std;
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <gameobject.h>
#include <imagetransform.h>
#include <transformbuilder.h>

#include "floor.h"
#include "gamescene.h"
#include "player.h"
#include "wall.h"
#include "core.h"
#include "gamewindow.h"
#include "instructionwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /*auto player = new QMediaPlayer;
    player->setSource(QUrl::fromLocalFile(":/images/Image/gamemusic.mp3"));
    player->play();*/
    /*auto player = new QMediaPlayer;
    auto audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setSource(QUrl::fromLocalFile(":/images/Image/gamemusic.mp3"));
    audioOutput->setVolume(50);
    player->play();*/

    auto player = new QSoundEffect();
    player->setSource(QUrl::fromLocalFile(":/images/Image/music.wav"));
    player->setLoopCount(QSoundEffect::Infinite);
    player->setVolume(0.25f);
    player->play();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    gamewindow *configWindow = new gamewindow;
    configWindow->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    exit(0);
}


void MainWindow::on_pushButton_3_clicked()
{
    instructionwindow *configWindow = new instructionwindow;
    configWindow->show();
}

