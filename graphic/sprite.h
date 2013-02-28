#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <dxerr.h>
#include "../common/strcode.h"

namespace mihajong_graphic {

class SpriteRenderer {
private: /* Singleton class idioms */
	SpriteRenderer(const SpriteRenderer&) {throw _T("Attempt to copy singleton instance");}
	SpriteRenderer& operator=(const SpriteRenderer&) {throw _T("Attempt to copy singleton instance");}
	SpriteRenderer(LPDIRECT3DDEVICE9 device);
private:
	LPD3DXSPRITE sprite;
public:
	void ShowSprite(LPDIRECT3DTEXTURE9 texture, int X, int Y, int Width, int Height,
		D3DCOLOR color = 0xffffffff, RECT* rect = nullptr, int CenterX = 0, int CenterY = 0, LPD3DXMATRIX matrix = nullptr);
	void Start();
	void End();
	static SpriteRenderer* instantiate(LPDIRECT3DDEVICE9 device);
	~SpriteRenderer();
};

}