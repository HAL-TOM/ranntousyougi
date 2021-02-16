
#include"camera.h"
#include"model.h"
#include"model_drawer.h"
#include"SkyBox.h"
#include"bord.h"
#include"square.h"
#include"square_table.h"
#include"player.h"
#include"piece.h"
#include"number.h"
#include"PIECE_STATE.h"
#include"select.h"
#include"pointer.h"
#include"game_manager.h"
#include"piece_drawer.h"
#include"game_timer.h"
#include"sound.h"
#include"main.h"
#include "player_to_player_game_scene.h"
CPlayerToPlayerGameScene::CPlayerToPlayerGameScene()
{
}


CPlayerToPlayerGameScene::~CPlayerToPlayerGameScene()
{
}

void CPlayerToPlayerGameScene::Load()
{
	//データロード
	CPiece::Load();
	CPieceDrawer::Load();
	CBord::Load();
	CSelect::Load();
	CNumber::Load();
	CPointer::Load();
}
void CPlayerToPlayerGameScene::UnLoad()
{
	CPiece::UnLoad();
	CPieceDrawer::UnLoad();

	CBord::UnLoad();
	CSelect::UnLoad();
	CNumber::UnLoad();
	CPointer::UnLoad();
}

void CPlayerToPlayerGameScene::Init()
{

	m_frame = 0;

	CGameObject* gameobject;

	//////////////////////////////////////////////////////////////////
	gameobject = AddGameObject(LAYER_STATE_D3);
	gameobject->AddComponent<CGameManager>();
	CGameManager::SetType(GAME_TYPE_PP);
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	gameobject = AddGameObject(LAYER_STATE_CAMERA);//カメラ
	CCamera* camera = gameobject->AddComponent<CCamera>();
	camera->SetSatate(CAMERA_POSITION_STATE_STAY);
	gameobject->SetPosition(D3DXVECTOR3(0.0f, 20.0f, -1.0f));
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	gameobject = AddGameObject(LAYER_STATE_D3);//squaretable
	CSquareTable *table = gameobject->AddComponent<CSquareTable>();

	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	gameobject = AddGameObject(LAYER_STATE_D3);//gametimer
	CGameTimer* timer = gameobject->AddComponent<CGameTimer>();
	timer->TimerSet(60 * 300);
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	gameobject = AddGameObject(LAYER_STATE_D3);//bord
	CBord* bord = gameobject->AddComponent<CBord>();

	camera->SetTarget(gameobject);
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	gameobject = AddGameObject(LAYER_STATE_D3);//player01
	CPlayer* player01 = gameobject->AddComponent<CPlayer>();
	player01->Setting(PLAYER_STATE::PLAYER_STATE_01, table);

	gameobject = AddGameObject(LAYER_STATE_D3);//player02
	CPlayer* player02 = gameobject->AddComponent<CPlayer>();

	player02->Setting(PLAYER_STATE::PLAYER_STATE_02, table);


	//////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////
	CPiece*piece;


	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KYOUSYA, player02, table->GetSquare(0, 0));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KEIMA, player02, table->GetSquare(1, 0));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_GINN, player02, table->GetSquare(2, 0));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KINN, player02, table->GetSquare(3, 0));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_GYOKU, player02, table->GetSquare(4, 0));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KINN, player02, table->GetSquare(5, 0));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_GINN, player02, table->GetSquare(6, 0));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KEIMA, player02, table->GetSquare(7, 0));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KYOUSYA, player02, table->GetSquare(8, 0));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HISYA, player02, table->GetSquare(7, 1));


	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KAKU, player02, table->GetSquare(1, 1));


	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player02, table->GetSquare(0, 2));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player02, table->GetSquare(1, 2));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player02, table->GetSquare(2, 2));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player02, table->GetSquare(3, 2));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player02, table->GetSquare(4, 2));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player02, table->GetSquare(5, 2));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player02, table->GetSquare(6, 2));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player02, table->GetSquare(7, 2));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player02, table->GetSquare(8, 2));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KYOUSYA, player01, table->GetSquare(0, 8));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KEIMA, player01, table->GetSquare(1, 8));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_GINN, player01, table->GetSquare(2, 8));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KINN, player01, table->GetSquare(3, 8));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_GYOKU, player01, table->GetSquare(4, 8));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KINN, player01, table->GetSquare(5, 8));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_GINN, player01, table->GetSquare(6, 8));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KEIMA, player01, table->GetSquare(7, 8));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KYOUSYA, player01, table->GetSquare(8, 8));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HISYA, player01, table->GetSquare(1, 7));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_KAKU, player01, table->GetSquare(7, 7));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player01, table->GetSquare(0, 6));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player01, table->GetSquare(1, 6));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player01, table->GetSquare(2, 6));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player01, table->GetSquare(3, 6));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player01, table->GetSquare(4, 6));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player01, table->GetSquare(5, 6));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player01, table->GetSquare(6, 6));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player01, table->GetSquare(7, 6));

	gameobject = AddGameObject(LAYER_STATE_D3);
	piece = gameobject->AddComponent<CPiece>();
	piece->StateSetting(PIECE_TYPE_HUHYOU, player01, table->GetSquare(8, 6));
	//////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////
	gameobject = AddGameObject(LAYER_STATE_D3);
	camera->SetTarget(gameobject);
	gameobject = AddGameObject(LAYER_STATE_SKYBOX);
	CSkyBox* skybox = gameobject->AddComponent<CSkyBox>();
	skybox->Load("asset\\texture\\game_background.png");
	//////////////////////////////////////////////////////////////////
}

