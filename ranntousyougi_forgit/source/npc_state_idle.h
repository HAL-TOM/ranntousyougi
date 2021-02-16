#pragma once
#include "npc_state.h"
class CNpcStateIdle :
	public CNpcState
{
private:
	int m_frame ;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void StateChenge();

	void Action();

	void Enter();
	void Exit();
};

