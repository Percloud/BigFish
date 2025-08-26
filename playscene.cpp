#include "playscene.h"
#include <QLabel>
#include <QPainter>
#include "Player.h"
#include "ChooseScene.h"
#include <QPushButton>
#include <QDebug>
#include <QDialog>
#include <QPixmap>
#include <QTimer>
#include <windows.h>
#include <winuser.h>
#include <cmath>
#include <ctime>
#include <QSound>
#include <QMessageBox>
#include <config.h>

PlayScene::PlayScene(bool IsSingle , QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(playscene_Width,playscene_Height);//设置窗口固定大小
    this->setWindowTitle(playscene_Title);//设置标题
    this->setWindowIcon(QPixmap(Icon0));//设置图标
    this->IsSingle = IsSingle;//是否单人
    createfish = true;//是否产生鱼
    srand((unsigned int)time(NULL));//设定随机数种子
    retry = true;//是否重新开始

    QPushButton * btn1 = new QPushButton("重新开始",this);//重新开始按钮
    QPushButton * btn2 = new QPushButton("退出",this);//退出按钮

    btn1->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btn1->setGeometry(this->width()/2 - 200,400,400,65);//重新开始按钮设置

    btn2->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btn2->setGeometry(this->width()/2 - 200,480,400,65);//退出按钮设置

    //实现重新开始
    connect(btn1,&QPushButton::clicked,[=](){
        retry = true;
        if(fir != nullptr || sec != nullptr)
        {
            delete fir;
            delete sec;
            fir = nullptr;
            sec = nullptr;
        }
    });

    //实现退出
    connect(btn2,&QPushButton::clicked,[=](){
        this->close();
    });

    //单人模式
    if(IsSingle)
    {

        QTimer * timer = new QTimer(this);//创建计时器
        timer->start(25);//画面刷新以及函数调用频率
        connect(timer,&QTimer::timeout,[=]()mutable{
            //初始化和重新开始
            if(retry)
            {
                fir = new Player(this);//初始化玩家1
                sec = new Player(this);//初始化玩家2
                //加载玩家1相关图片
                fir->pix.load(player_Pix1);
                fir->pix_.load(player_Pix1_);
                //加载玩家2相关图片
                sec->pix.load(player_Pix2);
                sec->pix_.load(player_Pix2_);

                //按钮隐藏
                btn1->hide();
                btn2->hide();

                for(QVector<Fish *>::iterator it = v_fish.begin();it != v_fish.end();it++)
                {
                    if((*it) != nullptr)
                    {
                        delete (*it);
                        *it = nullptr;
                    }
                    it = v_fish.erase(it) - 1;
                }
                retry = false;
            }

            //游戏进行函数
            if(fir->m_Score <= 78800 && fir->num_life > 0)
            {
                keyPress();//键盘响应
                addfish();//产生鱼
                move_fish();//鱼移动
                collisiondetection();//碰撞检测
                clean();//清除出界的鱼

                fir->turn();//体积变化
                fir->move();//人物移动
            }

            //游戏结束
            else
            {
                //按钮出现
                btn1->show();
                btn2->show();
            }

            //画面刷新
            update();
        });


    }

    //双人模式
    if(!IsSingle)
    {
        QTimer * timer = new QTimer(this);//创建计时器
        timer->start(25);//画面刷新以及函数调用频率
        connect(timer,&QTimer::timeout,[=](){
            //初始化和重新开始
            if(retry)
            {
                fir = new Player(this);//初始化玩家1
                sec = new Player(this);//初始化玩家2
                //改变初始位置
                fir->x -= 100;
                sec->x += 100;

                //加载玩家1相关图片
                fir->pix.load(player_Pix1);
                fir->pix_.load(player_Pix1_);
                //加载玩家2相关图片
                sec->pix.load(player_Pix2);
                sec->pix_.load(player_Pix2_);

                //按钮隐藏
                btn1->hide();
                btn2->hide();

                for(QVector<Fish *>::iterator it = v_fish.begin();it != v_fish.end();it++)
                {
                    if((*it) != nullptr)
                    {
                        delete (*it);
                        *it = nullptr;
                    }
                    it = v_fish.erase(it) - 1;
                }

                retry = false;
            }

            //游戏进行函数
            if((fir->m_Score <= 78800 && sec->m_Score <= 78800) && (fir->num_life > 0 || sec->num_life > 0))
            {
                keyPress();//键盘响应
                addfish();//产生鱼
                move_fish();//鱼移动
                collisiondetection();//碰撞检测
                clean();//清除出界的鱼

                fir->turn();//1P体积变化
                sec->turn();//2P体积变化

                fir->move();//1P人物移动
                sec->move();//2P人物移动
            }

            //游戏结束
            else
            {
                //按钮出现
                btn1->show();
                btn2->show();
            }

            //画面刷新
            update();

        });
    }
}

