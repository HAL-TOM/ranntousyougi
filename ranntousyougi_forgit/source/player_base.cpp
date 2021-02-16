#include "player_base.h"
#include"square_table.h"
#include"square.h"
#include"scene.h"
#include"manager.h"
#include"game_object.h"
#include"select.h"
#include"piece_effect.h"
#include"pointer.h"
CPlayerBase::CPlayerBase()
{

}


CPlayerBase::~CPlayerBase()
{
}
void CPlayerBase::Setting(PLAYER_STATE state, CSquareTable* table)
{
	

}

void CPlayerBase::AddHand(HANDBORD_TYPE piece)
{
	m_hand[(int)piece]->Add(1);
	
}
void CPlayerBase::DownHand(HANDBORD_TYPE piece)
{
	m_hand[(int)piece]->Add(-1);

}
void CPlayerBase::MovePiece(CSquare *next, CPiece *piece)
{
	
	CSquare* backS = piece->GetSquare();
	
	bool rank = false;
	//���݂̃}�X����������
	{
		piece->GetSquare()->SetPiece(nullptr);
	}
	//��̎�ޕύX
	{
		switch (GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (backS->GetY() <= 2)
			{
				rank = piece->RankUp();
				break;
			}

			if (next->GetY() <= 2)
			{
				rank = piece->RankUp();
				break;
			}
			break;

		case PLAYER_STATE_02:
			if (backS->GetY() >= 6)
			{
				rank = piece->RankUp();
				break;
			}
			if (next->GetY() >= 6)
			{
				rank = piece->RankUp();
				break;
			}
			break;

		}
	}
	//��̈ړ�
	
	piece->StateSet(piece->GetType(), this, next);
	piece->CoolSet();

	//�G�t�F�N�g�Đ�
	CPieceMoveEffect::Play(piece);

	D3DXVECTOR3 dif = next->GetGameObject()->GetPosition() - backS->GetGameObject()->GetPosition();

	
	//CPieceMoveLineEffect::Play(backS->GetGameObject()->GetPosition(), D3DXVec3Length(&dif), 0);
	CPieceMoveLineEffect::Play(backS->GetGameObject()->GetPosition(), 10, 1.5);
	if (rank)
	{

		//�G�t�F�N�g�Đ�
		CPieceRankUpEffect::Play(piece);
	}

	m_select->SelectNon();
}
void CPlayerBase::TakePiece(CSquare *next, CPiece *myPiece, CPiece *enemyPiece)
{
	//������𑝂₷
	if (enemyPiece->GetType() != PIECE_TYPE_GYOKU)
	{
		AddHand(CHandBord::HandtypeToPiecetype(enemyPiece->GetType()));
	}

	//�G�̋�I�΂�Ă���Ȃ�I�΂�Ă��Ȃ���Ԃɂ���
	if (next == enemyPiece->GetPlayer()->GetSelect()->GetSelectSquare())
	{
		enemyPiece->GetPlayer()->GetSelect()->SelectNon();
	}
	//�G�̋������
	enemyPiece->GetGameObject()->SetDestoroy();



	//��𓮂���
	MovePiece(next, myPiece);
}
void CPlayerBase::ChoiceSquare()
{
	m_select->ChoiceSquare();
}
void CPlayerBase::ChoiceHand()
{
	CHandBord* hand = GetHand((HANDBORD_TYPE)m_select->GetPosHandIndex());
	if (hand->GetNum() > 0)
	{
		m_select->ChoiceHand();

	}

}

void CPlayerBase::ChoiceNon()
{
	m_select->SelectNon();
}

void CPlayerBase::UseHand()
{
	
	//���������
	if (GetHand((HANDBORD_TYPE)m_select->GetSelectHandIndex())->GetNum() > 0)
	{
		//����΍�
		if ((HANDBORD_TYPE)m_select->GetSelectHandIndex()==HANDBORD_TYPE_HUHYOU)
		{
			for (int y = 0; y <= SQUARE_TABLE_MAX_Y; y++)
			{
				CSquare* s = m_select->GetPosSquare();
				if (s->GetY()!=y)//�����s�̃}�X
				{
					CPiece* p = m_table->GetSquare(s->GetX(), y)->GetPiece();
					if(p!=nullptr)//�����
					{
						if (p->GetType()==PIECE_TYPE_HUHYOU)
						{

							if (p->GetPlayer()->GetPlayerState()==m_playerState)
							{

								return;
							}
						}
					}
				}
				
			}
			


		}

		//������
		CPiece*	piece = m_select->CreatePiece(CHandBord::PiecetypeToHandtype((HANDBORD_TYPE)m_select->GetSelectHandIndex()), m_select->GetPosSquare());
		//��ɃN�[���^�C�����Z�b�g����
		piece->CoolSet();

		//����������炷
		DownHand((HANDBORD_TYPE)m_select->GetSelectHandIndex());

		CPieceUseHandEffect::Play(piece);

		//�����I��ł��Ȃ���Ԃɂ���
		ChoiceNon();
		return;

	}
}
