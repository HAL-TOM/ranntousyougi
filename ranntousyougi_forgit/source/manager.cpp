
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include"camera.h"
#include"game_object.h"
#include<list>
#include"scene.h"
#include"input.h"
#include"title_scene.h"
#include"fade_in.h"
#include"sound.h"
#include"effecseer.h"
#include"effekseer_renderer.h"
#include"effekseer_manager.h"

CScene * CManager::m_scene= nullptr;
CScene * CManager::m_nextScene = nullptr;
int CManager::m_moveFrame = 0;
int CManager::m_moveEndFrame = 0;
bool CManager::m_move = false;

void CManager::Init()
{

	CRenderer::Init();
	CInput::Init();
	CEffekseerRenderer::Init();
	CEffecseerManager::Init();
	CEffekseerRenderer::SetBackGroundTex();
	//if (!CSound::InitSound(GetWindow()))
	//{
		//PostQuitMessage(0);
	//}
	CSound::InitSound(GetWindow());

	CreateScene(new CTitleScene());
	
}

void CManager::Uninit()
{
	
	m_scene->Unint();
	delete m_scene;

	if (m_nextScene!=nullptr)
	{
		m_nextScene->Unint();
		delete m_nextScene;
	}
	CInput::Uninit();
	CRenderer::Uninit();
	CEffekseerRenderer::Uninit();
	CEffecseerManager::Uninit();
	CSound::UninitSound();
}

void CManager::Update()
{

	CInput::Update();
	m_scene->Update();

	if (m_move==true)
	{
		m_moveFrame++;
		CRenderer::SetGloabalAlpha(1.0f - ((float)m_moveFrame/ (float)m_moveEndFrame));
		if (m_moveEndFrame<m_moveFrame)
		{
			Move();
		}
	}
	
}

void CManager::Draw()
{
	
	m_scene->Draw();

}
CScene* CManager::GetScene()
{
	return m_scene;
}
void CManager::CreateScene(CScene* scene)
{
	m_scene = scene;
	m_scene->Load();

	m_scene->Init();
}

void CManager::Move()
{
	m_scene->Unint();
	delete m_scene;

	CreateScene(m_nextScene);
	
	CGameObject* gameobject= m_scene->AddGameObject(LAYER_STATE_D3);
	CFadeIn *f = gameobject->AddComponent<CFadeIn>();
	f->m_moveEndFrame = m_moveEndFrame;
	f->m_moveFrame = 0;
	m_nextScene = nullptr;
	m_moveEndFrame = 0;
	m_moveFrame = 0;
	m_move = false;
}