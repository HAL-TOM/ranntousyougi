#include<minmax.h>
#include"model_drawer.h"
#include"game_object.h"
#include"player_base.h"
#include"square.h"
#include"square_table.h"
#include"piece_drawer.h"
#include"scene.h"
#include"piece_cool_timer.h"
#include"sound.h"
#include<vector>
#include"piece_effect.h"

#include "piece.h"

CModel* CPiece::m_model[PIECE_TYPE_NUM];
CSound* CPiece::m_moveSe;

CPiece::CPiece()
{
}


CPiece::~CPiece()
{
}


void CPiece::Load()
{
	m_model[PIECE_TYPE::PIECE_TYPE_HUHYOU] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_NARIKIN] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_KYOUSYA] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_NARIKYOU] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_KEIMA] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_NARIKEI] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_GINN] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_NARIGINN] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_KINN] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_KAKU] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_UMA] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_HISYA] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_RYUUOU] = new CModel();
	m_model[PIECE_TYPE::PIECE_TYPE_GYOKU] = new CModel();

	m_model[PIECE_TYPE::PIECE_TYPE_HUHYOU]->Load("asset\\model\\koma\\huhyou\\huhyou.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_NARIKIN]->Load("asset\\model\\koma\\tokinn\\tokinn.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_KYOUSYA]->Load("asset\\model\\koma\\kyousya\\kyousya.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_NARIKYOU]->Load("asset\\model\\koma\\narikyou\\narikyou.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_KEIMA]->Load("asset\\model\\koma\\keima\\keima.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_NARIKEI]->Load("asset\\model\\koma\\narikei\\narikei.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_GINN]->Load("asset\\model\\koma\\ginn\\ginn.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_NARIGINN]->Load("asset\\model\\koma\\nariginn\\nariginn.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_KINN]->Load("asset\\model\\koma\\kinn\\kinn.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_KAKU]->Load("asset\\model\\koma\\kaku\\kaku.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_UMA]->Load("asset\\model\\koma\\uma\\uma.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_HISYA]->Load("asset\\model\\koma\\hisya\\hisya.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_RYUUOU]->Load("asset\\model\\koma\\ryuu\\ryuu.obj");
	m_model[PIECE_TYPE::PIECE_TYPE_GYOKU]->Load("asset\\model\\koma\\gyoku\\gyoku.obj");

	CPieceEffect::Load();
}


void CPiece::UnLoad()
{
	m_model[PIECE_TYPE::PIECE_TYPE_HUHYOU]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_HUHYOU];
	
	m_model[PIECE_TYPE::PIECE_TYPE_NARIKIN]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_NARIKIN];
	
	m_model[PIECE_TYPE::PIECE_TYPE_KYOUSYA]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_KYOUSYA];
	
	m_model[PIECE_TYPE::PIECE_TYPE_NARIKYOU]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_NARIKYOU];
	
	m_model[PIECE_TYPE::PIECE_TYPE_KEIMA]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_KEIMA];
	
	m_model[PIECE_TYPE::PIECE_TYPE_NARIKEI]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_NARIKEI];
	
	m_model[PIECE_TYPE::PIECE_TYPE_GINN]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_GINN];
	
	m_model[PIECE_TYPE::PIECE_TYPE_NARIGINN]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_NARIGINN];
	
	m_model[PIECE_TYPE::PIECE_TYPE_KINN]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_KINN];
	
	m_model[PIECE_TYPE::PIECE_TYPE_KAKU]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_KAKU];
	
	m_model[PIECE_TYPE::PIECE_TYPE_UMA]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_UMA];
	
	m_model[PIECE_TYPE::PIECE_TYPE_HISYA]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_HISYA];
	
	m_model[PIECE_TYPE::PIECE_TYPE_RYUUOU]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_RYUUOU];
	
	m_model[PIECE_TYPE::PIECE_TYPE_GYOKU]->Unload();
	delete m_model[PIECE_TYPE::PIECE_TYPE_GYOKU];

	CPieceEffect::UnLoad();

}

CPiece * CPiece::CreatePiece(PIECE_TYPE state, CPlayerBase * player, CSquare * square)
{
	CPiece* piece = new CPiece();
	piece->SetSquareUnCmoponent(square);
	piece->SetPlayer(player);
	piece->SetType(state);
	return piece;
}

bool CPiece::Judge(CSquare* square)
{

	if (m_cool)
	{
		return false;
	}
	int bitweenX = square->GetX() - this->m_square->GetX();
	int bitweenY = square->GetY() - this->m_square->GetY();
	CSquare* s;
	CSquareTable* squareTable = CManager::GetScene()->FindComponent<CSquareTable>();

	switch (m_pieceState)
	{
	case PIECE_TYPE::PIECE_TYPE_HUHYOU:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX ==0)&&(bitweenY ==-1))
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIKIN:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == 1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == -1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_KYOUSYA:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (bitweenX==0)
			{	
				if (bitweenY < 0)//下
				{
					for (int i = -bitweenY - 1; i > 0; i--)
					{
						s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() - i);
						if (s->GetPiece() != nullptr)
						{
							return false;
						}
					}
					if (this->PossibleSquareJuge(square) == true)
					{
						return true;
					}
				}
				
			}
			break;

		case PLAYER_STATE_02:
			if (bitweenX == 0)
			{
				if (bitweenY > 0)//上
				{
					for (int i = bitweenY - 1; i > 0; i--)
					{
						s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() + i);
						if (s->GetPiece() != nullptr)
						{
							return false;
						}
					}
					if (this->PossibleSquareJuge(square) == true)
					{
						return true;
					}
				}
			
			}
			break;

		default:
			break;
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_NARIKYOU:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == 1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == -1))//後ろ
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_KEIMA:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 1) && (bitweenY == -2))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			if ((bitweenX == -1) && (bitweenY == -2))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:

			if ((bitweenX == 1) && (bitweenY == 2))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
	
			if ((bitweenX == -1) && (bitweenY == 2))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIKEI:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == 1))//後ろ
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == -1))//後ろ
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;
	case PIECE_TYPE::PIECE_TYPE_GINN:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			
			if ((bitweenX == 1) && (bitweenY == 1))//右後
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左後
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右後
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左後
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIGINN:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == 1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == -1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_KINN:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == 1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == -1))//後ろ
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_KAKU:

		if (fabs(bitweenX)!=fabs(bitweenY))
		{
			return false;
		}
		if (bitweenX > 0)
		{
			if (bitweenY > 0)
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}


				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			if (bitweenY < 0)
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}


				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		if (bitweenX < 0)
		{

			if (bitweenY > 0)
			{
				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			if (bitweenY < 0)
			{
				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_UMA:
		//上下
		if ((bitweenX == 1) && (bitweenY == 0))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == 0))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 0) && (bitweenY == 1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 0) && (bitweenY == -1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}

		if (fabs(bitweenX) != fabs(bitweenY))
		{
			return false;
		}
		if (bitweenX > 0)
		{
			if (bitweenY > 0)
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			if (bitweenY < 0)
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		if (bitweenX < 0)
		{
			if (bitweenY > 0)
			{
				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if (bitweenY < 0)
			{
				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_HISYA:
		if (bitweenX == 0)
		{
			if (bitweenY > 0)//上
			{
				for (int i = bitweenY - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if (bitweenY < 0)//下
			{
				for (int i = -bitweenY - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		if (bitweenY == 0)
		{
			if (bitweenX > 0)//右
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY());
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if (bitweenX < 0)//左
			{
				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY());
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_RYUUOU:
		if ((bitweenX == 1) && (bitweenY == 1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == 1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 1) && (bitweenY == -1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == -1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if (bitweenX == 0)
		{
			if (bitweenY > 0)//上
			{
				for (int i = bitweenY - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if (bitweenY < 0)//下
			{
				for (int i = -bitweenY - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		if (bitweenY == 0)
		{
			if (bitweenX > 0)//右
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY());
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if (bitweenX < 0)//左
			{

				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY());
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_GYOKU:
		if ((bitweenX == 0) && (bitweenY == -1))//前
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 1) && (bitweenY == -1))//右前
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 1) && (bitweenY == 0))//右
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 1) && (bitweenY == 1))//右後
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 0) && (bitweenY == 1))//後ろ
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == 1))//左後
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == 0))//左
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == -1))//左前
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}

	default:
		break;
	}
	return false;
}

