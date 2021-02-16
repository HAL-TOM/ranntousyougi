#include"effecseer.h"
#include "effekseer_renderer.h"
#include "effekseer_manager.h"

//static変数
::Effekseer::Manager*  CEffecseerManager::m_effekseerManager;

void CEffecseerManager::Play( CEffecseer * effecseer)
{
	effecseer->SetHandle( m_effekseerManager->Play(effecseer->GetEffect(), 0, 0, 0));
	
}

void CEffecseerManager::Stop(CEffecseer * effecseer)
{
	m_effekseerManager->StopEffect(effecseer->GetHandle());

}

void CEffecseerManager::Init()
{
	m_effekseerManager = ::Effekseer::Manager::Create(EFFECT_MAXNUM);
	::EffekseerRendererDX11::Renderer* renderer = CEffekseerRenderer::GetRenderer();
	// 描画方法を指定します。独自に拡張することもできます。
	m_effekseerManager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(renderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(renderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(renderer->CreateModelRenderer());
	// テクスチャ画像の読込方法の指定(パッケージ等から読み込む場合拡張する必要があります。)
	m_effekseerManager->SetTextureLoader(renderer->CreateTextureLoader());
	


}
void CEffecseerManager::Uninit()
{
	if (m_effekseerManager!=nullptr)
	{
		m_effekseerManager->Destroy();
		m_effekseerManager = nullptr;
	}
}
void CEffecseerManager::Update()
{
	m_effekseerManager->Update();
}
void CEffecseerManager::Draw()
{
	m_effekseerManager->Draw();
}

