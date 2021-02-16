#pragma once
#include "action.h"
#include"handbord_type.h"
class CPlayerBase;
class CActionUseHand :
	public CAction
{
protected:
	CPlayerBase* m_player;
	CPlayerBase* m_enemy;

	HANDBORD_TYPE m_handbordType;
	CSquare* m_targetSquare;
public:
	CActionUseHand(ACTION_TYPE type) { m_type = type; }

	void Setting(CPlayerBase* player, CPlayerBase* enemy, HANDBORD_TYPE handbordType, CSquare* targetSquare);

	int  CreateValue()override;

	HANDBORD_TYPE GetHandBordType() {return m_handbordType; }
	CSquare* GetTarget() { return m_targetSquare; }

};

