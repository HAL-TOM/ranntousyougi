#include <string>
#include <vector>
#include <memory>

#include "sound.h"

HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);


IXAudio2* CSound::m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
IXAudio2MasteringVoice* CSound::m_pMasteringVoice ;			// マスターボイス
std::map<std::string, SDate> CSound::m_sourceVoiceDatebase;//

void CSound::Crear()
{
	for (auto itr = m_sourceVoiceDatebase.begin(); itr != m_sourceVoiceDatebase.end(); ++itr)
	{

		if (itr->second.m_SourceVoice!=nullptr)
		{
			itr->second.m_SourceVoice->Stop();
			// ソースボイスの破棄
			itr->second.m_SourceVoice->DestroyVoice();
			itr->second.m_SourceVoice = NULL;

		}
		if (itr->second.m_DataAudio!=nullptr)
		{
			// オーディオデータの開放
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

	// COMライブラリの初期化
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if (m_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}
//	MessageBox(hWnd, "マスターボイスの生成に成功！", "警告！", MB_ICONWARNING);

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

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	m_sourceVoiceDatebase.find(fname);

	if (m_sourceVoiceDatebase.count(fname)!=0)
	{
		m_sourceVoiceDatebase[fname].m_SourceVoice->Stop();

		// ソースボイスの破棄
		m_sourceVoiceDatebase[fname].m_SourceVoice->DestroyVoice();
		m_sourceVoiceDatebase[fname].m_SourceVoice = NULL;
		// オーディオデータの開放
		free(m_sourceVoiceDatebase[fname].m_DataAudio);

	}
	m_sourceVoiceDatebase[fname]=SDate();
	// サウンドデータファイルの生成
	hFile = CreateFile(fname.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
		return false;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
		return false;
	}

	// WAVEファイルのチェック
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return false;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return false;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
		return false;
	}

	// フォーマットチェック
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return false;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return false;
	}
// オーディオデータ読み込み
	hr = CheckChunk(hFile, 'atad', &m_sourceVoiceDatebase[fname].m_SizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
		return false;
	}
	m_sourceVoiceDatebase[fname].m_DataAudio = (BYTE*)malloc(m_sourceVoiceDatebase[fname].m_SizeAudio);
	
	hr = ReadChunkData(hFile, m_sourceVoiceDatebase[fname].m_DataAudio, m_sourceVoiceDatebase[fname].m_SizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
		return false;
	}

	// ソースボイスの生成
	hr = m_pXAudio2->CreateSourceVoice(&m_sourceVoiceDatebase[fname].m_SourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
		return false;
	}

	//MessageBox(hWnd, "ロード成功", "警告！", MB_ICONWARNING);

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sourceVoiceDatebase[fname].m_SizeAudio;
	buffer.pAudioData = m_sourceVoiceDatebase[fname].m_DataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = 1;

	// オーディオバッファの登録
	m_sourceVoiceDatebase[fname].m_SourceVoice->SubmitSourceBuffer(&buffer);

	return true;
	
}
bool CSound::SetSound(std::string fname, HWND hWnd)
{
	//ファイルがあるかどうか確認
	if (m_sourceVoiceDatebase.count(fname)==0)
	{
		//ファイルがない
		
		//読み込み
		bool b= CSound::LoadSound(fname, hWnd);
		
		if (!b)
		{
			//読み込み失敗
			return false;
		}
	}
	m_date = m_sourceVoiceDatebase[fname];

	return true;
}
void CSound::UninitSound(void)
{
	Crear();
		
	
	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	if (m_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

void CSound::Play()
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;
	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_date.m_SizeAudio;
	buffer.pAudioData = m_date.m_DataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_date.nCntLoop;
	//buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	// 状態取得
	m_date.m_SourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_date.m_SourceVoice->Stop(0);

		// オーディオバッファの削除
		m_date.m_SourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_date.m_SourceVoice->SubmitSourceBuffer(&buffer);
	m_date.m_SourceVoice->SetVolume(m_volume);

	// 再生
	m_date.m_SourceVoice->Start(0);
	m_play = true;
}
void CSound::Play(int loopCount)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;
	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_date.m_SizeAudio;
	buffer.pAudioData = m_date.m_DataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = loopCount;
	
	// 状態取得
	m_date.m_SourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_date.m_SourceVoice->Stop(0);

		// オーディオバッファの削除
		m_date.m_SourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_date.m_SourceVoice->SubmitSourceBuffer(&buffer);

	m_date.m_SourceVoice->SetVolume(m_volume);
	// 再生
	m_date.m_SourceVoice->Start(0);
	m_play = true;
}

void CSound::StopSound()
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_date.m_SourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_date.m_SourceVoice->Stop(0);
		m_play = false;
		// オーディオバッファの削除
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
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
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
