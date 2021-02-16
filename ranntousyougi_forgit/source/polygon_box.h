#pragma once
#include "component.h"

class CPolygonBox :
	public CComponent
{
private:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11ShaderResourceView* m_texture;
public:
	CPolygonBox();
	~CPolygonBox();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Load(const char* filename);
};