bool CPiece::JudgeCoolThrough(CSquare * square)
{
	int bitweenX = square->GetX() - this->m_square->GetX();
	int bitweenY = square->GetY() - this->m_square->GetY();
	CSquare* s;
	CSquareTable* squareTable = CManager::GetScene()->FindComponent<CSquareTable>();

	switch (m_pieceState)
	{
	case PIECE_TYPE::PIECE_TYPE_HUHYOU:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIKIN:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:

			if ((bitweenX == 0) && (bitweenY == -1))//前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == 1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == -1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_KYOUSYA:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (bitweenX == 0)
			{
				if (bitweenY < 0)//下
				{
					for (int i = -bitweenY - 1; i > 0; i--)
					{
						s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() - i);
						if (s->GetPiece() != nullptr)
						{
							return false;
						}
					}
					if (this->PossibleSquareJuge(square) == true)
					{
						return true;
					}
				}

			}
			break;

		case PLAYER_STATE_02:
			if (bitweenX == 0)
			{
				if (bitweenY > 0)//上
				{
					for (int i = bitweenY - 1; i > 0; i--)
					{
						s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() + i);
						if (s->GetPiece() != nullptr)
						{
							return false;
						}
					}
					if (this->PossibleSquareJuge(square) == true)
					{
						return true;
					}
				}

			}
			break;

		default:
			break;
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_NARIKYOU:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == 1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == -1))//後ろ
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_KEIMA:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 1) && (bitweenY == -2))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			if ((bitweenX == -1) && (bitweenY == -2))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:

			if ((bitweenX == 1) && (bitweenY == 2))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			if ((bitweenX == -1) && (bitweenY == 2))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIKEI:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == 1))//後ろ
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == -1))//後ろ
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;
	case PIECE_TYPE::PIECE_TYPE_GINN:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			if ((bitweenX == 1) && (bitweenY == 1))//右後
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左後
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右後
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左後
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIGINN:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == 1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == -1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_KINN:
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if ((bitweenX == 0) && (bitweenY == -1))//前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == -1))//右前
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == 1))//後ろ
			{
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == -1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		case PLAYER_STATE_02:
			if ((bitweenX == 0) && (bitweenY == 1))//前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 1))//右前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 1) && (bitweenY == 0))//右
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == 0) && (bitweenY == -1))//後ろ
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 0))//左
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if ((bitweenX == -1) && (bitweenY == 1))//左前
			{

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			break;

		default:
			break;
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_KAKU:

		if (fabs(bitweenX) != fabs(bitweenY))
		{
			return false;
		}
		if (bitweenX > 0)
		{
			if (bitweenY > 0)
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}


				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			if (bitweenY < 0)
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}


				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		if (bitweenX < 0)
		{

			if (bitweenY > 0)
			{
				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			if (bitweenY < 0)
			{
				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_UMA:
		//上下
		if ((bitweenX == 1) && (bitweenY == 0))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == 0))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 0) && (bitweenY == 1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 0) && (bitweenY == -1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}

		if (fabs(bitweenX) != fabs(bitweenY))
		{
			return false;
		}
		if (bitweenX > 0)
		{
			if (bitweenY > 0)
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}

			if (bitweenY < 0)
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		if (bitweenX < 0)
		{
			if (bitweenY > 0)
			{
				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}

				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if (bitweenY < 0)
			{
				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_HISYA:
		if (bitweenX == 0)
		{
			if (bitweenY > 0)//上
			{
				for (int i = bitweenY - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if (bitweenY < 0)//下
			{
				for (int i = -bitweenY - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		if (bitweenY == 0)
		{
			if (bitweenX > 0)//右
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY());
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if (bitweenX < 0)//左
			{
				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY());
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_RYUUOU:
		if ((bitweenX == 1) && (bitweenY == 1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == 1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 1) && (bitweenY == -1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == -1))
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if (bitweenX == 0)
		{
			if (bitweenY > 0)//上
			{
				for (int i = bitweenY - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() + i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if (bitweenY < 0)//下
			{
				for (int i = -bitweenY - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX(), m_square->GetY() - i);
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		if (bitweenY == 0)
		{
			if (bitweenX > 0)//右
			{
				for (int i = bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() + i, m_square->GetY());
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
			if (bitweenX < 0)//左
			{

				for (int i = -bitweenX - 1; i > 0; i--)
				{
					s = squareTable->GetSquare(m_square->GetX() - i, m_square->GetY());
					if (s->GetPiece() != nullptr)
					{
						return false;
					}
				}
				if (this->PossibleSquareJuge(square) == true)
				{
					return true;
				}
			}
		}
		break;

	case PIECE_TYPE::PIECE_TYPE_GYOKU:
		if ((bitweenX == 0) && (bitweenY == -1))//前
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 1) && (bitweenY == -1))//右前
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 1) && (bitweenY == 0))//右
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 1) && (bitweenY == 1))//右後
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == 0) && (bitweenY == 1))//後ろ
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == 1))//左後
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == 0))//左
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}
		if ((bitweenX == -1) && (bitweenY == -1))//左前
		{
			if (this->PossibleSquareJuge(square) == true)
			{
				return true;
			}
		}

	default:
		break;
	}
	return false;
}

