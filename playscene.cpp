#include "playscene.h"
#include "basescene.h"
#include "scenemanager.h"
#include "audiomanager.h"
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <windows.h>
#include <winuser.h>
#include <cmath>
#include <ctime>
#include <QMessageBox>
#include <QFont>
#include <config.h>

PlayScene::PlayScene(SceneManager* manager, bool isSinglePlayer, QWidget* parent)
    : BaseScene(manager, parent)
    , m_isSinglePlayer(isSinglePlayer)
    , m_fir(nullptr)
    , m_sec(nullptr)
    , m_createfish(true)
    , m_retry(true)
    , m_btnRestart(nullptr)
    , m_btnBack(nullptr)
{
    this->setFixedSize(playscene_Width, playscene_Height);
    srand((unsigned int)time(NULL));

    setupConnections();
    setupGame();
}

PlayScene::~PlayScene()
{
    cleanupGame();
}

void PlayScene::onEnter()
{
    // 场景进入时继续播放游戏音乐（已在 ChooseScene 播放）
    AudioManager::instance()->playBgMusic(AudioManager::GAME_MUSIC);

    // 重置游戏状态
    m_retry = true;
    m_createfish = true;
}

void PlayScene::onExit()
{
    // 场景退出时清理游戏资源
    cleanupGame();
}

void PlayScene::cleanupGame()
{
    // 清理所有鱼
    for (Fish* fish : m_v_fish) {
        if (fish) {
            delete fish;
        }
    }
    m_v_fish.clear();

    // 清理玩家
    if (m_fir) {
        delete m_fir;
        m_fir = nullptr;
    }
    if (m_sec) {
        delete m_sec;
        m_sec = nullptr;
    }
}

void PlayScene::setupGame()
{
    m_btnRestart = new QPushButton("重新开始", this);
    m_btnBack = new QPushButton("返回", this);

    m_btnRestart->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    m_btnRestart->setGeometry(this->width() / 2 - 200, 400, 400, 65);

    m_btnBack->setStyleSheet("background-color:DeepSkyBlue;font-size:40px;color:white");
    m_btnBack->setGeometry(this->width() / 2 - 200, 480, 400, 65);

    // 重新开始按钮
    connect(m_btnRestart, &QPushButton::clicked, this, [this]() {
        cleanupGame();
        m_retry = true;
        m_btnRestart->hide();
        m_btnBack->hide();
    });

    // 返回按钮 - 返回选择场景
    connect(m_btnBack, &QPushButton::clicked, this, [this]() {
        m_sceneManager->switchToChooseScene();
    });

    // 单人模式计时器
    if (m_isSinglePlayer) {
        QTimer* timer = new QTimer(this);
        timer->start(16); // 60 FPS
        connect(timer, &QTimer::timeout, this, [this]() mutable {
            if (m_retry) {
                m_fir = new Player(this);
                m_fir->pix.load(player_Pix1);
                m_fir->pix_.load(player_Pix1_);

                m_btnRestart->hide();
                m_btnBack->hide();

                m_retry = false;
            }

            if (m_fir && m_fir->m_Score <= 78800 && m_fir->num_life > 0) {
                keyPress();
                addfish();
                move_fish();
                collisiondetection();
                clean();

                m_fir->turn();
                m_fir->move();
                if (m_fir->protection) m_fir->blinkCount++;
            } else {
                m_btnRestart->show();
                m_btnBack->show();
            }

            update();
        });
    }
    // 双人模式计时器
    else {
        QTimer* timer = new QTimer(this);
        timer->start(16); // 60 FPS
        connect(timer, &QTimer::timeout, this, [this]() {
            if (m_retry) {
                m_fir = new Player(this);
                m_sec = new Player(this);

                // 改变初始位置
                m_fir->x -= 100;
                m_sec->x += 100;

                m_fir->pix.load(player_Pix1);
                m_fir->pix_.load(player_Pix1_);
                m_sec->pix.load(player_Pix2);
                m_sec->pix_.load(player_Pix2_);

                m_btnRestart->hide();
                m_btnBack->hide();

                m_retry = false;
            }

            if (m_fir && m_sec &&
                (m_fir->m_Score <= 78800 && m_sec->m_Score <= 78800) &&
                (m_fir->num_life > 0 || m_sec->num_life > 0)) {

                keyPress();
                addfish();
                move_fish();
                collisiondetection();
                clean();

                m_fir->turn();
                m_sec->turn();

                m_fir->move();
                if (m_fir->protection) m_fir->blinkCount++;
                m_sec->move();
                if (m_sec->protection) m_sec->blinkCount++;
            } else {
                m_btnRestart->show();
                m_btnBack->show();
            }

            update();
        });
    }
}

