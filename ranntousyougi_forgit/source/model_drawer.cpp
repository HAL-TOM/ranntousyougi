#include "model_drawer.h"
#include"game_object.h"
#include"model.h"
CModelDrawer::CModelDrawer()
{
}


CModelDrawer::~CModelDrawer()
{

}
void CModelDrawer::Init()
{

}
void CModelDrawer::Uninit()
{

}
void CModelDrawer::Update()
{


}
void CModelDrawer::Draw()
{
	D3DXQUATERNION rot = m_gameobject->GetRotation();

	//マトリクス変換
	D3DXMATRIX mtxWorld, mtxScale, mtxRot, mtxTrans;
	D3DXMatrixScaling(&mtxScale, m_gameobject->GetScale().x, m_gameobject->GetScale().y, m_gameobject->GetScale().z);
	D3DXMatrixRotationQuaternion(&mtxRot, &rot);
	D3DXMatrixTranslation(&mtxTrans, m_gameobject->GetPosition().x, m_gameobject->GetPosition().y, m_gameobject->GetPosition().z);
	mtxWorld = mtxScale * mtxRot * mtxTrans;

	CRenderer::SetWorldMatrix(&mtxWorld);

	m_model->ModelDraw();
	
}
