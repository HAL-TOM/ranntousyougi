#include"piece.h"
#include"handbord.h"
#include"square.h"
#include "aspect.h"
#include"game_object.h"
#include"handbord.h"
#include"square_table.h"
#include"player_base.h"
#include<list>
#include"action_take_piece.h"
#include"action_move_piece.h"
#include"action_use_hand.h"
struct	Evaluation
{
	int MovePossibleSquareNum = 0;//移動可能マス数
	int TakePieceSquare = 0;//取ることが出来る駒の価値の合計
	int HaveSquarePiece = 0;//盤上の駒の価値の合計
	int HaveHandPiece = 0;//持ち駒の駒の価値の合計

	//案①成れる状態を評価する
	//【要素】次の駒の移動後に成れるかどうか
	//成るよりもなれる状態のほうが価値が高くなる可能性がある
	//無暗に成るのではない、と考えるとそれもいいかもしれない
	//敵が成れる状況を脅威として判定してくれるかもしれない
	
	//案②玉の硬さ
	//【要素】不明
	//現状守りに対する評価が希薄なので強化したい
	//すべての駒を守るのは難しいためせめて玉は守りたい


	int GetValue() { return (MovePossibleSquareNum * 5) + (TakePieceSquare * 10) + (HaveSquarePiece * 11) + (HaveHandPiece * 12); }//自分の評価
	int GetValue2() { return (MovePossibleSquareNum * 5) + (TakePieceSquare * 12) + (HaveSquarePiece * 11) + (HaveHandPiece * 10); }//敵の評価

};



int CAspect::GetValue()
{
	Evaluation me;
	Evaluation enemy;
	std::list<CPiece*> myPiece;
	std::list<CPiece*> enemyPiece;

	for (int x = 0; x <= SQUARE_TABLE_MAX_X; ++x)
	{
		for(int y=0;y<=SQUARE_TABLE_MAX_Y;++y)
		{
			CPiece* piece = m_table->GetSquare(x, y)->GetPiece();
			if (piece !=nullptr)
			{
				if (piece->GetPlayer()->GetPlayerState()==m_player01->GetPlayerState())//自分の駒
				{

					me.HaveSquarePiece += CPiece::GetValue(piece->GetType());//駒価値分足す
					myPiece.push_back(piece);
				}
				else
				{
					enemy.HaveSquarePiece+= CPiece::GetValue(piece->GetType());//駒価値分足す
					enemyPiece.push_back(piece);
				}
			}
		}
	}
	

	for (int x = 0; x <= SQUARE_TABLE_MAX_X ; ++x)
	{
		for (int y = 0; y <= SQUARE_TABLE_MAX_Y ; ++y)
		{
			CSquare* s = m_table->GetSquare(x, y);
			for (CPiece* p:myPiece)
			{
				if (p->JudgeCoolThrough(s)==true)//進める(クールタイム中かどうかを考慮しない)
				{
					if (s->GetPiece()!=nullptr)
					{

						if (s->GetPiece()->GetPlayer()->GetPlayerState() == m_player02->GetPlayerState())//敵の駒
						{
							me.TakePieceSquare += CPiece::GetValue(s->GetPiece()->GetType());
						}
					}
					me.MovePossibleSquareNum++;
					break;
				}
			}
			for (CPiece* p : enemyPiece)
			{
				
				if (p->JudgeCoolThrough(s) == true)//進める(クールタイム中かどうかを考慮しない)
				{
					if (s->GetPiece() != nullptr)
					{
						if (s->GetPiece()->GetPlayer()->GetPlayerState() == m_player01->GetPlayerState())//自分の駒
						{
							enemy.TakePieceSquare += CPiece::GetValue(s->GetPiece()->GetType());
						}
					}

					enemy.MovePossibleSquareNum++;
					break;
				}
			}
		}
	}

	//持ち駒の価値
	for (int i = 0; i < HANDBORD_TYPE_NUM; i++)
	{
		me.HaveHandPiece += m_hand01[i]->GetNum()*CPiece::GetValue(CHandBord::PiecetypeToHandtype(m_hand01[i]->GetType()));
		enemy.HaveHandPiece += m_hand02[i]->GetNum()*CPiece::GetValue(CHandBord::PiecetypeToHandtype(m_hand02[i]->GetType()));
	}

	return me.GetValue() - enemy.GetValue2();
}
