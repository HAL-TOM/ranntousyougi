#pragma once
#include "npc_state.h"
class CSquare;
class CNpcStateSelectSquare :	public CNpcState
{
protected:
	CSquare* m_targetSquare;
	int m_frame = 0;

public:



	void Init();
	void Uninit();
	void Update();
	void Draw();

	void StateChengeMovePiece();
	void StateChengeIdle();
	void Action();

	void Enter() ;
	void Exit() ;
};

