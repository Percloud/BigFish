#include "scenemanager.h"
#include "basescene.h"
#include <QDebug>

SceneManager::SceneManager(QStackedWidget* stack, QObject* parent)
    : QObject(parent), m_stack(stack), m_currentType(START_SCENE)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::registerScene(SceneType type, QWidget* scene)
{
    if (!scene) {
        qWarning() << "SceneManager: Cannot register null scene";
        return;
    }
    m_scenes[type] = scene;
}

void SceneManager::switchToScene(SceneType type)
{
    if (!m_scenes.contains(type)) {
        qWarning() << "SceneManager: Scene not registered:" << type;
        return;
    }

    // 调用当前场景的 onExit
    if (m_scenes.contains(m_currentType)) {
        if (auto* baseScene = qobject_cast<BaseScene*>(m_scenes[m_currentType])) {
            baseScene->onExit();
        }
    }

    SceneType from = m_currentType;
    m_currentType = type;

    // 切换场景
    m_stack->setCurrentWidget(m_scenes[type]);

    // 调用新场景的 onEnter
    if (auto* baseScene = qobject_cast<BaseScene*>(m_scenes[type])) {
        baseScene->onEnter();
    }

    emit sceneChanged(from, type);
}

void SceneManager::switchToStartScene()
{
    switchToScene(START_SCENE);
}

void SceneManager::switchToChooseScene()
{
    switchToScene(CHOOSE_SCENE);
}

void SceneManager::switchToPlayScene(bool isSinglePlayer)
{
    switchToScene(isSinglePlayer ? PLAY_SCENE_SINGLE : PLAY_SCENE_DOUBLE);
}

QWidget* SceneManager::currentScene() const
{
    return m_stack ? m_stack->currentWidget() : nullptr;
}
