#pragma once
#include "component.h"
class CWinTexture :
	public CComponent
{
protected:
	static ID3D11Buffer* m_vertexBuffer;
	static ID3D11ShaderResourceView* m_texture;
	static void VertexInit();

public:
	CWinTexture();
	~CWinTexture();
	static void Load();
	static void UnLoad();

	void Init();
	void Update();
	void Uninit();
	void Draw();
};

