#pragma once
#include "component.h"
class CLeftPolygon :public CComponent
{
protected:
	static ID3D11Buffer* m_vertexBuffer ;
	static ID3D11ShaderResourceView* m_texture;

public:
	CLeftPolygon();
	~CLeftPolygon();
	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

