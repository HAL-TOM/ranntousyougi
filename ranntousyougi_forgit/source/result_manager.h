#pragma once
#include"component.h"
class CResultManager:public CComponent
{
public:
	CResultManager();
	~CResultManager();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

