#pragma once
#include "component.h"

#include"player_base.h"

enum GAME_TYPE
{
	GAME_TYPE_PP=0,
	GAME_TYPE_PN,
	GAME_TYPE_NUM
};

class CGameManager :
	public CComponent
{
protected:
	static PLAYER_STATE m_winner;
	static bool m_loose;
	static bool m_draw;
	static GAME_TYPE m_type;



public:
	CGameManager();
	~CGameManager();
	
	static void SetWinner(PLAYER_STATE set) { m_winner = set; }
	static void SetLoose(bool set) { m_loose = set; }
	static void SetDraw(bool set) { m_draw = set; }
	static void SetType(GAME_TYPE set) { m_type = set; }

	static PLAYER_STATE GetWinner() { return m_winner; }
	static bool GetLoose() { return m_loose; }
	static bool GetDraw() { return m_draw; }
	static GAME_TYPE GetType() { return m_type; }
	
	void Init();
	void Update();
	void Uninit();
	void Draw();
	void Juge();
};

