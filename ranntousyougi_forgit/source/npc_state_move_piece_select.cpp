
#include"square.h"
#include"piece.h"
#include"player_base.h"
#include"npc.h"
#include"player.h"
#include"select.h"
#include"square_table.h"
#include"action_move_piece.h"
#include"action_take_piece.h"
#include"action_use_hand.h"
#include"npc_state_move_piece_select.h"
#include"npc_state_move_piece_nonselect.h"
#include"npc_state_take_piece_select.h"
#include"npc_state_take_piece_non_select.h"
#include "npc_state_use_hand_piece.h"
#include"scene.h"
#include"manager.h"




CNpcStateMovePieceSelect::CNpcStateMovePieceSelect()
{
}


CNpcStateMovePieceSelect::~CNpcStateMovePieceSelect()
{

}

void CNpcStateMovePieceSelect::Init()
{

	m_type = NPC_STATE_TYPE::MOVE_SELECT;
}

void CNpcStateMovePieceSelect::Uninit()
{
}

void CNpcStateMovePieceSelect::Update()
{

	if (m_moveTarget == nullptr)
	{
		//ステートを変える、どうやって変えようか...取り敢えずリセット
		Reset();
		return;
		
	}
	if (m_npc->GetSelect()->GetSelectSquare() == nullptr)//マスを選択していない
	{
		Reset();
		return;
	}
	if (m_npc->GetSelect()->GetSelectSquare()->GetPiece()==nullptr)//動かす駒がない
	{
		Reset();
		return;
	}
	if (m_npc->GetSelect()->GetSelectSquare()->GetPiece()->GetPlayer()->GetPlayerState() !=m_npc->GetPlayerState())//動かす駒が取られた？
	{
		Reset();
		return;
	}
	if (m_npc->GetSelect()->GetSelectSquare()->GetPiece()->Judge(m_moveTarget) == false)
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

void CNpcStateMovePieceSelect::Draw()
{
}

void CNpcStateMovePieceSelect::Setting(CSquare * move)
{
	m_moveTarget = move;
}

void CNpcStateMovePieceSelect::Action()
{
	
	if ((m_npc->GetSelect()->GetPosSquare()->GetX()== m_moveTarget->GetX()) && (m_npc->GetSelect()->GetPosSquare()->GetY() == m_moveTarget->GetY()))
	{
		if (m_npc->GetSelect()->GetSelectSquare()->GetPiece()->GetMovePossible())
		{

			if (m_moveTarget->GetPiece() != nullptr)
			{
				//駒がある
				if (m_moveTarget->GetPiece()->GetPlayer()->GetPlayerState() != m_npc->GetPlayerState())//敵の駒
				{
					//予定変更、駒とっちゃえ
					m_npc->TakePiece(m_npc->GetSelect()->GetPosSquare(), m_npc->GetSelect()->GetSelectSquare()->GetPiece(), m_npc->GetSelect()->GetPosSquare()->GetPiece());
					Reset();
					return;
				}
				else//自分の駒
				{
					//ここには来ないはず・エラーは出さないYO
					//ステイト変更
					Reset();
					return;
				}
			}
			else
			{
				//駒がない
				//駒を移動させる
				m_npc->MovePiece(m_npc->GetSelect()->GetPosSquare(), m_npc->GetSelect()->GetSelectSquare()->GetPiece());
				Reset();
				return;
			}
		}
	}
	else
	{
		m_npc->MoveSelectToSquare(m_moveTarget);//移動
		return;
	}
}

void CNpcStateMovePieceSelect::Enter()
{
	m_frame = 13;
}

void CNpcStateMovePieceSelect::Exit()
{
}
