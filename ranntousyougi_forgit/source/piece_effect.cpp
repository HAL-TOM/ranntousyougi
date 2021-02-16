
#include"piece.h"
#include"sound.h"
#include"effecseer.h"
#include"main.h"
#include"game_object.h"
#include"manager.h"
#include"scene.h"
#include"piece.h"
#include"piece_effect.h"


CEffecseer* CPieceMoveEffect::m_effecseer;
CSound* CPieceMoveEffect::m_sound;
CPieceMoveEffect* CPieceMoveEffect::m_this = nullptr;

CEffecseer* CPieceRankUpEffect::m_effecseer;
CSound* CPieceRankUpEffect::m_sound;
CPieceRankUpEffect* CPieceRankUpEffect::m_this = nullptr;


CSound* CPieceUseHandEffect::m_sound;
CEffecseer* CPieceUseHandEffect::m_effecseer;
CPieceUseHandEffect* CPieceUseHandEffect::m_this = nullptr;


CEffecseer* CPieceMoveLineEffect::m_effecseer;
CPieceMoveLineEffect* CPieceMoveLineEffect::m_this = nullptr;



void CPieceEffect::Load()
{
	CPieceMoveEffect::Load();
	CPieceRankUpEffect::Load();
	CPieceUseHandEffect::Load();
	CPieceMoveLineEffect::Load();
}
void CPieceEffect::UnLoad()
{
	CPieceMoveEffect::UnLoad();
	CPieceRankUpEffect::UnLoad();
	CPieceUseHandEffect::UnLoad();
	CPieceMoveLineEffect::UnLoad();
}


//////////////////////////////////////////////////

void CPieceMoveEffect::Load()
{

	
	CGameObject* g = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);

	m_effecseer =g->AddComponent<CEffecseer>();
	m_effecseer->Load((const EFK_CHAR*)L"asset/efekseer/moev_piece.efk", 30, 0.5f, false);
	/*
	CSound::LoadSound("asset\\sound\\wav\\move_piece.wav", GetWindow());
	m_sound = g->AddComponent<CSound>();
	m_sound->SetSound("asset\\sound\\wav\\move_piece.wav", GetWindow());
	m_sound->m_volume = 4.0f;
	*/

	m_this = g->AddComponent<CPieceMoveEffect>();
}
void CPieceMoveEffect::UnLoad()
{
	m_this = nullptr;
}

void CPieceMoveEffect::Init() 
{

}
void CPieceMoveEffect::Uninit() 
{
	if (m_sound!=nullptr)
	{
		m_sound->m_play = false;
	}
}
void CPieceMoveEffect::Update() 
{
	if (m_effecseer)
	{
		return;

	}
	if (m_effecseer->GetPlayFlag() == false)
	{

		return;
	}
	if (m_sound==nullptr)
	{
		return;
	}
	if (m_sound->m_play==false)
	{

		return;
	}
	

	m_frame++;
	if (m_frame>=m_maxFrame)
	{
		m_effecseer->Stop();
	//	m_sound->StopSound();
	
		return;
	}
}
void CPieceMoveEffect::Draw() 
{

}

void CPieceMoveEffect::Play(CPiece* piece)
{

	//CManager::GetScene()->FindComponent<CDebugLogStringManager>()->Add("pieceplay");
	m_this->GetGameObject()->SetPosition(piece->GetGameObject()->GetPosition()+D3DXVECTOR3(0.0f,0.1f,0.0f));
	
	m_effecseer->Play();
	//m_sound->Play();
	
	m_this->m_frame = 0;

}

//////////////////////////////////////////////////////////////

void CPieceRankUpEffect::Load()
{

	CGameObject* g = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);

	m_effecseer = g->AddComponent<CEffecseer>();
	m_effecseer->Load((const EFK_CHAR*)L"asset/efekseer/rankup.efk", 30, 0.5f, false);
	/*
	CSound::LoadSound("asset\\sound\\wav\\rankup.wav", GetWindow());
	m_sound = g->AddComponent<CSound>();
	m_sound->SetSound("asset\\sound\\wav\\rankup.wav", GetWindow());
	m_sound->m_volume = 2.0f;
	*/
	m_this = g->AddComponent<CPieceRankUpEffect>();
}

