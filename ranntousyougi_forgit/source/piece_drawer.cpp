#include<D3D11.h>
#include<io.h>
#include"renderer.h"
#include"model.h"
#include"game_object.h"
#include"piece.h"
#include "piece_drawer.h"

 ID3D11VertexShader*     CPieceDrawer::m_vertexShader;
 ID3D11PixelShader*      CPieceDrawer::m_pixelShader;
 ID3D11InputLayout*      CPieceDrawer::m_vertexLayout;

void CPieceDrawer::Load()
{
	// 頂点シェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen("rimLightingVS.cso", "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		CRenderer::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &m_vertexShader);


		// 入力レイアウト生成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		CRenderer::GetDevice()->CreateInputLayout(layout,
			numElements,
			buffer,
			fsize,
			&m_vertexLayout);

		delete[] buffer;
	}



	// ピクセルシェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen("rimLightingPS.cso", "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		CRenderer::GetDevice()->CreatePixelShader(buffer, fsize, NULL, &m_pixelShader);

		delete[] buffer;
	}
}

void CPieceDrawer::UnLoad()
{
	m_pixelShader->Release();
	m_vertexShader->Release();
	m_vertexLayout->Release();
}



void CPieceDrawer::Init()
{
}

void CPieceDrawer::Uninit()
{
}

void CPieceDrawer::Draw()
{
	D3DXQUATERNION rot = m_gameobject->GetRotation();

	//マトリクス変換
	D3DXMATRIX mtxWorld, mtxScale, mtxRot, mtxTrans;
	D3DXMatrixScaling(&mtxScale, m_gameobject->GetScale().x, m_gameobject->GetScale().y, m_gameobject->GetScale().z);
	D3DXMatrixRotationQuaternion(&mtxRot, &rot);
	D3DXMatrixTranslation(&mtxTrans, m_gameobject->GetPosition().x, m_gameobject->GetPosition().y, m_gameobject->GetPosition().z);
	mtxWorld = mtxScale * mtxRot * mtxTrans;

	CRenderer::SetWorldMatrix(&mtxWorld);

	CRenderer::SetShader(m_vertexShader, m_pixelShader, m_vertexLayout);

	CPiece::GetModel(m_piece->GetType())->ModelDraw();
	CRenderer::SetDefaultShader();
}

void CPieceDrawer::Update()
{
}


