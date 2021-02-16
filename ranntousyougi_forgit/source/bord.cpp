#include "bord.h"
#include"model.h"
#include"model_drawer.h"
#include"game_object.h"
#include"component.h"
CModel* CBord::m_model=nullptr;

CBord::CBord()
{
}


CBord::~CBord()
{

}
void CBord:: Load()
{
	m_model = new CModel();
	m_model->Load("asset\\model\\bord.obj");
}
void CBord::UnLoad()
{
	m_model->Unload();
	delete m_model;

}
void CBord::Init()
{
	CModelDrawer* modelDrawer = m_gameobject->AddComponent<CModelDrawer>();
	modelDrawer->SetModel(m_model);
}
void CBord::Uninit()
{

}
void CBord::Draw()
{

}
void CBord::Update()
{

}