#pragma once
#include "select.h"
#include<vector>
class CEffecseer;
class CPlayerSelect : public CSelect
{

private:
	std::vector<CEffecseer*> m_effecseerList;
	void CreateEffect();
	void DestoroyEfect();
public:


	virtual void ChoiceSquare()override;//���I������i�Ֆʁj
	void SelectNon() override;
	void Update()override;
};

