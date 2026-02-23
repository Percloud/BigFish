#include "startscene.h"
#include "scenemanager.h"
#include "audiomanager.h"
#include <QPainter>
#include <QPushButton>
#include <QMessageBox>
#include <QFont>
#include <QApplication>
#include <config.h>

StartScene::StartScene(SceneManager* manager, QWidget* parent)
    : BaseScene(manager, parent)
{
    this->setFixedSize(playscene_Width, playscene_Height);

    setupConnections();
}

StartScene::~StartScene()
{
}

void StartScene::onEnter()
{
    // 场景进入时播放开始音乐
    AudioManager::instance()->playBgMusic(AudioManager::START_MUSIC);
}

void StartScene::onExit()
{
    // 场景退出时停止开始音乐（AudioManager 会自动切换到游戏音乐）
    AudioManager::instance()->stopBgMusic();
}

void StartScene::setupConnections()
{
    QString helpText = "游 戏 玩 法：\n"
                       "1.控制您的鱼去吃体积更小的鱼使体积更大。\n"
                       "2.到达一定体积，将成为海中霸主。\n"
                       "3.每人五条命，失败一次扣除一条命。\n"
                       "4.生命为零时游戏失败。\n\n"
                       "游 戏 按 键：\n"
                       "W  1P向上  S  1P向下\n"
                       "A  1P向左  D  1P向右\n"
                       "↑   2P向上  ↓   2P向下\n"
                       "←  2P向左  → 2P向右\n"
                       "esc  游戏暂停";

    QPushButton* btnStart = new QPushButton("开始", this);
    QPushButton* btnHelp = new QPushButton("帮助", this);
    QPushButton* btnExit = new QPushButton("退出", this);

    btnStart->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btnStart->setGeometry(this->width() / 2 - 200, 400, 400, 65);

    btnHelp->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btnHelp->setGeometry(this->width() / 2 - 200, 480, 400, 65);

    btnExit->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btnExit->setGeometry(this->width() / 2 - 200, 560, 400, 65);

    // 开始按钮 - 进入选择场景
    connect(btnStart, &QPushButton::clicked, this, [this]() {
        m_sceneManager->switchToChooseScene();
    });

    // 帮助按钮
    connect(btnHelp, &QPushButton::clicked, this, [this, helpText]() {
        QMessageBox::about(this, "游戏帮助", helpText);
    });

    // 退出按钮
    connect(btnExit, &QPushButton::clicked, this, []() {
        qApp->quit();
    });
}

void StartScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;

    // 画背景
    pix.load(playscene_Background1);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    // 画界面图标与标题
    pix.load(Icon1);
    painter.drawPixmap(290, 100, 200, 200, pix);
    painter.setPen(Qt::black);
    painter.setFont(QFont("SimSun-extB", 75));
    painter.drawText(500, 245, "BIGFISH");
}
