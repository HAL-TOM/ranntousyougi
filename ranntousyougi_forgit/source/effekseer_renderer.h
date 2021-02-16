#pragma once

#include"effecseer.h"

class CEffekseerRenderer
{
private:
	//@brief�@Renderer������
	static ::EffekseerRendererDX11::Renderer* m_effekseerRenderer;
	


public:
	CEffekseerRenderer() = delete;
	
	static void DrawBegin();
	static void DrawEnd();
	
	static ::EffekseerRendererDX11::Renderer* GetRenderer() { return m_effekseerRenderer; }
	//@brief�@Renderer��ProjectionMatrix���Z�b�g����
//@pram mat�@Renderer�ɃZ�b�g����Matrix
	static void RendererSetProjectionMatrix(const ::Effekseer::Matrix44& mat);

	//@brief�@Renderer��CameraMatrix���Z�b�g����
	static void RendererSetCameraMatrix(const ::Effekseer::Matrix44& mat);

	static void SetBackGroundTex();

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	
};

