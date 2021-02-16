#pragma once
#include"component.h"

#include"main.h"
enum CAMERA_POSITION_STATE
{
	CAMERA_POSITION_STATE_STAY = 0,
	CAMERA_POSITION_STATE_TARGET_THIRD_PERSON,
	CAMERA_POSITION_STATE_TARGET_TOP_VIEW,
	CAMERA_POSITION_STATE_NUM

};


class  CCamera:public CComponent
{
private:
	CGameObject* m_Target;
	D3DXMATRIX m_viewMatrix;
	CAMERA_POSITION_STATE m_cameraPosState=CAMERA_POSITION_STATE_STAY;
public:
	CGameObject* GetTarget() { return m_Target; }
	void SetTarget(CGameObject* set) { m_Target = set; }
	D3DXMATRIX GetViewMatrix() { return m_viewMatrix; }
	void SetSatate(CAMERA_POSITION_STATE set) { m_cameraPosState = set; }
	void Init();
	void Uninit();
	void Update();
	void Draw();
};