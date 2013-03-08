#pragma once

#include <array>
#include "sysscr.h"
#include "../../common/gametbl.h"

namespace mihajong_graphic {

class ResultScreen : public SystemScreen {
private:
	class RankRenderer;
	std::array<RankRenderer*, mihajong_structs::Players> rankRenderer;
public:
	ResultScreen(ScreenManipulator* const manipulator);
	~ResultScreen();
	void Render();
	virtual void KeyboardInput(LPDIDEVICEOBJECTDATA od);
	virtual void MouseInput(LPDIDEVICEOBJECTDATA od, int X, int Y);
};

class ResultScreen::RankRenderer {
private:
	LPDIRECT3DDEVICE9 myDevice;
	uint64_t startTime;
	int myID;
public:
	RankRenderer(LPDIRECT3DDEVICE9 device, int id);
	~RankRenderer();
	void Render();
};

}
