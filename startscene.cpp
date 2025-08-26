#include "startscene.h"
#include "ui_startscene.h"
#include "choosescene.h"
#include "playscene.h"
#include <QPainter>
#include <QPushButton>
#include <QColor>
#include <QTimer>
#include <QSound>
#include <QMessageBox>
#include <QMediaPlayer>
#include <config.h>

StartScene::StartScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScene)
{
    ui->setupUi(this);

    //播放开始背景音乐  设置单曲循环
    QSound * startSound = new QSound(bg_music1,this);
    startSound->play();
    startSound->setLoops(-1);

    //创建游戏背景音乐
    QSound * playSound = new QSound(bg_music2,this);

    this->setFixedSize(playscene_Width,playscene_Height); //设置窗口固定大小
    this->setWindowTitle(playscene_Title); //设置标题
    this->setWindowIcon(QPixmap(Icon0));   //设置图标

    QString Help = "游 戏 玩 法：\n"
                   "1.控制您的鱼去吃体积更小的鱼使体积更大。\n"
                   "2.到达一定体积，将成为海中霸主。\n"
                   "3.每人五条命，失败一次扣除一条命。\n"
                   "4.生命为零时游戏失败。\n\n"
                   "游 戏 按 键：\n"
                   "W  1P向上  S  1P向下\n"
                   "A  1P向左  A  1P向右\n"
                   "↑   2P向上  ↓   2P向下\n"
                   "←  2P向左  → 2P向右\n"
                   "esc  游戏暂停";

    QPushButton * btn1 = new QPushButton("开始",this); //开始按钮
    QPushButton * btn2 = new QPushButton("帮助",this); //帮助按钮
    QPushButton * btn3 = new QPushButton("退出",this); //退出按钮

    btn1->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btn1->setGeometry(this->width()/2 - 200,400,400,65); //开始按钮设置

    btn2->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btn2->setGeometry(this->width()/2 - 200,480,400,65); //帮助按钮设置

    btn3->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btn3->setGeometry(this->width()/2 - 200,560,400,65); //退出按钮设置

    ChooseScene * choosescene = new ChooseScene;//创建选择场景

    //开始功能实现  进入选择场景
    connect(btn1,&QPushButton::clicked,[=](){
        QTimer::singleShot(50,this,[=](){//延时进入
        this->hide();
        startSound->stop(); //开始背景音乐暂停
        choosescene->show();
        //播放游戏背景音乐  设置单曲循环
        playSound->play();
        playSound->setLoops(-1);
        });
    });

    //帮助对话框实现
    connect(btn2,&QPushButton::clicked,[=](){
        QMessageBox::about(this,"游戏帮助",Help);
    });

    //退出功能实现
    connect(btn3,&QPushButton::clicked,[=](){
        this->close();
    });

    //接收选择界面的返回信号
    connect(choosescene,&ChooseScene::backStart,[=](){
        choosescene->hide();
        this->show();
        //开始背景音乐继续播放
        startSound->play();
        startSound->setLoops(-1);
        //游戏背景音乐暂停
        playSound->stop();
    });

}

//重写绘图事件
void StartScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;

    //画背景
    pix.load(playscene_Background1);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画界面图标与标题
    pix.load(Icon1);
    painter.drawPixmap(290,100,200,200,pix);
    painter.setPen(Qt::black);
    painter.setFont(QFont("SimSun-extB",75));
    painter.drawText(500,245,"BIGFISH");
}

StartScene::~StartScene()
{
    delete ui;
}

