#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "basescene.h"
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>
#include <player.h>
#include <fish.h>
#include <QVector>

// 游戏场景（主要游戏逻辑）
class PlayScene : public BaseScene
{
    Q_OBJECT

public:
    explicit PlayScene(SceneManager* manager, bool isSinglePlayer, QWidget* parent = nullptr);
    ~PlayScene() override;

    // 场景生命周期
    void onEnter() override;
    void onExit() override;

    // 清理游戏资源
    void cleanupGame();

    // 重写绘图事件
    void paintEvent(QPaintEvent*) override;

    // 按键响应
    void keyPress();

    // 碰撞检测
    void collisiondetection();

    // 产生鱼
    void addfish();

    // 清除出界的鱼
    void clean();

    // 鱼移动
    void move_fish();

private:
    void setupGame();
    void setupConnections();

    // 游戏状态
    bool m_isSinglePlayer;   // 是否单人模式
    bool m_createfish;       // 是否产生鱼
    bool m_retry;            // 是否重新开始

    // 游戏对象
    Player* m_fir;           // 玩家1P
    Player* m_sec;           // 玩家2P
    QVector<Fish*> m_v_fish; // 鱼容器

    // UI 按钮
    QPushButton* m_btnRestart;
    QPushButton* m_btnBack;
};

#endif // PLAYSCENE_H
