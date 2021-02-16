#pragma once
#include "action.h"
class CSquare;
class CPlayerBase;
class CActionMovePiece :
	public CAction
{
protected:
	CPlayerBase* m_player; 
	CPlayerBase* m_enemy;

	CSquare* m_pieceSquare;
	CSquare* m_targetSquare;



public:
	CActionMovePiece(ACTION_TYPE type) { m_type = type; }
	void Setting(CPlayerBase* player, CPlayerBase* enemy, CSquare* pieceSquare, CSquare* targetSquare);
	int  CreateValue()override;

	CPlayerBase* GetPlayer() {return m_player; }
	CPlayerBase* GetEnemy() {return m_enemy; }

	CSquare* GetPieceSquare() { return m_pieceSquare; }
	CSquare* GetTargetSquare() { return m_targetSquare; }
};

