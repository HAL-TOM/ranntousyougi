

#include"renderer.h"
#include"game_object.h"
#include"title_sakura_manager.h"
#include"main.h"

#include "title_sakura.h"

ID3D11Buffer* CTitleSakura::m_vertexBuffer;
ID3D11ShaderResourceView* CTitleSakura::m_texture;



void CTitleSakura::Load()
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

	 D3DX11CreateShaderResourceViewFromFile
	 (
		 CRenderer::GetDevice(),
		 "asset\\texture\\sakura.png",
		 NULL,
		 NULL,
		 &m_texture,
		 NULL
	 );
}
void CTitleSakura::UnLoad()
{
	m_texture->Release();
	m_texture = nullptr;
}
void CTitleSakura::Init()
{


}

void CTitleSakura::Uninit()
{
}
void CTitleSakura::Update()
{

	
	if (m_gameobject->GetPosition().x<-30||m_gameobject->GetPosition().y>SCREEN_HEIGHT+30)
	{
		m_gameobject->SetDestoroy();
		m_manager->Remove(this);
		return;
	}

	m_gameobject->AddPosition(D3DXVECTOR3(-0.3f, 0.3f, 0.0f));

	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), -0.02f);
	m_gameobject->AddRotation(quat);

	m_frame++;
}
void CTitleSakura::Draw()
{

}

void CTitleSakura::DrawSakura()
{
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
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	//プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}

void CTitleSakura::SetManager(CTitleSakuraManager* set)
{
	
	m_manager = set;

}