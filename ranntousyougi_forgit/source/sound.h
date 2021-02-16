#pragma once
#include<map>
#include <XAudio2.h>

#include "component.h"
//音声情報
struct SDate
{
	IXAudio2SourceVoice* m_SourceVoice;	// ソースボイス
	BYTE * m_DataAudio ;					// オーディオデータ
	DWORD m_SizeAudio ;					// オーディオデータサイズ
	int nCntLoop = 0;		// ループカウント

};

class CSound :
	public CComponent
{
protected:

	static IXAudio2* m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice ;			// マスターボイス
	static std::map<std::string, SDate> m_sourceVoiceDatebase;//データベース
	SDate m_date;
public:
	int m_frame = 0;
	float m_volume;
	bool m_play;//再生するかどうか
	static void Crear();//データ削除
	static HRESULT InitSound(HWND hWnd);//初期化処理
	static void UninitSound(void);//終了処理
	static bool LoadSound(std::string fname , HWND hWnd);//データ追加
	bool SetSound(std::string fname, HWND hWnd);
	void Play();//再生
	void Play(int loopCount);//XAUDIO2_END_OF_STREAMで無限ループ

	void StopSound();//停止

	void Init();
	void Uninit();
	void Draw();
	void Update();
		
	CSound();
	~CSound();

};