void CPieceRankUpEffect::UnLoad()
{

	m_this = nullptr;
}

void CPieceRankUpEffect::Init()
{
}

void CPieceRankUpEffect::Uninit()
{
	if (m_sound!=nullptr)
	{
		m_sound->m_play = false;
	}
}

void CPieceRankUpEffect::Update()
{
	if (m_effecseer->GetPlayFlag() == false)
	{

		return;
	}
	if (m_sound==nullptr)
	{
		return;
	}
	if (m_sound->m_play == false)
	{

		return;
	}


	m_frame++;
	if (m_frame >= m_maxFrame)
	{
		m_effecseer->Stop();
		m_sound->StopSound();

		return;
	}
}

void CPieceRankUpEffect::Draw()
{
}

void CPieceRankUpEffect::Play(CPiece * piece)
{
	m_this->GetGameObject()->SetPosition(piece->GetGameObject()->GetPosition() + D3DXVECTOR3(0.0f, 0.1f, 0.0f));

	m_effecseer->Play();
	//m_sound->Play();

	m_this->m_frame = 0;

}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////

void CPieceUseHandEffect::Load()
{

	CGameObject* g = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);

	m_effecseer = g->AddComponent<CEffecseer>();
	m_effecseer->Load((const EFK_CHAR*)L"asset/efekseer/move_piece.efk", 30, 0.5f, false);

	//CSound::LoadSound("asset\\sound\\wav\\move_piece.wav", GetWindow());
	//m_sound = g->AddComponent<CSound>();
	//m_sound->SetSound("asset\\sound\\wav\\move_piece.wav", GetWindow());
	//m_sound->m_volume = 2.0f;

	m_this = g->AddComponent<CPieceUseHandEffect>();
}

void CPieceUseHandEffect::UnLoad()
{

	m_this = nullptr;
}

void CPieceUseHandEffect::Init()
{
}

void CPieceUseHandEffect::Uninit()
{
	if (m_sound!=nullptr)
	{
		m_sound->m_play = false;
	}
}

void CPieceUseHandEffect::Update()
{
	if (m_effecseer->GetPlayFlag() == false)
	{
		return;
	}
	if (m_sound==nullptr)
	{
		return;
	}
	if (m_sound->m_play == false)
	{
		return;
	}
	m_frame++;
	if (m_frame >= m_maxFrame)
	{
		m_effecseer->Stop();
		m_sound->StopSound();
		return;
	}
}

void CPieceUseHandEffect::Draw()
{
}

void CPieceUseHandEffect::Play(CPiece * piece)
{
	m_this->GetGameObject()->SetPosition(piece->GetGameObject()->GetPosition() + D3DXVECTOR3(0.0f, 0.1f, 0.0f));

	m_effecseer->Play();
	//m_sound->Play();

	m_this->m_frame = 0;

}

//////////////////////////////////////////////////////////////////

void CPieceMoveLineEffect::Load()
{

	CGameObject* g = CManager::GetScene()->AddGameObject(LAYER_STATE_D3);

	m_effecseer = g->AddComponent<CEffecseer>();
	m_effecseer->Load((const EFK_CHAR*)L"asset/efekseer/move_piece2.efk", 30, 0.5f, false);

	

	m_this = g->AddComponent<CPieceMoveLineEffect>();
}

void CPieceMoveLineEffect::UnLoad()
{

	m_this = nullptr;
}

void CPieceMoveLineEffect::Init()
{
}

void CPieceMoveLineEffect::Uninit()
{

}

void CPieceMoveLineEffect::Update()
{
	if (m_effecseer->GetPlayFlag() == false)
	{

		return;
	}


	m_frame++;
	if (m_frame >= m_maxFrame)
	{
		m_effecseer->Stop();
		return;
	}
	D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, ((float)m_frame / (float)m_maxFrame)*m_dif);
	m_gameobject->SetScale(scale);
}

void CPieceMoveLineEffect::Draw()
{

}

void CPieceMoveLineEffect::Play(D3DXVECTOR3 pos, float dif,float rot)
{
	return;
	m_this->GetGameObject()->SetPosition(pos);
	m_this->m_dif = dif;
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), rot);
	m_this->GetGameObject()->SetRotation(quat);
	m_effecseer->Play();

	m_this->m_frame = 0;

}
