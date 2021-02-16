#pragma once
#include"state.h"
#include"handbord_type.h"
enum NPC_STATE_TYPE
{
	IDLE = 0,
	MOVE,
	SELECT,
	MOVE_NON_SELECT,
	MOVE_SELECT,
	TAKE_NON_SELECT,
	TAKE_SELECT,
	USE_PIECE

};

class CNPC;
class CSquare;
class CNpcState:public CState
{
protected:
	CNPC* m_npc;
	static int m_fileNumber ;
public:
	
	virtual void Action() = 0;
	void Reset();
	void StateChengeMovePieceNonSelect(CSquare* move, CSquare* select);
	void StateChengeTakePieceNonSelect(CSquare* move, CSquare* select);
	void StateChengeUseHandPiece(CSquare* move, HANDBORD_TYPE type);

	void SetNpc(CNPC* set) { m_npc = set; }
	NPC_STATE_TYPE m_type;
};

