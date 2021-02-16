#pragma once
#include "component.h"
#include"model.h"
#include"model_drawer.h"
#include"PIECE_STATE.h"
#include<vector>
#define PIECE_COOL_HUHYOU		(240)
#define PIECE_COOL_NARIKIN		(240)
#define PIECE_COOL_KYOUSYA		(240)
#define PIECE_COOL_NARIKYOU		(240)
#define PIECE_COOL_KEIMA		(240)
#define PIECE_COOL_NARIKEI		(240)
#define PIECE_COOL_GINN			(300)
#define PIECE_COOL_NARIGINN		(300)
#define PIECE_COOL_KINN			(300)
#define PIECE_COOL_KAKU			(420)
#define PIECE_COOL_UMA			(420)
#define PIECE_COOL_HISYA		(420)
#define PIECE_COOL_RYUUOU		(420)
#define PIECE_COOL_GYOKU		(300)
class CPlayerBase;
class CPPIECE_TYPE_NUM;
class CSquare;
class CPieceCoolTimer;
class CPieceDrawer;
class CSound;

class CPiece :
	public CComponent
{
protected:


	CPlayerBase* m_player;
	PIECE_TYPE m_pieceState;
	CSquare* m_square;//現在位置
	bool m_cool = false;

	static CModel* m_model[PIECE_TYPE_NUM];
	static CSound* m_moveSe;
	//CModelDrawer* m_drawer;
	CPieceDrawer* m_drawer;
	CPieceCoolTimer* m_coolTimer=nullptr;
	
public:
	

	CPiece();
	~CPiece();

	static void Load();
	static void UnLoad();
	static CModel* GetModel(PIECE_TYPE m_pieceState);
	static int GetValue(PIECE_TYPE type) 
	{
		//①効きの数
		//②駒のスピード
		//③局面による誤差
		//香車の価値を測るのは難しいらしい
		//乱闘将棋の場合クールタイムもあるので考慮すべきかもしれない
		//歩(1):香(3):桂(4):銀(5);金(6):角(8):飛(12)
		//自玉を軽く見る原因がわからない
		switch (type)
		{
		case PIECE_TYPE::PIECE_TYPE_HUHYOU:
			return 3;
			break;
		case PIECE_TYPE::PIECE_TYPE_KYOUSYA:
			return 9;
			break;

		case PIECE_TYPE::PIECE_TYPE_NARIKYOU:
			return 18;
			break;

		case PIECE_TYPE::PIECE_TYPE_KEIMA:
			return 12;
			break;

		case PIECE_TYPE::PIECE_TYPE_NARIKEI:
			return 18;
			break;

		case PIECE_TYPE::PIECE_TYPE_GINN:
			return 15;

		case PIECE_TYPE::PIECE_TYPE_NARIGINN:
			return 18;
			break;

		case PIECE_TYPE::PIECE_TYPE_KINN:
			return 18;
			break;

		case PIECE_TYPE::PIECE_TYPE_KAKU:
			return 24;
			break;

		case PIECE_TYPE::PIECE_TYPE_UMA:
			return 30;
			break;

		case PIECE_TYPE::PIECE_TYPE_HISYA:
			return 36;
			break;

		case PIECE_TYPE::PIECE_TYPE_RYUUOU:
			return 45;
			break;

		case PIECE_TYPE::PIECE_TYPE_GYOKU:
			return 300;
			break;

		default:
			return 0;
			break;
		}
	}
	static CPiece* CreatePiece(PIECE_TYPE state, CPlayerBase* player, CSquare* square);//GameObjectとはかかわりあわない

	bool Judge(CSquare* square);

	bool JudgeCoolThrough(CSquare* square);

	CPlayerBase* GetPlayer() { return m_player; }
	CSquare* GetSquare() { return m_square; }
	PIECE_TYPE GetType() { return m_pieceState; }
	bool GetCool() { return m_cool; }
	void StateSetting(PIECE_TYPE state, CPlayerBase* player,CSquare* square);/////////////////////
	void StateSet(PIECE_TYPE state, CPlayerBase* player, CSquare* square);
	void SetSquare(CSquare* set);
	void SetSquareUnCmoponent(CSquare* set);//GameObjectとはかかわりあわない
	void SetPlayer(CPlayerBase* set) { m_player = set; }
	void SetType(PIECE_TYPE type) { m_pieceState = type; }



	bool GetMovePossible();
	void GetPossibleSquares(std::vector<CSquare*> *out);
	int GetPossibleSquareNum();

	inline void PossibleSquaresSet(CSquare* square, std::vector<CSquare*> *out);

	
	bool PossibleSquareJuge(CSquare* square);

	bool RankUp();

	void CoolSet();
	void CoolUnSet();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	
};

