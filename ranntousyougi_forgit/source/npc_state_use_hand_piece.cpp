#include"square.h"
#include"piece.h"
#include"player_base.h"
#include"player.h"
#include"npc.h"
#include"game_object.h"
#include"select.h"
#include"square_table.h"
#include"manager.h"
#include"scene.h"
#include"action.h"
#include"action_move_piece.h"
#include"action_take_piece.h"
#include"action_use_hand.h"
#include"npc_state_move_piece_select.h"
#include"npc_state_move_piece_nonselect.h"
#include"npc_state_take_piece_select.h"
#include"npc_state_take_piece_non_select.h"

#include "npc_state_use_hand_piece.h"

CNpcStateUseHandPiece::CNpcStateUseHandPiece()
{
}


CNpcStateUseHandPiece::~CNpcStateUseHandPiece()
{
}

void CNpcStateUseHandPiece::Init()
{
	m_type = NPC_STATE_TYPE::USE_PIECE;
}

void CNpcStateUseHandPiece::Uninit()
{
}

void CNpcStateUseHandPiece::Update()
{
	if ((m_moveTarget == nullptr))
	{
		//ステートを変える
		Reset();
		return;

	}
	
	if (m_moveTarget->GetPiece()!=nullptr)//既に駒がある
	{
		Reset();
		return;
	}
	if (m_npc->GetHand(m_selectTarget)->GetNum()<=0)
	{
		Reset();
		return;
	}
	if (m_npc->GetHand(m_selectTarget)->Judge(m_moveTarget)==false)//駒がおけるか
	{

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

void CNpcStateUseHandPiece::Draw()
{
}

void CNpcStateUseHandPiece::Setting(CSquare * move, HANDBORD_TYPE type)
{
	m_moveTarget = move;
	m_selectTarget = type;

}
void CNpcStateUseHandPiece::Action()
{
	//駒を選択できていないなら
	
	if ((m_npc->GetSelect()->GetSelectHandIndex() != m_selectTarget))
	{

		if (m_npc->GetSelect()->GetPosState() == SELECT_POS_STATE_SQUARE)
		{

			m_npc->GetSelect()->Down();
			return;

		}
		if (m_npc->GetSelect()->GetPosState() == SELECT_POS_STATE_HAND)
		{

			if (m_npc->GetSelect()->GetPosHandIndex() > m_selectTarget)
			{
				m_npc->GetSelect()->Left();
				return;


			}
			if (m_npc->GetSelect()->GetPosHandIndex() < m_selectTarget)
			{
				m_npc->GetSelect()->Right();

				return;

			}
			if (m_npc->GetSelect()->GetPosHandIndex() == m_selectTarget)
			{

				m_npc->GetSelect()->ChoiceHand();
				return;

			}
		}
	}
	else
	{
		if ((m_npc->GetSelect()->GetPosSquare()->GetX() == m_moveTarget->GetX()) && (m_npc->GetSelect()->GetPosSquare()->GetY() == m_moveTarget->GetY()))
		{

			//駒がない
			//駒を移動させる？まあいいや？
			m_npc->UseHand();
			Reset();
			return;

		}
		else
		{
			m_npc->MoveSelectToSquare(m_moveTarget);//移動
			return;
		}
	}
	


}

void CNpcStateUseHandPiece::Enter()
{
	m_frame = 13;
}

void CNpcStateUseHandPiece::Exit()
{
}
