#include "pointer.h"
#include"component.h"
#include"game_object.h"
#include"model_drawer.h"
#include"select.h"
#include"player.h"
CModel* CPointer::m_blueModel;
CModel* CPointer::m_redModel;
CPointer::CPointer()
{
}


CPointer::~CPointer()
{
}
void  CPointer::Load()
{
	m_redModel = new CModel();
	m_blueModel = new CModel();

	m_redModel->Load("asset\\model\\pointer_red.obj");
	m_blueModel->Load("asset\\model\\pointer_blue.obj");
}
void  CPointer::UnLoad()
{
	m_redModel->Unload();
	m_blueModel->Unload();

	delete m_redModel;
	delete m_blueModel;
}
void CPointer::Init()
{
	m_model = m_gameobject->AddComponent<CModel>();
	m_drawer = m_gameobject->AddComponent<CModelDrawer>();
	
	
}
void CPointer::Uninit()
{

}
void CPointer::Update()
{

	m_model->SetModelAlpha((float)m_frame / (float)m_interval);
	if (m_up)
	{
		m_frame++;
		if (m_interval<m_frame)
		{
			m_frame = m_interval;
			m_up = false;
		}
	}
	else
	{
		m_frame--;
		if (0 > m_frame)
		{
			m_frame =0;
			m_up = true;
		}
	}
}
void CPointer::Draw()
{

}
void CPointer::Setting(CSelect* select, int interval)
{
	m_select = select;
	m_interval = interval;
	m_frame = 0;
	m_up = true;
	m_gameobject->SetPosition(m_select->GetGameObject()->GetPosition());
	m_gameobject->SetScale(m_select->GetGameObject()->GetScale());
	if (m_select->GetPlayer()->GetPlayerState() == PLAYER_STATE_01)
	{
		m_model = new CModel(*m_redModel);
		m_drawer->SetModel(m_model);
		return;
	}
	if (m_select->GetPlayer()->GetPlayerState() == PLAYER_STATE_02)
	{
		m_model = new CModel(*m_blueModel);
		m_drawer->SetModel(m_model);
		return;
	}
	return;
}