#pragma once

#include"component.h"


class CAspect//局面
{

protected:

	CPlayerBase* m_player01;//基本的にNPCのこと
	CPlayerBase* m_player02;//敵（プレイヤー）
	CHandBord* m_hand01[HANDBORD_TYPE_NUM];
	CHandBord* m_hand02[HANDBORD_TYPE_NUM];

	CSquareTable* m_table;
	
public:

	int GetValue();//評価関数::+なら有利-なら不利
	


	void SetPlayer01(CPlayerBase* set) { m_player01 = set; }
	void SetPlayer02(CPlayerBase* set) { m_player02 = set; }
	void SetHand01(HANDBORD_TYPE type, CHandBord* set) { m_hand01[type] = set; }
	void SetHand02(HANDBORD_TYPE type, CHandBord* set) { m_hand02[type] = set; }
	void SetTable(CSquareTable* table) { m_table = table; }

};

