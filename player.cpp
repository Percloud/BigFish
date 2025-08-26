#include "player.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QMainWindow>
#include <QRect>
#include <QGraphicsEllipseItem>
#include <cmath>
#include <config.h>

Player::Player(QMainWindow * game)
{
    m_Score = 0;//人物分数
    wid = player_Width;//人物宽度
    hei = player_Height;//人物高度
    x = (game->width() - player_Width)/2;//人物横坐标
    y = (game->height() - player_Height)/2;//人物纵坐标
    num_life = 5;//生命数
    game_wid = game->width();//界面宽
    game_hei = game->height();//界面高

    up = false;//是否向上
    down = false;//是否向下
    left = false;//是否向左
    right = false;//是否向右
    towards = true;//朝向(真为向左)
    protection = false;//扣血保护(真为受保护状态)

}

//人物移动
void Player::move()
{
    //边界碰撞
    if(x < 0)x = 0;
    if(x > game_wid - wid)x = game_wid - wid;
    if(y < 0)y = 0;
    if(y > game_hei - hei)y = game_hei - hei;

    //实现移动
    if(up)
    {
        y -= player_Speed;
        up = false;
    }
    if(down)
    {
        y += player_Speed;
        down = false;
    }
    if(left)
    {
        x -= player_Speed;
        left = false;
    }
    if(right)
    {
        x += player_Speed;
        right = false;
    }

}

//碰撞
bool Player::collision(Fish * fish)
{
    //创建椭圆
    QGraphicsEllipseItem ell1(x * 0.83,y * 0.83,wid * 0.71,hei * 0.71);
    QGraphicsEllipseItem ell2(fish->X * 0.83,fish->Y * 0.83,fish->Wid * 0.71,fish->Hei * 0.71);
    //返回碰撞判定结果
    return ell1.collidesWithItem(&ell2,Qt::IntersectsItemShape);
}

//体积变化
void Player::turn()
{
    this->wid = (int)sqrt(this->m_Score + (player_Width * player_Height));
    this->hei = (int)sqrt(this->m_Score + (player_Width * player_Height));
}






