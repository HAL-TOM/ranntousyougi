


#include"game_object.h"
#include"renderer.h"


#include<map>
#include<vector>
#include"effekseer_manager.h"
#include<Effekseer.h>
#include "effecseer.h"

#define EFFECT_ASSET_FILE_PATH ("asset\\effect")

CEffecseer::CEffecseer()
{
}


CEffecseer::~CEffecseer()
{
}


bool CEffecseer::Load(const EFK_CHAR* fileName, int frame, float scale, bool loop)
{
	auto effect = ::Effekseer::Effect::Create(CEffecseerManager::GetManager(), fileName, scale);
	
	m_effect = effect;
	m_frameMax = frame;
	SetLoop(loop);
	if (effect == nullptr)
	{
		return false;
	}
	return true;

}

void CEffecseer::UnLoad()
{
	//	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	ES_SAFE_RELEASE(m_effect);
}

void CEffecseer::Play()
{
	if (m_play==true)
	{
		return;
	}
	CEffecseerManager::Play(this);

	m_frame = 0;
	m_play = true;
}

void CEffecseer::Stop()
{
	CEffecseerManager::Stop(this);
	m_play = false;
}




void CEffecseer::Init()
{
	m_frame = 0;
}

void CEffecseer::Uninit()
{
	Stop();

	ES_SAFE_RELEASE(m_effect);

}

void CEffecseer::Update()
{
	if (m_play==true)
	{
		CEffecseerManager::GetManager()->SetLocation(m_handle, ::Effekseer::Vector3D(m_gameobject->GetPosition().x, m_gameobject->GetPosition().y, m_gameobject->GetPosition().z));
		if (m_loop == false)
		{
			if (m_frame%m_frameMax == m_frameMax - 1)
			{
				Stop();
			}
		}
		m_frame++;
	}
}

void CEffecseer::Draw()
{
}
