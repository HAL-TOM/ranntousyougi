#include "piece_cool_timer.h"
#include"piece.h"
#include"number.h"
#include"manager.h"
#include"scene.h"
#include"game_object.h"
#include"player.h"
CPieceCoolTimer::CPieceCoolTimer()
{
}


CPieceCoolTimer::~CPieceCoolTimer()
{
}
void CPieceCoolTimer::Init()
{

}
void CPieceCoolTimer::Uninit()
{

}
void CPieceCoolTimer::Update()
{
	m_number->SetNum(m_timer / 60);
	m_gameobject->SetPosition(m_piece->GetGameObject()->GetPosition() + D3DXVECTOR3(0.4f, 0.4f, -0.4f));
	m_timer--;
	if (m_timer<0)
	{
		m_piece->CoolUnSet();
	}
}
void CPieceCoolTimer::Draw()
{

}

void CPieceCoolTimer::Setting(CPiece* piece, int time)
{
	m_piece = piece;
	m_timer = time;

	m_number = m_gameobject->AddComponent<CNumber>();
	
	m_number->SetNum(m_timer / 60);
	m_gameobject->SetPosition(m_piece->GetGameObject()->GetPosition() + D3DXVECTOR3(0.4f, 0.4f, -0.4f));
	m_gameobject->SetScale(D3DXVECTOR3(0.75f, 0.75f, 0.75f));

}