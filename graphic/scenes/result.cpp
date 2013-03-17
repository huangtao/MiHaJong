#ifdef _MSC_VER
#define NOMINMAX
#define _USE_MATH_DEFINES /* TODO: 仮対処。M_PIのヘッダ定義用(非推奨に付き自前で定義すること！) */
#endif
#include "result.h"
#include <cmath>
#include <algorithm>
#include "../utils.h"
#include "../gametbl.h"
#include "../finscore.h"

namespace mihajong_graphic {

using namespace mihajong_structs;

// -------------------------------------------------------------------------

ResultScreen::ResultScreen(ScreenManipulator* const manipulator) : SystemScreen(manipulator) {
	rankRenderer.fill(nullptr);
}

ResultScreen::~ResultScreen() {
	for (auto k = rankRenderer.begin(); k != rankRenderer.end(); ++k)
		if (*k) delete *k;
}

void ResultScreen::Render() {
	clearWithGameTypeColor();
	for (int i = 0; i < Players; ++i)
		if ((myTimer.elapsed() >= (1000000 + i * 500000)) && (rankRenderer[i] == nullptr))
			rankRenderer[i] = new RankRenderer(caller->getDevice(), i);
	for (auto k = rankRenderer.begin(); k != rankRenderer.end(); ++k)
		if (*k) (*k)->Render();
}

void ResultScreen::KeyboardInput(LPDIDEVICEOBJECTDATA od) {
}

void ResultScreen::MouseInput(LPDIDEVICEOBJECTDATA od, int X, int Y) {
}

// -------------------------------------------------------------------------

ResultScreen::RankRenderer::RankRenderer(LPDIRECT3DDEVICE9 device, int id) {
	myDevice = device;
	myID = id;
	BaseY = (3 - id) * 150 + 300;
	PlayerRankList rank = utils::calcRank(GameStatus::retrGameStat());
	player = -1;
	for (PlayerID i = 0; i < (utils::chkGameType(GameStatus::retrGameStat(), SanmaT) ? 3 : 4); ++i)
		if (rank[i] == (4 - id)) player = i;
	nameRenderer = new SmallTextRenderer(device);
	rankRenderer = new HugeTextRenderer(device);
	scoreRenderer = new ScoreDigitRenderer(device);
}

ResultScreen::RankRenderer::~RankRenderer() {
	delete nameRenderer;
	delete rankRenderer;
	delete scoreRenderer;
}

unsigned ResultScreen::RankRenderer::stringWidth(const CodeConv::tstring& str) {
	std::wstring wstr(
#ifdef _UNICODE
		str
#else
		CodeConv::ANSItoWIDE(str)
#endif
		);
	unsigned Anzahl = 0;
	for (auto k = wstr.begin(); k != wstr.end(); ++k)
		Anzahl += (*k <= L'\x7f') ? 1 : 2;
	return Anzahl;
}

void ResultScreen::RankRenderer::RenderRank() {
	CodeConv::tostringstream o; o << (4 - myID);
	D3DCOLOR txtcolor;
	switch (4 - myID) {
		case 1:  txtcolor = 0xffffd700; break;
		case 2:  txtcolor = 0xffffffff; break;
		case 3:  txtcolor = 0xffb87333; break;
		default: txtcolor = 0xff9955ee; break;
	}
	rankRenderer->NewText(0, o.str(), 60, BaseY, 0.625f, 1.0f, txtcolor);
	rankRenderer->Render();
}

void ResultScreen::RankRenderer::RenderNameScore() {
	const uint64_t tempus = myTimer.elapsed();
	const D3DCOLOR aColor = D3DCOLOR_ARGB((tempus >= animTime) ? 255 :
		(255 - (int)(200.0 - ((double)tempus / (double)animTime * 200.0))),
		255, 255, 255);
	const D3DCOLOR color = (player != GameStatus::gameStat()->PlayerID) ? 0xffffffff :
		D3DCOLOR_ARGB(255, 255,
		(int)(200.0 - sin((double)myTimer.elapsed() * M_PI / 500000.0) * 50.0),
		(int)(200.0 - sin((double)myTimer.elapsed() * M_PI / 500000.0) * 50.0)
		);
	const CodeConv::tstring nomen(utils::getName(player));
	const unsigned latitudoNominis = stringWidth(nomen);
	nameRenderer->NewText(0, nomen, 150, BaseY + 10, 3.0f,
		(latitudoNominis >= 30) ? 30.0f / (float)latitudoNominis : 1.0f,
		aColor & color);
	const CodeConv::tstring punctaticum(
		CodeConv::tstring(_T("素点：")) +
		GameStatus::gameStat()->Player[player].PlayerScore.bignumtotext(_T(""), _T("△")));
	const unsigned latitudoPunctatici = stringWidth(punctaticum);
	nameRenderer->NewText(1, punctaticum, 150, BaseY + 70, 3.0f,
		(latitudoPunctatici >= 30) ? 30.0f / (float)latitudoPunctatici : 1.0f,
		aColor & color);
	nameRenderer->Render();
}

void ResultScreen::RankRenderer::RenderScore() {
	const unsigned widthLimit = 4u;
	const uint64_t tempus = myTimer.elapsed();
	const D3DCOLOR aColor = D3DCOLOR_ARGB((tempus >= animTime) ? 255 :
		(255 - (int)(200.0 - ((double)tempus / ((double)animTime / 200.0)))),
		255, 255, 255);
	const float scale = (tempus >= animTime) ? 1.0f :
		1.0f + pow((float)(animTime - tempus) / (float)animTime * 3.5f, 2);
	const LargeNum point(FinalScoreDat::getData(player));
	const CodeConv::tstring scoreTxt(point.bignumtotext(_T("+"), _T("△")));
	const D3DCOLOR color =
		(point > LargeNum::fromInt(0)) ? 0xffccffcc :
		(point < LargeNum::fromInt(0)) ? 0xffffcccc : 0xffffffcc;
	const unsigned strWidth = [](const CodeConv::tstring& str) -> unsigned {
		const std::wstring ws =
#ifdef _UNICODE
			str;
#else
			CodeConv::ANSItoWIDE(str);
#endif
		return ws.length();
	} (scoreTxt);
	scoreRenderer->NewText(0, scoreTxt,
		1000 + 96 * std::max((signed)widthLimit - (signed)strWidth, 0) -
		(int)(96.0f * (float)std::min(strWidth, widthLimit) * (scale - 1.0)),
		BaseY + 10 - (int)(64.0f * (scale - 1.0)),
		scale,
		(float)widthLimit / (float)std::max(strWidth, widthLimit),
		aColor & color);
	scoreRenderer->Render();
}

void ResultScreen::RankRenderer::Render() {
	RenderRank();
	RenderNameScore();
	RenderScore();
}

// -------------------------------------------------------------------------

}
