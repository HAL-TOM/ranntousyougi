#include"player_base.h"
#include"square_table.h"
#include"square.h"
#include"piece.h"
#include"handbord.h"
#include"aspect.h"
#include<list>

#include "action_take_piece.h"

void CActionTakePiece::Setting(CPlayerBase * player, CPlayerBase * enemy, CSquare * pieceSquare, CSquare * targetSquare)
{
	m_player = player;
	m_enemy = enemy;
	m_pieceSquare = pieceSquare;
	m_targetSquare = targetSquare;
}

int CActionTakePiece::CreateValue()
{

	int ret = 0;
	CSquareTable * originalTable = m_player->GetTable();
	CSquareTable *table = new CSquareTable();
	CSquare* square[SQUARE_TABLE_MAX_X + 1][SQUARE_TABLE_MAX_Y + 1];
	std::list<CPiece*> pieceList;
	CHandBord* hand1[HANDBORD_TYPE_NUM];
	CHandBord* hand2[HANDBORD_TYPE_NUM];
	CNumber* num1[HANDBORD_TYPE_NUM];
	CNumber* num2[HANDBORD_TYPE_NUM];
	CAspect* aspect;

	//盤面のデータ生成
	{
		for (int y = 0; y < SQUARE_TABLE_MAX_Y + 1; y++)
		{
			for (int x = 0; x < SQUARE_TABLE_MAX_X + 1; x++)
			{
				square[x][y] = new CSquare();
				square[x][y]->SetTable(table);
				square[x][y]->SetXY(x, y);
				if (originalTable->GetSquare(x, y)->GetPiece() != nullptr)
				{
					CPiece* piece = new CPiece(*originalTable->GetSquare(x, y)->GetPiece());
					square[x][y]->SetPiece(piece);
					pieceList.push_back(piece);
				}
				table->SetSquare(x, y, square[x][y]);
			}
		}

		for (int i = 0; i < HANDBORD_TYPE_NUM; i++)
		{
			hand1[i] = new CHandBord(*m_player->GetHand((HANDBORD_TYPE)i));
			hand2[i] = new CHandBord(*m_enemy->GetHand((HANDBORD_TYPE)i));
			num1[i] = new CNumber();
			num2[i] = new CNumber();
			num1[i]->SetNum(hand1[i]->GetNum());
			num2[i]->SetNum(hand2[i]->GetNum());
			hand1[i]->SetNumClass(num1[i]);
			hand2[i]->SetNumClass(num2[i]);

		}
	}

	//アクションの結果を反映させる
	{
		//持ち駒を増やす
		if (m_targetSquare->GetPiece()->GetType() != PIECE_TYPE_GYOKU)//玉でないなら
		{
			hand1[CHandBord::HandtypeToPiecetype(m_targetSquare->GetPiece()->GetType())] ->Add(1);
		}
		//駒の移動
		{
			CPiece* piece = table->GetSquare(m_pieceSquare->GetX(), m_pieceSquare->GetY())->GetPiece();
			CSquare* target = table->GetSquare(m_targetSquare->GetX(), m_targetSquare->GetY());
	
			//駒の種類変更
			{
				switch (m_player->GetPlayerState())
				{
				case PLAYER_STATE_01:
					if (m_pieceSquare->GetY() <= 2)
					{
						piece->RankUp();
						break;
					}

					if (target->GetY() <= 2)
					{
						piece->RankUp();
						break;
					}
					break;

				case PLAYER_STATE_02:
					if (m_pieceSquare->GetY() >= 6)
					{
						piece->RankUp();
						break;
					}
					if (target->GetY() >= 6)
					{
						piece->RankUp();
						break;
					}
					break;

				}
			}
			//駒の移動			
			piece->SetSquareUnCmoponent(table->GetSquare(m_targetSquare->GetX(), m_targetSquare->GetY()));
			piece->GetSquare()->SetPiece(nullptr);
		}
	}

	//Aspect
	{
		aspect = new CAspect();
		for (int i = 0; i < HANDBORD_TYPE_NUM; i++)
		{
			aspect->SetHand01((HANDBORD_TYPE)i, hand1[i]);
			aspect->SetHand02((HANDBORD_TYPE)i, hand2[i]);
		}
		aspect->SetPlayer01(m_player);
		aspect->SetPlayer02(m_enemy);
		aspect->SetTable(table);
		ret = aspect->GetValue();
	}
	{
		//インスタント削除
		delete table;
		for (int y = 0; y < SQUARE_TABLE_MAX_Y + 1; y++)
		{
			for (int x = 0; x < SQUARE_TABLE_MAX_X + 1; x++)
			{
				delete square[x][y];
			}
		}
		for (int i = 0; i < HANDBORD_TYPE_NUM; i++)
		{
			delete hand1[i];
			delete hand2[i];
			delete num1[i];
			delete num2[i];
		}
		for (CPiece* p : pieceList)
		{
			delete p;
		}
		delete aspect;
	}
	m_value = ret;
	return ret;
}
