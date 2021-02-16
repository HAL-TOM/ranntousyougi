#pragma once
#include "component.h"

class CTitleMoveScenePolygon :
	public CComponent
{
protected:
	static ID3D11Buffer* m_vertexBuffer;
	ID3D11ShaderResourceView* m_texture;

public:
	CTitleMoveScenePolygon();
	~CTitleMoveScenePolygon();
	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(ID3D11ShaderResourceView* texture) { m_texture = texture; }
};

