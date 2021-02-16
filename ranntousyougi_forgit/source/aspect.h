#pragma once

#include"component.h"


class CAspect//�ǖ�
{

protected:

	CPlayerBase* m_player01;//��{�I��NPC�̂���
	CPlayerBase* m_player02;//�G�i�v���C���[�j
	CHandBord* m_hand01[HANDBORD_TYPE_NUM];
	CHandBord* m_hand02[HANDBORD_TYPE_NUM];

	CSquareTable* m_table;
	
public:

	int GetValue();//�]���֐�::+�Ȃ�L��-�Ȃ�s��
	


	void SetPlayer01(CPlayerBase* set) { m_player01 = set; }
	void SetPlayer02(CPlayerBase* set) { m_player02 = set; }
	void SetHand01(HANDBORD_TYPE type, CHandBord* set) { m_hand01[type] = set; }
	void SetHand02(HANDBORD_TYPE type, CHandBord* set) { m_hand02[type] = set; }
	void SetTable(CSquareTable* table) { m_table = table; }

};

