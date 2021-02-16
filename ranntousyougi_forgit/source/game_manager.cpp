#include "game_manager.h"

#include"manager.h"
#include"scene.h"
#include"game_object.h"
#include"player.h"
#include"player_base.h"
#include"npc.h"
#include"piece.h"
#include"square_table.h"
#include"square.h"
#include"result_scene.h"

PLAYER_STATE CGameManager::m_winner;
bool CGameManager::m_loose;

bool CGameManager::m_draw;
GAME_TYPE CGameManager::m_type;


CGameManager::CGameManager()
{
}


CGameManager::~CGameManager()
{
}
void CGameManager::Init()
{
	m_winner = PLAYER_STATE_NUM;
	m_loose = false;
	m_draw = false;
}
void CGameManager::Update()
{
	Juge();
}
void CGameManager::Uninit()
{
}
void CGameManager::Draw()
{
}

void CGameManager::Juge()
{
	CScene* scene = CManager::GetScene();

	std::vector<CPlayer*> players;
	scene->FindComponents<CPlayer>(&players);

	std::vector<CNPC*> npcs;
	scene->FindComponents<CNPC>(&npcs);
	
	CSquareTable* table = scene->FindComponent<CSquareTable>();

	for (CPlayer* p : players)
	{
	
		if (p->GetLoose())
		{
			if (npcs.size()>0)
			{
				CGameManager::SetLoose(true);
				CManager::MoveScene<CResultScene>(16);

				return;
			}

			if (p->GetPlayerState()==PLAYER_STATE_01)
			{
				CGameManager::SetWinner(PLAYER_STATE_02);
				CManager::MoveScene<CResultScene>(16);

				return;
			}
			if (p->GetPlayerState() == PLAYER_STATE_02)
			{
				CGameManager::SetWinner(PLAYER_STATE_01);
				CManager::MoveScene<CResultScene>(16);

				return;
			}

		}
	}
	for (CNPC* n : npcs)
	{

		if (n->GetLoose())
		{


			if (n->GetPlayerState() == PLAYER_STATE_01)
			{
				CGameManager::SetWinner(PLAYER_STATE_02);
				CManager::MoveScene<CResultScene>(16);

				return;
			}
			if (n->GetPlayerState() == PLAYER_STATE_02)
			{
				CGameManager::SetWinner(PLAYER_STATE_01);
				CManager::MoveScene<CResultScene>(16);

				return;
			}

		}
	}
	if (m_draw==true)
	{
		CManager::MoveScene<CResultScene>(16);
	}



}