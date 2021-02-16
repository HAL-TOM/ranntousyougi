#pragma once
#include"component.h"
class CModel;
class CSquareTable;
class CPiece;
class CEffecseer;

struct SSquareDate
{

	int m_posX;//位置
	int m_posY;//位置
	CPiece* m_piece = nullptr;//コマ
	CSquareTable* m_table;//所属しているテーブル
};


class CSquare:public CComponent
{
protected:
	
	SSquareDate m_date;

	CEffecseer* m_effect;
	static CModel* m_model;
public:
	CSquare();
	~CSquare();

	static void Load();
	static void UnLoad();
	static CModel* GetModel() { return m_model; };
	CEffecseer* GetEffect() { return m_effect; }
	void Init();
	void Uninit();
	void Draw();
	void Update();
	CPiece* GetPiece() { return m_date.m_piece; }
	void SetPiece(CPiece* set) { m_date.m_piece = set; }
	void SetTable(CSquareTable* table) { m_date.m_table = table; }
	void SetXY(int x, int y) { m_date.m_posX = x; m_date.m_posY = y; }
	int GetX() { return  m_date.m_posX; }
	int GetY() { return  m_date.m_posY; }

	void EffectPlay();
	void EffectStop();
};

