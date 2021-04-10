#pragma once
#include "component.h"
#include"manager.h"

#pragma warning(push)
#pragma warning(disable:4005)

#include <d3dx9.h>
#include <d3dx11.h>

#pragma warning(pop)

class CNumber :
	public CComponent
{
private:
	int m_num=0;
	static int m_texid;
	ID3D11Buffer* m_vertexBuffer = nullptr;
	static ID3D11ShaderResourceView* m_texture;
	void VertexInit();//頂点バッファ初期化

public:

	CNumber();
	~CNumber();
 	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Draw();
	void Update();

	int GetNum() { return m_num; }
	void SetNum(int set) { m_num = set; }
	void AddNum(int set) { m_num += set; }
	void DrawNumber(int num,D3DXVECTOR3 pos);
};

