
#pragma once
#include "component.h"

class CBillBordDrawer :public CComponent
{

private:


	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_texture = nullptr;
	//int m_frame;
	void VertexInit();//頂点バッファ初期化
public:
	CBillBordDrawer() {}
	~CBillBordDrawer() {}

	void TextuerInit(const char* filename);//テクスチャ初期化

	void Init();
	void Uninit();
	void Update();
	void Draw();
};