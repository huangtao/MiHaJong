#pragma once

#include "../mjcore/strcode.h"
#include <d3dx9.h>
#include <dxerr.h>
#include <WinUser.h>
#include <Imm.h>
#include <tuple>
#include "text.h"
#include <vector>

namespace mihajong_graphic {

class EditBox { // 自前のエディットボックスもどき
private:
	HWND myHWnd;
	CodeConv::tstring myText;
	std::tuple<int, int, unsigned, unsigned> myRegion;
	SmallTextRenderer* myTextRenderer;
	LPDIRECT3DDEVICE9 myDevice;
	unsigned maxStr;
	bool isFullWidth(wchar_t chr);
	bool isFullWidth(char chr);
	LPD3DXLINE cursorLine;
	unsigned cursorPos;
	unsigned long long cursorBlinkStart;
	unsigned long long currTime();
	class IMStat;
	bool isLeadingByte(wchar_t chr);
	bool isLeadingByte(char chr);
	void renderNormalText(unsigned start, unsigned end, int X, int Y, unsigned& TextID, unsigned& cols, signed& cursorcol);
	void renderIMText(IMStat& imStat, int X, int Y, unsigned& TextID, unsigned& cols, signed& cursorcol);
	void renderIMCandidates(IMStat& imStat, int X, int Y, unsigned& TextID);
	void renderCursor(IMStat& imStat, int X, int Y, signed& cursorcol);
public:
	EditBox(HWND hwnd, LPDIRECT3DDEVICE9 device, int X, int Y, unsigned width, unsigned height);
	~EditBox();
	void Render();
	void KeyboardInput(WPARAM wParam, LPARAM lParam);
	void IMEvent(UINT message, WPARAM wParam, LPARAM lParam);
};

class EditBox::IMStat { // IMEの状態
private:
	HWND hwnd; HIMC hIMC;
	IMStat(const IMStat&) {}; // disable copy constructor
	std::vector<BYTE> getCompositionString(DWORD InfoType);
public:
	IMStat(HWND hWnd);
	~IMStat();
	bool isOpened();
	std::tuple<DWORD, DWORD> getConvStat();
	CodeConv::tstring getGCSCompStr();
	std::vector<BYTE> getGCSCompAttr();
	CodeConv::tstring getGCSResultStr();
	int getGCSCursorPos();
	std::tuple<unsigned, std::vector<CodeConv::tstring>, unsigned, unsigned> getCandidateList();
};

}
