#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseScene(QWidget *parent = nullptr);

    PlayScene * playscene;

    //重写绘图事件
    void paintEvent(QPaintEvent *);

signals:
    //返回开始界面
    void backStart();

public slots:

};

#endif // CHOOSESCENE_H
