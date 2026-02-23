#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class SceneManager;
class AudioManager;
class StartScene;
class ChooseScene;
class PlayScene;

// 主窗口，统一管理所有场景
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void setupScenes();

    QStackedWidget* m_stack;
    SceneManager* m_sceneManager;

    // 场景指针（单例模式）
    StartScene* m_startScene;
    ChooseScene* m_chooseScene;
    PlayScene* m_playSceneSingle;   // 单人模式游戏场景
    PlayScene* m_playSceneDouble;   // 双人模式游戏场景
};

#endif // MAINWINDOW_H
