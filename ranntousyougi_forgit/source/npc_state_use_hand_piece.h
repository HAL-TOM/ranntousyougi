#pragma once
#include "npc_state.h"

class CNpcStateUseHandPiece :
	public CNpcState
{
protected:
	int m_frame;
	CSquare* m_moveTarget;
	HANDBORD_TYPE m_selectTarget;


public:
	CNpcStateUseHandPiece();
	~CNpcStateUseHandPiece();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Setting(CSquare* move, HANDBORD_TYPE type);

	void Action();

	void Enter();
	void Exit();
};

