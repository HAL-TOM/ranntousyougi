#pragma once
#include"component.h"
#define SQUARE_TABLE_MIN_X (0)
#define SQUARE_TABLE_MIN_Y (0)
#define SQUARE_TABLE_MAX_X (8)
#define SQUARE_TABLE_MAX_Y (8)
#define SQUARE_CUT_LENGH (1.8f)
class CSquare;
class CBord;
class CSquareTable :public CComponent
{
public:


	CBord* m_bord;
	//x,y
	CSquare* m_square[9][9];

	CSquareTable();
	~CSquareTable();
	CSquare* GetSquare(int x, int y) 
	{
		if ((SQUARE_TABLE_MAX_X >= x) && (SQUARE_TABLE_MAX_Y >= y) && (SQUARE_TABLE_MIN_X <= x) && (SQUARE_TABLE_MIN_Y <= y)) 
		{
			return m_square[x][y];
		} 
		return nullptr;
	}
	void SetSquare(int x, int y, CSquare* set) 
	{
		if ((SQUARE_TABLE_MAX_X >= x) && (SQUARE_TABLE_MAX_Y >= y) && (SQUARE_TABLE_MIN_X <= x) && (SQUARE_TABLE_MIN_Y <= y))
		{
			m_square[x][y] = set;
		}
	}
	void Init();
	void Uninit();
	void Draw();
	void Update();
};

