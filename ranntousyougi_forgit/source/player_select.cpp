#include"manager.h"
#include"scene.h"
#include"game_object.h"
#include"piece.h"
#include"square.h"
#include"handbord.h"
#include"effecseer.h"
#include"player_base.h"
#include "player_select.h"
#include"square_table.h"
#include"input.h"
void CPlayerSelect::ChoiceSquare()
{

	m_selectSquare = m_posSquare;
	m_selectHandIndex = 0;
	m_selectState = SELECT_STATE_EXIST_SQUARE;
	CreatePointer();


	//DestoroyEfect();
	
	
	//CreateEffect();

}

void CPlayerSelect::SelectNon()
{
	m_selectSquare = nullptr;
	m_selectHandIndex = 0;
	m_selectState = SELECT_STATE_NON;
	DestroyPointer();
	DestoroyEfect();

	return;
}

void CPlayerSelect::Update()
{


	if (m_selectSquare == nullptr)
	{
		DestoroyEfect();
	}
	else
	{
		CreateEffect();
	}
}

void CPlayerSelect::CreateEffect()
{

	
	CSquareTable* table = m_player->GetTable();
	std::vector<CSquare*> squareList;

	m_selectSquare->GetPiece()->GetPossibleSquares(&squareList);

	/*
	for (CSquare* s:squareList)
	{
		if (s->GetEffect()->GetPlayFlag() == false)//‚Ü‚¾Ä¶‚¢‚Ä‚¢‚È‚¢‚È‚ç
		{
			s->EffectPlay();
		}
		
	}
	for (int x = 0; x <= SQUARE_TABLE_MAX_X; x++)
	{
		for (int y = 0; y <= SQUARE_TABLE_MAX_Y; y++)
		{
			CSquare* s = table->GetSquare(x, y);
			if (s->GetEffect()->GetPlayFlag() == true)
			{
				bool f = true;
				for (CSquare* sl : squareList)
				{
					if ((x==sl->GetX())&&(y==sl->GetY()))
					{
						f = false;
					}

				}
				if (f == true)
				{
					s->EffectStop();
				}

			}
		}
	}
	*/
	
	for (int x = 0; x <= SQUARE_TABLE_MAX_X; x++)
	{
		for (int y = 0; y <= SQUARE_TABLE_MAX_Y; y++)
		{
			CSquare* s = table->GetSquare(x, y);
			if (m_selectSquare->GetPiece()->Judge(s)==true)//‚»‚Ìƒ}ƒX‚Éi‚ß‚é
			{
				if (s->GetEffect()->GetPlayFlag()==false)//‚Ü‚¾Ä¶‚¢‚Ä‚¢‚È‚¢‚È‚ç
				{
					s->EffectPlay();
				}

			}
			else
			{
				s->EffectStop();
			}
		}
	}
	
	
}

void CPlayerSelect::DestoroyEfect()
{
	
	CSquareTable* table = CManager::GetScene()->FindComponent<CSquareTable>();
	for (int x = 0; x <= SQUARE_TABLE_MAX_X; x++)
	{
		for (int y = 0; y <= SQUARE_TABLE_MAX_Y; y++)
		{
			table->GetSquare(x, y)->EffectStop();
		}
	}
}
