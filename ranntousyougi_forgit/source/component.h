#pragma once
class CGameObject;
class CComponent
{
protected:
	

	bool m_Destoroy = false;
	bool m_enable = true;
	CGameObject* m_gameobject;
public:
	CComponent() {}
	virtual ~CComponent() {}

	CGameObject* GetGameObject() { return m_gameobject; }

	void SetGameObject(CGameObject* set) { m_gameobject = set; }
	void SetDestoroy() { m_Destoroy = true; }
	bool GetEnable() { return m_enable; }
	void SetEnable(bool set) { m_enable = set; }

	bool Destoroy()
	{
		if (m_Destoroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}

	}

	virtual	void Init() = 0;
	virtual	void Uninit() = 0;
	virtual	void Update() = 0;
	virtual	void Draw() = 0;

};