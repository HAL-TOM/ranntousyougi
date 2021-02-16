#pragma once
#include "component.h"
class CModel;
class CModelDrawer :public CComponent
{
protected:
	CModel* m_model = nullptr;
public:
	CModelDrawer();
	~CModelDrawer();
	CModel* GetModel() { return m_model; }
	void SetModel(CModel* set) {m_model = set; }
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

