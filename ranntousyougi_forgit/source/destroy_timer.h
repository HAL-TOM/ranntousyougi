#pragma once
#include "component.h"
class CDestoroyTimer :
	public CComponent
{
private:
	int m_frame = 0;
	int m_endFrame = 0;
	bool m_count;
	
public:
	CDestoroyTimer();
	~CDestoroyTimer();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(int frame);//初期化時に必ず使うこと
	void Reset();//カウントリセット
	void Stop();//停止
	void Play();//再開

};

