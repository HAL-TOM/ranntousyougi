#pragma once
#include "component.h"
class CSquare;
//”Õ–Ê‚ÌˆÊ’uŽw’è—p
enum BORD_X
{
	BORD_X_1=0,
	BORD_X_2,
	BORD_X_3,
	BORD_X_4,
	BORD_X_5,
	BORD_X_6,
	BORD_X_7,
	BORD_X_8,
	BORD_X_9,
	BORD_X_NUM
};
enum BORD_Y
{
	BORD_Y_1 = 0,
	BORD_Y_2,
	BORD_Y_3,
	BORD_Y_4,
	BORD_Y_5,
	BORD_Y_6,
	BORD_Y_7,
	BORD_Y_8,
	BORD_Y_9,
	BORD_Y_NUM
};
class CModel;

class CBord :
	public CComponent
{
private:
	static CModel* m_model;

public:
	CBord();
	~CBord();
	static void Load();
	static void UnLoad();
	static CModel* GetModel() { return m_model; }
	void Init();
	void Uninit();
	void Draw();
	void Update();


};