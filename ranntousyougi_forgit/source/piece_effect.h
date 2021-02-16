#pragma once
#include"component.h"
class  CPiece;
class CEffecseer;
class CSound; 
class CPieceEffect:public CComponent
{
private:

public:
	CPiece* m_piece;

	static void Load();
	static void UnLoad();

};


class CPieceMoveEffect:public CPieceEffect
{
private:
	//効果音
	static CSound* m_sound;
	//エフェクト
	static CEffecseer* m_effecseer;
	
	static CPieceMoveEffect* m_this;
	int m_frame=0;
	const int m_maxFrame = 30;
public :
	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	static void Play(CPiece* piece);

};

class CPieceRankUpEffect :public CPieceEffect
{
private:
	//効果音
	static CSound* m_sound;
	//エフェクト
	static CEffecseer* m_effecseer;

	static CPieceRankUpEffect* m_this;
	int m_frame = 0;
	const int m_maxFrame = 40;
public:
	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	static void Play(CPiece* piece);

};


class CPieceUseHandEffect :public CPieceEffect
{
private:
	//効果音
	static CSound* m_sound;
	//エフェクト
	static CEffecseer* m_effecseer;

	static CPieceUseHandEffect* m_this;
	int m_frame = 0;
	const int m_maxFrame = 30;
public:
	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	static void Play(CPiece* piece);

};

class CPieceMoveLineEffect :public CPieceEffect
{
private:
	
	//エフェクト
	static CEffecseer* m_effecseer;

	static CPieceMoveLineEffect* m_this;
	int m_frame = 0;
	const int m_maxFrame = 30;

	

public:

	float m_dif = 0;
	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	static void Play(D3DXVECTOR3 pos,float dif, float rot);

};