void PlayScene::setupConnections()
{
    // 按钮连接已在 setupGame 中处理
}

void PlayScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;

    // 画背景
    pix.load(playscene_Background1);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    // 画鱼
    for (int i = 0; i < m_v_fish.size(); i++) {
        if (m_v_fish[i]->towards == 1) {
            painter.drawPixmap(m_v_fish[i]->X, m_v_fish[i]->Y, m_v_fish[i]->Wid, m_v_fish[i]->Hei, m_v_fish[i]->Pix);
        } else {
            painter.drawPixmap(m_v_fish[i]->X, m_v_fish[i]->Y, m_v_fish[i]->Wid, m_v_fish[i]->Hei, m_v_fish[i]->Pix_);
        }
    }

    // 单人模式
    if (m_isSinglePlayer) {
        if (m_fir) {
            // 画人物（无敌状态闪烁）
            bool shouldShow = !m_fir->protection || (m_fir->blinkCount % 20 < 10);
            if (m_fir->towards && m_fir->num_life && shouldShow) {
                painter.drawPixmap(m_fir->x, m_fir->y, m_fir->wid, m_fir->hei, m_fir->pix);
            }
            if (!m_fir->towards && m_fir->num_life && shouldShow) {
                painter.drawPixmap(m_fir->x, m_fir->y, m_fir->wid, m_fir->hei, m_fir->pix_);
            }

            // 写信息
            painter.setFont(QFont("黑体", 20));
            painter.drawText(25, 50, QString("分数：%1").arg(m_fir->m_Score));
            painter.drawText(25, 100, QString("生命：%1").arg(m_fir->num_life));

            // 结束显示
            if (m_fir->m_Score > 78800) {
                painter.setFont(QFont("黑体", 30));
                painter.drawText(460, 200, "你已是海上霸主");
            } else if (m_fir->num_life < 1) {
                painter.setFont(QFont("黑体", 100));
                painter.drawText(552, 250, "菜");
            }
        }
    }
    // 双人模式
    else {
        if (m_fir) {
            bool firShouldShow = !m_fir->protection || (m_fir->blinkCount % 20 < 10);
            if (m_fir->towards && m_fir->num_life && firShouldShow) {
                painter.drawPixmap(m_fir->x, m_fir->y, m_fir->wid, m_fir->hei, m_fir->pix);
            }
            if (!m_fir->towards && m_fir->num_life && firShouldShow) {
                painter.drawPixmap(m_fir->x, m_fir->y, m_fir->wid, m_fir->hei, m_fir->pix_);
            }
        }
        if (m_sec) {
            bool secShouldShow = !m_sec->protection || (m_sec->blinkCount % 20 < 10);
            if (m_sec->towards && m_sec->num_life && secShouldShow) {
                painter.drawPixmap(m_sec->x, m_sec->y, m_sec->wid, m_sec->hei, m_sec->pix);
            }
            if (!m_sec->towards && m_sec->num_life && secShouldShow) {
                painter.drawPixmap(m_sec->x, m_sec->y, m_sec->wid, m_sec->hei, m_sec->pix_);
            }
        }

        // 写信息
        painter.setFont(QFont("黑体", 20));
        if (m_fir) {
            painter.drawText(25, 50, QString("分数：%1").arg(m_fir->m_Score));
            painter.drawText(25, 100, QString("生命：%1").arg(m_fir->num_life));
        }
        if (m_sec) {
            painter.drawText(1000, 50, QString("分数：%1").arg(m_sec->m_Score));
            painter.drawText(1000, 100, QString("生命：%1").arg(m_sec->num_life));
        }

        // 结束显示
        if (m_fir && m_fir->m_Score > 78800) {
            painter.setFont(QFont("黑体", 30));
            painter.drawText(460, 200, "P1已是海上霸主");
        } else if (m_sec && m_sec->m_Score > 78800) {
            painter.setFont(QFont("黑体", 30));
            painter.drawText(460, 200, "P2已是海上霸主");
        } else if ((m_fir && m_fir->num_life < 1) && (m_sec && m_sec->num_life < 1)) {
            painter.setFont(QFont("黑体", 100));
            painter.drawText(552, 250, "菜");
        }
    }
}

