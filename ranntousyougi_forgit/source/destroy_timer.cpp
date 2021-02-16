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

//���������ɕK���g������
void CDestoroyTimer::Set(int frame)
{
	m_count = true;
	m_endFrame = frame;
	m_frame = 0;
}

//�J�E���g���Z�b�g
void CDestoroyTimer::Reset()
{
	m_frame = 0;
}

//��~
void CDestoroyTimer::Stop()
{
	m_count = false;
}

//�ĊJ
void CDestoroyTimer::Play() 
{
	m_count = true;
}