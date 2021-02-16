#pragma once
#include"component.h"
class CNumber;
class CGameTimer:public CComponent
{
protected:
	int m_time;
	int m_timeMax;
	CNumber* m_number;
public:
	CGameTimer();
	~CGameTimer();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void TimerSet(int time);
};

