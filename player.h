#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMainWindow>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QGraphicsEllipseItem>
#include <fish.h>


class Player : public QObject
{
    Q_OBJECT
public:
    Player(QMainWindow * game = nullptr);

    int m_Score;//任务分数
    double x;//人物横坐标
    double y;//人物纵坐标
    int wid;//人物宽度
    int hei;//人物高度
    int num_life;//生命数
    int game_wid;//界面宽
    int game_hei;//界面高

    bool up;//是否向上
    bool down;//是否向下
    bool left;//是否向左
    bool right;//是否向右
    bool towards;//朝向(真为向左)
    bool protection;//扣血保护(真为受保护状态)

    QPixmap pix;//人物左向图
    QPixmap pix_;//人物右向图


    //人物移动
    void move();

    //碰撞
    bool collision(Fish *);

    //分数和宽高转化
    void turn();

signals:

public slots:
};

#endif // PLAYER_H
