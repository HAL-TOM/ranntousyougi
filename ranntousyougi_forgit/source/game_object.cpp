#include"game_object.h"
#include"component.h"

bool CGameObject::Destoroy()
{
	if (m_Destoroy)
	{
		Uninit();
		delete this;
		return true;
	}
	else
	{
		m_component.remove_if([](CComponent* component) {return component->Destoroy(); });

		return false;
	}
	
}
void CGameObject::Init()
{

}
void CGameObject::Uninit()
{
	for (CComponent *comp : m_component)
	{
		comp->Uninit();
		delete comp;
	}
}
void CGameObject::Update()
{
	for (CComponent *comp : m_component)
	{
		if (comp->GetEnable() == true)
		{
			comp->Update();
		}

	}

}
void CGameObject::Draw()
{
	for (CComponent *comp : m_component)
	{
		if (comp->GetEnable()==true)
		{
			comp->Draw();
		}
	}
}
