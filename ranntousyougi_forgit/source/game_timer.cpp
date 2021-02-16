#include "game_timer.h"
#include"manager.h"
#include"scene.h"
#include"game_manager.h"
#include"number.h"
#include"result_scene.h"
CGameTimer::CGameTimer()
{
}


CGameTimer::~CGameTimer()
{
}

void CGameTimer::Init()
{
	m_number=m_gameobject->AddComponent<CNumber>();
	m_number->SetNum((m_timeMax - m_time) / 60);

	m_gameobject->SetPosition(D3DXVECTOR3(14.0f, 0.0f, 13.0f));
	m_gameobject->SetScale(D3DXVECTOR3(1.0f,1.0f, 1.0f));
}

void CGameTimer::Uninit()
{
}

void CGameTimer::Update()
{
	m_number->SetNum((m_timeMax - m_time) / 60);

	if (m_time>m_timeMax)
	{
		CGameManager::SetDraw(true);
	
	}
	m_time++;
}

void CGameTimer::Draw()
{
}

void CGameTimer::TimerSet(int time)
{
	m_timeMax = time;
	m_time = 0;
}
