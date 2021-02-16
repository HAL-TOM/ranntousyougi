#include "result_manager.h"
#include"manager.h"
#include"scene.h"
#include"title_scene.h"
#include"input.h"

CResultManager::CResultManager()
{
}


CResultManager::~CResultManager()
{
}
void CResultManager::Init()
{

}
void CResultManager::Uninit()
{

}
void CResultManager::Update()
{
	if (CInput::GetKeyPress('A'))
	{
		CManager::MoveScene<CTitleScene>(30);
	}
	if (CInput::GetKeyPress(VK_SPACE))
	{
		CManager::MoveScene<CTitleScene>(30);
	}
}
void CResultManager::Draw()
{

}
