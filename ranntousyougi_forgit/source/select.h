#pragma once
#include "component.h"
#include"PIECE_STATE.h"
#include <vector>
class CSquare;
class CPlayerBase;
class CHandBord;
class CModel;
class CModelDrawer;
class CPointer;
class CPiece;
#define SELECT_UP_INITIAL_X (4)
#define SELECT_UP_INITIAL_Y (8)
#define SELECT_DOWN_INITIAL_X (4)
#define SELECT_DOWN_INITIAL_Y (0)


enum SELECT_STATE//�I��ł�����̂����Ȃ̂�
{

	SELECT_STATE_EXIST_SQUARE=0,
	SELECT_STATE_EXIST_HAND,
	SELECT_STATE_NON,
	SELECT_STATE_NUM,
};
enum SELECT_POS_STATE
{
	SELECT_POS_STATE_SQUARE=0,
	SELECT_POS_STATE_HAND,
	SELECT_POS_STATE_NON,
	SELECT_POS_STATE_NUM,
};

class CSelect:
	public CComponent
{
protected:
	CPlayerBase* m_player = nullptr;

	//���f���f�[�^
	static CModel* m_redModel;
	static CModel* m_blueModel;
	
	//�`��N���X
	CModelDrawer *m_modelDrawre = nullptr;
	

	//����I��ł��邩
	SELECT_STATE m_selectState = SELECT_STATE_NON;
	//�ǂ��ɂ��邩
	SELECT_POS_STATE m_posState = SELECT_POS_STATE_NON;
	
	CPointer* m_pointer = nullptr;


	//�I�����Ă���ꏊ
	CSquare* m_selectSquare = nullptr;
	int m_selectHandIndex = 0;

	//���ݒn
	CSquare* m_posSquare = nullptr;
	int m_posHandIndex = 0;

public:
	

	static void Load();
	static void UnLoad();
	static CModel* GetRedModel() { return m_redModel; }
	static CModel* GetBlueModel() { return m_blueModel; }
	SELECT_STATE GetSelectState() { return m_selectState; }
	SELECT_POS_STATE GetPosState() { return m_posState; }
	CSquare* GetSelectSquare() { return m_selectSquare; }
	int GetSelectHandIndex() { return m_selectHandIndex; }
	CSquare* GetPosSquare() { return m_posSquare; }
	int GetPosHandIndex() { return m_posHandIndex; }
	CPointer* GetPointer() { return m_pointer; }


	void SetSelectState(SELECT_STATE set) { m_selectState = set; }
	void SetPosState(SELECT_POS_STATE state) { m_posState = state; }
	void SetSelectSquare(CSquare* set) { m_selectSquare = set; }
	void SetSelectHandIndex(int set) { m_selectHandIndex = set; }
	void SetPosSquare(CSquare* set) { m_posSquare = set; }
	void SetPosHandIndex(int set) { m_posHandIndex = set; }

	void SetState(CPlayerBase* set);
	
	

	virtual void ChoiceSquare();//���I������i�Ֆʁj
	virtual void ChoiceHand();//���I������i������j
	virtual void SetSquarePos(CSquare* square);//�Ֆʂ��ړ�����
	virtual void SetHandPos(CHandBord* hand);//��������ړ�����
	
	
	virtual void SelectNon();//�����I�΂Ȃ�

	void Up();//�����
	void Down();//������
	void Left();//������
	void Right();//�E����

	void CreatePointer();//�|�C���^�G�t�F�N�g�����
	void DestroyPointer();//�|�C���^�G�t�F�N�g������
	
	CPiece* CreatePiece(PIECE_TYPE type, CSquare* pos);//������

	CPlayerBase* GetPlayer() { return m_player; }

	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;

};

