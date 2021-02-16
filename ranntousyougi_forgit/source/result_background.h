#pragma once
#include "component.h"
class CResultBackGround :
	public CComponent
{
protected:
	static ID3D11Buffer* m_vertexBuffer;
	static ID3D11ShaderResourceView* m_texture;

	static void VertexInit();//頂点バッファ初期化
public:
	CResultBackGround();
	~CResultBackGround();
	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

