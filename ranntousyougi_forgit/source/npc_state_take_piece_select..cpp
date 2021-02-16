#include"square.h"
#include"piece.h"
#include"player_base.h"
#include"npc.h"
#include"player.h"
#include"select.h"
#include"square_table.h"
#include"action.h"
#include"action_move_piece.h"
#include"action_take_piece.h"
#include"action_use_hand.h"
#include"scene.h"
#include"npc_state_move_piece_select.h"
#include"npc_state_move_piece_nonselect.h"
#include"npc_state_take_piece_non_select.h"
#include"npc_state_use_hand_piece.h"
#include "npc_state_take_piece_select.h"



CNpcStateTakePieceSelect::CNpcStateTakePieceSelect()
{
}


CNpcStateTakePieceSelect::~CNpcStateTakePieceSelect()
{
}

void CNpcStateTakePieceSelect::Init()
{
	m_type = NPC_STATE_TYPE::TAKE_SELECT;
}

void CNpcStateTakePieceSelect::Uninit()
{
}

void CNpcStateTakePieceSelect::Update()
{
	{
		if ((m_moveTarget == nullptr))
		{
			//�X�e�[�g��ς���
			Reset();
			return;

		}
		
		if (m_npc->GetSelect()->GetSelectSquare() == nullptr)//�}�X��I�����Ă��Ȃ�
		{
			Reset();
			return;
		}
		if (m_npc->GetSelect()->GetSelectSquare()->GetPiece() == nullptr)//��������Ȃ�(���Ԃ���ꂽ)
		{
			//�X�e�[�g��ς���
			Reset();
			return;
		}
		if (m_npc->GetSelect()->GetSelectSquare()->GetPiece()->GetPlayer()->GetPlayerState() != m_npc->GetPlayerState())//��������G�̋�ɂȂ��Ă�i���Ԃ���ꂽ�j
		{
			//�X�e�[�g��ς���
			Reset();
			return;
		}
		if (m_npc->GetSelect()->GetSelectSquare()->GetPiece()->Judge(m_moveTarget)==false)
		{

			//�X�e�[�g��ς���
			Reset();
			return;
		}

	}
	m_frame--;


	if (m_frame <= 0)
	{
		Action();
		m_frame = 13;
	}
}

void CNpcStateTakePieceSelect::Draw()
{
}

void CNpcStateTakePieceSelect::Setting(CSquare * move)
{
	m_moveTarget = move;
}
void CNpcStateTakePieceSelect::Action()
{
	if ((m_npc->GetSelect()->GetPosSquare()->GetX() == m_moveTarget->GetX()) && (m_npc->GetSelect()->GetPosSquare()->GetY() == m_moveTarget->GetY()))
	{

		if (m_npc->GetSelect()->GetSelectSquare()->GetPiece()->Judge(m_moveTarget))
		{
			if (m_moveTarget->GetPiece() != nullptr)
			{
				//�����
				if (m_moveTarget->GetPiece()->GetPlayer()->GetPlayerState() != m_npc->GetPlayerState())//�G�̋�
				{

					//�\��ύX�A��Ƃ����Ⴆ
					m_npc->TakePiece(m_npc->GetSelect()->GetPosSquare(), m_npc->GetSelect()->GetSelectSquare()->GetPiece(), m_npc->GetSelect()->GetPosSquare()->GetPiece());
					Reset();
					return;
				}
				else//�����̋�
				{
					//�����ɂ͗��Ȃ��͂��E�G���[�͏o���Ȃ�YO
					//�X�e�C�g�ύX
					Reset();
					return;
				}
			}
			else
			{
				//��Ȃ�
				//����ړ�������H�܂�������H
				m_npc->MovePiece(m_npc->GetSelect()->GetPosSquare(), m_npc->GetSelect()->GetSelectSquare()->GetPiece());
				Reset();
				return;
			}
		}
		else
		{
			
			if (m_moveTarget->GetPiece()!=nullptr)
			{
				Reset();
				return;
			}
			return;
		}
		
		
	}
	else
	{
		m_npc->MoveSelectToSquare(m_moveTarget);//�ړ�
		return;
	}
}

void CNpcStateTakePieceSelect::Enter()
{
	m_frame = 13;

}

void CNpcStateTakePieceSelect::Exit()
{

}
