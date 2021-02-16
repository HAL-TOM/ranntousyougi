#pragma once
#include "component.h"
class CWinnerTexture :
	public CComponent
{
protected:
	static ID3D11Buffer* m_vertexBuffer;
	static ID3D11ShaderResourceView* m_texture;

	static void VertexInit();//���_�o�b�t�@������
public:
	CWinnerTexture();
	~CWinnerTexture();
	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

