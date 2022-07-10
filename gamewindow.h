#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <gamescene.h>

#include <QGraphicsView>
#include <QWidget>

namespace Ui {
class gamewindow;
}

class gamewindow : public QWidget
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = nullptr);
    ~gamewindow();

private:
    Ui::gamewindow *ui;
    GameScene *gameScene;
};

#endif // GAMEWINDOW_H
