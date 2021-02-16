#include"effecseer.h"
#include "effekseer_renderer.h"
#include "effekseer_manager.h"

//static�ϐ�
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
	// �`����@���w�肵�܂��B�Ǝ��Ɋg�����邱�Ƃ��ł��܂��B
	m_effekseerManager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(renderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(renderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(renderer->CreateModelRenderer());
	// �e�N�X�`���摜�̓Ǎ����@�̎w��(�p�b�P�[�W������ǂݍ��ޏꍇ�g������K�v������܂��B)
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

