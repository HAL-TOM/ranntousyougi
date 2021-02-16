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
	//現在のマスから駒を消す
	{
		piece->GetSquare()->SetPiece(nullptr);
	}
	//駒の種類変更
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
	//駒の移動
	
	piece->StateSet(piece->GetType(), this, next);
	piece->CoolSet();

	//エフェクト再生
	CPieceMoveEffect::Play(piece);

	D3DXVECTOR3 dif = next->GetGameObject()->GetPosition() - backS->GetGameObject()->GetPosition();

	
	//CPieceMoveLineEffect::Play(backS->GetGameObject()->GetPosition(), D3DXVec3Length(&dif), 0);
	CPieceMoveLineEffect::Play(backS->GetGameObject()->GetPosition(), 10, 1.5);
	if (rank)
	{

		//エフェクト再生
		CPieceRankUpEffect::Play(piece);
	}

	m_select->SelectNon();
}
void CPlayerBase::TakePiece(CSquare *next, CPiece *myPiece, CPiece *enemyPiece)
{
	//持ち駒を増やす
	if (enemyPiece->GetType() != PIECE_TYPE_GYOKU)
	{
		AddHand(CHandBord::HandtypeToPiecetype(enemyPiece->GetType()));
	}

	//敵の駒が選ばれているなら選ばれていない状態にする
	if (next == enemyPiece->GetPlayer()->GetSelect()->GetSelectSquare())
	{
		enemyPiece->GetPlayer()->GetSelect()->SelectNon();
	}
	//敵の駒を消す
	enemyPiece->GetGameObject()->SetDestoroy();



	//駒を動かす
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
	
	//持ち駒がある
	if (GetHand((HANDBORD_TYPE)m_select->GetSelectHandIndex())->GetNum() > 0)
	{
		//二歩対策
		if ((HANDBORD_TYPE)m_select->GetSelectHandIndex()==HANDBORD_TYPE_HUHYOU)
		{
			for (int y = 0; y <= SQUARE_TABLE_MAX_Y; y++)
			{
				CSquare* s = m_select->GetPosSquare();
				if (s->GetY()!=y)//同じ行のマス
				{
					CPiece* p = m_table->GetSquare(s->GetX(), y)->GetPiece();
					if(p!=nullptr)//駒がある
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

		//駒を作る
		CPiece*	piece = m_select->CreatePiece(CHandBord::PiecetypeToHandtype((HANDBORD_TYPE)m_select->GetSelectHandIndex()), m_select->GetPosSquare());
		//駒にクールタイムをセットする
		piece->CoolSet();

		//持ち駒を減らす
		DownHand((HANDBORD_TYPE)m_select->GetSelectHandIndex());

		CPieceUseHandEffect::Play(piece);

		//何も選んでいない状態にする
		ChoiceNon();
		return;

	}
}
