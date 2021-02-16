#pragma once


#include "renderer.h"
#include"component.h"
// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};


// 描画サブセット構造体
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// モデル構造体
struct MODEL
{
	VERTEX_3D	*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};





class CModel:public CComponent 
{
private:

	ID3D11Buffer*	m_vertexBuffer;
	ID3D11Buffer*	m_IndexBuffer;

	SUBSET*	m_SubsetArray;
	unsigned int	m_SubsetNum;
	float m_modelAlpha = 1;
	void LoadObj( const char *FileName, MODEL *Model );
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void ModelDraw();
	void Load( const char *FileName );
	void Unload();

	float GetModelAlpha();
	void SetModelAlpha(float set);


};