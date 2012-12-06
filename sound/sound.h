#pragma once

#include <Windows.h>
#include <dsound.h>

#ifdef SOUND_EXPORTS
#define SOUNDDLL_EXPORT __declspec(dllexport)
#include "soundobj.h"
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

	SOUNDDLL_EXPORT int LoadWave(unsigned ID, LPCSTR filename, int looped); // WAVE読み込み
	SOUNDDLL_EXPORT int LoadVorbis(unsigned ID, LPCSTR filename, int looped); // Vorbis読み込み
	SOUNDDLL_EXPORT int LoadMidi(unsigned ID, LPCSTR filename, int looped); // MIDI読み込み

	SOUNDDLL_EXPORT int Play(unsigned ID); // 再生
	SOUNDDLL_EXPORT int Stop(unsigned ID); // 停止
}
