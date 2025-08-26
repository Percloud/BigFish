#include "choosescene.h"
#include <QPainter>
#include <QPushButton>
#include "playscene.h"
#include <QTimer>
#include <QSound>
#include <config.h>
#include <QDebug>

ChooseScene::ChooseScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(playscene_Width,playscene_Height);//设置窗口固定大小
    this->setWindowTitle(playscene_Title);//设置标题
    this->setWindowIcon(QPixmap(Icon0));//设置图标

    QPushButton * btn1 = new QPushButton("1P",this);//单人按钮
    QPushButton * btn2 = new QPushButton("2P",this);//双人按钮
    QPushButton * btn3 = new QPushButton("返回",this);//返回按钮

    btn1->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btn1->setGeometry(this->width()/2 - 400,this->height()/2 - 75,300,150);//单人按钮设置

    btn2->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btn2->setGeometry(this->width()/2 + 100,this->height()/2 - 75,300,150);//双人按钮设置

    btn3->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btn3->setGeometry(this->width() - 250,this->height() - 115,200,65);//返回按钮设置

    //单人按钮实现进入单人界面
    connect(btn1,&QPushButton::clicked,[=](){
        playscene = new PlayScene(1,this);
        QTimer::singleShot(150,this,[=](){//延时进入
        this->hide();
        playscene->show();

        });
    });

    //双人按钮实现进入双人界面
    connect(btn2,&QPushButton::clicked,[=](){
        playscene = new PlayScene(0,this);
        QTimer::singleShot(150,this,[=](){//延时进入
        this->hide();
        playscene->show();
        });
    });

    //返回按钮实现返回
    connect(btn3,&QPushButton::clicked,[=](){
        QTimer::singleShot(150,this,[=](){//延时返回
        emit backStart();
        });
    });
}

//重写绘图事件
void ChooseScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //画背景
    pix.load(":/new/pixmap/background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
