#pragma once
#include "npc_state.h"
class CNpcStateTakePieceSelect :
	public CNpcState
{
protected:
	int m_frame;
	CSquare* m_moveTarget;

public:
	CNpcStateTakePieceSelect();
	~CNpcStateTakePieceSelect();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Setting(CSquare* move);

	void Action();

	void Enter();
	void Exit();
};

