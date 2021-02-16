#include "title_scene.h"
#include"polygon.h"
#include"title_manager.h"
#include"title_texture.h"
#include"right_polygon.h"
#include"left_polygon.h"
#include"title_move_scene_polygon.h"
#include"skybox.h"
#include"sound.h"
#include"title_sakura.h"
#include"main.h"
#include"title_sakura_manager.h"
CTitleScene::CTitleScene()
{
}


CTitleScene::~CTitleScene()
{
}
void CTitleScene::Load()
{
	CTitleTexture::Load();
	CRightPolygon::Load();
	CLeftPolygon::Load();
	CTitleManager::Load();
	CTitleMoveScenePolygon::Load();
	CTitleSakura::Load();
	//CSound::LoadSound("asset\\sound\\wav\\Title.wav",GetWindow());

	
}
void CTitleScene::UnLoad()
{
	CTitleTexture::UnLoad();
	CRightPolygon::UnLoad();
	CLeftPolygon::UnLoad();
	CTitleManager::UnLoad();
	CTitleMoveScenePolygon::UnLoad();
	CTitleSakura::UnLoad();
	CSound::Crear();
	
}
void CTitleScene::Init()
{
	CGameObject* gameobject = AddGameObject(LAYER_STATE_CAMERA);
	CCamera *camera = gameobject->AddComponent<CCamera>();
	camera->SetSatate(CAMERA_POSITION_STATE_STAY);
	gameobject->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 10.0f));
	
	gameobject = AddGameObject(LAYER_STATE_CAMERA);
	camera->SetTarget(gameobject);

	gameobject = AddGameObject(LAYER_STATE_D2);
	gameobject->AddComponent<CTitleSakuraManager>();



	gameobject = AddGameObject(LAYER_STATE_D2);
	gameobject->SetScale(D3DXVECTOR3(400.0f, 150.0f, 80.0f));
	gameobject->SetPosition(D3DXVECTOR3((SCREEN_WIDTH / 2.0f) , 180.0f, 0.0f));

	gameobject->AddComponent<CTitleTexture>();

	/*
	gameobject = AddGameObject(LAYER_STATE_D2);
	gameobject->SetScale(D3DXVECTOR3(80.0f, 80.0f, 80.0f));
	gameobject->SetPosition(D3DXVECTOR3((SCREEN_WIDTH/2.0f)+300, 400.0f, 0.0f));
	gameobject->AddComponent<CRightPolygon>();



	gameobject = AddGameObject(LAYER_STATE_D2);
	gameobject->SetScale(D3DXVECTOR3(80.0f, 80.0f, 80.0f));
	gameobject->SetPosition(D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - 300, 400.0f, 0.0f));
	gameobject->AddComponent<CLeftPolygon>();
	*/


	gameobject = AddGameObject(LAYER_STATE_D2);
	gameobject->SetScale(D3DXVECTOR3(300.0f, 300.0f, 80.0f));
	gameobject->SetPosition(D3DXVECTOR3((SCREEN_WIDTH / 2.0f) , 400.0f, 0.0f));
	CTitleMoveScenePolygon* moveScenePolygon = gameobject->AddComponent<CTitleMoveScenePolygon>();


	gameobject = AddGameObject(LAYER_STATE_D3);
	CTitleManager* manager = gameobject->AddComponent<CTitleManager>();
	manager->Setting(moveScenePolygon);


	gameobject = AddGameObject(LAYER_STATE_SKYBOX);
	CSkyBox* skybox = gameobject->AddComponent<CSkyBox>();
	skybox->Load("asset\\texture\\game_background.png");
	/*
	gameobject = AddGameObject(LAYER_STATE_SKYBOX);
	CSound *s = gameobject->AddComponent<CSound>();
	s->SetSound("asset\\sound\\wav\\Title.wav", GetWindow());
	s->m_volume = 0.1f;
	s->Play(XAUDIO2_END_OF_STREAM);
	*/
}