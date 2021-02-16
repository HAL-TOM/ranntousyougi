#pragma once
#include "component.h"
#include<list>
class CTitleSakura;
class CTitleSakuraManager :
	public CComponent
{
private:
	std::list<CTitleSakura*> m_sakura;
	int frame = 0;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Remove(CTitleSakura* s);
};

