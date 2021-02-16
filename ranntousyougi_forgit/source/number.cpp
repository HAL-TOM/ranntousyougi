#include"main.h"
#include"renderer.h"
#include"game_object.h"
#include"scene.h"
#include"camera.h"
#include"manager.h"
#include "number.h"

CNumber::CNumber()
{
}


CNumber::~CNumber()
{
}
ID3D11ShaderResourceView* CNumber::m_texture =nullptr;
void CNumber::Load()
{
	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile
	(
		CRenderer::GetDevice(),
		"asset\\texture\\number.png",
		NULL,
		NULL,
		&m_texture,
		NULL
	);
}
void CNumber::UnLoad()
{
	m_texture->Release();

}
void CNumber::VertexInit()//頂点バッファ初期化
{


	VERTEX_3D vertex[4];


	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	/////////////////////////////////////////////////////////////////
	//ここ！！
	/////////////////////////////////////////////////////////////////
	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);

}
void CNumber::Init()
{
	VertexInit();
}
void CNumber::Uninit()
{
	m_vertexBuffer->Release();
}
void CNumber::Draw()
{
	D3DXVECTOR3 drawPos = this->GetGameObject()->GetPosition();
	int num = m_num;
	do 
	{
		DrawNumber(num%10,drawPos);
		num /= 10;
		if (num>0)
		{
			drawPos.x -= this->GetGameObject()->GetScale().x;
		}
	} while (num > 0);

}
void CNumber::Update()
{

}

void CNumber::DrawNumber(int num, D3DXVECTOR3 pos)
{
	float cut_X = 1.0f / 5.0f;
	float cut_Y = 1.0f / 5.0f;


	float uv_X,uv_Y;
	if (num<0)
	{
		return;
			
	}
	if (num >= 10)
	{
		return;
	}
	uv_X = cut_X * (num % 5);
	uv_Y = cut_Y * (num / 5);
	D3D11_MAPPED_SUBRESOURCE msr;

	CRenderer::GetDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D * vertex = (VERTEX_3D*)msr.pData;
	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(uv_X, uv_Y);

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(uv_X + cut_X, uv_Y);

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(uv_X, uv_Y + cut_Y);

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(uv_X + cut_X, uv_Y + cut_Y);

	CRenderer::GetDeviceContext()->Unmap(m_vertexBuffer, 0);

	///////////////////////////////////////////////////////////////////



	CScene *scene = CManager::GetScene();

	CCamera* camera = scene->FindComponent<CCamera>();

	D3DXMATRIX view = camera->GetViewMatrix();
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	//マトリクス変換
	D3DXMATRIX mtxWorld, mtxScale,/* mtxRot,*/ mtxTrans;
	D3DXMatrixScaling(&mtxScale, m_gameobject->GetScale().x, m_gameobject->GetScale().y, m_gameobject->GetScale().z);
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	mtxWorld = mtxScale * invView * mtxTrans;

	CRenderer::SetWorldMatrix(&mtxWorld);


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