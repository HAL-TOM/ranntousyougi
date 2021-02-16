#include"action_move_piece.h"
#include"action_take_piece.h"
#include"action_use_hand.h"
#include"npc_state_move_piece_nonselect.h"
#include"npc_state_take_piece_non_select.h"
#include"npc_state_use_hand_piece.h"
#include<vector>
#include<list>
#include"square.h"
#include"square_table.h"
#include"npc.h"
#include"player.h"
#include"scene.h"
#include"manager.h"
#include<algorithm>
#include<iostream>
#include<fstream>
#include<string>
#include <direct.h>
#include <sys/stat.h>
#include "npc_state.h"
int CNpcState::m_fileNumber = 0;


void CNpcState::Reset()
{
	std::vector<CSquare*> myPieceList;
	myPieceList.reserve(80);

	std::vector<CSquare*> enemyPieceList;
	enemyPieceList.reserve(80);

	//���ςT�O�ق�
	std::vector<CAction*> actionList;
	actionList.reserve(200);

	std::vector<CActionMovePiece*> actionMovePieceList;
	actionMovePieceList.reserve(100);

	std::vector<CActionTakePiece*> actionTakePieceList;
	actionTakePieceList.reserve(100);

	std::vector<CActionUseHand*> actionUsePieceList;
	actionUsePieceList.reserve(100);

	CSquareTable* table = m_npc->GetTable();

	std::vector<CPlayerBase*> playerbaseList;
	std::vector<CNPC*> npcList;
	std::vector<CPlayer*>playerList;
	CManager::GetScene()->FindComponents<CNPC>(&npcList);
	CManager::GetScene()->FindComponents<CPlayer>(&playerList);

	CPlayerBase* enemy;


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
		if (p->GetPlayerState() != m_npc->GetPlayerState())//�G�Ȃ�
		{
			enemy = p;
			break;
		}
	}

	//������
	//myPieceList
	//enemyPieceList
	{
		for (int x = 0; x <= SQUARE_TABLE_MAX_X; ++x)
		{
			for (int y = 0; y <= SQUARE_TABLE_MAX_Y; ++y)
			{
				CSquare *s = table->GetSquare(x, y);
				if (s->GetPiece() != nullptr)
				{
					if (s->GetPiece()->GetPlayer()->GetPlayerState() == this->m_npc->GetPlayerState())
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
	}



	//Action�𐶐�
	{
		for (CSquare* myPieceSquare : myPieceList)
		{
			if (myPieceSquare->GetPiece()->GetCool() == false)
			{

				std::vector<CSquare*> sv;
				sv.reserve(20);
				myPieceSquare->GetPiece()->GetPossibleSquares(&sv);

				for (CSquare* sm : sv)//�ړ��\�ȃ}�X�͈̔͂�{��
				{
					if (sm->GetPiece() != nullptr)
					{
						if (sm->GetPiece()->GetPlayer()->GetPlayerState() == this->m_npc->GetPlayerState())//�����̋�
						{
							//�����ł��Ȃ��Ƃ������{�������ɂ͗��Ȃ�
						}
						else
						{
							//�G�̋�
							CActionTakePiece* take = new CActionTakePiece(ACTION_TYPE::ACTION_TYPE_TAKEPIECE);
							actionList.push_back(take);
							actionTakePieceList.push_back(take);
							take->Setting(m_npc, enemy, myPieceSquare, sm);
						}
					}
					else
					{
						//��Ȃ��}�X

						CActionMovePiece* move = new CActionMovePiece(ACTION_TYPE::ACTION_TYPE_MOVEPIECE);
						actionList.push_back(move);
						actionMovePieceList.push_back(move);
						move->Setting(m_npc, enemy, myPieceSquare, sm);
					}
				}
			}


		}
		for (int x = 0; x < SQUARE_TABLE_MAX_X + 1; x++)
		{
			for (int y = 0; y < SQUARE_TABLE_MAX_Y + 1; y++)
			{
				//��Ȃ��Ȃ�
				if (m_npc->GetTable()->GetSquare(x, y)->GetPiece() == nullptr)
				{
					for (int i = 0; i < HANDBORD_TYPE_NUM; i++)
					{
						if (m_npc->GetHand((HANDBORD_TYPE)i)->GetNum() > 0)
						{
							if (m_npc->GetHand((HANDBORD_TYPE)i)->Judge(m_npc->GetTable()->GetSquare(x, y)))
							{
								CActionUseHand* use = new CActionUseHand(ACTION_TYPE::ACTION_TYPE_USEHAND);
								actionList.push_back(use);
								actionUsePieceList.push_back(use);
								use->Setting(m_npc, enemy, (HANDBORD_TYPE)i, m_npc->GetTable()->GetSquare(x, y));
							}
						}
					}
				}
			}

		}
	}

	//�]���l����
	for (CAction* a : actionList)
	{
		int value = a->CreateValue();
		
	}
	//�]���l���\�[�g�i�����_���j
	std::sort(actionList.begin(), actionList.end(),
		[](CAction* const& left, CAction* const& right)
		{
			return left->GetValue() > right->GetValue();
		});

	//�]���l���o��
	struct stat statBuf;
	std::string fname = "Out";
	//Out�t�H���_�̑��݊m�F
	if (stat(fname.c_str(), &statBuf) == 0)
	{
		std::ofstream outputfile("Out\\text" + std::to_string(m_fileNumber) + ".txt");
		for (CAction* a : actionList)
		{
			//�A�N�V�������̕]���l���o��
			outputfile << a->GetValue() << std::endl;
		}
		outputfile.close();

		m_fileNumber++;
	}

	//�]���l���ő�̃A�N�V���������s����X�e�[�g�ɑJ�ڂ���
	switch (actionList.front()->GetType())//�擪���]���l���ő�
	{
	case ACTION_TYPE::ACTION_TYPE_MOVEPIECE:
		
		for (CActionMovePiece* a : actionMovePieceList)
		{
			if (a->GetValue() == actionList.front()->GetValue())
			{
				StateChengeMovePieceNonSelect(a->GetTargetSquare(), a->GetPieceSquare());
				return;
			}
		}
		break;
	
	case ACTION_TYPE::ACTION_TYPE_TAKEPIECE:				
		for (CActionTakePiece* a : actionTakePieceList)
		{
			if (a->GetValue() == actionList.front()->GetValue())
			{
				//���̃X�e�[�g�ł͂Ȃ��Ȃ�
				StateChengeTakePieceNonSelect(a->GetTargetSquare(), a->GetPieceSquare());
				return;
			}
		}
		break;

	case ACTION_TYPE::ACTION_TYPE_USEHAND:		
		for (CActionUseHand* a : actionUsePieceList)
		{
			if (a->GetValue() == actionList.front()->GetValue())
			{
				StateChengeUseHandPiece(a->GetTarget(), a->GetHandBordType());
				return;
			}
		}
		break;
	default:
		break;
	}

}

void CNpcState::StateChengeMovePieceNonSelect(CSquare* move, CSquare* select)
{
	CNpcStateMovePieceNonselect* next = m_gameobject->AddComponent<CNpcStateMovePieceNonselect>();
	next->SetNpc(m_npc);
	next->Setting(move,select);
	m_npc->SetState(next);
	next->Enter();
	Exit();
	this->SetDestoroy();
}

void CNpcState::StateChengeTakePieceNonSelect(CSquare * move, CSquare * select)
{
	CNpcStateTakePieceNonSelect* next = m_gameobject->AddComponent<CNpcStateTakePieceNonSelect>();
	next->SetNpc(m_npc);
	next->Setting(move, select);
	m_npc->SetState(next);
	next->Enter();
	Exit();
	this->SetDestoroy();

}

void CNpcState::StateChengeUseHandPiece(CSquare * move, HANDBORD_TYPE type)
{
	CNpcStateUseHandPiece* next = m_gameobject->AddComponent<CNpcStateUseHandPiece>();
	next->SetNpc(m_npc);
	next->Setting(move, type);
	m_npc->SetState(next);
	next->Enter();
	Exit();
	this->SetDestoroy();
}
