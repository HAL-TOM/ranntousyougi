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


enum SELECT_STATE//選んでいるものが何なのか
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

	//モデルデータ
	static CModel* m_redModel;
	static CModel* m_blueModel;
	
	//描画クラス
	CModelDrawer *m_modelDrawre = nullptr;
	

	//何を選んでいるか
	SELECT_STATE m_selectState = SELECT_STATE_NON;
	//どこにいるか
	SELECT_POS_STATE m_posState = SELECT_POS_STATE_NON;
	
	CPointer* m_pointer = nullptr;


	//選択している場所
	CSquare* m_selectSquare = nullptr;
	int m_selectHandIndex = 0;

	//現在地
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
	
	

	virtual void ChoiceSquare();//駒を選択する（盤面）
	virtual void ChoiceHand();//駒を選択する（持ち駒）
	virtual void SetSquarePos(CSquare* square);//盤面を移動する
	virtual void SetHandPos(CHandBord* hand);//持ち駒を移動する
	
	
	virtual void SelectNon();//何も選ばない

	void Up();//上入力
	void Down();//下入力
	void Left();//左入力
	void Right();//右入力

	void CreatePointer();//ポインタエフェクトを作る
	void DestroyPointer();//ポインタエフェクトを消す
	
	CPiece* CreatePiece(PIECE_TYPE type, CSquare* pos);//駒を作る

	CPlayerBase* GetPlayer() { return m_player; }

	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;

};

