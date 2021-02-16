
#include"manager.h"
#include"square.h"
#include"scene.h"
#include "square_table.h"

CSquareTable::CSquareTable()
{
}


CSquareTable::~CSquareTable()
{
}
void CSquareTable::Init()
{
	CScene* scene = CManager::GetScene();
	CGameObject* gameobject;
	for (int i = 0; i < SQUARE_TABLE_MAX_Y+1 ; i++)
	{
		for (int j = 0; j < SQUARE_TABLE_MAX_X+1; j++)
		{
			gameobject= scene->AddGameObject(LAYER_STATE_D3);
			
			gameobject->SetPosition(D3DXVECTOR3((4 - i)*SQUARE_CUT_LENGH, 1.0f, (4 - j)*SQUARE_CUT_LENGH));
			m_square[i][j] = gameobject->AddComponent<CSquare>();
			m_square[i][j]->SetTable(this);
			m_square[i][j]->SetXY(i, j);
		}
	}
}
void CSquareTable::Uninit()
{

}
void CSquareTable::Draw()
{
	
}
void CSquareTable::Update()
{

}