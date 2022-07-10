#ifndef INSTRUCTIONWINDOW_H
#define INSTRUCTIONWINDOW_H

#include "gamescene.h"
#include <QWidget>

namespace Ui {
class instructionwindow;
}

class instructionwindow : public QWidget
{
    Q_OBJECT

public:
    explicit instructionwindow(QWidget *parent = nullptr);
    ~instructionwindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::instructionwindow *ui;
    GameScene *gameScene;
};

#endif // INSTRUCTIONWINDOW_H
