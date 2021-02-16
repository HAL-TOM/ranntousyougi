#include"square.h"
#include"piece.h"
#include"player_base.h"
#include"npc.h"
#include"select.h"
#include"square_table.h"
#include"action.h"
#include"action_move_piece.h"
#include"action_take_piece.h"
#include"action_use_hand.h"
#include"scene.h"

#include"npc_state_move_piece_select.h"
#include"npc_state_move_piece_nonselect.h"
#include"npc_state_take_piece_select.h"
#include"npc_state_use_hand_piece.h"

#include "npc_state_take_piece_non_select.h"

CNpcStateTakePieceNonSelect::CNpcStateTakePieceNonSelect()
{
}


CNpcStateTakePieceNonSelect::~CNpcStateTakePieceNonSelect()
{
}

void CNpcStateTakePieceNonSelect::Init()
{
	m_type = NPC_STATE_TYPE::TAKE_NON_SELECT;
}

void CNpcStateTakePieceNonSelect::Uninit()
{

}

void CNpcStateTakePieceNonSelect::Update()
{
	if ((m_moveTarget == nullptr) || (m_selectTarget == nullptr))
	{
		//ステートを変える

		
		Reset();
		return;
	}
	if (m_selectTarget->GetPiece() == nullptr)//動かす駒がない
	{
		//ステートを変える
		Reset();
		return;
	}
	if (m_selectTarget->GetPiece()->GetPlayer()->GetPlayerState() != m_npc->GetPlayerState())//動かす駒がない
	{
		//ステートを変える
		Reset();
		return;
	}


	m_frame--;


	if (m_frame <= 0)
	{
		Action();
		m_frame = 13;
	}
}

void CNpcStateTakePieceNonSelect::Draw()
{
}

void CNpcStateTakePieceNonSelect::Setting(CSquare * move, CSquare* select)
{
	m_moveTarget = move;
	m_selectTarget = select;
}


void CNpcStateTakePieceNonSelect::StateChengeTakePieceSelect(CSquare * move)
{
	CNpcStateTakePieceSelect* next = m_gameobject->AddComponent<CNpcStateTakePieceSelect>();
	next->SetNpc(m_npc);
	next->Setting(move);
	m_npc->SetState(next);
	next->Enter();
	Exit();
	this->SetDestoroy();
}



void CNpcStateTakePieceNonSelect::Action()
{
	if ((m_npc->GetSelect()->GetPosSquare()->GetX() == m_selectTarget->GetX()) && (m_npc->GetSelect()->GetPosSquare()->GetY() == m_selectTarget->GetY()))
	{
		if (m_selectTarget->GetPiece() != nullptr)
		{
			if (m_selectTarget->GetPiece()->GetPlayer()->GetPlayerState() == m_npc->GetPlayerState())
			{
				//自分の駒
				m_npc->ChoiceSquare();
				//ステイト変更
				StateChengeTakePieceSelect(m_moveTarget);
				return;
			}
			else
			{
				Reset();
				return;
			}
		}
		else
		{
			Reset();
			return;
		}
	}
	else
	{
		m_npc->MoveSelectToSquare(m_selectTarget);//移動
		return;
	}
}

void CNpcStateTakePieceNonSelect::Enter()
{
	m_frame = 13;
}

void CNpcStateTakePieceNonSelect::Exit()
{
}
