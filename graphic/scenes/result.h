#pragma once

#include <array>
#include "sysscr.h"
#include "../../common/gametbl.h"
#include "../timer.h"
#include "../text.h"

namespace mihajong_graphic {

class ResultScreen : public SystemScreen {
private:
	class RankRenderer;
	std::array<RankRenderer*, mihajong_structs::Players> rankRenderer;
	HugeTextRenderer* titleRenderer;
	Timer myTimer;
public:
	ResultScreen(ScreenManipulator* const manipulator);
	ResultScreen(const ResultScreen&) = delete; // Delete unexpected copy constructor
	ResultScreen& operator= (const ResultScreen&) = delete; // Delete unexpected assign operator
	~ResultScreen();
	void Render();
#ifdef _WIN32
	virtual void KeyboardInput(LPDIDEVICEOBJECTDATA od);
	virtual void MouseInput(LPDIDEVICEOBJECTDATA od, int X, int Y);
#else /*_WIN32*/
	virtual void KeyboardInput(const XEvent* od);
	virtual void MouseInput(const XEvent* od, int X, int Y);
#endif /*_WIN32*/
};

class ResultScreen::RankRenderer {
private:
	static const unsigned animTime = 500000u;
private:
	DevicePtr myDevice;
	Timer myTimer;
	int myID;
	int BaseY;
	mihajong_structs::PlayerID player;
private:
	HugeTextRenderer* rankRenderer;
	void RenderRank();
private:
	SmallTextRenderer* nameRenderer;
	void RenderNameScore();
private:
	ScoreDigitRenderer* scoreRenderer;
	void RenderScore();
public:
	RankRenderer(DevicePtr device, int id);
	RankRenderer(const RankRenderer&) = delete; // Delete unexpected copy constructor
	RankRenderer& operator= (const RankRenderer&) = delete; // Delete unexpected assign operator
	~RankRenderer();
	void Render();
};

}
