#pragma once
#include "component.h"
#include"model.h"
class CSelect;
class CModelDrawer;
class CPointer :
	public CComponent
{
public:
	static CModel* m_redModel;
	static CModel* m_blueModel;

	int m_interval;
	int m_frame=0;
	bool m_up;


	CModel* m_model;
	CModelDrawer* m_drawer;
	CSelect* m_select;
	CPointer();
	~CPointer();
	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Setting(CSelect* select,int interval);
};

