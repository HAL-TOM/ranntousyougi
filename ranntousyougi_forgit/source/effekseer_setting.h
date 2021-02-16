#pragma once
#include "component.h"
#include"Effekseer.h"
#include"EffekseerRendererDX11.h"

class CEffekseerSetting 
{
protected:
	static ::Effekseer::Setting* m_setting;
public:
	CEffekseerSetting();
	~CEffekseerSetting();
	static ::Effekseer::Setting* GetSetting() { return m_setting; }

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};

