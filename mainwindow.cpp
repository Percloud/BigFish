#include "mainwindow.h"
#include "scenemanager.h"
#include "audiomanager.h"
#include "startscene.h"
#include "choosescene.h"
#include "playscene.h"
#include <QPixmap>
#include <config.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUI();
    setupScenes();

    // 设置窗口属性
    this->setWindowTitle(playscene_Title);
    this->setWindowIcon(QPixmap(Icon0));
    this->setFixedSize(playscene_Width, playscene_Height);

    // 初始显示启动界面
    m_sceneManager->switchToStartScene();
}

MainWindow::~MainWindow()
{
    // Qt 对象树自动清理子对象
}

void MainWindow::setupUI()
{
    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    m_sceneManager = new SceneManager(m_stack, this);
}

void MainWindow::setupScenes()
{
    // 创建所有场景（只创建一次）
    m_startScene = new StartScene(m_sceneManager, this);
    m_chooseScene = new ChooseScene(m_sceneManager, this);
    m_playSceneSingle = new PlayScene(m_sceneManager, true, this);
    m_playSceneDouble = new PlayScene(m_sceneManager, false, this);

    // 注册到 SceneManager
    m_sceneManager->registerScene(SceneManager::START_SCENE, m_startScene);
    m_sceneManager->registerScene(SceneManager::CHOOSE_SCENE, m_chooseScene);
    m_sceneManager->registerScene(SceneManager::PLAY_SCENE_SINGLE, m_playSceneSingle);
    m_sceneManager->registerScene(SceneManager::PLAY_SCENE_DOUBLE, m_playSceneDouble);

    // 添加到 QStackedWidget
    m_stack->addWidget(m_startScene);
    m_stack->addWidget(m_chooseScene);
    m_stack->addWidget(m_playSceneSingle);
    m_stack->addWidget(m_playSceneDouble);
}
