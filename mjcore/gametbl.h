#ifndef GAMETBL_H
#define GAMETBL_H

#include <array>
#include <bitset>
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include "tilecode.h"
#include "ruletbl.h"
#include "largenum.h"

// -------------------------------------------------------------------------

enum gameTypeID { // 卓の種類(四麻、三麻)指定用
	Yonma = 0x01, Sanma = 0x02, Sanma4 = 0x04, SanmaS = 0x08,
	AllSanma = 0x0e, SanmaT = 0x0a, SanmaX = 0x06
};

// -------------------------------------------------------------------------

struct TILE { // 赤ドラデータを含めた牌のデータ
	tileCode tile;
	uint8_t red;
};

// -------------------------------------------------------------------------

#define PLAYERS 4
#define ACTUAL_PLAYERS (chkGameType(&GameStat, SanmaT) ? 3 : 4)
#define NUM_OF_TILES_IN_HAND 14
#define SIZE_OF_DISCARD_BUFFER 33

typedef int8_t PLAYER_ID; // プレイヤー番号

// -------------------------------------------------------------------------

typedef std::array<TILE, NUM_OF_TILES_IN_HAND> HAND_TILES;

// -------------------------------------------------------------------------

#define SUTEHAI_TYPE_STEP 200
enum discardStat {
	discardNormal,
	discardTaken,
	discardRiichi,
	discardRiichiTaken,
};
struct discardTile {
	TILE tcode;
	discardStat dstat;
	bool isDiscardThrough; // ツモ切りフラグ
};
typedef std::array<discardTile, SIZE_OF_DISCARD_BUFFER> DISCARD_BUF;

// -------------------------------------------------------------------------

#define SIZE_OF_MELD_BUFFER 5
#define MELD_TYPE_STEP 1000
enum meldStat {
	meldSequenceConcealed,      // 手の内の順子
	meldSequenceExposedLower,   // 小さい方をチー
	meldSequenceExposedMiddle,  // 嵌張をチー
	meldSequenceExposedUpper,   // 大きい方をチー
	meldTripletConcealed,       // 暗刻
	meldTripletExposedLeft,     // 上家からポン
	meldTripletExposedCenter,   // 対面からポン
	meldTripletExposedRight,    // 下家からポン
	meldQuadConcealed,          // 暗槓
	meldQuadExposedLeft,        // 上家から明槓
	meldQuadExposedCenter,      // 対面から明槓
	meldQuadExposedRight,       // 下家から明槓
	meldQuadAddedLeft,          // 上家からポンの後カン
	meldQuadAddedCenter,        // 対面からポンの後カン
	meldQuadAddedRight          // 下家からポンの後カン
};
struct meldCode {
	TILE tcode;
	meldStat mstat;
};
typedef std::array<meldCode, SIZE_OF_MELD_BUFFER> MELD_BUF;

// -------------------------------------------------------------------------

enum RICHI_STAT_BITS { // 立直フラグを格納
	RichiFlag, IppatsuFlag, DoubleFlag, OpenFlag,
	RichiStatBits
};
typedef std::bitset<RichiStatBits> RichiStat;

// -------------------------------------------------------------------------

struct KANGSTAT { uint8_t kangFlag, chainFlag, topFlag, chankanFlag; };

// -------------------------------------------------------------------------

#define PAO_YAKU_PAGES 4
enum paoYakuPage {pyDaisangen, pyDaisixi, pySikang, pyMinkan};

struct PAOSTAT { PLAYER_ID paoPlayer, agariPlayer; };
typedef std::array<PAOSTAT, PAO_YAKU_PAGES> paoStatBook;


// -------------------------------------------------------------------------

typedef std::array<TILE, 144> DeckBuf; // 最初はunionでやろうと思ったけどおかしくなるのでやめた

// -------------------------------------------------------------------------

struct prevMeldBook { tileCode Discard, Stepped; };

// -------------------------------------------------------------------------

typedef std::array<uint8_t, TILE_NONFLOWER_MAX> DORASTAT;
struct doraStatBook { DORASTAT Omote, Ura; };

