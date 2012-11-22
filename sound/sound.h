#ifndef SOUND_DLL_SOUND_H
#define SOUND_DLL_SOUND_H

#include <Windows.h>
#include <dsound.h>
#include "soundobj.h"

#ifdef SOUND_EXPORTS
#define SOUNDDLL_EXPORT __declspec(dllexport)
#else
#define SOUNDDLL_EXPORT __declspec(dllimport)
#endif

namespace sound {

#ifdef SOUND_EXPORTS
	extern SoundManipulator* soundManipulator;
#endif

	SOUNDDLL_EXPORT int Initialize(); // 初期化
	SOUNDDLL_EXPORT int Initialize(HWND hWnd); // 初期化
	SOUNDDLL_EXPORT void Cleanup(); // 後始末

	SOUNDDLL_EXPORT int LoadWave(unsigned ID, LPCSTR filename); // WAVE読み込み

	SOUNDDLL_EXPORT int Play(unsigned ID); // 再生
	SOUNDDLL_EXPORT int Stop(unsigned ID); // 停止
}

#endif
