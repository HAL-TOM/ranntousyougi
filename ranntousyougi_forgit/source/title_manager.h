#pragma once
#include "component.h"



enum MOVE_SCENE
{
	P_TO_P = 0,//プレイヤー対プレイヤー
	P_TO_N,//プレイヤー対NPC
	MOVE_SCENE_NUM//数
};
class CTitleMoveScenePolygon;
class CSound;
class CTitleManager :public CComponent
{
private:
	static ID3D11ShaderResourceView* m_texture[MOVE_SCENE_NUM];
	static CSound * m_seslectSe;
	static CSound * m_ketteiSe;
	MOVE_SCENE m_moveScene;
	CTitleMoveScenePolygon* m_moveScenePolygon = nullptr;
	
	void Right();
	void Left();
	void SetTexture();
	void Move();
public:
	CTitleManager();
	~CTitleManager();

	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Setting(CTitleMoveScenePolygon* polygon); 

};