//重写绘图事件
void PlayScene::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    QPixmap pix;
    //画背景
    pix.load(playscene_Background1);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画鱼
    for(int i = 0;i < v_fish.size();i++)
    {
        if(v_fish[i]->towards == 1){painter.drawPixmap(v_fish[i]->X,v_fish[i]->Y,v_fish[i]->Wid,v_fish[i]->Hei,v_fish[i]->Pix);}
        else{painter.drawPixmap(v_fish[i]->X,v_fish[i]->Y,v_fish[i]->Wid,v_fish[i]->Hei,v_fish[i]->Pix_);}
    }

    //单人模式
    if(IsSingle)
    {
        //画人物
        if(fir->towards && fir->num_life){painter.drawPixmap(fir->x,fir->y,fir->wid,fir->hei,fir->pix);}//1左
        if(!fir->towards && fir->num_life){painter.drawPixmap(fir->x,fir->y,fir->wid,fir->hei,fir->pix_);}//1右

        //写信息
        painter.setFont(QFont("黑体",20));
        painter.drawText(25,50,QString("分数：%1").arg(fir->m_Score));
        painter.drawText(25,100,QString("生命：%1").arg(fir->num_life));

        //结束显示
        if(fir->m_Score > 78800)//获胜
        {
            painter.setFont(QFont("黑体",30));
            painter.drawText(460,200,"你已是海上霸主");
        }
        else if(fir->num_life < 1)//失败
        {
            painter.setFont(QFont("黑体",100));
            painter.drawText(552,250,"菜");
        }
    }

    //双人模式
    if(!IsSingle)
    {
        //画人物
        if(fir->towards && fir->num_life){painter.drawPixmap(fir->x,fir->y,fir->wid,fir->hei,fir->pix);}//1左
        if(!fir->towards && fir->num_life){painter.drawPixmap(fir->x,fir->y,fir->wid,fir->hei,fir->pix_);}//1右
        if(sec->towards && sec->num_life){painter.drawPixmap(sec->x,sec->y,sec->wid,sec->hei,sec->pix);}//2左
        if(!sec->towards && sec->num_life){painter.drawPixmap(sec->x,sec->y,sec->wid,sec->hei,sec->pix_);}//2右

        //写信息
        painter.setFont(QFont("黑体",20));
        painter.drawText(25,50,QString("分数：%1").arg(fir->m_Score));
        painter.drawText(25,100,QString("生命：%1").arg(fir->num_life));
        painter.drawText(1000,50,QString("分数：%1").arg(sec->m_Score));
        painter.drawText(1000,100,QString("生命：%1").arg(sec->num_life));

        //结束显示
        if(fir->m_Score > 78800)//1P获胜
        {
            painter.setFont(QFont("黑体",30));
            painter.drawText(460,200,"P1已是海上霸主");
        }
        else if(sec->m_Score > 78800)//2P获胜
        {
            painter.setFont(QFont("黑体",30));
            painter.drawText(460,200,"P2已是海上霸主");
        }
        else if(fir->num_life < 1 && sec->num_life < 1)//失败
        {
            painter.setFont(QFont("黑体",100));
            painter.drawText(552,250,"菜");
        }
    }
}