// -------------------------------------------------------------------------

struct DECLFLAG {
	bool Ron, Kan, Pon;
	int8_t Chi;
};

// -------------------------------------------------------------------------

struct CURRPLAYER { PLAYER_ID Active, Passive, Agari, Furikomi; };

// -------------------------------------------------------------------------

struct PlayerTable { // プレイヤーの状態を格納
	LargeNum PlayerScore;
	int playerChip; // チップの収支
	bool SumaroFlag; // 四馬路解禁フラグ
	bool YakitoriFlag; // 焼き鳥フラグ
	HAND_TILES Hand; // 手牌の配列
	DISCARD_BUF Discard; // 捨牌の配列
	uint8_t DiscardPointer;
	MELD_BUF Meld; // 鳴き面子を格納
	uint8_t MeldPointer;
	bool MenzenFlag; // 門前フラグ
	int8_t HandStat; // 手牌の状態（立てる・見せる・伏せる）
	int8_t NumberOfQuads; // 槓子の数（四槓流局、三槓子、四槓子などの判定に使う）
	RichiStat RichiFlag; // リーチしているかどうか
	bool FirstDrawFlag; // １巡目である（地和、ダブル立直の判定に使う）
	bool DoujunFuriten; // 同順振聴である
	bool AgariHouki; // 和了り放棄の罰則中かどうか
	uint8_t FlowerFlag; // 晒している花牌を格納するフラグ
	uint8_t NorthFlag; // 晒している北風牌を格納するフラグ
	bool ConnectionLost;
	DECLFLAG DeclarationFlag; // 鳴きの宣言
};

// -------------------------------------------------------------------------

struct GameTable { // 卓の情報を格納する
	gameTypeID gameType;
	std::array<PlayerTable, PLAYERS> Player;
	PLAYER_ID PlayerID;
	int GameLength;
	int GameRound;
	int LoopRound;
	int Honba;
	int Deposit;
	int AgariChain;
	int LastAgariPlayer;
	std::array<bool, TILE_NONFLOWER_MAX> OpenRichiWait; // プンリーの待ち牌(ＣＯＭに意図的な放銃を起こさせないために使用)
	KANGSTAT KangFlag; // 嶺上開花；連開花と槓振り；頭槓和；搶槓の判定に使う
	uint8_t TurnRound; // 現在の巡目
	uint8_t KangNum; // 四槓流局、四槓子などの判定に使う
	bool RichiCounter; // リーチをカウンター(宣言牌をロン)
	PLAYER_ID WaremePlayer; // 割れ目の位置(-1で割れ目なし)
	PLAYER_ID DoukasenPlayer; // 導火線の位置(-1で導火線なし)
	uint8_t Dice1;
	uint8_t Dice2;
	bool Dice1Direction;
	bool Dice2Direction;
	paoStatBook PaoFlag; // 包フラグ（-1…なし、0〜3…該当プレイヤー）
	DeckBuf Deck; // 壁牌の配列
	uint8_t DeadTiles; // 王牌の数
	uint8_t ExtraRinshan; // 追加の嶺上牌の数
	bool ShibariFlag; //二飜縛り
	doraStatBook DoraFlag; // ドラ判定の配列
	uint8_t TilePointer; // ツモ牌のポインタ
	uint16_t DoraPointer;
	uint8_t RinshanPointer; // 嶺上牌のポインタ
	bool TianHuFlag; // 親の第一打牌がまだ（天和の判定などに使う）
	prevMeldBook PreviousMeld; // 先ほど鳴いた牌（喰い替えの判定に使う）
	CURRPLAYER CurrentPlayer;
	bool TsumoAgariFlag; // ツモアガリ？
	int16_t AgariSpecialStat; // 今のところ食い変えでチョンボになる場合だけ使ってる？
	TILE CurrentDiscard;
};

// -------------------------------------------------------------------------

extern GameTable GameStat;
inline bool chkGameType(GameTable* gameStat, gameTypeID gameType);

// -------------------------------------------------------------------------

#endif
