#include"player.h"
#include"select.h"
#include"manager.h"
#include"scene.h"
#include"game_object.h"
#include"handbord.h"
#include"piece.h"
#include"input.h"
#include"player_select.h"
#include"square.h"
void CPlayer::SelectSquare(CSquare* pos)
{
	std::vector<CHandBord*>::iterator handItr;
	CPiece* piece;
	CNumber number;
	switch (m_select->GetSelectState())
	{


	case SELECT_STATE_EXIST_SQUARE:
	{
		if (pos->GetPiece() != nullptr)//	引数のマスに駒があるか
		{
			if (pos->GetPiece()->GetPlayer()->GetPlayerState() == GetPlayerState())//自分の駒
			{
				//引数の駒を選択する
				ChoiceSquare();

				return;
			}
			else//敵の駒
			{


				piece = m_select->GetSelectSquare()->GetPiece();
				CPiece* enemyPiece = pos->GetPiece();

				if (piece->Judge(pos) == true)//そのマスに移動出来るかどうか
				{
					//敵の駒関係
					{
						TakePiece(pos, piece, enemyPiece);
						return;
					}
				}
			}
		}
		else
		{
			piece = m_select->GetSelectSquare()->GetPiece();

			if (piece->Judge(pos) == true)//そのマスに移動出来るかどうか
			{
				//駒の移動
				MovePiece(pos, piece);
			

				//何も選んでいない状態にする
				ChoiceNon();
				return;
			}
		}
	}
	break;
	case SELECT_STATE_EXIST_HAND:
		//持ち駒を選択している
		if (pos->GetPiece() != nullptr)//	引数のマスに駒がある
		{
			if (pos->GetPiece()->GetPlayer()->GetPlayerState() == GetPlayerState())//自分の駒
			{
				//引数の駒を選択する
				ChoiceSquare();
				return;
			}

		}
		else//引数のマスに駒がない
		{
			UseHand();
		}
		break;
	case SELECT_STATE_NON:
		if (pos->GetPiece() != nullptr)//	引数のマスに駒があるか
		{
			if (pos->GetPiece()->GetPlayer()->GetPlayerState() == GetPlayerState())//自分の駒かどうか
			{
				//駒を選択
				ChoiceSquare();
				return;
			}
		}
		break;
	default:
		break;
	}
}
void CPlayer::SelectHand()
{
	ChoiceHand();
	//m_select->SelectHand();
}
void CPlayer::Select()
{
	switch (m_select->GetPosState())
	{
	case SELECT_POS_STATE_SQUARE:
		SelectSquare(m_select->GetPosSquare());
		break;
	case SELECT_POS_STATE_HAND:
		SelectHand();
		break;
	default:
		break;
	}
}

void CPlayer::Init()
{


	
}
void CPlayer::Uninit()
{

}
void CPlayer::Update() 
{
	switch (m_playerState)
	{

	case PLAYER_STATE_01:
		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			Select();
		}
		if (CInput::GetKeyTrigger('W'))
		{
			Up();
		}

		if (CInput::GetKeyTrigger('S'))
		{
			Down();
		}
		if (CInput::GetKeyTrigger('A'))
		{
			Left();
		}
		if (CInput::GetKeyTrigger('D'))
		{
			Right();
		}

		break;
	case PLAYER_STATE_02:
		if (CInput::GetKeyTrigger(VK_RETURN))
		{
			Select();
		}
		if (CInput::GetKeyTrigger(VK_UP))
		{
			Up();
		}
		if (CInput::GetKeyTrigger(VK_DOWN))
		{
			Down();
		}
		if (CInput::GetKeyTrigger(VK_RIGHT))
		{
			Right();
		}
		if (CInput::GetKeyTrigger(VK_LEFT))
		{
			Left();
		}
		

		break;
	default:
		break;
	}

}
void CPlayer::Draw()
{

}

void CPlayer::Setting(PLAYER_STATE state, CSquareTable* table)
{
	SetPlayerState(state);
	SetTable(table);
	D3DXVECTOR3 pos;
	D3DXQUATERNION quat;

	CGameObject* gameobject = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);
	m_select = gameobject->AddComponent<CPlayerSelect>();
	m_select->SetState(this);

	for (int i = 0; i < HANDBORD_TYPE_NUM; i++)
	{
		gameobject = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);;


		switch (this->m_playerState)
		{
		case PLAYER_STATE_01:
			pos = D3DXVECTOR3(-9.0f, 1.0f, -11.0f);

			gameobject->SetPosition(pos + (D3DXVECTOR3((i % 10)*1.8f, 0.0f, (i / 10) * -1.8f)));
			D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(0));
			gameobject->SetRotation(quat);
			gameobject->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			break;
		case PLAYER_STATE_02:
			pos = D3DXVECTOR3(-9.0f, 1.0f, 11.0f);

			gameobject->SetPosition(pos + (D3DXVECTOR3((i % 10)*1.8f, 0.0f, (i / 10) * -1.8f)));
			D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(0));
			gameobject->SetRotation(quat);
			gameobject->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

			break;
		default:
			break;
		}
		m_hand[i] = gameobject->AddComponent<CHandBord>();
		m_hand[i]->Setting(this, (HANDBORD_TYPE)i);

	}
}

void CPlayer::Up()
{
	m_select->Up();
}
void CPlayer::Down()
{
	m_select->Down();

}
void CPlayer::Left()
{
	m_select->Left();

}
void CPlayer::Right()
{
	m_select->Right();


}
