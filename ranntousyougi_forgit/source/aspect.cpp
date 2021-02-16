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
	int MovePossibleSquareNum = 0;//�ړ��\�}�X��
	int TakePieceSquare = 0;//��邱�Ƃ��o�����̉��l�̍��v
	int HaveSquarePiece = 0;//�Տ�̋�̉��l�̍��v
	int HaveHandPiece = 0;//������̋�̉��l�̍��v

	//�ć@������Ԃ�]������
	//�y�v�f�z���̋�̈ړ���ɐ���邩�ǂ���
	//��������Ȃ���Ԃ̂ق������l�������Ȃ�\��������
	//���Âɐ���̂ł͂Ȃ��A�ƍl����Ƃ����������������Ȃ�
	//�G�������󋵂����ЂƂ��Ĕ��肵�Ă���邩������Ȃ�
	
	//�ćA�ʂ̍d��
	//�y�v�f�z�s��
	//������ɑ΂���]�����󔖂Ȃ̂ŋ���������
	//���ׂĂ̋�����͓̂�����߂��߂ċʂ͎�肽��


	int GetValue() { return (MovePossibleSquareNum * 5) + (TakePieceSquare * 10) + (HaveSquarePiece * 11) + (HaveHandPiece * 12); }//�����̕]��
	int GetValue2() { return (MovePossibleSquareNum * 5) + (TakePieceSquare * 12) + (HaveSquarePiece * 11) + (HaveHandPiece * 10); }//�G�̕]��

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
				if (piece->GetPlayer()->GetPlayerState()==m_player01->GetPlayerState())//�����̋�
				{

					me.HaveSquarePiece += CPiece::GetValue(piece->GetType());//��l������
					myPiece.push_back(piece);
				}
				else
				{
					enemy.HaveSquarePiece+= CPiece::GetValue(piece->GetType());//��l������
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
				if (p->JudgeCoolThrough(s)==true)//�i�߂�(�N�[���^�C�������ǂ������l�����Ȃ�)
				{
					if (s->GetPiece()!=nullptr)
					{

						if (s->GetPiece()->GetPlayer()->GetPlayerState() == m_player02->GetPlayerState())//�G�̋�
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
				
				if (p->JudgeCoolThrough(s) == true)//�i�߂�(�N�[���^�C�������ǂ������l�����Ȃ�)
				{
					if (s->GetPiece() != nullptr)
					{
						if (s->GetPiece()->GetPlayer()->GetPlayerState() == m_player01->GetPlayerState())//�����̋�
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

	//������̉��l
	for (int i = 0; i < HANDBORD_TYPE_NUM; i++)
	{
		me.HaveHandPiece += m_hand01[i]->GetNum()*CPiece::GetValue(CHandBord::PiecetypeToHandtype(m_hand01[i]->GetType()));
		enemy.HaveHandPiece += m_hand02[i]->GetNum()*CPiece::GetValue(CHandBord::PiecetypeToHandtype(m_hand02[i]->GetType()));
	}

	return me.GetValue() - enemy.GetValue2();
}
