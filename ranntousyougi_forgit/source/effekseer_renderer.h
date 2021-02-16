#pragma once

#include"effecseer.h"

class CEffekseerRenderer
{
private:
	//@brief　Renderer初期化
	static ::EffekseerRendererDX11::Renderer* m_effekseerRenderer;
	


public:
	CEffekseerRenderer() = delete;
	
	static void DrawBegin();
	static void DrawEnd();
	
	static ::EffekseerRendererDX11::Renderer* GetRenderer() { return m_effekseerRenderer; }
	//@brief　RendererにProjectionMatrixをセットする
//@pram mat　RendererにセットするMatrix
	static void RendererSetProjectionMatrix(const ::Effekseer::Matrix44& mat);

	//@brief　RendererにCameraMatrixをセットする
	static void RendererSetCameraMatrix(const ::Effekseer::Matrix44& mat);

	static void SetBackGroundTex();

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	
};