void PlayScene::keyPress()
{
    if (m_isSinglePlayer && m_fir) {
        if (GetAsyncKeyState('W') & 0x8000) m_fir->up = true;
        if (GetAsyncKeyState('S') & 0x8000) m_fir->down = true;
        if (GetAsyncKeyState('A') & 0x8000) { m_fir->left = true; m_fir->towards = true; }
        if (GetAsyncKeyState('D') & 0x8000) { m_fir->right = true; m_fir->towards = false; }
    } else {
        if (m_fir) {
            if (GetAsyncKeyState('W') & 0x8000) m_fir->up = true;
            if (GetAsyncKeyState('S') & 0x8000) m_fir->down = true;
            if (GetAsyncKeyState('A') & 0x8000) { m_fir->left = true; m_fir->towards = true; }
            if (GetAsyncKeyState('D') & 0x8000) { m_fir->right = true; m_fir->towards = false; }
        }
        if (m_sec) {
            if (GetAsyncKeyState(VK_UP) & 0x8000) m_sec->up = true;
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) m_sec->down = true;
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_sec->left = true; m_sec->towards = true; }
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_sec->right = true; m_sec->towards = false; }
        }
    }

    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        QMessageBox::about(this, "暂停", "是否继续?");
    }
}

void PlayScene::addfish()
{
    if (!m_fir) return;

    if (m_v_fish.size() < maxnum_fish && m_createfish) {
        int kind = 0;
        if (m_fir->wid * m_fir->hei < 2250) {
            kind = rand() % 3;
        } else if (m_fir->wid * m_fir->hei < 10212 && m_fir->wid * m_fir->hei > 2250) {
            kind = rand() % 6;
        } else {
            kind = rand() % 8;
        }

        int percent = rand() % 31 + 70;

        switch (kind) {
        case 0: m_v_fish.push_back(new Fish_lv1(percent, this)); break;
        case 1: m_v_fish.push_back(new Fish_lv2(percent, this)); break;
        case 2: m_v_fish.push_back(new Fish_lv3(percent, this)); break;
        case 3: m_v_fish.push_back(new Fish_lv4(percent, this)); break;
        case 4: m_v_fish.push_back(new Fish_lv5(percent, this)); break;
        case 5: m_v_fish.push_back(new Fish_lv6(percent, this)); break;
        case 6: m_v_fish.push_back(new Fish_lv7(percent, this)); break;
        case 7: m_v_fish.push_back(new Fish_lv8(percent, this)); break;
        }

        m_createfish = false;
        QTimer::singleShot(fish_recordor, this, [this]() { m_createfish = true; });
    }
}

void PlayScene::move_fish()
{
    for (Fish* fish : m_v_fish) {
        fish->move();
    }
}

