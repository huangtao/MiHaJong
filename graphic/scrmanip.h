#pragma once

#include <d3dx9.h>
#include <dxerr.h>
#include <tchar.h>
#include <functional>
#include "scenes/scenes.h"
#include "input.h"

namespace mihajong_graphic {

class ScreenManipulator {
private:
	HWND hWnd;
	LPDIRECT3D9 pd3d; // Direct3D
	LPDIRECT3DDEVICE9 pDevice; // Direct3Dデバイス
	Scene* myScene; // シーン管理用のクラス
	FPSIndicator* myFPSIndicator; // FPS計算・表示
	UINT64 lastRedrawTime;
	bool redrawFlag; // 画面の再描画をするかどうかのフラグ
	void InitDevice(); // Direct3D オブジェクト初期化
	void inputProc(input::InputDevice* inputDev, std::function<void (Scene*, LPDIDEVICEOBJECTDATA)> f);
public:
	void Render(); // 画面の再描画
	ScreenManipulator(HWND windowHandle);
	~ScreenManipulator();
	HWND getHWnd() {return hWnd;}
	LPDIRECT3DDEVICE9 getDevice() {return pDevice;}
	void inputProc(input::InputManipulator* iManip);
	void transit(sceneID scene);
};

}
