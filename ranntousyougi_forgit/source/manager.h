#pragma once
#include<time.h>

class CScene;
class CManager
{
private:
	static void Move();
public:
	static CScene* m_scene;
	static CScene* m_nextScene;
	static int m_moveFrame;
	static int m_moveEndFrame;
	static bool m_move;
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static CScene* GetScene();
	static void CreateScene(CScene* scene);
	template <typename T>
	static void MoveScene(int frame)
	{
		if (m_move==true)
		{
			return;
		}

		m_nextScene = new T();
		m_move = true;
		m_moveFrame = 0;
		m_moveEndFrame = frame;

	}
};