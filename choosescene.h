#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include "basescene.h"

// 选择场景（单人/双人选择）
class ChooseScene : public BaseScene
{
    Q_OBJECT

public:
    explicit ChooseScene(SceneManager* manager, QWidget* parent = nullptr);
    ~ChooseScene() override;

    // 场景生命周期
    void onEnter() override;
    void onExit() override;

    // 重写绘图事件
    void paintEvent(QPaintEvent*) override;

private:
    void setupConnections();
};

#endif // CHOOSESCENE_H
