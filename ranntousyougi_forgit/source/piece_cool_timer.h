#pragma once
#include "component.h"
class CPiece;
class CNumber;
class CPieceCoolTimer :
	public CComponent
{
public:
	CPiece* m_piece;
	CNumber* m_number;
	int m_timer;
	CPieceCoolTimer();
	~CPieceCoolTimer(); 

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Setting(CPiece* piece,int time);
};

