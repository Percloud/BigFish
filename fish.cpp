#include "fish.h"

#include <QTimer>
#include <QDebug>
#include <QPixmap>
#include <ctime>
#include <config.h>

Fish::Fish(int per,QMainWindow * game)
{

}

//鱼lv1构造函数
Fish_lv1::Fish_lv1(int per,QMainWindow * game) : Fish(per,game)
{
    this->Score = 1056 * per * per /10000;
    this->Wid = 44 * per/100;
    this->Hei = 24 * per/100;
    this->towards = rand()%2;
    this->X = (towards == 1) ? game->width() : (0 - Wid);
    this->Y = rand()%(game->height() - Hei + 1);
    this->Pix.load(fish_Lv1_Pix);
    this->Pix_.load(fish_Lv1_Pix_);
}

//鱼lv2构造函数
Fish_lv2::Fish_lv2(int per,QMainWindow * game) : Fish(per,game)
{
    this->Score = 2250 * per * per /10000;
    this->Wid = 50 * per/100;
    this->Hei = 45 * per/100;
    this->towards = rand()%2;
    this->X = (towards == 1) ? game->width() : (0 - Wid);
    this->Y = rand()%(game->height() - Hei + 1);
    this->Pix.load(fish_Lv2_Pix);
    this->Pix_.load(fish_Lv2_Pix_);
}

//鱼lv3构造函数
Fish_lv3::Fish_lv3(int per,QMainWindow * game) : Fish(per,game)
{
    this->Score = 3825 * per * per /10000;
    this->Wid = 85 * per/100;
    this->Hei = 45 * per/100;
    this->towards = rand()%2;
    this->X = (towards == 1) ? game->width() : (0 - Wid);
    this->Y = rand()%(game->height() - Hei + 1);
    this->Pix.load(fish_Lv3_Pix);
    this->Pix_.load(fish_Lv3_Pix_);
}

//鱼lv4构造函数
Fish_lv4::Fish_lv4(int per,QMainWindow * game) : Fish(per,game)
{
    this->Score = 6827 * per * per /10000;
    this->Wid = 123 * per/100;
    this->Hei = 55 * per/100;
    this->towards = rand()%2;
    this->X = (towards == 1) ? game->width() : (0 - Wid);
    this->Y = rand()%(game->height() - Hei + 1);
    this->Pix.load(fish_Lv4_Pix);
    this->Pix_.load(fish_Lv4_Pix_);
}

//鱼lv5构造函数
Fish_lv5::Fish_lv5(int per,QMainWindow * game) : Fish(per,game)
{
    this->Score = 10212 * per * per /10000;
    this->Wid = 138 * per/100;
    this->Hei = 74 * per/100;
    this->towards = rand()%2;
    this->X = (towards == 1) ? game->width() : (0 - Wid);
    this->Y = rand()%(game->height() - Hei + 1);
    this->Pix.load(fish_Lv5_Pix);
    this->Pix_.load(fish_Lv5_Pix_);
}

//鱼lv6构造函数
Fish_lv6::Fish_lv6(int per,QMainWindow * game) : Fish(per,game)
{
    this->Score = 19890 * per * per /10000;
    this->Wid = 170 * per/100;
    this->Hei = 117 * per/100;
    this->towards = rand()%2;
    this->X = (towards == 1) ? game->width() : (0 - Wid);
    this->Y = rand()%(game->height() - Hei + 1);
    this->Pix.load(fish_Lv6_Pix);
    this->Pix_.load(fish_Lv6_Pix_);
}

//鱼lv7构造函数
Fish_lv7::Fish_lv7(int per,QMainWindow * game) : Fish(per,game)
{
    this->Score = 39762 * per * per /10000;
    this->Wid = 282 * per/100;
    this->Hei = 141 * per/100;
    this->towards = rand()%2;
    this->X = (towards == 1) ? game->width() : (0 - Wid);
    this->Y = rand()%(game->height() - Hei + 1);
    this->Pix.load(fish_Lv7_Pix);
    this->Pix_.load(fish_Lv7_Pix_);
}

//鱼lv8构造函数
Fish_lv8::Fish_lv8(int per,QMainWindow * game) : Fish(per,game)
{
    this->Score = 69056 * per * per /10000;
    this->Wid = 336 * per/100;
    this->Hei = 208 * per/100;
    this->towards = rand()%2;
    this->X = (towards == 1) ? game->width() : (0 - Wid);
    this->Y = rand()%(game->height() - Hei + 1);
    this->Pix.load(fish_Lv8_Pix);
    this->Pix_.load(fish_Lv8_Pix_);
}

//移动
void Fish::move()
{
    if(towards)
    {
        this->X -= fish_Speed;
    }

    else if(!towards)
    {
        this->X += fish_Speed;
    }
}

