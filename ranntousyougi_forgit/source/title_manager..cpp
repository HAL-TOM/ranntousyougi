#include"manager.h"
#include"main.h"
#include"input.h"
#include"title_move_scene_polygon.h"
#include"player_to_player_game_scene.h"
#include"player_to_npc_game_scene.h"
#include"sound.h"
#include"game_object.h"
#include "title_manager.h"

ID3D11ShaderResourceView* CTitleManager::m_texture[MOVE_SCENE_NUM];
CSound * CTitleManager::m_seslectSe;
CSound * CTitleManager::m_ketteiSe;
CTitleManager::CTitleManager()
{
}


CTitleManager::~CTitleManager()
{

}
void CTitleManager::Load()
{

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile
	(
		CRenderer::GetDevice(),
		"asset\\texture\\vs_player.png",
		NULL,
		NULL,
		&m_texture[MOVE_SCENE::P_TO_P],
		NULL
	);
	D3DX11CreateShaderResourceViewFromFile
	(
		CRenderer::GetDevice(),
		"asset\\texture\\vs_npc.png",
		NULL,
		NULL,
		&m_texture[MOVE_SCENE::P_TO_N],
		NULL
	);

	//m_seslectSe = new CSound();
	//m_ketteiSe = new CSound();
	//m_seslectSe->SetSound("asset\\sound\\wav\\select.wav", GetWindow());
	//m_seslectSe->m_volume = 0.1f;
	//
	//m_ketteiSe->SetSound("asset\\sound\\wav\\kettei01.wav", GetWindow());
	//m_ketteiSe->m_volume = 0.1f;
}
void CTitleManager::UnLoad()
{
	for (int i = 0; i < MOVE_SCENE_NUM; i++)
	{
		m_texture[i]->Release();
	}
}
void CTitleManager::Init()
{
	m_moveScene = P_TO_N;

}
void CTitleManager::Uninit()
{

}
void CTitleManager::Update()
{
	if (CInput::GetKeyPress((BYTE)VK_SPACE))
	{
		Move();
	}
	//プレイヤー対戦をしないバージョンのためコメントアウト
	//if (CInput::GetKeyTrigger((BYTE)'A'))
	//{
	//	Left();
	//}
	//if (CInput::GetKeyTrigger((BYTE)'D'))
	//{
	//	Right();
	//}
}
void CTitleManager::Draw()
{

}

void CTitleManager::Right()
{
	m_moveScene = (MOVE_SCENE)((m_moveScene + 1) % MOVE_SCENE::MOVE_SCENE_NUM);
	
	//音声データがない為再生しない
	//m_seslectSe->Play();

	SetTexture();
}
void CTitleManager::Left()
{
	int num = m_moveScene - 1;
	if (num<0)
	{
		num = MOVE_SCENE_NUM - 1;

	}
	m_moveScene =(MOVE_SCENE) num;
	//音声データがない為再生しない
	//m_seslectSe->Play();
	SetTexture();
}
void CTitleManager::SetTexture()
{
	m_moveScenePolygon->SetTexture(m_texture[m_moveScene]);
}
void CTitleManager::Move()
{	
	//m_ketteiSe->Play();
	switch (m_moveScene)
	{
	case MOVE_SCENE::P_TO_P:
		CManager::MoveScene<CPlayerToPlayerGameScene>(30);
		break;
	case MOVE_SCENE::P_TO_N:
		//現在のバージョン06ではここにしか来ない
		CManager::MoveScene<CPlayerToNpcGameScene>(30);
		break;
	default:
		break;
	}

}
void CTitleManager::Setting(CTitleMoveScenePolygon* polygon)
{
	m_moveScenePolygon = polygon;
	SetTexture();
}
