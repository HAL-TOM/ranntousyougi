#include"player_base.h"
#include"square_table.h"
#include"square.h"
#include"piece.h"
#include"handbord.h"
#include"aspect.h"
#include<list>
#include "action_use_hand.h"

void CActionUseHand::Setting(CPlayerBase * player, CPlayerBase * enemy, HANDBORD_TYPE handbordType, CSquare * targetSquare)
{
	m_player = player;
	m_enemy = enemy;
	m_handbordType = handbordType;//使う駒
	m_targetSquare = targetSquare;
}

int CActionUseHand::CreateValue()
{
	int ret = 0;//返り値
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

	//持ち駒を減らす
	hand1[m_handbordType]->Add(-1);
	//駒を作る
	CPiece* piece = CPiece::CreatePiece(CHandBord::PiecetypeToHandtype(m_handbordType), m_player, table->GetSquare(m_targetSquare->GetX(), m_targetSquare->GetY()));
	pieceList.push_back(piece);
	//持ち駒を使う
	table->GetSquare(m_targetSquare->GetX(), m_targetSquare->GetY())->SetPiece(piece);
	
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
		for (int y = 0; y < SQUARE_TABLE_MAX_Y + 1; y++)
		{
			for (int x = 0; x < SQUARE_TABLE_MAX_X + 1; x++)
			{
				delete square[x][y];
			}
		}
		for (CPiece* p:pieceList)
		{
			delete p;
		}
		for (int i = 0; i < HANDBORD_TYPE_NUM; i++)
		{
			delete hand1[i];
			delete hand2[i];
			delete num1[i];
			delete num2[i];
		}
	}
	m_value = ret;
	return ret;
}
