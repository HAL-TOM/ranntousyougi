#pragma once
enum ACTION_TYPE
{
	ACTION_TYPE_MOVEPIECE = 0,
	ACTION_TYPE_TAKEPIECE,
	ACTION_TYPE_USEHAND
};

class CAction
{
protected:
	//その行動に必要なパラメータ（マスとか）



	ACTION_TYPE m_type;//何のアクションか
	int m_value = 0;

public:
	//その行動に必要なパラメータをセットする
	//void　Setting();//引数がクラスごとに異なるから仮想関数にできない（つらい）
	
	
	//その行動の結果有利になるかどうか、＋の値が高いほど有利（Actionクラスが評価するべきなのか？）
	virtual int CreateValue()=0;
	//評価値を取得
	int GetValue() { return m_value; }
	ACTION_TYPE GetType() { return m_type; }
};

