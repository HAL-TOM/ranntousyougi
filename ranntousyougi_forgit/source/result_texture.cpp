#include"player.h"
#include"main.h"
#include"renderer.h"
#include "result_texture.h"
#include"game_object.h"
ID3D11Buffer* CResultTexture::m_vertexBuffer;
ID3D11ShaderResourceView* CResultTexture::m_player1_texture;
ID3D11ShaderResourceView* CResultTexture::m_player2_texture;

CResultTexture::CResultTexture()
{
}


CResultTexture::~CResultTexture()
{
}
void CResultTexture::VertexInit()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);
}

void CResultTexture::Load()
{
	VertexInit();
	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile
	(
		CRenderer::GetDevice(),
		"asset\\texture\\player1.png",
		NULL,
		NULL,
		&m_player1_texture,
		NULL
	);
	D3DX11CreateShaderResourceViewFromFile
	(
		CRenderer::GetDevice(),
		"asset\\texture\\player2.png",
		NULL,
		NULL,
		&m_player2_texture,
		NULL
	);
}
void CResultTexture::UnLoad()
{
	m_player1_texture->Release();
	m_player1_texture = nullptr; 
	m_player2_texture->Release();
	m_player2_texture = nullptr;

}
void CResultTexture::Setting(PLAYER_STATE state)
{
	m_state = state;
}

void CResultTexture::Init()
{

}
void CResultTexture::Update()
{

}
void CResultTexture::Uninit()
{

}
void CResultTexture::Draw()
{
	ID3D11ShaderResourceView* texture;

	switch (m_state)
	{
	case PLAYER_STATE_01:
		texture = m_player1_texture;		
		break;
	case PLAYER_STATE_02:
		texture = m_player2_texture;
		break;
	default:
		return;
		break;
	}
	D3DXQUATERNION rot = m_gameobject->GetRotation();
	
	//マトリクス変換
	D3DXMATRIX mtxWorld, mtxScale, mtxRot, mtxTrans;
	D3DXMatrixScaling(&mtxScale, m_gameobject->GetScale().x, m_gameobject->GetScale().y, m_gameobject->GetScale().z);
	D3DXMatrixRotationQuaternion(&mtxRot, &rot);
	D3DXMatrixTranslation(&mtxTrans, m_gameobject->GetPosition().x, m_gameobject->GetPosition().y, m_gameobject->GetPosition().z);
	mtxWorld = mtxScale * mtxRot * mtxTrans;
	

	//マトリクス変換
	CRenderer::SetWorldViewProjection2D(&mtxWorld);
	

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers
	(
		0, 1, &m_vertexBuffer, &stride, &offset
	);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	CRenderer::SetMaterial(material);

	//テクスチャ設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

	//プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);

}