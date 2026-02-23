#include "basescene.h"
#include "scenemanager.h"

BaseScene::BaseScene(SceneManager* manager, QWidget* parent)
    : QWidget(parent), m_sceneManager(manager)
{
}

BaseScene::~BaseScene()
{
}
