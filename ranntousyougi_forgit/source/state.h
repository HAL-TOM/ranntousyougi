#pragma once
#include"component.h"
class CState :public CComponent{
public:
	
	//�J�n�@
	virtual void Enter() = 0;
	//�I��
	virtual void Exit() = 0;
};