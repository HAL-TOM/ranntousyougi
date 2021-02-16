
#pragma once
#include "component.h"

class CBillBordDrawer :public CComponent
{

private:


	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_texture = nullptr;
	//int m_frame;
	void VertexInit();//���_�o�b�t�@������
public:
	CBillBordDrawer() {}
	~CBillBordDrawer() {}

	void TextuerInit(const char* filename);//�e�N�X�`��������

	void Init();
	void Uninit();
	void Update();
	void Draw();
};