
#include"manager.h"
#include"renderer.h"
#include"game_object.h"
#include"Effekseer.h"
#include"effekseer_renderer.h"
#include"camera.h"

void CCamera::Init()
{
}

void CCamera::Uninit()
{

}
void CCamera::Update()
{
	D3DXVECTOR3 forward = m_Target->GetForward();
	D3DXVECTOR3 up = m_Target->GetUp();
	D3DXVECTOR3 right = m_Target->GetRight();
	switch (this->m_cameraPosState)
	{
	case CAMERA_POSITION_STATE_STAY:
		break;

	case CAMERA_POSITION_STATE_TARGET_TOP_VIEW:
		//トップビュー
		m_gameobject->SetPosition(m_Target->GetPosition() + D3DXVECTOR3(0.0f, 5.0f, -3.0f));
		break;

	case CAMERA_POSITION_STATE_TARGET_THIRD_PERSON:
		//サードパーソンビュー
	
		m_gameobject->SetPosition(m_Target->GetPosition() - forward * 5.0f + up * 3.0f + right * 1.0f);
		break;
	default:
		break;
	}
	
	
	}
void CCamera::Draw()
{
	//ビューマトリクス設定
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_gameobject->GetPosition(), &m_Target->GetPosition(), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));


	CRenderer::SetViewMatrix(&m_viewMatrix);

	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(
		&projectionMatrix,
		1.2f,//ラジアン角
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,//アスペクト比 
		1.0f,
		1000.0f);

	CRenderer::SetProjectionMatrix(&projectionMatrix);

	//Effecseer系
	{

		::Effekseer::Matrix44 viewMat;
		{
			viewMat.Values[0][0] = m_viewMatrix._11;
			viewMat.Values[0][1] = m_viewMatrix._12;
			viewMat.Values[0][2] = m_viewMatrix._13;
			viewMat.Values[0][3] = m_viewMatrix._14;

			viewMat.Values[1][0] = m_viewMatrix._21;
			viewMat.Values[1][1] = m_viewMatrix._22;
			viewMat.Values[1][2] = m_viewMatrix._23;
			viewMat.Values[1][3] = m_viewMatrix._24;

			viewMat.Values[2][0] = m_viewMatrix._31;
			viewMat.Values[2][1] = m_viewMatrix._32;
			viewMat.Values[2][2] = m_viewMatrix._33;
			viewMat.Values[2][3] = m_viewMatrix._34;

			viewMat.Values[3][0] = m_viewMatrix._41;
			viewMat.Values[3][1] = m_viewMatrix._42;
			viewMat.Values[3][2] = m_viewMatrix._43;
			viewMat.Values[3][3] = m_viewMatrix._44;
		}
		CEffekseerRenderer::RendererSetCameraMatrix(viewMat);

		::Effekseer::Matrix44 projectionMat;
		{
			projectionMat.Values[0][0] = projectionMatrix._11;
			projectionMat.Values[0][1] = projectionMatrix._12;
			projectionMat.Values[0][2] = projectionMatrix._13;
			projectionMat.Values[0][3] = projectionMatrix._14;

			projectionMat.Values[1][0] = projectionMatrix._21;
			projectionMat.Values[1][1] = projectionMatrix._22;
			projectionMat.Values[1][2] = projectionMatrix._23;
			projectionMat.Values[1][3] = projectionMatrix._24;

			projectionMat.Values[2][0] = projectionMatrix._31;
			projectionMat.Values[2][1] = projectionMatrix._32;
			projectionMat.Values[2][2] = projectionMatrix._33;
			projectionMat.Values[2][3] = projectionMatrix._34;

			projectionMat.Values[3][0] = projectionMatrix._41;
			projectionMat.Values[3][1] = projectionMatrix._42;
			projectionMat.Values[3][2] = projectionMatrix._43;
			projectionMat.Values[3][3] = projectionMatrix._44;
		}
		CEffekseerRenderer::RendererSetProjectionMatrix(projectionMat);

	}
}

D3DXMATRIX CCamera::GetViewMatrix()
{
	return m_viewMatrix;
} 
