#ifndef BASESCENE_H
#define BASESCENE_H

#include <QWidget>

class SceneManager;

// 场景基类，提供生命周期钩子
class BaseScene : public QWidget
{
    Q_OBJECT

public:
    explicit BaseScene(SceneManager* manager, QWidget* parent = nullptr);
    virtual ~BaseScene();

    // 场景进入/退出钩子（子类重写）
    virtual void onEnter() {}
    virtual void onExit() {}

protected:
    SceneManager* m_sceneManager;  // 场景管理器指针
};

#endif // BASESCENE_H
