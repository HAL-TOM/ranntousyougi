#include "fade_in.h"

#include"renderer.h"
#include"component.h"
#include"game_object.h"
CFadeIn::CFadeIn()
{
}


CFadeIn::~CFadeIn()
{
}
void CFadeIn::Init()
{

}
void CFadeIn::Uninit()
{

}
void CFadeIn::Update()
{
	m_moveFrame++;
	CRenderer::SetGloabalAlpha((float)m_moveFrame / (float)m_moveEndFrame);
	if (m_moveEndFrame < m_moveFrame)
	{
		CRenderer::SetGloabalAlpha(1);
		m_gameobject->SetDestoroy();
		
	}

}
void CFadeIn::Draw()
{

}