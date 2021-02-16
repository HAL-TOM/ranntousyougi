#pragma once
#include "npc_state.h"
class CSquare;

class CNpcStateMovePiece :	public CNpcState
{
protected:
	CSquare* m_targetSquare;
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

