#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include <QStackedWidget>
#include <QMap>

class BaseScene;

// 场景管理器
class SceneManager : public QObject
{
    Q_OBJECT

public:
    enum SceneType {
        START_SCENE = 0,
        CHOOSE_SCENE = 1,
        PLAY_SCENE_SINGLE = 2,
        PLAY_SCENE_DOUBLE = 3
    };

    explicit SceneManager(QStackedWidget* stack, QObject* parent = nullptr);
    ~SceneManager();

    // 场景注册
    void registerScene(SceneType type, QWidget* scene);

    // 场景切换
    void switchToScene(SceneType type);
    void switchToStartScene();
    void switchToChooseScene();
    void switchToPlayScene(bool isSinglePlayer);

    // 获取当前场景
    QWidget* currentScene() const;
    SceneType currentSceneType() const { return m_currentType; }

signals:
    void sceneChanged(SceneType from, SceneType to);

private:
    QStackedWidget* m_stack;
    QMap<SceneType, QWidget*> m_scenes;
    SceneType m_currentType;
};

#endif // SCENEMANAGER_H
