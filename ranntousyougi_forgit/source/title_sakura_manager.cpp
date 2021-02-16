#include"title_sakura.h"
#include"game_object.h"
#include"manager.h"
#include"scene.h"
#include"main.h"
#include "title_sakura_manager.h"
void CTitleSakuraManager::Init()
{

}
void CTitleSakuraManager::Uninit() 
{

}
void CTitleSakuraManager::Update() 
{
	if (frame%30==0)
	{
		if (m_sakura.size()<100)
		{
			CGameObject* g = CManager::GetScene()->AddGameObject(LAYER_STATE_D2);
			g->SetScale(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
			
			if ((rand()*rand())%2==0)
			{
				g->SetPosition(D3DXVECTOR3((SCREEN_WIDTH/2) + (((rand() % 1000) / 1000.0f)-0.5f)*SCREEN_WIDTH, - 30 ,0));

			}
			else
			{
				g->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + 30, (SCREEN_HEIGHT / 2) + (((rand() % 1000) / 1000.0f) - 0.5f)*SCREEN_HEIGHT , 0));

			}
			CTitleSakura* s = g->AddComponent<CTitleSakura>();
			s->SetManager(this);
			m_sakura.push_back(s);
		}
	}
	frame++;
}
void CTitleSakuraManager::Draw()
{
	for (CTitleSakura* s:m_sakura)
	{

		s->DrawSakura();
	}
}

void CTitleSakuraManager::Remove(CTitleSakura* s)
{
	m_sakura.remove(s);

}
