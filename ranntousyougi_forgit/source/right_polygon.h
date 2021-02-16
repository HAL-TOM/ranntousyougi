#pragma once
#include "component.h"
class CRightPolygon :
	public CComponent
{
protected:
	static ID3D11Buffer* m_vertexBuffer;
	static ID3D11ShaderResourceView* m_texture;

public:
	CRightPolygon();
	~CRightPolygon();
	static void Load();
	static void UnLoad();

	void Init();
	void Uninit();
	void Update();
	void Draw();

};

