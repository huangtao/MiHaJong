#ifndef MNZDAT_H
#define MNZDAT_H

#include <windows.h>
#ifdef MJCORE_EXPORTS
#include <cstdio>
#endif
#include <cstdint>
#ifdef MJCORE_EXPORTS
#include <cstdlib>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "resource.h"
#include "lzma/LzmaLib.h"
#include "lzma/Sha256.h"
#endif
#include "except.h"
#include "mjexport.h"
#include "gametbl.h"
#include "tilecode.h"
#include "func.h"
#ifdef MJCORE_EXPORTS
#include "logging.h"
#include "dllmain.h"
#endif

#define SHANTEN_IMPOSSIBLE 999

#ifdef MJCORE_EXPORTS
void LoadFileInResource(int name, int type, DWORD& size, const char*& data);
size_t decompressMentsuAnalysisDat();
void calcSHA256(uint8_t* digest, const uint8_t* buf, size_t bufSize);
std::string bytesToHexString(std::vector<std::uint8_t> byteStr);
void verifyMentsuAnalysisDat(size_t bufSize);
__declspec(dllexport) void initMentsuAnalysisDat();
#endif

typedef int SHANTEN; // 向聴数のためのデータ型（0=聴牌、-1=和了、999=無効）
enum shantenType : uint8_t { // getShantenに渡すスイッチ用
	shantenAll, // すべて求める
	shantenRegular, // 普通の和了形のみ
	shantenPairs, // 七対子
	shantenOrphans, // 国士無双
	shantenStellar, // 七星無靠
	shantenCivilWar, // 南北戦争
	shantenSyzygy, // 惑星直列
	shantenQuanbukao // 全不靠
};

MJCORE SHANTEN calcShanten(const GameTable* const gameStat, PLAYER_ID playerID, shantenType mode);
#ifdef MJCORE_EXPORTS
__declspec(dllexport) int calcShanten(const GameTable* const gameStat, int playerID, int mode);
SHANTEN calcShantenRegular(const GameTable* const gameStat, PLAYER_ID playerID, TileCount& tileCount);
SHANTEN calcShantenChiitoi(const GameTable* const gameStat, PLAYER_ID playerID, TileCount& tileCount);
SHANTEN calcShantenKokushi(const GameTable* const gameStat, PLAYER_ID playerID, TileCount& tileCount);
SHANTEN calcShantenStellar(const GameTable* const gameStat, PLAYER_ID playerID, TileCount& tileCount, bool qixing);
SHANTEN calcShantenCivilWar(const GameTable* const gameStat, PLAYER_ID playerID, TileCount& tileCount);
SHANTEN calcShantenSyzygy(const GameTable* const gameStat, PLAYER_ID playerID, TileCount& tileCount);
#endif

#endif
