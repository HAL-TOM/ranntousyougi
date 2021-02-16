#pragma once
#include "npc_state.h"
class CNpcStateMovePieceNonselect :
	public CNpcState
{

protected:
	int m_frame;
	CSquare* m_moveTarget;
	CSquare* m_selectTarget;
	//void Reset();

public:
	CNpcStateMovePieceNonselect();
	~CNpcStateMovePieceNonselect();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Setting(CSquare* move, CSquare* select);
	void StateChengeMovePieceSelect(CSquare* move);
	//void StateChengeTakePieceNonSelect(CSquare* move, CSquare* select);
	//void StateChengeTakePieceSelect(CSquare* move);
	//void StateChengeUseHandPiece(CSquare* move,HANDBORD_TYPE type);

	void Action();

	void Enter();
	void Exit();
};

