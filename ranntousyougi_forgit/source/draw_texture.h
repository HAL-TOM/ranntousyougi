#pragma once
#include "component.h"
class CDrawTexture :
	public CComponent
{
protected:
	static ID3D11Buffer* m_vertexBuffer;
	static ID3D11ShaderResourceView* m_texture;
	static void VertexInit();

public:
	CDrawTexture();
	~CDrawTexture();
	static void Load();
	static void UnLoad();

	void Init();
	void Update();
	void Uninit();
	void Draw();

};

