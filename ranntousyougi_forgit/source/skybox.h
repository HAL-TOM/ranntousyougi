#pragma once
#include"component.h"
#define SKYBOX_SCALE ((float)400.0f)
class CSkyBox:public CComponent
{
private:

	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_texture = nullptr;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Load(const char* filename);
	void UnLoad();
	CSkyBox() {}
	~CSkyBox() {}
};

