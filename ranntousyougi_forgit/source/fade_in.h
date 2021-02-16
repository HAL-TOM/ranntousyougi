#pragma once
#include "component.h"
class CFadeIn :
	public CComponent
{
public:
	int m_moveFrame;
	int m_moveEndFrame;
	CFadeIn();
	~CFadeIn();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

