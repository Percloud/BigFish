#ifndef FISH_H
#define FISH_H

#include <QObject>
#include <QMainWindow>
#include <QGraphicsEllipseItem>

class Fish : public QObject
{
    Q_OBJECT
public:
    explicit Fish(int per,QMainWindow * game = nullptr);

    int Score;//分数
    int X;//横坐标
    int Y;//纵坐标
    int Wid;//宽度
    int Hei;//高度
    QPixmap Pix;//左向图
    QPixmap Pix_;//右向图
    int towards;//朝向(真为向左)

    //鱼移动
    void move();

signals:

public slots:
};

//鱼lv1构造函数
class Fish_lv1 : public Fish
{
public:
    Fish_lv1(int per,QMainWindow * game = nullptr);

};

//鱼lv2构造函数
class Fish_lv2 : public Fish
{
public:
    Fish_lv2(int per,QMainWindow * game = nullptr);

};

//鱼lv3构造函数
class Fish_lv3 : public Fish
{
public:
    Fish_lv3(int per,QMainWindow * game = nullptr);

};

//鱼lv4构造函数
class Fish_lv4 : public Fish
{
public:
    Fish_lv4(int per,QMainWindow * game = nullptr);

};

//鱼lv5构造函数
class Fish_lv5 : public Fish
{
public:
    Fish_lv5(int per,QMainWindow * game = nullptr);

};

//鱼lv6构造函数
class Fish_lv6 : public Fish
{
public:
    Fish_lv6(int per,QMainWindow * game = nullptr);

};

//鱼lv7构造函数
class Fish_lv7 : public Fish
{
public:
    Fish_lv7(int per,QMainWindow * game = nullptr);

};

//鱼lv8构造函数
class Fish_lv8 : public Fish
{
public:
    Fish_lv8(int per,QMainWindow * game = nullptr);

};

#endif // FISH_H


