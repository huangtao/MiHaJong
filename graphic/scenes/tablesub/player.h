#pragma once

#include "tablesub.h"
#include "../../text.h"

namespace mihajong_graphic {

class TableSubscenePlayerProto : public TableSubscene {
protected:
	static const int timeX = 725;
	static const int timeY = 900;
	static const unsigned timeResolution = 10000000u;
	TextRenderer* myTextRenderer;
	int timeout_val; /* 制限時間をミリ秒で */
	void showTimeout();
public:
	TableSubscenePlayerProto(LPDIRECT3DDEVICE9 device);
	virtual ~TableSubscenePlayerProto();
	std::int32_t timeout(); // タイムアウト判定用（オーバーライド）
};

class TableSubscenePlayerDahai : public TableSubscenePlayerProto {
public:
	TableSubscenePlayerDahai(LPDIRECT3DDEVICE9 device);
	~TableSubscenePlayerDahai();
	void Render();
};

class TableSubscenePlayerNaki : public TableSubscenePlayerProto {
public:
	TableSubscenePlayerNaki(LPDIRECT3DDEVICE9 device);
	~TableSubscenePlayerNaki();
	void Render();
};

}
