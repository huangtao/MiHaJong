#ifndef FUNC_H
#define FUNC_H

#include <array>
#include <cstdint>
#include "gametbl.h"

typedef std::array<uint8_t, TILE_CODE_MAXIMUM> tileCountTbl;

class TileCount { // 手牌にある種類別の牌の数
public:
	tileCountTbl count;
	TileCount() {
		this->count.fill(0);
	}
};

TileCount countTilesInHand(GameTable gameStat, PLAYER_ID playerID);

#endif
