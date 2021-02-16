#pragma once
#include "component.h"
#include"handbord.h"
enum PLAYER_STATE
{
	PLAYER_STATE_01 = 0,
	PLAYER_STATE_02,
	PLAYER_STATE_NUM
};
class CSelect;
class CSquareTable;
class CPlayerBase :public CComponent
{
protected:
	PLAYER_STATE m_playerState;
	bool m_loose = false;
	CHandBord* m_hand[HANDBORD_TYPE::HANDBORD_TYPE_NUM];
	CSelect* m_select;
	CSquareTable* m_table;


public:
	CPlayerBase();
	~CPlayerBase();
	//持ち駒を増やす
	void AddHand(HANDBORD_TYPE piece);
	//持ち駒を減らす
	void DownHand(HANDBORD_TYPE piece);  
	//駒を動かす
	void MovePiece(CSquare *next, CPiece *piece);
	//敵の駒を取る
	void TakePiece(CSquare *next, CPiece *myPiece, CPiece *enemyPiece);
	//駒があるマスを選択する
	void ChoiceSquare();
	//駒がある持ち駒を選択する
	void ChoiceHand();
	//駒を選択していない状態にする
	void ChoiceNon();
	//持ち駒を使う
	void UseHand();


	virtual void Setting(PLAYER_STATE state, CSquareTable* table) = 0;


	void SetPlayerState(PLAYER_STATE set) { m_playerState = set; }
	PLAYER_STATE GetPlayerState() { return m_playerState; }
	void SetLoose(bool set) { m_loose = set; }
	bool GetLoose() { return m_loose; }
	void SetSelect(CSelect* set) { m_select = set; }
	CSelect* GetSelect() { return m_select; }
	

	CHandBord* GetHand(HANDBORD_TYPE type) { return m_hand[type]; }
	void SetTable(CSquareTable* set) { m_table = set; }
	CSquareTable* GetTable() { return m_table; }
	virtual	void Init() = 0;
	virtual	void Uninit() = 0;
	virtual	void Update() = 0;
	virtual	void Draw() = 0;
	
};
