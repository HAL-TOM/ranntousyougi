#pragma once
#include "component.h"
class CPiece;
class CPieceDrawer :
	public CComponent
{
protected:
	static ID3D11VertexShader*     m_vertexShader;
	static ID3D11PixelShader*      m_pixelShader;
	static ID3D11InputLayout*      m_vertexLayout;
	CPiece* m_piece;
public:
	CPieceDrawer() {}
	~CPieceDrawer() {}

	static void Load();
	static void UnLoad();


	void Init();
	void Uninit();
	void Draw();
	void Update();
	void SetPiece(CPiece* piece) { m_piece = piece; }
};

