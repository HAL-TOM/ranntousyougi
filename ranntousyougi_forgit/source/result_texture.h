#pragma once
#include "component.h"	
class CResultTexture :
	public CComponent
{
protected:
	static ID3D11Buffer* m_vertexBuffer;
	static ID3D11ShaderResourceView* m_player1_texture;
	static ID3D11ShaderResourceView* m_player2_texture;

	static void VertexInit();
	PLAYER_STATE m_state;
public:
	CResultTexture();
	~CResultTexture();
	static void Load();
	static void UnLoad();
	void Setting(PLAYER_STATE state);

	void Init();
	void Update();
	void Uninit();
	void Draw();
};

