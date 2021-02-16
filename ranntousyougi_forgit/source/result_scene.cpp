#include"scene.h"
#include"game_object.h"
#include"player.h"
#include"game_manager.h"
#include"manager.h"
#include"title_scene.h"
#include"winner_texture.h"
#include"result_texture.h"
#include"draw_texture.h"
#include"result_background.h"
#include"skybox.h"
#include"camera.h"
#include"result_manager.h"
#include"loose_texture.h"
#include"win_texture.h"
#include"main.h"
#include "result_scene.h"

CResultScene::CResultScene()
{
}


CResultScene::~CResultScene()
{
}
void CResultScene::Load()
{
	CWinnerTexture::Load();
	CResultTexture::Load();
	CResultBackGround::Load();
	CDrawTexture::Load();
	CLooseTexture::Load();
	CWinTexture::Load();
}
void CResultScene::UnLoad()
{
	CWinnerTexture::UnLoad();
	CResultTexture::UnLoad();
	CResultBackGround::UnLoad();
	CDrawTexture::UnLoad ();
	CLooseTexture::UnLoad();
	CWinTexture::UnLoad();
}

void CResultScene::Init()
{
	CScene* scene = CManager::GetScene();
	CGameObject* gameobject;
	
	gameobject = scene->AddGameObject(LAYER_STATE_D2);
	gameobject->AddComponent<CResultBackGround>();
	gameobject = scene->AddGameObject(LAYER_STATE_D3);
	gameobject->AddComponent<CResultManager>();

	switch (CGameManager::GetType())
	{
	case GAME_TYPE::GAME_TYPE_PP:
		if (CGameManager::GetWinner() == PLAYER_STATE_01)
		{
			gameobject = scene->AddGameObject(LAYER_STATE_D2);
			gameobject->AddComponent<CWinnerTexture>();
			gameobject->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f));
			gameobject->SetScale(D3DXVECTOR3(200.0f, 200.0f, 100.0f));

			gameobject = scene->AddGameObject(LAYER_STATE_D2);
			gameobject->AddComponent<CResultTexture>()->Setting(PLAYER_STATE_01);
			gameobject->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f));
			gameobject->SetScale(D3DXVECTOR3(300.0f, 300.0f, 0.0f));

		}
		else if (CGameManager::GetWinner() == PLAYER_STATE_02)
		{


			gameobject = scene->AddGameObject(LAYER_STATE_D2);
			gameobject->AddComponent<CWinnerTexture>();
			gameobject->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f));
			gameobject->SetScale(D3DXVECTOR3(200.0f, 200.0f, 100.0f));

			gameobject = scene->AddGameObject(LAYER_STATE_D2);
			gameobject->AddComponent<CResultTexture>()->Setting(PLAYER_STATE_02);
			gameobject->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f));
			gameobject->SetScale(D3DXVECTOR3(300.0f, 300.0f, 0.0f));


		}
		else if(CGameManager::GetDraw() == true)
		{
			gameobject = scene->AddGameObject(LAYER_STATE_D2);
			gameobject->AddComponent<CDrawTexture>();
			gameobject->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f));
			gameobject->SetScale(D3DXVECTOR3(300.0f, 300.0f, 0.0f));
		}
		break;
	case GAME_TYPE::GAME_TYPE_PN:



		if (CGameManager::GetLoose() == true)
		{
			gameobject = scene->AddGameObject(LAYER_STATE_D2);
			gameobject->AddComponent<CLooseTexture>();
			gameobject->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f));
			gameobject->SetScale(D3DXVECTOR3(300.0f, 300.0f, 0.0f));
		}
		else if (CGameManager::GetDraw() == true)
		{
			gameobject = scene->AddGameObject(LAYER_STATE_D2);
			gameobject->AddComponent<CDrawTexture>();
			gameobject->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f));
			gameobject->SetScale(D3DXVECTOR3(300.0f, 300.0f, 0.0f));
		}
		else if (CGameManager::GetWinner() != PLAYER_STATE::PLAYER_STATE_NUM)
		{
			gameobject = scene->AddGameObject(LAYER_STATE_D2);
			gameobject->AddComponent<CWinTexture>();
			gameobject->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f));
			gameobject->SetScale(D3DXVECTOR3(500.0f, 500.0f, 0.0f));
		}
		break;
	default:
		//想定外・・とりあえずタイトルに返す
		CManager::MoveScene<CTitleScene>(30);
		return;
		break;
	}


	//想定外・・とりあえずタイトルに返す
	CManager::MoveScene<CTitleScene>(30);
	return;





}

