#include "npc.h"

#include"manager.h"
#include"game_object.h"
#include"scene.h"


#include"player_base.h"
#include"player.h"

#include"select.h"
#include"piece.h"
#include"square_table.h"
#include"square.h"
#include<vector>
#include"action_move_piece.h"
#include"action_take_piece.h"
#include"action_use_hand.h"
#include"npc_state_move_piece_nonselect.h"
#include"npc_state_take_piece_select.h"
#include"npc_state_take_piece_non_select.h"
#include"npc_state_use_hand_piece.h"
#include "npc_state_move_piece_select.h"
#include"npc_state_select_square.h"
CNPC::CNPC()
{
}


CNPC::~CNPC()
{
}

void CNPC::MoveSelectToSquare(CSquare*nextSquare)
{
	int UX, UY, DX, DY;
	int bitzeenX = nextSquare->GetX() - m_select->GetPosSquare()->GetX();
	int bitzeenY = nextSquare->GetY() - m_select->GetPosSquare()->GetY();
	switch (m_select->GetPosState())
	{
	case SELECT_POS_STATE_SQUARE:

		//

		if (bitzeenX > 0)
		{

			m_select->Left();
			return;
		}
		if (bitzeenX < 0)
		{
			m_select->Right();

			return;
		}
		if (bitzeenY < 0)
		{
			m_select->Up();

			return;
		}
		if (bitzeenY > 0)
		{
			m_select->Down();

			return;
		}

		break;
	case SELECT_POS_STATE_HAND:
		UX = nextSquare->GetX() - SELECT_UP_INITIAL_X;
		UY = nextSquare->GetY() - SELECT_UP_INITIAL_Y;
		DX = nextSquare->GetX() - SELECT_DOWN_INITIAL_X;
		DY = nextSquare->GetY() - SELECT_DOWN_INITIAL_Y;

		if (UX + UY > DX + DY)
		{
			m_select->Down();
			return;
		}
		else
		{
			m_select->Up();
			return;
		}

		break;
	default:
		break;
	}
}

void CNPC::MoveSelectToHand(HANDBORD_TYPE nextHand)
{
	switch (m_select->GetPosState())
	{
	case SELECT_POS_STATE_SQUARE:

		if (m_select->GetPosSquare()->GetX()>4)
		{
			m_select->Down();
			return;
		}
		else
		{
			m_select->Up();
			return;
		}
		break;
	case SELECT_POS_STATE_HAND:
		if (m_select->GetPosHandIndex()> nextHand)	
		{
			m_select->Left();
			return;
		}
		else
		{
			m_select->Right();
			return;

		}
		break;
	default:
		break;
	}
}
void CNPC::Setting(PLAYER_STATE state, CSquareTable * table)
{

	SetPlayerState(state);
	SetTable(table);
	D3DXVECTOR3 pos;
	D3DXQUATERNION quat;

	CGameObject* gameobject = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);
	m_select = gameobject->AddComponent<CSelect>();
	m_select->SetState(this);

	for (int i = 0; i < HANDBORD_TYPE_NUM; i++)
	{
		gameobject = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);;


		switch (this->m_playerState)
		{
		case PLAYER_STATE_01:
			pos = D3DXVECTOR3(-9.0f, 1.0f, -11.0f);

			gameobject->SetPosition(pos + (D3DXVECTOR3((i % 10)*1.8f, 0.0f, (i / 10) * -1.8f)));
			D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(0));
			gameobject->SetRotation(quat);
			gameobject->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			break;
		case PLAYER_STATE_02:
			pos = D3DXVECTOR3(-9.0f, 1.0f, 11.0f);

			gameobject->SetPosition(pos + (D3DXVECTOR3((i % 10)*1.8f, 0.0f, (i / 10) * -1.8f)));
			D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(0));
			gameobject->SetRotation(quat);
			gameobject->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

			break;
		default:
			break;
		}
		m_hand[i] = gameobject->AddComponent<CHandBord>();
		m_hand[i]->Setting(this, (HANDBORD_TYPE)i);

	}
}
void CNPC::Init()
{
	m_frame = 0;



}
void CNPC::Uninit()
{

}
void CNPC::Update()
{

	std::vector<CPlayerBase*> p;
	CManager::GetScene()->FindComponents(&p);
	if (p.size()>2)
	{
		int a = 0;
		a++;
	}
	m_frame--;
	if (m_frame<=0)
	{

		m_frame = 30;
	
	}

}
void CNPC::Draw()
{

}

