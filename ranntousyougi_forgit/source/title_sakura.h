#pragma once
#include "component.h"


#include"main.h"

class CTitleSakuraManager;


class CTitleSakura :public CComponent
{
private:
	static ID3D11Buffer* m_vertexBuffer;
	static ID3D11ShaderResourceView* m_texture;
	CTitleSakuraManager* m_manager;
	int m_frame = 0;
public:

	static void Load();
	static void UnLoad();

	void SetManager(CTitleSakuraManager* set);
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawSakura();

};

