
#include <list>
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "polygon.h"
#include "enemy.h"
#include "scene.h"
#include "manager.h"

CScene* g_scene;


void CManager::Init()
{
	CRenderer::Init();
	CInput::Init();

	g_scene = new CScene();
	g_scene->Init();

}

void CManager::Uninit()
{
	g_scene->Uninit();
	delete g_scene;

	CInput::Uninit();
	CRenderer::Uninit();

}

void CManager::Update()
{
	CInput::Update();

	g_scene->Update();
}

void CManager::Draw()
{

	CRenderer::Begin();

	g_scene->Draw();

	CRenderer::End();

}

CScene*  CManager::GetScene()
{
	return g_scene;
}
