#pragma once
#include<list>
#include<vector>
#include"game_object.h"
#include"camera.h"
#include"renderer.h"
#include"effekseer_manager.h"
#include"effekseer_renderer.h"
enum LAYER_STATE
{
	LAYER_STATE_CAMERA = 0,
	LAYER_STATE_SKYBOX,
	LAYER_STATE_D3,
	LAYER_STATE_D2,
	LAYER_NUM,
};


class CScene
{
private:

protected:
	std::list<CGameObject*> m_gameObject[LAYER_NUM];
	int m_frame = 0;

public:

	
	CScene() 
	{

	};
	virtual ~CScene() {};

	CGameObject* AddGameObject(LAYER_STATE layer)
	{
	

		CGameObject* gameobject = new CGameObject;
		m_gameObject[layer].push_back(gameobject);
		gameobject->Init();
		return gameobject;
	}

	template <typename T>
	T*  FindComponent()
	{
		for (int i = 0; i < LAYER_NUM; ++i)
		{
			for (CGameObject *obj : m_gameObject[i])
			{
				T* a = obj->FindComponent<T>();
				if (a !=nullptr)
				{
					return a;
				}
			}
		}
		return nullptr;
	
	}
	template <typename T>
	void FindComponents(std::vector<T*> *out)
	{
		for (int i = 0; i < LAYER_NUM; ++i)
		{

			for (CGameObject *obj : m_gameObject[i])
			{
				obj->FindComponents(out);
			}
		}
	}
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void UnLoad() = 0;


	virtual void Unint()
	{
		UnLoad();
		for (int i = 0; i < LAYER_NUM; i++)
		{
			for (CGameObject *obj : m_gameObject[i])
			{
				obj->Uninit();
				delete obj;
			}
			m_gameObject[i].clear();
		}

		
	}
	void Update()
	{
		
		for (int i = 0; i < LAYER_NUM; i++)
		{

			for (CGameObject *obj : m_gameObject[i])
			{
				if (obj->GetEnable()==true)
				{
					obj->Update();
				}
			}
		}
		CEffekseerRenderer::Update();
		CEffecseerManager::Update();
		for (int i = 0; i < LAYER_NUM; i++)
		{

			m_gameObject[i].remove_if([](CGameObject* object) 
			{return object->Destoroy(); });
			//ƒ‰ƒ€ƒ_Ž®
		}
		m_frame++;
		
	}
	void Draw()
	{

		
	//	CScene::SetDafaltLight();

		CRenderer::Begin();
		for (int i = 0; i < LAYER_NUM; i++)
		{

			for (CGameObject *obj : m_gameObject[i])
			{
				if (obj->GetEnable() == true)
				{

					obj->Draw();

				}	
			}
		}
		{
			CEffekseerRenderer::DrawBegin();
			CEffekseerRenderer::Draw();
			CEffecseerManager::Draw();
			CEffekseerRenderer::DrawEnd();
		}
		CRenderer::End();
	}

	static void SetDafaltLight()
	{
		LIGHT light;
		light.Enable = true;
		light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
		D3DXVec4Normalize(&light.Direction, &light.Direction);
		light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		CRenderer::SetLight(light);
	}
	int GetFrame()
	{
		return m_frame;
	}
};
