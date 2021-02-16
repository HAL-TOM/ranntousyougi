#include "destroy_timer.h"
#include"game_object.h"


CDestoroyTimer::CDestoroyTimer()
{
}


CDestoroyTimer::~CDestoroyTimer()
{
}

void CDestoroyTimer::Init()
{
	m_count = false;
	m_endFrame = 0;
	m_frame = 0;
}
void CDestoroyTimer::Uninit()
{

}
void CDestoroyTimer::Update()
{
	if (m_count==true)
	{
		m_frame++;
		if (m_frame>=m_endFrame)
		{
			m_gameobject->SetDestoroy();
		}
	}
}
void CDestoroyTimer::Draw()
{

}

//初期化時に必ず使うこと
void CDestoroyTimer::Set(int frame)
{
	m_count = true;
	m_endFrame = frame;
	m_frame = 0;
}

//カウントリセット
void CDestoroyTimer::Reset()
{
	m_frame = 0;
}

//停止
void CDestoroyTimer::Stop()
{
	m_count = false;
}

//再開
void CDestoroyTimer::Play() 
{
	m_count = true;
}