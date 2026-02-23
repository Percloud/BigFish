#include "choosescene.h"
#include "basescene.h"
#include "scenemanager.h"
#include "audiomanager.h"
#include <QPainter>
#include <QPushButton>
#include <config.h>

ChooseScene::ChooseScene(SceneManager* manager, QWidget* parent)
    : BaseScene(manager, parent)
{
    this->setFixedSize(playscene_Width, playscene_Height);
    setupConnections();
}

ChooseScene::~ChooseScene()
{
}

void ChooseScene::onEnter()
{
    // 场景进入时播放游戏背景音乐
    AudioManager::instance()->playBgMusic(AudioManager::GAME_MUSIC);
}

void ChooseScene::onExit()
{
    // 场景退出时停止游戏音乐（会自动切换到开始音乐或游戏内音乐）
    AudioManager::instance()->stopBgMusic();
}

void ChooseScene::setupConnections()
{
    QPushButton* btn1P = new QPushButton("1P", this);   // 单人按钮
    QPushButton* btn2P = new QPushButton("2P", this);   // 双人按钮
    QPushButton* btnBack = new QPushButton("返回", this); // 返回按钮

    btn1P->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btn1P->setGeometry(this->width() / 2 - 400, this->height() / 2 - 75, 300, 150);

    btn2P->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btn2P->setGeometry(this->width() / 2 + 100, this->height() / 2 - 75, 300, 150);

    btnBack->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    btnBack->setGeometry(this->width() - 250, this->height() - 115, 200, 65);

    // 单人按钮 - 进入单人游戏场景
    connect(btn1P, &QPushButton::clicked, this, [this]() {
        m_sceneManager->switchToPlayScene(true);  // true = 单人模式
    });

    // 双人按钮 - 进入双人游戏场景
    connect(btn2P, &QPushButton::clicked, this, [this]() {
        m_sceneManager->switchToPlayScene(false); // false = 双人模式
    });

    // 返回按钮 - 返回启动界面
    connect(btnBack, &QPushButton::clicked, this, [this]() {
        m_sceneManager->switchToStartScene();
    });
}

void ChooseScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;

    // 画背景
    pix.load(":/new/pixmap/background.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
