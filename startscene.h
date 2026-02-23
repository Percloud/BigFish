#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "basescene.h"

// 启动场景（开始界面）
class StartScene : public BaseScene
{
    Q_OBJECT

public:
    explicit StartScene(SceneManager* manager, QWidget* parent = nullptr);
    ~StartScene() override;

    // 场景生命周期
    void onEnter() override;
    void onExit() override;

    // 重写绘图事件
    void paintEvent(QPaintEvent*) override;

private:
    void setupConnections();
};

#endif // STARTSCENE_H
