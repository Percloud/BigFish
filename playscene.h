#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <player.h>
#include <fish.h>
#include <QVector>
#include <QSound>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(bool IsSingle , QWidget *parent = nullptr);

    Player * fir;//人物1P
    Player * sec;//人物2P
    QVector<Fish *> v_fish;//鱼容器

    bool IsSingle;//是否单人
    bool createfish;//是否产生鱼
    bool retry;//是否重新开始

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //按键响应
    void keyPress();

    //碰撞检测
    void collisiondetection();

    //产生鱼
    void addfish();

    //清除出界的鱼
    void clean();

    //鱼移动
    void move_fish();

signals:

public slots:
};

#endif // PLAYSCENE_H
