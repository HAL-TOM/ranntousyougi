#include <string>
#include <vector>
#include <memory>

#include "sound.h"

HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);


IXAudio2* CSound::m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
IXAudio2MasteringVoice* CSound::m_pMasteringVoice ;			// �}�X�^�[�{�C�X
std::map<std::string, SDate> CSound::m_sourceVoiceDatebase;//

void CSound::Crear()
{
	for (auto itr = m_sourceVoiceDatebase.begin(); itr != m_sourceVoiceDatebase.end(); ++itr)
	{

		if (itr->second.m_SourceVoice!=nullptr)
		{
			itr->second.m_SourceVoice->Stop();
			// �\�[�X�{�C�X�̔j��
			itr->second.m_SourceVoice->DestroyVoice();
			itr->second.m_SourceVoice = NULL;

		}
		if (itr->second.m_DataAudio!=nullptr)
		{
			// �I�[�f�B�I�f�[�^�̊J��
			free(itr->second.m_DataAudio);

		}
	}

	m_sourceVoiceDatebase.clear();

}

CSound::CSound()
{
}


CSound::~CSound()
{
}

HRESULT CSound::InitSound(HWND hWnd)
{

	HRESULT hr;

	// COM���C�u�����̏�����
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if (m_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}
//	MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����ɐ����I", "�x���I", MB_ICONWARNING);

	return S_OK;

}
bool CSound::LoadSound(std::string fname, HWND hWnd)
{
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;
	HRESULT hr;

	// �o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	m_sourceVoiceDatebase.find(fname);

	if (m_sourceVoiceDatebase.count(fname)!=0)
	{
		m_sourceVoiceDatebase[fname].m_SourceVoice->Stop();

		// �\�[�X�{�C�X�̔j��
		m_sourceVoiceDatebase[fname].m_SourceVoice->DestroyVoice();
		m_sourceVoiceDatebase[fname].m_SourceVoice = NULL;
		// �I�[�f�B�I�f�[�^�̊J��
		free(m_sourceVoiceDatebase[fname].m_DataAudio);

	}
	m_sourceVoiceDatebase[fname]=SDate();
	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(fname.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return false;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return false;
	}

	// WAVE�t�@�C���̃`�F�b�N
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return false;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return false;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �t�H�[�}�b�g�`�F�b�N
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return false;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return false;
	}
// �I�[�f�B�I�f�[�^�ǂݍ���
	hr = CheckChunk(hFile, 'atad', &m_sourceVoiceDatebase[fname].m_SizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return false;
	}
	m_sourceVoiceDatebase[fname].m_DataAudio = (BYTE*)malloc(m_sourceVoiceDatebase[fname].m_SizeAudio);
	
	hr = ReadChunkData(hFile, m_sourceVoiceDatebase[fname].m_DataAudio, m_sourceVoiceDatebase[fname].m_SizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �\�[�X�{�C�X�̐���
	hr = m_pXAudio2->CreateSourceVoice(&m_sourceVoiceDatebase[fname].m_SourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return false;
	}

	//MessageBox(hWnd, "���[�h����", "�x���I", MB_ICONWARNING);

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sourceVoiceDatebase[fname].m_SizeAudio;
	buffer.pAudioData = m_sourceVoiceDatebase[fname].m_DataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = 1;

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_sourceVoiceDatebase[fname].m_SourceVoice->SubmitSourceBuffer(&buffer);

	return true;
	
}
bool CSound::SetSound(std::string fname, HWND hWnd)
{
	//�t�@�C�������邩�ǂ����m�F
	if (m_sourceVoiceDatebase.count(fname)==0)
	{
		//�t�@�C�����Ȃ�
		
		//�ǂݍ���
		bool b= CSound::LoadSound(fname, hWnd);
		
		if (!b)
		{
			//�ǂݍ��ݎ��s
			return false;
		}
	}
	m_date = m_sourceVoiceDatebase[fname];

	return true;
}
void CSound::UninitSound(void)
{
	Crear();
		
	
	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	if (m_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

void CSound::Play()
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;
	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_date.m_SizeAudio;
	buffer.pAudioData = m_date.m_DataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_date.nCntLoop;
	//buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	// ��Ԏ擾
	m_date.m_SourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_date.m_SourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_date.m_SourceVoice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_date.m_SourceVoice->SubmitSourceBuffer(&buffer);
	m_date.m_SourceVoice->SetVolume(m_volume);

	// �Đ�
	m_date.m_SourceVoice->Start(0);
	m_play = true;
}
void CSound::Play(int loopCount)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;
	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_date.m_SizeAudio;
	buffer.pAudioData = m_date.m_DataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = loopCount;
	
	// ��Ԏ擾
	m_date.m_SourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_date.m_SourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_date.m_SourceVoice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_date.m_SourceVoice->SubmitSourceBuffer(&buffer);

	m_date.m_SourceVoice->SetVolume(m_volume);
	// �Đ�
	m_date.m_SourceVoice->Start(0);
	m_play = true;
}

void CSound::StopSound()
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_date.m_SourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_date.m_SourceVoice->Stop(0);
		m_play = false;
		// �I�[�f�B�I�o�b�t�@�̍폜
		m_date.m_SourceVoice->FlushSourceBuffers();
	}
}



void CSound::Init()
{

}
void CSound::Uninit()
{

}
void CSound::Draw()
{

}
void CSound::Update()
{
	if (!m_play)
	{
		StopSound();
		return;
	}
}



HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
