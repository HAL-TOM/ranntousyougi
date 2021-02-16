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
	//������𑝂₷
	void AddHand(HANDBORD_TYPE piece);
	//����������炷
	void DownHand(HANDBORD_TYPE piece);  
	//��𓮂���
	void MovePiece(CSquare *next, CPiece *piece);
	//�G�̋�����
	void TakePiece(CSquare *next, CPiece *myPiece, CPiece *enemyPiece);
	//�����}�X��I������
	void ChoiceSquare();
	//����鎝�����I������
	void ChoiceHand();
	//���I�����Ă��Ȃ���Ԃɂ���
	void ChoiceNon();
	//��������g��
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
