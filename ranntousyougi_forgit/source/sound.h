#pragma once
#include<map>
#include <XAudio2.h>

#include "component.h"
//�������
struct SDate
{
	IXAudio2SourceVoice* m_SourceVoice;	// �\�[�X�{�C�X
	BYTE * m_DataAudio ;					// �I�[�f�B�I�f�[�^
	DWORD m_SizeAudio ;					// �I�[�f�B�I�f�[�^�T�C�Y
	int nCntLoop = 0;		// ���[�v�J�E���g

};

class CSound :
	public CComponent
{
protected:

	static IXAudio2* m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice ;			// �}�X�^�[�{�C�X
	static std::map<std::string, SDate> m_sourceVoiceDatebase;//�f�[�^�x�[�X
	SDate m_date;
public:
	int m_frame = 0;
	float m_volume;
	bool m_play;//�Đ����邩�ǂ���
	static void Crear();//�f�[�^�폜
	static HRESULT InitSound(HWND hWnd);//����������
	static void UninitSound(void);//�I������
	static bool LoadSound(std::string fname , HWND hWnd);//�f�[�^�ǉ�
	bool SetSound(std::string fname, HWND hWnd);
	void Play();//�Đ�
	void Play(int loopCount);//XAUDIO2_END_OF_STREAM�Ŗ������[�v

	void StopSound();//��~

	void Init();
	void Uninit();
	void Draw();
	void Update();
		
	CSound();
	~CSound();

};