//键盘响应
void PlayScene::keyPress()
{
    //单人模式
    if(IsSingle)
    {
        if(GetAsyncKeyState('W')&0x8000){fir->up = true;}//1P 上
        if(GetAsyncKeyState('S')&0x8000){fir->down = true;}//1P 下/
        if(GetAsyncKeyState('A')&0x8000){fir->left = true;fir->towards = true;}//1P 左
        if(GetAsyncKeyState('D')&0x8000){fir->right = true;fir->towards = false;}//1P 右
    }

    //双人模式
    else
    {
        if(GetAsyncKeyState('W')&0x8000){fir->up = true;}//1P 上
        if(GetAsyncKeyState('S')&0x8000){fir->down = true;}//1P 下
        if(GetAsyncKeyState('A')&0x8000){fir->left = true;fir->towards = true;}//1P 左
        if(GetAsyncKeyState('D')&0x8000){fir->right = true;fir->towards = false;}//1P 右

        if(GetAsyncKeyState(VK_UP)&0x8000){sec->up = true;}//2P 上
        if(GetAsyncKeyState(VK_DOWN)&0x8000){sec->down = true;}//2P 下
        if(GetAsyncKeyState(VK_LEFT)&0x8000){sec->left = true;sec->towards = true;}//2P 左
        if(GetAsyncKeyState(VK_RIGHT)&0x8000){sec->right = true;sec->towards = false;}//2P 右
    }

    //esc暂停
    if(GetAsyncKeyState(VK_ESCAPE)&0x8000)
    {
        QMessageBox::about(this,"暂停","是否继续?");
    }
}

//产生鱼
void PlayScene::addfish()
{
    if(v_fish.size() < maxnum_fish && createfish)
    {
        //鱼种类
        int kind = 0;
        //按人物分数产生鱼
        if(fir->wid * fir->hei < 2250){kind = rand()%3;}
        else if(fir->wid * fir->hei < 10212 && fir->wid * fir->hei > 2250){kind = rand()%6;}
        else{kind = rand()%8;}
        //鱼长宽比例
        int percent = rand()%31 + 70;

        //产生不同种鱼
        switch(kind)
        {
        case 0:
        {
            Fish_lv1 * f1 =  new Fish_lv1(percent,this);
            v_fish.push_back(f1);
            break;
        }
        case 1:
        {
            Fish_lv2 * f2 =  new Fish_lv2(percent,this);
            v_fish.push_back(f2);
            break;
        }
        case 2:
        {
            Fish_lv3 * f3 =  new Fish_lv3(percent,this);
            v_fish.push_back(f3);
            break;
        }
        case 3:
        {
            Fish_lv4 * f4 =  new Fish_lv4(percent,this);
            v_fish.push_back(f4);
            break;
        }
        case 4:
        {
            Fish_lv5 * f5 =  new Fish_lv5(percent,this);
            v_fish.push_back(f5);
            break;
        }
        case 5:
        {
            Fish_lv6 * f6 =  new Fish_lv6(percent,this);
            v_fish.push_back(f6);
            break;
        }
        case 6:
        {
            Fish_lv7 * f7 =  new Fish_lv7(percent,this);
            v_fish.push_back(f7);
            break;
        }
        case 7:
        {
            Fish_lv8 * f8 =  new Fish_lv8(percent,this);
            v_fish.push_back(f8);
            break;
        }
        }

        createfish = false;
        QTimer::singleShot(fish_recordor,this,[=](){
            createfish = true;
        });
    }
}

//鱼移动
void PlayScene::move_fish()
{
    for(QVector<Fish *>::iterator it = v_fish.begin();it != v_fish.end();it++)
    {
        (*it)->move();
    }
}

//清除出界的鱼
void PlayScene::clean()
{
    //遍历所有鱼
    for(QVector<Fish *>::iterator it = v_fish.begin();it != v_fish.end();it++)
    {
        //判断出界  删除
        if((*it)->X < 0 - (*it)->Wid || (*it)->X > playscene_Width || (*it)->Y < 0 - (*it)->Hei || (*it)->Y > playscene_Height)
        {
            if(*it != nullptr)
            {
                delete (*it);
                (*it) = nullptr;
            }
            it = v_fish.erase(it) - 1;
        }
    }
}

