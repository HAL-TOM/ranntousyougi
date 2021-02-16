#include "square.h"
#include"model_drawer.h"
#include"model.h"
#include"effecseer.h"
#include"game_object.h"

CModel*  CSquare::m_model = nullptr;



CSquare::CSquare()
{
}


CSquare::~CSquare()
{
}
void CSquare::Load()
{
	
}
void CSquare::UnLoad()
{
	
}

void CSquare::Init()
{
	m_effect = m_gameobject->AddComponent<CEffecseer>();
	
	if (m_effect->Load((const EFK_CHAR*)L"asset/efekseer/square_effect.efk", 60, 0.5f, true))
	{
		int a = 0;
		a++;

	}
	else
	{
		int b = 0;
		b++;
	}
}
void CSquare::Uninit()
{

}
void CSquare::Draw()
{

}
void CSquare::Update()
{

}

void CSquare::EffectPlay()
{
	m_effect->Play();
	
}

void CSquare::EffectStop()
{
	m_effect->Stop();
}
