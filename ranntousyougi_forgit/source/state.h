#pragma once
#include"component.h"
class CState :public CComponent{
public:
	
	//開始　
	virtual void Enter() = 0;
	//終了
	virtual void Exit() = 0;
};