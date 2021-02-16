#include"effecseer.h"
#include "effekseer_setting.h"

::Effekseer::Setting*  CEffekseerSetting::m_setting;

CEffekseerSetting::CEffekseerSetting()
{
}


CEffekseerSetting::~CEffekseerSetting()
{
}

void CEffekseerSetting::Init()
{
	m_setting = ::Effekseer::Setting::Create();
	
}

void CEffekseerSetting::Uninit()
{
}

void CEffekseerSetting::Update()
{
}

void CEffekseerSetting::Draw()
{
}
