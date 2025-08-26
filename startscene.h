#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>
#include <playscene.h>

namespace Ui {
class StartScene;
}

class StartScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartScene(QWidget *parent = nullptr);
    ~StartScene();

    //重写绘图事件
    void paintEvent(QPaintEvent *);

private:
    Ui::StartScene *ui;
};

#endif // STARTSCENE_H
