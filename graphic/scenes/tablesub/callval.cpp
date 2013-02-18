#include "callval.h"
#include "../../utils.h"
#include "../../calltext.h"
#include <cmath>
#include <cassert>

namespace mihajong_graphic {

TableSubsceneCallValue::TableSubsceneCallValue(LPDIRECT3DDEVICE9 device, const CodeConv::tstring& caption) : TableSubscene(device) {
	fontRenderer = new CallDigitRenderer(device);
	captionRenderer = nullptr;
	if (!caption.empty()) captionRenderer = new TableSubsceneMsg(device, caption);
}

TableSubsceneCallValue::~TableSubsceneCallValue() {
	delete fontRenderer;
	if (captionRenderer) delete captionRenderer;
}

const std::array<CodeConv::tstring, 17> TableSubsceneCallValue::digitName = {
	_T(""),
	_T("万"),     _T("億"),     _T("兆"),     _T("京"),
	_T("垓"),     _T("杼"),     _T("穣"),     _T("溝"),
	_T("澗"),     _T("正"),     _T("載"),     _T("極"),
	_T("恒河沙"), _T("阿僧祇"), _T("那由他"), _T("不可思議"),
};

void TableSubsceneCallValue::ShowCall(PlayerID player, int x, int y) {
	fontRenderer->DelText(player);
	callvalue::CallValue c_val = callvalue::getVal(player);
	if ((c_val.Mantissa == 0) && (c_val.Exponent == 0)) return; // 表示しない場合
	assert(c_val.Exponent >= 2u); // 小数には対応しない

	const std::uint64_t curr = currTime();
	const int animationLength = 2500000;
	const D3DCOLOR col = D3DCOLOR_ARGB(
		(curr >= (startTime + animationLength)) ? 255 :
		(int)std::pow((float)((curr - startTime) * 255) / animationLength / 16.0f, 2),
		c_val.Mantissa > 0 ? 0xcc : 0xff,
		c_val.Mantissa < 0 ? 0xcc : 0xff,
		0xcc);

	CodeConv::tostringstream o; unsigned callLen = 0u;
	if (c_val.Mantissa != 0) {
		o << ((c_val.Mantissa > 0) ? _T('+') : _T('-')); // 符号
		if (c_val.Exponent < 5u) { // 100〜99900まで
			o << std::abs(c_val.Mantissa);
			if      (c_val.Exponent == 4u) o << _T("00");
			else if (c_val.Exponent == 3u) o << _T("0");
			callLen = o.str().size();
		} else { // 青天ルール用
			switch (c_val.Exponent % 4) {
			case 0:
				o << (std::abs(c_val.Mantissa) / 100) << _T('.') << (std::abs(c_val.Mantissa) % 100);
				break;
			case 1:
				o << (std::abs(c_val.Mantissa) / 10) << _T('.') << (std::abs(c_val.Mantissa) % 10);
				break;
			case 2:
				o << std::abs(c_val.Mantissa);
				break;
			case 3:
				o << std::abs(c_val.Mantissa) << _T('0');
				break;
			}
			callLen = o.str().size() + 1u;
			o << digitName[c_val.Exponent / 4];
		}
	} else {
		o << _T('0'); callLen = 1u;
	}
	fontRenderer->NewText(player, o.str(), x - 24 * callLen, y - 48, 1.0f, 1.0f, col);
}

void TableSubsceneCallValue::ShowAllCall() {
	ShowCall(utils::RelativePositionOf(GameStatus::gameStat()->PlayerID, sOpposite), TableSize / 2      ,                 192);
	ShowCall(utils::RelativePositionOf(GameStatus::gameStat()->PlayerID, sLeft    ),                 256, TableSize / 2      );
	ShowCall(utils::RelativePositionOf(GameStatus::gameStat()->PlayerID, sRight   ), TableSize     - 256, TableSize / 2      );
	ShowCall(utils::RelativePositionOf(GameStatus::gameStat()->PlayerID, sSelf    ), TableSize / 2      , TableSize     - 192);
}

void TableSubsceneCallValue::Render() {
	captionRenderer->Render();
	ShowAllCall();
	fontRenderer->Render();
}

}
