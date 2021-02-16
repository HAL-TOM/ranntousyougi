#pragma once

#include "component.h"

#include<Effekseer.h>
#include<EffekseerRendererDX11.h>

#define EFFECT_MAXNUM (10000)

class CEffecseer :
	public CComponent
{
protected:

	::Effekseer::Effect *m_effect;
	int m_handle = -1;
	int m_frame = 0;
	int m_frameMax=-1;
	bool m_play = false;
	bool m_loop = false;
	::std::string m_filename;

public:

	CEffecseer();
	~CEffecseer();


	
	//@brief　ロード処理
	//@pram fileName　.efkのファイルパス
	bool Load(const EFK_CHAR* fileName, int frame, float scale = 1.0f, bool loop = false);

	//@brief　エフェクトアンロード
	void UnLoad();
	
	void Play();
	void Stop();
	::Effekseer::Effect * GetEffect() { return m_effect; }
	int GetHandle() { return m_handle; }
	void SetHandle(int set) { m_handle = set; }
	void SetLoop(bool set) { m_loop = set; }
	bool GetPlayFlag() { return m_play; }
	
	//CComponent
	void Init(); 
	void Uninit();
	void Update();
	void Draw();
	

};