CModel* CPiece::GetModel(PIECE_TYPE m_pieceState)
{
	switch (m_pieceState)
	{
	case PIECE_TYPE::PIECE_TYPE_HUHYOU:
		return m_model[PIECE_TYPE::PIECE_TYPE_HUHYOU];
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIKIN:
		return m_model[PIECE_TYPE::PIECE_TYPE_NARIKIN];
		break;

	case PIECE_TYPE::PIECE_TYPE_KYOUSYA:
		return m_model[PIECE_TYPE::PIECE_TYPE_KYOUSYA];
		break;

	case PIECE_TYPE::PIECE_TYPE_NARIKYOU:
		return m_model[PIECE_TYPE::PIECE_TYPE_NARIKYOU];
		break;

	case PIECE_TYPE::PIECE_TYPE_KEIMA:
		return m_model[PIECE_TYPE::PIECE_TYPE_KEIMA];

		break;
	case PIECE_TYPE::PIECE_TYPE_NARIKEI:
		return m_model[PIECE_TYPE::PIECE_TYPE_NARIKEI];

		break;
	case PIECE_TYPE::PIECE_TYPE_GINN:
		return m_model[PIECE_TYPE::PIECE_TYPE_GINN];

		break;
	case PIECE_TYPE::PIECE_TYPE_NARIGINN:
		return m_model[PIECE_TYPE::PIECE_TYPE_NARIGINN];

		break;

	case PIECE_TYPE::PIECE_TYPE_KINN:
		return m_model[PIECE_TYPE::PIECE_TYPE_KINN];
		break;

	case PIECE_TYPE::PIECE_TYPE_KAKU:
		return m_model[PIECE_TYPE::PIECE_TYPE_KAKU];
		break;
	case PIECE_TYPE::PIECE_TYPE_UMA:
		return m_model[PIECE_TYPE::PIECE_TYPE_UMA];
		break;

	case PIECE_TYPE::PIECE_TYPE_HISYA:
		return m_model[PIECE_TYPE::PIECE_TYPE_HISYA];
		break;

	case PIECE_TYPE::PIECE_TYPE_RYUUOU:
		return m_model[PIECE_TYPE::PIECE_TYPE_RYUUOU];
		break;
	case PIECE_TYPE::PIECE_TYPE_GYOKU:
		return m_model[PIECE_TYPE::PIECE_TYPE_GYOKU];

		break;

	default:
		return nullptr;

	}
}
void CPiece::StateSetting(PIECE_TYPE state, CPlayerBase* player, CSquare* square)
{
	m_pieceState = state;
	m_drawer = GetGameObject()->AddComponent<CPieceDrawer>();
	m_drawer->SetPiece(this);
	D3DXQUATERNION quat;
	m_player = player;
	//角度
	switch (m_player->GetPlayerState())
	{
	case PLAYER_STATE_01:
		D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(0));
		GetGameObject()->SetRotation(quat);
		break;

	case PLAYER_STATE_02:
		D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(180));
		GetGameObject()->SetRotation(quat);
		break;

	default:
		break;
	}

	SetSquare(square);
	square->SetPiece(this);
}
void CPiece::StateSet(PIECE_TYPE state, CPlayerBase* player, CSquare* square)
{
	m_pieceState = state;
	m_drawer->SetPiece(this);

	D3DXQUATERNION quat;
	m_player = player;
	switch (m_player->GetPlayerState())
	{
	case PLAYER_STATE_01:
		D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(0));
		GetGameObject()->SetRotation(quat);
		break;

	case PLAYER_STATE_02:
		D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(180));
		GetGameObject()->SetRotation(quat);
		break;

	default:
		break;
	
	}
	SetSquare(square);

}
void CPiece::SetSquare(CSquare* set)
{
	m_square = set;
	m_square->SetPiece(this);
	m_gameobject->SetPosition(m_square->GetGameObject()->GetPosition());
	m_gameobject->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
}
void CPiece::SetSquareUnCmoponent(CSquare* set)
{
	m_square = set;
	m_square->SetPiece(this);
}
bool CPiece::RankUp()
{
	switch (m_pieceState)
	{
	case PIECE_TYPE::PIECE_TYPE_HUHYOU:
		m_pieceState = PIECE_TYPE_NARIKIN;
		return true;
		break;
	
	case PIECE_TYPE::PIECE_TYPE_KYOUSYA:
		m_pieceState = PIECE_TYPE_NARIKYOU;
		return true;
		break;
	
	case PIECE_TYPE::PIECE_TYPE_KEIMA:
		m_pieceState = PIECE_TYPE_NARIKEI;
		return true;
		break;

	case PIECE_TYPE::PIECE_TYPE_GINN:
		m_pieceState = PIECE_TYPE_NARIGINN;
		return true;
		break;

	case PIECE_TYPE::PIECE_TYPE_KAKU:
		m_pieceState = PIECE_TYPE_UMA;
		return true;
		break;
	

	case PIECE_TYPE::PIECE_TYPE_HISYA:
		m_pieceState = PIECE_TYPE_RYUUOU;
		return true;
		break;


	default:
		return false;
		break;
	}
}
void CPiece::CoolSet()
{
	CGameObject* g = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);
	m_coolTimer = g->AddComponent<CPieceCoolTimer>();
	switch (m_pieceState)
	{
	case PIECE_TYPE::PIECE_TYPE_HUHYOU:
		m_coolTimer->Setting(this, PIECE_COOL_HUHYOU);
		break;

	case PIECE_TYPE::PIECE_TYPE_NARIKIN:
		m_coolTimer->Setting(this, PIECE_COOL_NARIKIN);
		break;
	
	case PIECE_TYPE::PIECE_TYPE_KYOUSYA:
		m_coolTimer->Setting(this, PIECE_COOL_KYOUSYA);
		break;
	
	case PIECE_TYPE::PIECE_TYPE_NARIKYOU:
		m_coolTimer->Setting(this, PIECE_COOL_NARIKYOU);
		break;
	
	case PIECE_TYPE::PIECE_TYPE_KEIMA:
		m_coolTimer->Setting(this, PIECE_COOL_KEIMA);
		break;
	
	case PIECE_TYPE::PIECE_TYPE_NARIKEI:
		m_coolTimer->Setting(this, PIECE_COOL_NARIKEI);
		break;

	case PIECE_TYPE::PIECE_TYPE_GINN:
		m_coolTimer->Setting(this, PIECE_COOL_GINN);
		break;

	case PIECE_TYPE::PIECE_TYPE_NARIGINN:
		m_coolTimer->Setting(this, PIECE_COOL_NARIGINN);
		break;

	case PIECE_TYPE::PIECE_TYPE_KINN:
		m_coolTimer->Setting(this, PIECE_COOL_KINN);
		break;
	
	case PIECE_TYPE::PIECE_TYPE_KAKU:
		m_coolTimer->Setting(this, PIECE_COOL_KAKU);
		break;

	case PIECE_TYPE::PIECE_TYPE_UMA:
		m_coolTimer->Setting(this, PIECE_COOL_UMA);
		break;
	
	case PIECE_TYPE::PIECE_TYPE_HISYA:
		m_coolTimer->Setting(this, PIECE_COOL_HISYA);
		break;
	
	case PIECE_TYPE::PIECE_TYPE_RYUUOU:
		m_coolTimer->Setting(this, PIECE_COOL_RYUUOU);
		break;
	
	case PIECE_TYPE::PIECE_TYPE_GYOKU:
		m_coolTimer->Setting(this, PIECE_COOL_GYOKU);
		break;
	
	default:
		return;
		break;
	}
	m_cool = true;
}
void CPiece::CoolUnSet()
{
	m_coolTimer->GetGameObject()->SetDestoroy();
	m_coolTimer = nullptr;
	m_cool = false;


}
bool CPiece::GetMovePossible()
{

	if (m_cool==false)
	{
		if (GetPossibleSquareNum()>0)
		{
			return true;
		}
	}
	return false;
}
void CPiece::GetPossibleSquares(std::vector<CSquare*> *out)
{
	CSquare* s;
	CSquareTable* squareTable = m_player->GetTable();

	const int x = m_square->GetX(),y= m_square->GetY();
	
	bool roopflag = true;
	
	//種類ごとに進めるマスのリストを返す
	switch (m_pieceState)
	{
	case PIECE_TYPE::PIECE_TYPE_HUHYOU://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:

			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);
			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);
			}
			break;

		default:
			break;
		}
		break;
	}
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIKIN://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);

			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);

				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					PossibleSquaresSet(s, out);

				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1 , y - 1);
					PossibleSquaresSet(s, out);

				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				PossibleSquaresSet(s, out);

			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				PossibleSquaresSet(s, out);

			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);


				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					PossibleSquaresSet(s, out);
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					PossibleSquaresSet(s, out);
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				PossibleSquaresSet(s, out);
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				PossibleSquaresSet(s, out);
			}
			break;

		default:
			break;
		}
	}
		break;
	case PIECE_TYPE::PIECE_TYPE_KYOUSYA://OK
	{
		bool flag = true;
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			
			if (y > SQUARE_TABLE_MIN_Y)
			{
				for (int i = 1;flag==true ; ++i)
				{
					
					s = squareTable->GetSquare(x, y-i);
					PossibleSquaresSet(s, out);
					if ((s->GetPiece() != nullptr)||(y - i - 1 < SQUARE_TABLE_MIN_Y))
					{
						flag = false;
					}
				
				}
			
			}

			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				for (int i = 1; flag == true; ++i)
				{

					s = squareTable->GetSquare(x, y + i);
					PossibleSquaresSet(s, out);
					if ((s->GetPiece() != nullptr)||(y + i + 1 > SQUARE_TABLE_MAX_Y))
					{
						flag = false;
					}
				
				}

			}
			break;

		default:
			break;
		}
	}	
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIKYOU://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);

			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);

				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					PossibleSquaresSet(s, out);

				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					PossibleSquaresSet(s, out);

				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				PossibleSquaresSet(s, out);

			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				PossibleSquaresSet(s, out);

			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);


				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					PossibleSquaresSet(s, out);
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					PossibleSquaresSet(s, out);
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				PossibleSquaresSet(s, out);
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				PossibleSquaresSet(s, out);
			}
			break;

		default:
			break;
		}
	}
		break;
	case PIECE_TYPE::PIECE_TYPE_KEIMA://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:

			if (y > SQUARE_TABLE_MIN_Y+1)
			{
				if (x > SQUARE_TABLE_MIN_X)
				{
					s = squareTable->GetSquare(x - 1, y - 2);
					PossibleSquaresSet(s, out);


				}
				if (x < SQUARE_TABLE_MAX_X)
				{
					s = squareTable->GetSquare(x + 1, y - 2);
					PossibleSquaresSet(s, out);

				}
			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y - 1)
			{
				if (x > SQUARE_TABLE_MIN_X)
				{
					s = squareTable->GetSquare(x - 1, y + 2);
					PossibleSquaresSet(s, out);


				}
				if (x < SQUARE_TABLE_MAX_X)
				{
					s = squareTable->GetSquare(x + 1, y + 2);
					PossibleSquaresSet(s, out);

				}
			}		break;

		default:
			break;
		}
		break;
	}
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIKEI://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);

			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);

				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					PossibleSquaresSet(s, out);

				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					PossibleSquaresSet(s, out);

				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				PossibleSquaresSet(s, out);

			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				PossibleSquaresSet(s, out);

			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);


				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					PossibleSquaresSet(s, out);
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					PossibleSquaresSet(s, out);
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				PossibleSquaresSet(s, out);
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				PossibleSquaresSet(s, out);
			}
			break;

		default:
			break;
		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_GINN: //OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				if (x < SQUARE_TABLE_MAX_X)//(1,1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					PossibleSquaresSet(s, out);

				}
				if (x > SQUARE_TABLE_MIN_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					PossibleSquaresSet(s, out);

				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);

				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					PossibleSquaresSet(s, out);

				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					PossibleSquaresSet(s, out);

				}
			}
			
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);

				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					PossibleSquaresSet(s, out);

				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					PossibleSquaresSet(s, out);

				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					PossibleSquaresSet(s, out);

				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					PossibleSquaresSet(s, out);

				}

			}
			break;

		default:
			break;
		}
	}
		break;
	case PIECE_TYPE::PIECE_TYPE_NARIGINN://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);
				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					PossibleSquaresSet(s, out);
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					PossibleSquaresSet(s, out);
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				PossibleSquaresSet(s, out);
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				PossibleSquaresSet(s, out);
			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);
				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					PossibleSquaresSet(s, out);
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					PossibleSquaresSet(s, out);
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);

			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				PossibleSquaresSet(s, out);
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				PossibleSquaresSet(s, out);
			}
			break;

		default:
			break;
		}
	}
		break;
	case PIECE_TYPE::PIECE_TYPE_KINN://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);

			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);

				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					PossibleSquaresSet(s, out);

				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1 , y - 1);
					PossibleSquaresSet(s, out);

				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				PossibleSquaresSet(s, out);

			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				PossibleSquaresSet(s, out);

			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);


				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					PossibleSquaresSet(s, out);
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					PossibleSquaresSet(s, out);
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				PossibleSquaresSet(s, out);
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				PossibleSquaresSet(s, out);
			}
			break;

		default:
			break;
		}
	}
		break;
	case PIECE_TYPE::PIECE_TYPE_KAKU:
	{
		if (y < SQUARE_TABLE_MAX_Y)
		{
			if (x < SQUARE_TABLE_MAX_X)
			{
				roopflag = true;
				for (int i = 1; roopflag == true; ++i)
				{
					s = squareTable->GetSquare(x + i, y + i);
					PossibleSquaresSet(s, out);
					if ((s->GetPiece() != nullptr)|| (x + i + 1 > SQUARE_TABLE_MAX_X) || (y + i + 1 > SQUARE_TABLE_MAX_Y))
					{
						roopflag = false;
					}
				
				}
			}
			if (x > SQUARE_TABLE_MIN_X)
			{
				roopflag = true;
				for (int i = 1; roopflag == true; ++i)
				{
					s = squareTable->GetSquare(x - i, y + i);
					PossibleSquaresSet(s, out);
					if ((s->GetPiece() != nullptr)|| (x - i - 1 < SQUARE_TABLE_MIN_X) || (y + i + 1 > SQUARE_TABLE_MAX_Y))
					{
						roopflag = false;
					}
				
				}
			}
		}
		if (y > SQUARE_TABLE_MIN_Y)
		{
			if (x < SQUARE_TABLE_MAX_X)
			{
				//(1,1)
				roopflag = true;
				for (int i = 1; roopflag == true; ++i)
				{
					s = squareTable->GetSquare(x + i, y - i);
					PossibleSquaresSet(s, out);
					if ((s->GetPiece() != nullptr)|| (x + i + 1 > SQUARE_TABLE_MAX_X) || (y - i - 1 < SQUARE_TABLE_MIN_Y))
					{
						roopflag = false;
					}
				}
			}
			if (x > SQUARE_TABLE_MIN_X)
			{	
				roopflag = true;
				for (int i = 1; roopflag == true; ++i)
				{
					s = squareTable->GetSquare(x - i, y - i);
					PossibleSquaresSet(s, out);
					if ((s->GetPiece() != nullptr) || (x - i - 1 < SQUARE_TABLE_MIN_X) || (y - i - 1 < SQUARE_TABLE_MIN_Y))
					{
						roopflag = false;
					}
					
				}
			}
		}
	
	}
		break;
	case PIECE_TYPE::PIECE_TYPE_UMA:
	{

		//上下左右
		if (x < SQUARE_TABLE_MAX_X)
		{
			s = squareTable->GetSquare(x + 1, y);
			PossibleSquaresSet(s, out);
		}
		if (x > SQUARE_TABLE_MIN_X)
		{
			s = squareTable->GetSquare(x - 1, y);
			PossibleSquaresSet(s, out);
		}
		if (y < SQUARE_TABLE_MAX_Y)
		{
			s = squareTable->GetSquare(x, y + 1);
			PossibleSquaresSet(s, out);
		}
		if (y > SQUARE_TABLE_MIN_Y)
		{
			s = squareTable->GetSquare(x, y - 1);
			PossibleSquaresSet(s, out);
		}
		
		//斜め

		if (y < SQUARE_TABLE_MAX_Y)
		{
			if (x < SQUARE_TABLE_MAX_X)
			{
				roopflag = true;
				for (int i = 1; roopflag == true; ++i)
				{
					s = squareTable->GetSquare(x + i, y + i);
					PossibleSquaresSet(s, out);
					if ((s->GetPiece() != nullptr) || (x + i + 1 > SQUARE_TABLE_MAX_X) || (y + i + 1 > SQUARE_TABLE_MAX_Y))
					{
						roopflag = false;
					}

				}
			}
			if (x > SQUARE_TABLE_MIN_X)
			{
				roopflag = true;
				for (int i = 1; roopflag == true; ++i)
				{
					s = squareTable->GetSquare(x - i, y + i);
					PossibleSquaresSet(s, out);
					if ((s->GetPiece() != nullptr) || (x - i - 1 < SQUARE_TABLE_MIN_X) || (y + i + 1 > SQUARE_TABLE_MAX_Y))
					{
						roopflag = false;
					}

				}
			}
		}
		if (y > SQUARE_TABLE_MIN_Y)
		{
			if (x < SQUARE_TABLE_MAX_X)
			{
				//(1,1)
				roopflag = true;
				for (int i = 1; roopflag == true; ++i)
				{
					s = squareTable->GetSquare(x + i, y - i);
					PossibleSquaresSet(s, out);
					if ((s->GetPiece() != nullptr) || (x + i + 1 > SQUARE_TABLE_MAX_X) || (y - i - 1 < SQUARE_TABLE_MIN_Y))
					{
						roopflag = false;
					}
				}
			}
			if (x > SQUARE_TABLE_MIN_X)
			{
				roopflag = true;
				for (int i = 1; roopflag == true; ++i)
				{
					s = squareTable->GetSquare(x - i, y - i);
					PossibleSquaresSet(s, out);
					if ((s->GetPiece() != nullptr) || (x - i - 1 < SQUARE_TABLE_MIN_X) || (y - i - 1 < SQUARE_TABLE_MIN_Y))
					{
						roopflag = false;
					}

				}
			}
		}
		
	}
		break;		
	case PIECE_TYPE::PIECE_TYPE_HISYA:
	{
		//(1,0)
		if (x < SQUARE_TABLE_MAX_X)
		{
			roopflag = true;
			for (int i = 1; roopflag == true; ++i)
			{
				s = squareTable->GetSquare(x + i, y);
				PossibleSquaresSet(s, out);
				if ((s->GetPiece() != nullptr)|| (x + i + 1 > SQUARE_TABLE_MAX_X))
				{
					roopflag = false;
				}
				
			}
		}
		//(-1,0)
		if (x > SQUARE_TABLE_MIN_X)
		{
			roopflag = true;
			for (int i = 1; roopflag == true; ++i)
			{
				s = squareTable->GetSquare(x - i, y);
				PossibleSquaresSet(s, out);
				if ((s->GetPiece() != nullptr)||(x - i - 1 < SQUARE_TABLE_MIN_X))
				{
					roopflag = false;
				}
				

			}
		}
		//(0,1)
		if (y < SQUARE_TABLE_MAX_Y)
		{
			roopflag = true;
			for (int i = 1; roopflag == true; ++i)
			{
				s = squareTable->GetSquare(x, y+1);
				PossibleSquaresSet(s, out);
				if ((s->GetPiece() != nullptr)|| (y + i + 1 > SQUARE_TABLE_MAX_Y))
				{
					roopflag = false;
				}

			}
		}
		//(0,-1)
		if (y > SQUARE_TABLE_MIN_Y)
		{
			roopflag = true;
			for (int i = 1; roopflag == true; ++i)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);
				if ((s->GetPiece() != nullptr)|| (y - i - 1 < SQUARE_TABLE_MIN_Y))
				{
					roopflag = false;
				}
			

			}
		}
	}
		break;
	case PIECE_TYPE::PIECE_TYPE_RYUUOU:
	{
		//斜め
		if (x < SQUARE_TABLE_MAX_X)
		{
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x + 1, y + 1);
				PossibleSquaresSet(s, out);
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x + 1, y - 1);
				PossibleSquaresSet(s, out);
			}
		}
		if (x > SQUARE_TABLE_MIN_X)
		{
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x-1, y+1);
				PossibleSquaresSet(s, out);
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x-1, y-1);
				PossibleSquaresSet(s, out);
			}
		}
		//(1,0)
		if (x < SQUARE_TABLE_MAX_X)
		{
			roopflag = true;
			for (int i = 1; roopflag == true; ++i)
			{
				s = squareTable->GetSquare(x + i, y);
				PossibleSquaresSet(s, out);
				if ((s->GetPiece() != nullptr) || (x + i + 1 > SQUARE_TABLE_MAX_X))
				{
					roopflag = false;
				}

			}
		}
		//(-1,0)
		if (x > SQUARE_TABLE_MIN_X)
		{
			roopflag = true;
			for (int i = 1; roopflag == true; ++i)
			{
				s = squareTable->GetSquare(x - i, y);
				PossibleSquaresSet(s, out);
				if ((s->GetPiece() != nullptr) || (x - i - 1 < SQUARE_TABLE_MIN_X))
				{
					roopflag = false;
				}


			}
		}
		//(0,1)
		if (y < SQUARE_TABLE_MAX_Y)
		{
			roopflag = true;
			for (int i = 1; roopflag == true; ++i)
			{
				s = squareTable->GetSquare(x, y + 1);
				PossibleSquaresSet(s, out);
				if ((s->GetPiece() != nullptr) || (y + i + 1 > SQUARE_TABLE_MAX_Y))
				{
					roopflag = false;
				}

			}
		}
		//(0,-1)
		if (y > SQUARE_TABLE_MIN_Y)
		{
			roopflag = true;
			for (int i = 1; roopflag == true; ++i)
			{
				s = squareTable->GetSquare(x, y - 1);
				PossibleSquaresSet(s, out);
				if ((s->GetPiece() != nullptr) || (y - i - 1 < SQUARE_TABLE_MIN_Y))
				{
					roopflag = false;
				}


			}
		}
	}
		break;
	case PIECE_TYPE::PIECE_TYPE_GYOKU:
	{
		if (x < SQUARE_TABLE_MAX_X)
		{
			s = squareTable->GetSquare(x + 1, y);
			PossibleSquaresSet(s, out);
		}
		if (x > SQUARE_TABLE_MIN_X)
		{
			s = squareTable->GetSquare(x - 1, y);
			PossibleSquaresSet(s, out);
		}
		if (y < SQUARE_TABLE_MAX_Y)
		{
			s = squareTable->GetSquare(x, y + 1);
			PossibleSquaresSet(s, out);
			if (x < SQUARE_TABLE_MAX_X)
			{
				s = squareTable->GetSquare(x + 1, y + 1);
				PossibleSquaresSet(s, out);
			}
			if (x > SQUARE_TABLE_MIN_X)
			{
				s = squareTable->GetSquare(x - 1, y + 1);
				PossibleSquaresSet(s, out);
			}
		}
		if (y > SQUARE_TABLE_MIN_Y)
		{
			s = squareTable->GetSquare(x, y - 1);
			PossibleSquaresSet(s, out);

			if (x < SQUARE_TABLE_MAX_X)
			{
				s = squareTable->GetSquare(x + 1, y-1);
				PossibleSquaresSet(s, out);
			}
			if (x > SQUARE_TABLE_MIN_X)
			{
				s = squareTable->GetSquare(x - 1, y-1);
				PossibleSquaresSet(s, out);
			}
		}

	}
		break;
	default:
		break;
	}

	return;
}
int CPiece::GetPossibleSquareNum()
{

	int ret = 0;

	CSquare* s;
	CSquareTable* squareTable = CManager::GetScene()->FindComponent<CSquareTable>();

	const int x = m_square->GetX(), y = m_square->GetY();
	int xA, yA;
	bool roopflag = true;

	//種類ごとに進めるマスのリストを返す
	switch (m_pieceState)
	{
	case PIECE_TYPE::PIECE_TYPE_HUHYOU://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:

			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}

			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		default:
			break;
		}
		break;
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_NARIKIN://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}

				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		default:
			break;
		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_KYOUSYA://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y > SQUARE_TABLE_MIN_Y)
			{
				xA = x;
				yA = y - 1;
				do
				{
					s = squareTable->GetSquare(xA, yA);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
					if (s->GetPiece() != nullptr)
					{
						roopflag = false;
					}
					yA--;
				} while ((roopflag == true) && (yA >= SQUARE_TABLE_MIN_Y));
			}

			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				xA = x;
				yA = y + 1;
				do
				{
					s = squareTable->GetSquare(xA, yA);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
					if (s->GetPiece() != nullptr)
					{
						roopflag = false;
					}
					yA++;
				} while ((roopflag == true) && (yA <= SQUARE_TABLE_MAX_Y));
			}
			break;

		default:
			break;
		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_NARIKYOU://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}

				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		default:
			break;
		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_KEIMA://
	{


		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:

			if (y > SQUARE_TABLE_MIN_Y + 1)
			{
				if (x > SQUARE_TABLE_MIN_X)
				{
					s = squareTable->GetSquare(x - 1, y - 2);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x < SQUARE_TABLE_MAX_X)
				{
					s = squareTable->GetSquare(x + 1, y - 2);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y - 1)
			{
				if (x > SQUARE_TABLE_MIN_X)
				{
					s = squareTable->GetSquare(x - 1, y + 2);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}

				}
				if (x < SQUARE_TABLE_MAX_X)
				{
					s = squareTable->GetSquare(x + 1, y + 2);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}		
			break;

		default:
			break;
		}
		break;
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_NARIKEI://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		default:
			break;
		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_GINN: //OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				if (x < SQUARE_TABLE_MAX_X)//(1,1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}

			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}

			}
			break;

		default:
			break;
		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_NARIGINN://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		default:
			break;
		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_KINN://OK
	{
		switch (m_player->GetPlayerState())
		{
		case PLAYER_STATE_01:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (x < SQUARE_TABLE_MAX_X)//(1,-1)
				{
					s = squareTable->GetSquare(x + 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1,-1)
				{
					s = squareTable->GetSquare(x - 1, y - 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		case PLAYER_STATE_02:
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}

				if (x < SQUARE_TABLE_MAX_X)//(1, 1)
				{
					s = squareTable->GetSquare(x + 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
				if (x > SQUARE_TABLE_MIN_X)//(-1, 1)
				{
					s = squareTable->GetSquare(x - 1, y + 1);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x < SQUARE_TABLE_MAX_X)//(1,0)
			{
				s = squareTable->GetSquare(x + 1, y);
				if (PossibleSquareJuge(s)==true)
				{
						ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)//(-1,0)
			{
				s = squareTable->GetSquare(x - 1, y);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			break;

		default:
			break;
		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_KAKU:
	{
		if (y < SQUARE_TABLE_MAX_Y)
		{
			if (x < SQUARE_TABLE_MAX_X)
			{
				//(1,1)
				xA = x + 1;
				yA = y + 1;


				do
				{
					s = squareTable->GetSquare(xA, yA);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
					if (s->GetPiece() != nullptr)
					{
						roopflag = false;
					}
					xA++;
					yA++;
				} while ((roopflag == true) && (xA >= SQUARE_TABLE_MAX_X) && (yA >= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));
			}
		}
		if (y > SQUARE_TABLE_MIN_Y)
		{
			if (x < SQUARE_TABLE_MAX_X)
			{
				//(1,-1)
				xA = x + 1;
				yA = y - 1;


				do
				{
					s = squareTable->GetSquare(xA, yA);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
					if (s->GetPiece() != nullptr)
					{
						roopflag = false;
					}
					xA++;
					yA--;
				} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));
			}
		}
		if (y < SQUARE_TABLE_MAX_Y)
		{
			if (x > SQUARE_TABLE_MIN_X)
			{
				//(-1,1)
				xA = x - 1;
				yA = y + 1;


				do
				{
					s = squareTable->GetSquare(xA, yA);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
					if (s->GetPiece() != nullptr)
					{
						roopflag = false;
					}
					xA--;
					yA++;
				} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));
			}
		}
		if (y > SQUARE_TABLE_MIN_Y)
		{
			if (x > SQUARE_TABLE_MIN_X)
			{
				//(-1,-1)
				xA = x - 1;
				yA = y - 1;


				do
				{
					s = squareTable->GetSquare(xA, yA);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}

					if (s->GetPiece() != nullptr)
					{
						roopflag = false;
					}
					xA--;
					yA--;
				} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));
			}
		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_UMA:
	{

		//上下左右
		if (x < SQUARE_TABLE_MAX_X)
		{
			s = squareTable->GetSquare(x + 1, y);
			if (PossibleSquareJuge(s) == true)
			{
				ret++;
			}
		}
		if (x > SQUARE_TABLE_MIN_X)
		{
			s = squareTable->GetSquare(x - 1, y);
			if (PossibleSquareJuge(s) == true)
			{
				ret++;
			}
		}
		if (y < SQUARE_TABLE_MAX_Y)
		{
			s = squareTable->GetSquare(x, y + 1);
			if (PossibleSquareJuge(s) == true)
			{
				ret++;
			}
		}
		if (y > SQUARE_TABLE_MIN_Y)
		{
			s = squareTable->GetSquare(x, y - 1);
			if (PossibleSquareJuge(s) == true)
			{
				ret++;
			}
		}

		//斜め
		if (y < SQUARE_TABLE_MAX_Y)
		{
			if (x < SQUARE_TABLE_MAX_X)
			{
				//(1,1)
				xA = x + 1;
				yA = y + 1;


				do
				{
					s = squareTable->GetSquare(xA, yA);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
					if (s->GetPiece() != nullptr)
					{
						roopflag = false;
					}
					xA++;
					yA++;
				} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));
			}
		}
		if (y > SQUARE_TABLE_MIN_Y)
		{
			if (x < SQUARE_TABLE_MAX_X)
			{
				//(1,-1)
				xA = x + 1;
				yA = y - 1;


				do
				{
					s = squareTable->GetSquare(xA, yA);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
					if (s->GetPiece() != nullptr)
					{
						roopflag = false;
					}
					xA++;
					yA--;
				} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));
			}
		}
		if (y < SQUARE_TABLE_MAX_Y)
		{
			if (x > SQUARE_TABLE_MIN_X)
			{
				//(-1,1)
				xA = x - 1;
				yA = y + 1;


				do
				{
					s = squareTable->GetSquare(xA, yA);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
					if (s->GetPiece() != nullptr)
					{
						roopflag = false;
					}
					xA--;
					yA++;
				} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));
			}
		}
		if (y > SQUARE_TABLE_MIN_Y)
		{
			if (x > SQUARE_TABLE_MIN_X)
			{
				//(-1,-1)
				xA = x - 1;
				yA = y - 1;


				do
				{
					s = squareTable->GetSquare(xA, yA);
					if (PossibleSquareJuge(s) == true)
					{
						ret++;
					}
					if (s->GetPiece() != nullptr)
					{
						roopflag = false;
					}
					xA--;
					yA--;
				} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));
			}
		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_HISYA:
	{
		//(1,0)
		if (x < SQUARE_TABLE_MAX_X)
		{
			xA = x + 1;
			yA = y;

			do
			{
				s = squareTable->GetSquare(xA, yA);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (s->GetPiece() != nullptr)
				{
					roopflag = false;
				}
				xA++;
			} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));

		}
		//(-1,0)
		if (x > SQUARE_TABLE_MIN_X)
		{
			xA = x - 1;
			yA = y;

			do
			{
				s = squareTable->GetSquare(xA, yA);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (s->GetPiece() != nullptr)
				{
					roopflag = false;
				}
				xA--;
			} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));

		}
		//(0,1)
		if (y < SQUARE_TABLE_MAX_X)
		{
			xA = x;
			yA = y + 1;

			do
			{
				s = squareTable->GetSquare(xA, yA);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (s->GetPiece() != nullptr)
				{
					roopflag = false;
				}
				yA++;
			} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));

		}
		//(0,-1)
		if (y > SQUARE_TABLE_MIN_Y)
		{
			xA = x;
			yA = y - 1;

			do
			{
				s = squareTable->GetSquare(xA, yA);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (s->GetPiece() != nullptr)
				{
					roopflag = false;
				}
				yA--;
			} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));

		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_RYUUOU:
	{
		//斜め
		if (x < SQUARE_TABLE_MAX_X)
		{
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x + 1, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x + 1, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
		}
		if (x > SQUARE_TABLE_MIN_X)
		{
			if (y < SQUARE_TABLE_MAX_Y)
			{
				s = squareTable->GetSquare(x - 1, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (y > SQUARE_TABLE_MIN_Y)
			{
				s = squareTable->GetSquare(x - 1, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
		}
		//(1,0)
		if (x < SQUARE_TABLE_MAX_X)
		{
			xA = x + 1;
			yA = y;

			do
			{
				s = squareTable->GetSquare(xA, yA);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (s->GetPiece() != nullptr)
				{
					roopflag = false;
				}
				xA++;
			} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));

		}
		//(-1,0)
		if (x > SQUARE_TABLE_MIN_X)
		{
			xA = x - 1;
			yA = y;

			do
			{
				s = squareTable->GetSquare(xA, yA);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (s->GetPiece() != nullptr)
				{
					roopflag = false;
				}
				xA--;
			} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));

		}
		//(0,1)
		if (y < SQUARE_TABLE_MAX_X)
		{
			xA = x;
			yA = y + 1;

			do
			{
				s = squareTable->GetSquare(xA, yA);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}

				if (s->GetPiece() != nullptr)
				{
					roopflag = false;
				}
				yA++;
			} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));

		}
		//(0,-1)
		if (y > SQUARE_TABLE_MIN_Y)
		{
			xA = x;
			yA = y - 1;

			do
			{
				s = squareTable->GetSquare(xA, yA);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
				if (s->GetPiece() != nullptr)
				{
					roopflag = false;
				}
				yA--;
			} while ((roopflag == true) && (xA <= SQUARE_TABLE_MAX_X) && (yA <= SQUARE_TABLE_MAX_Y) && (yA >= SQUARE_TABLE_MIN_Y) && (xA >= SQUARE_TABLE_MIN_Y));

		}
	}
	break;
	case PIECE_TYPE::PIECE_TYPE_GYOKU:
	{
		if (x < SQUARE_TABLE_MAX_X)
		{
			s = squareTable->GetSquare(x + 1, y);
			if (PossibleSquareJuge(s) == true)
			{
				ret++;
			}
		
		}
		if (x > SQUARE_TABLE_MIN_X)
		{
			s = squareTable->GetSquare(x - 1, y);
			if (PossibleSquareJuge(s) == true)
			{
				ret++;
			}
		
		}
		if (y < SQUARE_TABLE_MAX_Y)
		{
			s = squareTable->GetSquare(x, y + 1);
			if (PossibleSquareJuge(s) == true)
			{
				ret++;
			}
			if (x < SQUARE_TABLE_MAX_X)
			{
				s = squareTable->GetSquare(x + 1, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)
			{
				s = squareTable->GetSquare(x - 1, y + 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
		}
		if (y > SQUARE_TABLE_MIN_Y)
		{
			s = squareTable->GetSquare(x, y - 1);
			if (PossibleSquareJuge(s) == true)
			{
				ret++;
			}
			if (x < SQUARE_TABLE_MAX_X)
			{
				s = squareTable->GetSquare(x + 1, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
			if (x > SQUARE_TABLE_MIN_X)
			{
				s = squareTable->GetSquare(x - 1, y - 1);
				if (PossibleSquareJuge(s) == true)
				{
					ret++;
				}
			}
		}

	}
	break;
	default:
		break;
	}
	return ret;
}


bool CPiece::PossibleSquareJuge(CSquare * square)
{
	if (square->GetPiece() == nullptr)
	{
	
		return true;
	}
	else
	{
		if (square->GetPiece()->GetPlayer()->GetPlayerState() != m_player->GetPlayerState())
		{


			return true;
		}
	}

	return false;
}

void CPiece::Init()
{

}
void CPiece::Uninit()
{
	if (m_pieceState==PIECE_TYPE_GYOKU)
	{
		if (m_player!=nullptr)
		{

			m_player->SetLoose(true);
		}
	}
	if (m_coolTimer!=nullptr)
	{
		m_coolTimer->GetGameObject()->SetDestoroy();
	}
}
void CPiece::Update()
{

}
void CPiece::Draw()
{
	
}



void CPiece::PossibleSquaresSet(CSquare* square, std::vector<CSquare*> *out)
{
	if (square->GetPiece() == nullptr)
	{
		for (CSquare* s : *out)
		{
			//既に駒があるなら
			if (s == square)
			{
				return;
			}
		}

	}
	else
	{
		if (square->GetPiece()->GetPlayer()->GetPlayerState() != m_player->GetPlayerState())
		{

			for (CSquare* s : *out)
			{
				if (s == square)
				{
					return;
				}
			}
		}
		else
		{
			return;
		}
	}
	out->push_back(square);
}