void CNPC::SetUp()
{
	/*
	RoutinSelectPieceInit();
	CNpcStateSelectSquare *state = m_gameobject->AddComponent<CNpcStateSelectSquare>();
	state->SetNpc(this);
	m_state = state;
	m_state->Enter();
	*/

	{

		std::vector<CSquare*> myPieceList;
		myPieceList.reserve(80);

		std::vector<CSquare*> enemyPieceList;
		enemyPieceList.reserve(80);

		std::vector<CAction*> actionList;
		actionList.reserve(1500);

		std::vector<CActionMovePiece*> actionMovePieceList;
		actionMovePieceList.reserve(500);

		std::vector<CActionTakePiece*> actionTakePieceList;
		actionTakePieceList.reserve(500);

		std::vector<CActionUseHand*> actionUsePieceList;
		actionUsePieceList.reserve(500);

		CSquareTable* table = GetTable();

		std::vector<CPlayerBase*> playerbaseList;
		std::vector<CNPC*> npcList;
		std::vector<CPlayer*>playerList;
		CManager::GetScene()->FindComponents<CNPC>(&npcList);
		CManager::GetScene()->FindComponents<CPlayer>(&playerList);

		CPlayerBase* enemy=nullptr;

		for (CPlayer* p : playerList)
		{

			playerbaseList.push_back(p);
		}
		for (CNPC* n : npcList)
		{
			playerbaseList.push_back(n);
		}
		playerbaseList.reserve(playerList.size() + npcList.size());


		for (CPlayerBase* p : playerbaseList)
		{
			if (p->GetPlayerState() != GetPlayerState())//敵なら
			{
				enemy = p;
				break;
			}
		}

		//初期化
		//myPieceList
		//enemyPieceList

		for (int x = 0; x <= SQUARE_TABLE_MAX_X; x++)
		{
			for (int y = 0; y <= SQUARE_TABLE_MAX_Y; y++)
			{
				CSquare *s = table->GetSquare(x, y);
				if (s->GetPiece() != nullptr)
				{
					if (s->GetPiece()->GetPlayer()->GetPlayerState() == this->GetPlayerState())
					{
						myPieceList.push_back(s);
					}
					else
					{
						enemyPieceList.push_back(s);
					}
				}
			}
		}

		//Actionを生成
		{
			for (CSquare* myPieceSquare : myPieceList)
			{
				std::vector<CSquare*> sv;
				{

					myPieceSquare->GetPiece()->GetPossibleSquares(&sv);

					for (CSquare* sm : sv)//移動可能なマスの範囲を捜索
					{
						if (sm->GetPiece() != nullptr)
						{
							if (sm->GetPiece()->GetPlayer()->GetPlayerState() == this->GetPlayerState())//自分の駒
							{
								//何もできないというか本来ここには来ない
							}
							else
							{
								//敵の駒
								CActionTakePiece* take = new CActionTakePiece(ACTION_TYPE::ACTION_TYPE_TAKEPIECE);
								actionList.push_back(take);
								actionTakePieceList.push_back(take);
								take->Setting(this, sm->GetPiece()->GetPlayer(), myPieceSquare, sm);
							}
						}
						else
						{
							//駒がないマス
							CActionMovePiece* move = new CActionMovePiece(ACTION_TYPE::ACTION_TYPE_MOVEPIECE);
							actionList.push_back(move);
							actionMovePieceList.push_back(move);
							move->Setting(this, enemy, myPieceSquare, sm);
						}
					}
				}
			}
			for (int x = 0; x <= SQUARE_TABLE_MAX_X; x++)
			{
				for (int y = 0; y <= SQUARE_TABLE_MAX_Y; y++)
				{
					//駒がないなら
					if (this->GetTable()->GetSquare(x, y)->GetPiece() == nullptr)
					{
						for (int i = 0; i < HANDBORD_TYPE_NUM; i++)
						{
							if (this->GetHand((HANDBORD_TYPE)i)->GetNum() > 0)
							{
								CActionUseHand* use = new CActionUseHand(ACTION_TYPE::ACTION_TYPE_USEHAND);
								actionList.push_back(use);
								actionUsePieceList.push_back(use);
								use->Setting(this, enemy, (HANDBORD_TYPE)i, this->GetTable()->GetSquare(x, y));
							}
						}
					}
				}

			}
		}

		//評価値生成
		int maxValue = -10000;//さすがにこれいかにはならんでしょ
		bool flag = false;
		for (CAction* a : actionList)
		{
			int value = a->CreateValue();
			if (maxValue < value)
			{
				flag = true;
				maxValue = value;
			}
		}


		if (flag == true)
		{
			//評価値が最大の行動を捜索
			std::vector<CAction*>actionMaxValue;
			for (CAction* a : actionList)
			{
				if (maxValue == a->GetValue())
				{
					actionMaxValue.push_back(a);
				}
			}
			srand(time(NULL));
			int r = rand();
			switch (actionMaxValue[r%actionMaxValue.size()]->GetType())
			{
			case ACTION_TYPE::ACTION_TYPE_MOVEPIECE:
				for (CActionMovePiece* a : actionMovePieceList)
				{
					if (a->GetValue() == maxValue)
					{
						CNpcStateMovePieceNonselect*state = m_gameobject->AddComponent<CNpcStateMovePieceNonselect>();
						state->SetNpc(this);
						state->Setting(a->GetTargetSquare(), a->GetPieceSquare());
						SetState(state);
						state->Enter();


						return;
					}
				}
				break;
			case ACTION_TYPE::ACTION_TYPE_TAKEPIECE:
				for (CActionTakePiece* a : actionTakePieceList)
				{
					if (a->GetValue() == maxValue)
					{
						//このステートではなくなる
						CNpcStateTakePieceNonSelect*state = m_gameobject->AddComponent<CNpcStateTakePieceNonSelect>() ;
						state->SetNpc(this);
						state->Setting(a->GetTargetSquare(), a->GetPieceSquare());
						SetState(state);
						state->Enter();
					}
				}
				break;
			case ACTION_TYPE::ACTION_TYPE_USEHAND:
				for (CActionUseHand* a : actionUsePieceList)
				{
					if (a->GetValue() == maxValue)
					{
						//このステートではなくなる
						CNpcStateUseHandPiece*state = m_gameobject->AddComponent<CNpcStateUseHandPiece>();
						state->SetNpc(this);
						state->Setting(a->GetTarget(), a->GetHandBordType());
						SetState(state);
						state->Enter();
						return;
					}
				}
				break;
			default:
				break;
			}
		}
		else
		{
			srand(time(NULL));
			int r = rand();
			switch (actionList[r%actionList.size()]->GetType())
			{
			case ACTION_TYPE::ACTION_TYPE_MOVEPIECE:
			{
				srand(time(NULL));
				int r2 = rand();
				CNpcStateMovePieceNonselect*stateMove = m_gameobject->AddComponent<CNpcStateMovePieceNonselect>();
				stateMove->SetNpc(this);
				stateMove->Setting(actionMovePieceList[r2%actionMovePieceList.size()]->GetTargetSquare(), actionMovePieceList[r2%actionMovePieceList.size()]->GetPieceSquare());
				SetState(stateMove);
				stateMove->Enter();

			}

				break;
			case ACTION_TYPE::ACTION_TYPE_TAKEPIECE:
			{
				srand(time(NULL));
				int r2 = rand();
				CNpcStateTakePieceNonSelect*stateTake = m_gameobject->AddComponent<CNpcStateTakePieceNonSelect>();
				stateTake->SetNpc(this);
				stateTake->Setting(actionTakePieceList[r2%actionMovePieceList.size()]->GetTargetSquare(), actionTakePieceList[r2%actionMovePieceList.size()]->GetPieceSquare());
				SetState(stateTake);
				stateTake->Enter();
			}
				break;
			case ACTION_TYPE::ACTION_TYPE_USEHAND:
			{
				srand(time(NULL));
				int r2 = rand();
				CNpcStateUseHandPiece*stateUse = m_gameobject->AddComponent<CNpcStateUseHandPiece>();
				stateUse->SetNpc(this);
				stateUse->Setting(actionUsePieceList[r2%actionUsePieceList.size()]->GetTarget(), actionUsePieceList[r2%actionUsePieceList.size()]->GetHandBordType());
				SetState(stateUse);
				stateUse->Enter();

			}
			
				break;

			}

		}

	}

}
	
