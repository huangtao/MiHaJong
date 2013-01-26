#pragma once

#ifdef MJCORE_EXPORTS
#include <type_traits>
#endif
#include <cstdint>
#include "mjexport.h"
#include "gametbl.h"

// -------------------------------------------------------------------------

EXPORT_STRUCT MachihaiTileInfo {
	bool MachihaiFlag; // 待ち牌になっているかのフラグ
	int8_t MachihaiCount; // 待ち牌の残り枚数
};
#ifdef MJCORE_EXPORTS
static_assert(std::is_pod<MachihaiTileInfo>::value, "MachihaiTileInfo is not POD");
#endif

EXPORT_TEMPLATE_STRUCT InfoByTile<MachihaiTileInfo>;
EXPORT_STRUCT MachihaiInfo { // 待ち牌とかの情報を格納(chkFuriten関数用)
	bool FuritenFlag; // フリテンかどうかのフラグ
	InfoByTile<MachihaiTileInfo> Machihai; // 待ち牌情報
	int8_t MachihaiTotal; // 待ち牌の合計枚数
	int8_t MachiMen; // 何面待ち？
};
#ifdef MJCORE_EXPORTS
static_assert(std::is_pod<MachihaiInfo>::value, "MachihaiInfo is not POD");
#endif

EXPORT_STRUCT TileStatus { // gettilestatus用
	bool isExistent, canFormQuad,
		seqMidWait, seqDoubleSideWait, seqSingleSideWait,
		formsPair, formsSequence, formsTriplet;
};
#ifdef MJCORE_EXPORTS
static_assert(std::is_pod<TileStatus>::value, "TileStatus is not POD");
#endif

// -------------------------------------------------------------------------

#ifdef MJCORE_EXPORTS
PLAYER_ID* tobePlayed(const GameTable* const gameStat);
PLAYER_ID tobePlayed(const GameTable* const gameStat, int id);

const tileCode* Honor_Major_Tiles();
tileCode Honor_Major_Tiles(int code);
bool isYaojiu(tileCode code);

void lipai(GameTable* const gameStat, PLAYER_ID targetPlayer);
__declspec(dllexport) void lipai(GameTable* const gameStat, int targetPlayer);
#endif

MJCORE Int8ByTile countseentiles(const GameTable* const gameStat);

MJCORE Int8ByTile countTilesInHand(const GameTable* const gameStat, PLAYER_ID playerID);
#ifdef MJCORE_EXPORTS
__declspec(dllexport) void countTilesInHand(int* const tileCount, const GameTable* const gameStat, int playerID);
#endif

MJCORE Int8ByTile countRedTilesInHand(const GameTable* const gameStat, PLAYER_ID playerID, int doraCol);

MJCORE TileStatus gettilestatus(
	const GameTable* const gameStat, PLAYER_ID targetPlayer, int targetTile, bool CheckMode);

MJCORE MachihaiInfo chkFuriten(const GameTable* const gameStat, PLAYER_ID targetPlayer);
#ifdef MJCORE_EXPORTS
__declspec(dllexport) void chkFuriten(
	int* const furitenFlag, int* const machihaiFlag, int* const machihaiCount,
	int* const machihaiTotal, int* const machiMen, const GameTable* const gameStat,
	int targetPlayer);

void chkOpenMachi(GameTable* const gameStat, PLAYER_ID targetPlayer);
__declspec(dllexport) void chkOpenMachi(GameTable* const gameStat, int targetPlayer);
#endif

MJCORE bool chkdaopaiability(const GameTable* const gameStat, PLAYER_ID targetPlayer);
#ifdef MJCORE_EXPORTS
__declspec(dllexport) int chkdaopaiability(const GameTable* const gameStat, int targetPlayer);

__declspec(dllexport) void setdora(GameTable* const gameStat, int Mode);
#endif

MJCORE bool chkAnkanAbility(const GameTable* const gameStat, PLAYER_ID targetPlayer);
#ifdef MJCORE_EXPORTS
__declspec(dllexport) int chkAnkanAbility(const GameTable* const gameStat, int targetPlayer);

__declspec(dllexport) void calcdoukasen(GameTable* const gameStat);

bool isTenpai(const GameTable* const gameStat, PLAYER_ID targetPlayer);
__declspec(dllexport) int isTenpai(const GameTable* const gameStat, void *, int targetPlayer);

bool isNagashiMangan(const GameTable* const gameStat, PLAYER_ID targetPlayer);
__declspec(dllexport) int isNagashiMangan(const GameTable* const gameStat, void *, int targetPlayer);
#endif
