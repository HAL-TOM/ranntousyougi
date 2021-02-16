#pragma once
#include "scene.h"
class CPlayerToPlayerGameScene :public CScene
{
public:
	CPlayerToPlayerGameScene();
	~CPlayerToPlayerGameScene();
	void Load();
	void UnLoad();
	void Init();
};