void PlayScene::clean()
{
    for (QVector<Fish*>::iterator it = m_v_fish.begin(); it != m_v_fish.end(); it++) {
        if ((*it)->X < 0 - (*it)->Wid || (*it)->X > playscene_Width ||
            (*it)->Y < 0 - (*it)->Hei || (*it)->Y > playscene_Height) {
            delete (*it);
            it = m_v_fish.erase(it) - 1;
        }
    }
}

void PlayScene::collisiondetection()
{
    for (QVector<Fish*>::iterator it = m_v_fish.begin(); it != m_v_fish.end(); it++) {
        Fish* fish = *it;
        if (!fish || !m_fir) continue;

        // 单人模式
        if (m_isSinglePlayer && m_fir->num_life) {
            if (m_fir->collision(fish)) {
                if ((m_fir->wid * m_fir->hei) > (fish->Wid * fish->Hei)) {
                    AudioManager::instance()->playSoundEffect(AudioManager::GET_SCORE);

                    float oldSize = sqrt(m_fir->wid * m_fir->hei);
                    float newSize = sqrt(oldSize * oldSize + fish->Score / per_turn);
                    float offset = (newSize - oldSize) / 2;
                    m_fir->x -= offset;
                    m_fir->y -= offset;
                    m_fir->m_Score += fish->Score / per_turn;

                    delete fish;
                    it = m_v_fish.erase(it) - 1;
                    continue;
                } else {
                    if (!m_fir->protection) {
                        AudioManager::instance()->playSoundEffect(AudioManager::LOSE_LIFE);
                        m_fir->num_life--;
                        m_fir->protection = true;
                        m_fir->blinkCount = 0;
                        QTimer::singleShot(3000, this, [this]() { m_fir->protection = false; });
                    }
                }
            }
        }

        // 双人模式
        if (!m_isSinglePlayer) {
            bool fishEaten = false;

            if (m_fir && m_fir->num_life && m_fir->collision(fish)) {
                if ((m_fir->wid * m_fir->hei) > (fish->Wid * fish->Hei)) {
                    AudioManager::instance()->playSoundEffect(AudioManager::GET_SCORE);

                    float oldSize = sqrt(m_fir->wid * m_fir->hei);
                    float newSize = sqrt(oldSize * oldSize + fish->Score / per_turn);
                    float offset = (newSize - oldSize) / 2;
                    m_fir->x -= offset;
                    m_fir->y -= offset;
                    m_fir->m_Score += fish->Score / per_turn;
                    fishEaten = true;
                } else {
                    if (!m_fir->protection) {
                        AudioManager::instance()->playSoundEffect(AudioManager::LOSE_LIFE);
                        m_fir->num_life--;
                        m_fir->protection = true;
                        m_fir->blinkCount = 0;
                        QTimer::singleShot(3000, this, [this]() { m_fir->protection = false; });
                    }
                }
            }

            if (!fishEaten && m_sec && m_sec->num_life && m_sec->collision(fish)) {
                if ((m_sec->wid * m_sec->hei) > (fish->Wid * fish->Hei)) {
                    AudioManager::instance()->playSoundEffect(AudioManager::GET_SCORE);

                    float oldSize = sqrt(m_sec->wid * m_sec->hei);
                    float newSize = sqrt(oldSize * oldSize + fish->Score / per_turn);
                    float offset = (newSize - oldSize) / 2;
                    m_sec->x -= offset;
                    m_sec->y -= offset;
                    m_sec->m_Score += fish->Score / per_turn;
                    fishEaten = true;
                } else {
                    if (!m_sec->protection) {
                        AudioManager::instance()->playSoundEffect(AudioManager::LOSE_LIFE);
                        m_sec->num_life--;
                        m_sec->protection = true;
                        m_sec->blinkCount = 0;
                        QTimer::singleShot(3000, this, [this]() { m_sec->protection = false; });
                    }
                }
            }

            if (fishEaten) {
                delete fish;
                it = m_v_fish.erase(it) - 1;
            }
        }
    }
}
