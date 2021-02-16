#pragma once
#include "action.h"
class CActionTakePiece :
	public CAction
{
protected:
	CPlayerBase* m_player;
	CPlayerBase* m_enemy;

	CSquare* m_pieceSquare;
	CSquare* m_targetSquare;

public:
	CActionTakePiece(ACTION_TYPE type) { m_type = type; }

	void Setting(CPlayerBase* player, CPlayerBase* enemy, CSquare* pieceSquare, CSquare* targetSquare);
	int  CreateValue()override;
	CSquare* GetPieceSquare() { return m_pieceSquare; }
	CSquare* GetTargetSquare() { return m_targetSquare; }


	

};

