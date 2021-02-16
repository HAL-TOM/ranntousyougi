#include"renderer.h"
#include "effekseer_renderer.h"
#include"effekseer_manager.h"
::EffekseerRendererDX11::Renderer* CEffekseerRenderer::m_effekseerRenderer;


void CEffekseerRenderer::RendererSetProjectionMatrix(const::Effekseer::Matrix44 & mat)
{
	m_effekseerRenderer->SetProjectionMatrix(mat);

}

void CEffekseerRenderer::RendererSetCameraMatrix(const::Effekseer::Matrix44 & mat)
{
	m_effekseerRenderer->SetCameraMatrix(mat);

}

void CEffekseerRenderer::SetBackGroundTex()
{
	CEffecseerManager::GetManager()->GetTextureLoader()->Load((EFK_CHAR*)L"asset\\effect\\Texture\\alfaNonTex.png", ::Effekseer::TextureType::Color);
}

void CEffekseerRenderer::DrawBegin()
{
	m_effekseerRenderer->BeginRendering();
	//CRenderer::SetDepthEnable(true);
}

void CEffekseerRenderer::DrawEnd()
{
	m_effekseerRenderer->EndRendering();
	//CRenderer::SetDepthEnable(true);
}


void CEffekseerRenderer::Init()
{
	m_effekseerRenderer = ::EffekseerRendererDX11::Renderer::Create(CRenderer::GetDevice(), CRenderer::GetDeviceContext(), EFFECT_MAXNUM);	
}
void CEffekseerRenderer::Uninit()
{

	if (m_effekseerRenderer != nullptr)
	{
		m_effekseerRenderer->Destroy();
		m_effekseerRenderer = nullptr;
	}
}
void CEffekseerRenderer::Update()
{

}
void CEffekseerRenderer::Draw()
{

}