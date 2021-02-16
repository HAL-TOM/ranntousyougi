#pragma once
#include "npc_state.h"

class CNpcStateTakePieceNonSelect :
	public CNpcState
{
protected:
	int m_frame;
	CSquare* m_moveTarget;
	CSquare* m_selectTarget;

	//void Reset();

public:
	CNpcStateTakePieceNonSelect();
	~CNpcStateTakePieceNonSelect();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Setting(CSquare* move, CSquare* select);
	//void StateChengeMovePieceNonSelect(CSquare* move, CSquare* select);
	//void StateChengeMovePieceSelect(CSquare* move);
	void StateChengeTakePieceSelect(CSquare* move);
	//void StateChengeUseHandPiece(CSquare* move, HANDBORD_TYPE type);
	void Action();

	void Enter();
	void Exit();
};

