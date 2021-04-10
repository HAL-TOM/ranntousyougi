#pragma once
#include<list>
#include<vector>
#include <typeinfo>


#pragma warning(push)
#pragma warning(disable:4005)

#include <d3dx9.h>

#pragma warning(pop)

class CComponent;
class CGameObject
{


protected:
	D3DXVECTOR3 m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXQUATERNION m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f,1.0f);
	D3DXVECTOR3 m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	std::list<CComponent*> m_component;
	bool m_Destoroy = false;
	bool m_enable = true;
public:
	CGameObject() {};
	virtual ~CGameObject() {};
	template <typename T>
	T* AddComponent()
	{
		T* component = new T;
		m_component.push_back(component);
		component->SetGameObject(this);
		component->Init();

		return component;
	}
	template <typename T>
	T*  FindComponent() {
		for (CComponent *comp : m_component)
		{
			if (typeid(*comp) == typeid(T))
			{
				return (T*)comp;
			}
		}
		return nullptr;
	}
	template <typename T>
	void FindComponents(std::vector<T*> *out)
	{
		for (CComponent *comp : m_component)
		{
			if (typeid(*comp)== typeid(T))
			{
				out->push_back((T*)comp);
			}
		}
	}


	D3DXVECTOR3 GetPosition()	{ return m_position;}
	D3DXQUATERNION GetRotation()	{ return m_rotation;}
	D3DXVECTOR3 GetScale()		{ return m_scale;}
	D3DXVECTOR3 GetForward()//前方向ベクトル 
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &m_rotation);
		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;
		D3DXVec3Normalize(&forward, &forward);

		return forward;
	}
	D3DXVECTOR3 GetRight()//上方向ベクトル
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &m_rotation);
		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;
		D3DXVec3Normalize(&right, &right);
		return right;
	}
	D3DXVECTOR3 GetUp()//右方向ベクトル
	{
		
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &m_rotation);
		D3DXVECTOR3 up;
		up.x = rot._21;
		up.y = rot._22;
		up.z = rot._23;
		D3DXVec3Normalize(&up, &up);

		return up;
	}
	bool GetEnable() { return m_enable; }
	void SetEnable(bool set) { m_enable = set; }

	void SetPosition(D3DXVECTOR3 set) { m_position = set; }
	void SetRotation(D3DXQUATERNION set) { m_rotation = set; }
	void SetScale(D3DXVECTOR3 set) { m_scale = set; }
	void AddPosition(D3DXVECTOR3 add) { m_position += add; }
	void AddRotation(D3DXQUATERNION add) { m_rotation *= add; }
	void AddScale(D3DXVECTOR3 add) { m_scale += add; }

	void SetDestoroy() {m_Destoroy = true;}
	bool Destoroy();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

