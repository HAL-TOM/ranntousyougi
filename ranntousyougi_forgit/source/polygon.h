#pragma once
#include"component.h"

class  CPolygon:public CComponent
{


private:
	ID3D11Buffer* m_vertexBuffer = NULL;
	ID3D11ShaderResourceView* m_texture = NULL;

	void VertexInit();//���_�o�b�t�@������
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void TextuerInit(const char* filename);//�e�N�X�`��������


};

