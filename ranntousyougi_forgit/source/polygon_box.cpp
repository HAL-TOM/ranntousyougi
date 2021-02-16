
#include"main.h"
#include"renderer.h"
#include"game_object.h"

#include"scene.h"
#include"manager.h"
#include "polygon_box.h"

CPolygonBox::CPolygonBox()
{
}


CPolygonBox::~CPolygonBox()
{
}
void CPolygonBox::Init()
{

}
void CPolygonBox::Uninit()
{
	m_texture->Release();
	m_vertexBuffer->Release();
}
void CPolygonBox::Update()
{

}
void CPolygonBox::Draw()
{
	//マトリクス変換
	D3DXMATRIX mtxWorld, mtxScale, mtxRot, mtxTrans;
	D3DXVECTOR3 half = m_gameobject->GetScale()/2.0f;
	D3DXVECTOR3 pos = m_gameobject->GetPosition();
	D3DXQUATERNION rot = m_gameobject->GetRotation();
	D3DXMatrixScaling(&mtxScale, m_gameobject->GetScale().x, m_gameobject->GetScale().y, m_gameobject->GetScale().z);


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




	//上////////////////////////////////////////////////////////

	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y+ half.y, pos.z);
	mtxWorld = mtxScale * mtxRot * mtxTrans;
	CRenderer::SetWorldMatrix(&mtxWorld);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);


	//下////////////////////////////////////////////////////////

	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, D3DXToRadian(180));
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y - half.y, pos.z);
	mtxWorld = mtxScale * mtxRot * mtxTrans;
	CRenderer::SetWorldMatrix(&mtxWorld);



	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);

	//前////////////////////////////////////////////////////////
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, D3DXToRadian(90), 0.0f);
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z+ half.z);
	mtxWorld = mtxScale * mtxRot * mtxTrans;
	CRenderer::SetWorldMatrix(&mtxWorld);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);

	//後ろ////////////////////////////////////////////////////////
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, D3DXToRadian(-90), 0.0f);
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z - half.z);

	mtxWorld = mtxScale * mtxRot * mtxTrans;
	CRenderer::SetWorldMatrix(&mtxWorld);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);

	//右////////////////////////////////////////////////////////
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(270), D3DXToRadian(-90), 0.0f); 

	D3DXMatrixTranslation(&mtxTrans, pos.x+ half.x, pos.y, pos.z );
	mtxWorld = mtxScale * mtxRot * mtxTrans;
	CRenderer::SetWorldMatrix(&mtxWorld);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);

	//左////////////////////////////////////////////////////////
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(90), D3DXToRadian(-90), 0.0f);

	D3DXMatrixTranslation(&mtxTrans, pos.x - half.x, pos.y, pos.z);
	
	mtxWorld = mtxScale * mtxRot * mtxTrans;
	CRenderer::SetWorldMatrix(&mtxWorld);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}
void CPolygonBox::Load(const char* filename)
{
	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile
	(
		CRenderer::GetDevice(),
		filename,
		NULL,
		NULL,
		&m_texture,
		NULL
	);
	assert(m_texture);

	//VERTEX

	VERTEX_3D vertex[4];
	vertex[0].Position = D3DXVECTOR3(-0.5f, 0.0f, 0.5f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(0.5f, 0.0f, 0.5f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-0.5f, 0.0f, -0.5f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(0.5f, 0.0f, -0.5f);
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