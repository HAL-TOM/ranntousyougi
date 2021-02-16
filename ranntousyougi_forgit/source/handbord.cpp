#include "piece.h"
#include"model_drawer.h"
#include"game_object.h"
#include"manager.h"
#include"scene.h"
#include"player_base.h"
#include"square.h"
#include"square_table.h"

#include "handbord.h"

CHandBord::CHandBord()
{
}


CHandBord::~CHandBord()
{
}
PIECE_TYPE CHandBord::PiecetypeToHandtype(HANDBORD_TYPE handType)
{
	switch (handType)
	{
	case HANDBORD_TYPE_HUHYOU:
		return PIECE_TYPE_HUHYOU;
		break;

	case HANDBORD_TYPE_KYOUSYA:
		return PIECE_TYPE_KYOUSYA;
		break;

	case HANDBORD_TYPE_KEIMA:
		return PIECE_TYPE_KEIMA;
		break;

	case HANDBORD_TYPE_GINN:
		return PIECE_TYPE_GINN;
		break;

	case HANDBORD_TYPE_KINN:
		return PIECE_TYPE_KINN;
		break;

	case HANDBORD_TYPE_KAKU:
		return PIECE_TYPE_KAKU;
		break;

	case HANDBORD_TYPE_HISYA:
		return PIECE_TYPE_HISYA;
		break;

	default:
		break;
	}

	return PIECE_TYPE_NUM;
}
HANDBORD_TYPE CHandBord::HandtypeToPiecetype(PIECE_TYPE pieceType)
{
	switch (pieceType)
	{
	case PIECE_TYPE_HUHYOU:
		return HANDBORD_TYPE_HUHYOU;
		break;

	case PIECE_TYPE_NARIKIN:
		return HANDBORD_TYPE_HUHYOU;
		break;

	case PIECE_TYPE_KYOUSYA:
		return HANDBORD_TYPE_KYOUSYA;
		break;

	case PIECE_TYPE_NARIKYOU:
		return HANDBORD_TYPE_KYOUSYA;
		break;

	case PIECE_TYPE_KEIMA:
		return HANDBORD_TYPE_KEIMA;
		break;

	case PIECE_TYPE_NARIKEI:
		return HANDBORD_TYPE_KEIMA;
		break;

	case PIECE_TYPE_GINN:
		return HANDBORD_TYPE_GINN;
		break;

	case PIECE_TYPE_NARIGINN:
		return HANDBORD_TYPE_GINN;
		break;

	case PIECE_TYPE_KINN:
		return HANDBORD_TYPE_KINN;
		break;

	case PIECE_TYPE_KAKU:
		return HANDBORD_TYPE_KAKU;
		break;

	case PIECE_TYPE_UMA:
		return HANDBORD_TYPE_KAKU;
		break;

	case PIECE_TYPE_HISYA:
		return HANDBORD_TYPE_HISYA;
		break;

	case PIECE_TYPE_RYUUOU:
		return HANDBORD_TYPE_HISYA;
		break;

	default:
		break;
	}

	return HANDBORD_TYPE_NUM;
}

void CHandBord::Setting(CPlayerBase* player,HANDBORD_TYPE type)
{
	this->SetType(type);
	this->SetPlayer(player);
	m_number->GetGameObject()->SetPosition(this->m_gameobject->GetPosition() + D3DXVECTOR3(0.4f, 0.4f, -0.4f));
	m_number->GetGameObject()->SetScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));
	CModelDrawer* model = GetGameObject()->AddComponent<CModelDrawer>();
	model->SetModel(CPiece::GetModel(CHandBord::PiecetypeToHandtype( m_type)));
	m_gameobject->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));

}
bool CHandBord::Judge(CSquare * s)
{
	if (s==nullptr)
	{
		return false;
	}
	if (s->GetPiece()!=nullptr)
	{
		return false;
	}
	if (this->m_type==HANDBORD_TYPE_HUHYOU)
	{
		for (int i = 0; i <= SQUARE_TABLE_MAX_Y; i++)
		{
			if (i!=s->GetY())
			{
				CPiece* piece = m_player->GetTable()->GetSquare(s->GetX(), i)->GetPiece();
				if (piece !=nullptr)
				{
					if (piece->GetType()==PIECE_TYPE_HUHYOU)
					{
						if (piece->GetPlayer()->GetPlayerState()==m_player->GetPlayerState())
						{
							return false;
						}
					}
				}
			}
		
		}
	}
	return true;
}
void CHandBord::Init()
{
	CGameObject * gameobject = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);
	m_number = gameobject->AddComponent<CNumber>();
	
}
void CHandBord::Uninit()
{

}
void CHandBord::Update()
{

}
void CHandBord::Draw()
{

}