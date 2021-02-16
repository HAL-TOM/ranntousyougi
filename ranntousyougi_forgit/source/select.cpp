#include "select.h"
#include"square.h"
#include"piece.h"
#include"player.h"
#include"handbord.h"
#include"model.h"
#include"game_object.h"
#include"input.h"
#include"manager.h"
#include"scene.h"
#include"square_table.h"
#include"number.h"
#include"pointer.h"
CModel* CSelect::m_redModel;
CModel* CSelect::m_blueModel;



void CSelect::Load()
{
	m_redModel = new CModel();
	m_blueModel = new CModel();

	m_redModel->Load("asset\\model\\selectRed.obj");
	m_blueModel->Load("asset\\model\\selectBlue.obj");
}
void CSelect::UnLoad()
{
	m_redModel->Unload();
	m_blueModel->Unload();

	delete m_redModel;
	delete m_blueModel;
}

void CSelect::ChoiceSquare()
{
	m_selectSquare = m_posSquare;
	m_selectHandIndex = 0;
	m_selectState = SELECT_STATE_EXIST_SQUARE;
	CreatePointer();
}
void CSelect::ChoiceHand()
{
	m_selectSquare = nullptr;
	m_selectHandIndex = m_posHandIndex;
	m_selectState = SELECT_STATE_EXIST_HAND;
	CreatePointer();


}
void CSelect::SelectNon()
{
	m_selectSquare = nullptr;
	m_selectHandIndex = HANDBORD_TYPE_NUM;
	m_selectState = SELECT_STATE_NON;
	DestroyPointer();
	return;
}

void CSelect::Up()//y-1
{
	
	CSquareTable* table = m_player->GetTable();
	int x, y;
	switch (m_posState)
	{
	case SELECT_POS_STATE_SQUARE:
		x = m_posSquare->GetX();
		y = m_posSquare->GetY();

		if ((y-1)>=SQUARE_TABLE_MIN_Y)
		{
			SetSquarePos(table->GetSquare(x, y - 1));
		}
		else
		{
			SetHandPos(m_player->GetHand((HANDBORD_TYPE)0));
		}

		break;
	case SELECT_POS_STATE_HAND:
		SetSquarePos(table->GetSquare(SELECT_UP_INITIAL_X, SELECT_UP_INITIAL_Y));

		break;
	default:
		break;
	}
}
void CSelect::Down()//y+1
{
	int x, y;

	CSquareTable* table = m_player->GetTable();
	switch (m_posState)
	{
	case SELECT_POS_STATE_SQUARE:
		x = m_posSquare->GetX();
		y = m_posSquare->GetY();
		if ((y + 1) <= SQUARE_TABLE_MAX_Y)
		{
			SetSquarePos(table->GetSquare(x, y + 1));
		}
		else
		{
			SetHandPos(m_player->GetHand((HANDBORD_TYPE)0));
		}
		break;
	case SELECT_POS_STATE_HAND:
		SetSquarePos(table->GetSquare(SELECT_DOWN_INITIAL_X, SELECT_DOWN_INITIAL_Y));

		break;
	default:
		break;
	}
}
void CSelect::Left()//x+1
{
	int x, y;

	CSquareTable* table = m_player->GetTable();

	switch (m_posState)
	{
	case SELECT_POS_STATE_SQUARE:
		x = m_posSquare->GetX();
		y = m_posSquare->GetY();
		if ((x + 1) <= SQUARE_TABLE_MAX_X)
		{
			SetSquarePos(m_player->GetTable()->GetSquare(x + 1, y));
		}
		else
		{
			SetSquarePos(m_player->GetTable()->GetSquare(SQUARE_TABLE_MIN_X, y));
		}
		break;
	case SELECT_POS_STATE_HAND:
		if (0<=(m_posHandIndex-1))
		{
			SetHandPos(m_player->GetHand((HANDBORD_TYPE)(m_posHandIndex - 1)));
		}
		else
		{
			SetHandPos(m_player->GetHand(HANDBORD_TYPE_HISYA));
		}
	default:
		break;
	}
}
void CSelect::Right()
{
	int x, y;

	CSquareTable* table = m_player->GetTable();

	switch (m_posState)
	{
	case SELECT_POS_STATE_SQUARE:
		x = m_posSquare->GetX();
		y = m_posSquare->GetY();
		if ((x - 1) >= SQUARE_TABLE_MIN_X)
		{
			SetSquarePos(m_player->GetTable()->GetSquare(x - 1, y));

		}
		else
		{
			SetSquarePos(m_player->GetTable()->GetSquare(SQUARE_TABLE_MAX_X, y));

		}
		break;
	case SELECT_POS_STATE_HAND:

		if (HANDBORD_TYPE_NUM > (m_posHandIndex + 1))
		{
			SetHandPos(m_player->GetHand((HANDBORD_TYPE)(m_posHandIndex + 1)));
		}
		else
		{
			SetHandPos(m_player->GetHand((HANDBORD_TYPE)0));
		}
	default:
		break;
	}
}


void CSelect::Init()
{
	m_modelDrawre = m_gameobject->AddComponent<CModelDrawer>();
	m_pointer = nullptr;
}
void CSelect::Uninit()
{

}
void CSelect::Update()
{

}
void CSelect::Draw()
{

}
void CSelect::SetState(CPlayerBase* set)
{
	m_player = set;


	switch (m_player->GetPlayerState())
	{
	case PLAYER_STATE_01:
		m_modelDrawre->SetModel(CSelect::GetRedModel());

		SetSquarePos(m_player->GetTable()->GetSquare(4, 8));

		m_posState = SELECT_POS_STATE_SQUARE;
		break;
	case PLAYER_STATE_02:
		m_modelDrawre->SetModel(CSelect::GetBlueModel());
		SetSquarePos(m_player->GetTable()->GetSquare(4, 0));
		m_posState = SELECT_POS_STATE_SQUARE;
		break;
	default:
		break;
	}


}

void CSelect::SetSquarePos(CSquare* square)
{
	m_posSquare = square;
	
	m_gameobject->SetPosition(m_posSquare->GetGameObject()->GetPosition() + D3DXVECTOR3(0, 0.5f, 0));

	m_posState = SELECT_POS_STATE_SQUARE;
}
void CSelect::SetHandPos(CHandBord* hand)
{
	
	m_posHandIndex = (int)hand->GetType();
	m_gameobject->SetPosition(hand->GetGameObject()->GetPosition() + D3DXVECTOR3(0, 0.5f, 0));
	m_posState = SELECT_POS_STATE_HAND;
}

void CSelect::CreatePointer()
{
	if (m_pointer!=nullptr)
	{
		m_pointer->GetGameObject()->SetDestoroy();
	}
	CGameObject* g = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);
	m_pointer = g->AddComponent<CPointer>();
	m_pointer->Setting(this, 20);
	
}
void CSelect::DestroyPointer()
{
	if (m_pointer != nullptr)
	{
		m_pointer->GetGameObject()->SetDestoroy();
		m_pointer = nullptr;
	}

}

CPiece* CSelect::CreatePiece(PIECE_TYPE type,CSquare* pos)
{
	CGameObject* gameobject = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);
	CPiece* piece = gameobject->AddComponent<CPiece>();

	piece->StateSetting(
		type,
		m_player,
		pos);
	return piece;
		
}