#pragma once
#include"Effekseer.h"
#include"EffekseerRendererDX11.h"

class CEffecseer;
class CEffecseerManager
{
private:
	static ::Effekseer::Manager* m_effekseerManager ;

public:
	CEffecseerManager()=delete;
	static ::Effekseer::Manager* GetManager() { return m_effekseerManager; }
	static void Play( CEffecseer* effecseer);
	static void Stop(CEffecseer * effecseer);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

};

