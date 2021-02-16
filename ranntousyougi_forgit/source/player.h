#pragma once

#include"component.h"
#include<vector>
#include"piece.h"
#include"handbord.h"
#include"player_base.h"
class CSelect;
class CSquareTable;
class CPlayer :public CPlayerBase
{

private:


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Setting(PLAYER_STATE state, CSquareTable* table);

	void SelectSquare(CSquare* pos);
	
	void SelectHand();

	void Select();

	void Up();

	void Down();

	void Left();

	void Right();
};

