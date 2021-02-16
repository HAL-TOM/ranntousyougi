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
	void Set(int frame);//���������ɕK���g������
	void Reset();//�J�E���g���Z�b�g
	void Stop();//��~
	void Play();//�ĊJ

};