//碰撞检测
void PlayScene::collisiondetection()
{
    //遍历所有鱼
    for(QVector<Fish *>::iterator it = v_fish.begin();it != v_fish.end();it++)
    {
        //单人模式
        if(IsSingle && fir->num_life)
        {
            if(fir->collision(*it))//碰撞
            {
                if((fir->wid * fir->hei) > ((*it)->Wid * (*it)->Hei))//体积较大
                {
                    QSound::play(player_getscore1);//播放得分音效
                    fir->x -= (sqrt(fir->wid * fir->hei + (*it)->Score/per_turn) - sqrt(fir->wid * fir->hei))/2;//横坐标变化
                    fir->y -= (sqrt(fir->wid * fir->hei + (*it)->Score/per_turn) - sqrt(fir->wid * fir->hei))/2;//纵坐标变化
                    fir->m_Score += (*it)->Score/per_turn;//分数变化
                    //清除鱼
                    if(*it != nullptr)
                    {
                        delete (*it);
                        (*it) = nullptr;
                    }
                    it = v_fish.erase(it) - 1;
                }

                else//体积较小
                {
                    if(!fir->protection)//不处于保护状态
                    {
                        QSound::play(player_loselife);//播放扣血音效
                        fir->num_life--;//扣血
                        fir->protection = true;//开启扣血保护
                        QTimer::singleShot(1000,this,[=](){//保护状态延时关闭
                            fir->protection = false;
                        });
                    }
                }
            }
        }

        //双人模式
        if(!IsSingle)
        {
            if(fir->collision(*it) && fir->num_life)//1P碰撞
            {
                if((fir->wid * fir->hei) > ((*it)->Wid * (*it)->Hei))//体积较大
                {
                    QSound::play(player_getscore1);//播放得分音效
                    fir->x -= (sqrt(fir->wid * fir->hei + (*it)->Score/per_turn) - sqrt(fir->wid * fir->hei))/2;//横坐标变化
                    fir->y -= (sqrt(fir->wid * fir->hei + (*it)->Score/per_turn) - sqrt(fir->wid * fir->hei))/2;//纵坐标变化
                    fir->m_Score += (*it)->Score/per_turn;//分数变化
                    //清除鱼
                    if(*it != nullptr)
                    {
                        delete (*it);
                        (*it) = nullptr;
                    }
                    it = v_fish.erase(it) - 1;
                }
                else//体积较小
                {
                    if(!fir->protection)//不处于保护状态
                    {
                        QSound::play(player_loselife);//播放扣血音效
                        fir->num_life--;//扣血
                        fir->protection = true;//开启扣血保护
                        QTimer::singleShot(1000,this,[=](){//扣血保护延时关闭
                            fir->protection = false;
                        });
                    }
                }
            }

            if(sec->collision(*it) && sec->num_life)//1P碰撞
            {
                if((sec->wid * sec->hei) > ((*it)->Wid * (*it)->Hei))//体积较大
                {
                    QSound::play(player_getscore1);//播放得分音效
                    sec->x -= (sqrt(sec->wid * sec->hei + (*it)->Score/per_turn) - sqrt(sec->wid * sec->hei))/2;//横坐标变化
                    sec->y -= (sqrt(sec->wid * sec->hei + (*it)->Score/per_turn) - sqrt(sec->wid * sec->hei))/2;//纵坐标变化
                    sec->m_Score += (*it)->Score/per_turn;//分数变化
                    //清除鱼
                    if(*it != nullptr)
                    {
                        delete (*it);
                        (*it) = nullptr;
                    }
                    it = v_fish.erase(it) - 1;
                }
                else//体积较小
                {
                    if(!sec->protection)//不处于保护状态
                    {
                        QSound::play(player_loselife);//播放扣血音效
                        sec->num_life--;//扣血
                        sec->protection = true;//开启扣血保护
                        QTimer::singleShot(1000,this,[=](){//扣血保护延时关闭
                            sec->protection = false;
                        });
                    }
                }
            }
        }
    }
}

