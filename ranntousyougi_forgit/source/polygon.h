#pragma once
#include"component.h"

class  CPolygon:public CComponent
{


private:
	ID3D11Buffer* m_vertexBuffer = NULL;
	ID3D11ShaderResourceView* m_texture = NULL;

	void VertexInit();//頂点バッファ初期化
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void TextuerInit(const char* filename);//テクスチャ初期化


};

