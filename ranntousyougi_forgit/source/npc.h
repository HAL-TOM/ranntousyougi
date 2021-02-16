#pragma once
#include"player_base.h"

class CSquare;
class CHandBord;
class CNpcState;

enum NPC_ROUTINE
{
	NPC_ROUTINE_SELECT_PIECE = 0,
	NPC_ROUTINE_MOVE_PIECE,

};

class CNPC :
	public CPlayerBase
{
private:
	int m_frame;
	CNpcState* m_state ;

	

public:
	CNPC();
	~CNPC();

	void MoveSelectToSquare(CSquare*nextSquare);
	void MoveSelectToHand(HANDBORD_TYPE nextHand);

	void SetState(CNpcState *state) { m_state = state; }
	virtual void Setting(PLAYER_STATE state, CSquareTable* table);
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetUp();

};

