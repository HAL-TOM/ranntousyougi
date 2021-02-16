#pragma once
#include "component.h"
#include"number.h"
#include"piece.h"
#include"handbord_type.h"
const int HANDBORD_X_NUM = 10;
const int HANDBORD_Y_NUM = 3;
const float HANDBORD_X_CUT = 1.0f;
const float HANDBORD_Y_CUT = 1.0f;
class CPlayerBase;

enum HANDBORD_STATE
{
	HANDBORD_STATE_EXIST,
	HANDBORD_STATE_NON,
	HANDBORD_STATE_NUM,

};

class CPiece;

class CHandBord :
	public CComponent
{
private:

public:
	CPlayerBase* m_player = nullptr;
	HANDBORD_STATE m_handState = HANDBORD_STATE_NON;
	HANDBORD_TYPE m_type;
	CNumber* m_number;
	CModel* m_model;
	CHandBord();
	~CHandBord();

	static PIECE_TYPE PiecetypeToHandtype(HANDBORD_TYPE handType);
	static HANDBORD_TYPE HandtypeToPiecetype(PIECE_TYPE pieceType);


	CPlayerBase* GetPlayer() { return m_player; }
	void SetPlayer(CPlayerBase* set) { m_player = set; }

	void Add(int i) { m_number->AddNum(i); }
	int GetNum() { return m_number->GetNum(); }
	HANDBORD_TYPE GetType() { return m_type; }
	void SetType(HANDBORD_TYPE set) { m_type = set; }
	void SetNumClass(CNumber* set) { m_number = set; }
	void Setting(CPlayerBase* player, HANDBORD_TYPE type);
	bool Judge(CSquare* s);

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

