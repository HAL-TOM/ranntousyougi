#pragma once
#include"npc_state.h"
class CNpcStateMovePieceSelect :
	public CNpcState
{
protected:
	int m_frame;
	CSquare* m_moveTarget;
	//void Reset();

public:
	CNpcStateMovePieceSelect();
	~CNpcStateMovePieceSelect();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Setting(CSquare* move);

	//void StateChengeMovePieceSelect();
	//void StateChengeMovePieceNonSelect(CSquare* move, CSquare* select);
	//void StateChengeTakePieceNonSelect(CSquare* move, CSquare* select);
	//void StateChengeTakePieceSelect(CSquare* move);
	//void StateChengeUseHandPiece(CSquare* move, HANDBORD_TYPE type);

	void Action();

	void Enter();
	void Exit();
};

