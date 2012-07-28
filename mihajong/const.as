/*=============================
 * HSP麻雀クライアントMiHaJong
 *        [定数の定義]
 *=============================
 */

/* バージョン情報 */
#define VERSION_MAJ 1
#define VERSION_MED 5
#define VERSION_MIN 4
#define VERSION_MIC ""

/* フォントの指定 */
/* 必ず等幅日本語フォントを指定すること */
#define fontname "ＭＳ 明朝"

/* 基本的なゲーム用の定数 */
#ifdef SANMAT
#define NUM_OF_ACTUAL_PLAYERS	3
#else
#define NUM_OF_ACTUAL_PLAYERS	4
#endif
#define NUM_OF_PLAYERS			4
#define NUM_OF_DIGIT_GROUPS		8
#define NUM_OF_TILES_IN_HAND	14
#const TSUMOHAI_INDEX			NUM_OF_TILES_IN_HAND-1
#define SIZE_OF_MELD_BUFFER		5
#define SIZE_OF_DISCARD_BUFFER	33

/* スクリーン管理番号 */
#enum SCR_TILE_PIC = 1
#enum SCR_DICE_PIC
#enum SCR_DICE_SHADE
#enum SCR_PLAYER_BUFFER_LOWER
#enum SCR_PLAYER_BUFFER_UPPER = (SCR_PLAYER_BUFFER_LOWER+NUM_OF_PLAYERS)
#enum SCR_TILE_BLOCK = (SCR_PLAYER_BUFFER_UPPER+NUM_OF_PLAYERS)
#enum SCR_TILE_SHADE
#enum SCR_AGARI_BUF
#enum SCR_TEXT_BUF
#enum SCR_TEXT_RESIZE_BUF
#enum SCR_BUTTON_FLAME_BUFFER
#enum SCR_MAIN_LOGO
#enum SCR_CHAT
#enum SCR_RULE
#enum SCR_TITLE_BACKGROUND
#enum SCR_TITLE_LOGO
#enum SCR_MAIN_BACKGROUND
#enum SCR_SPLASH_WINDOW
#enum SCR_SPLASH_BUF
#enum SCR_CONF_ITEM_CACHE

/* 通信ポート番号 */
#ifdef SANMAS
	#define PORT_GAME	50030
#else
	#ifdef SANMA4
		#define PORT_GAME	50040
	#else
		#ifdef SANMA
			#define PORT_GAME	50010
		#else
			#define PORT_GAME	50000
		#endif
	#endif
#endif
#define PORT_CHAT	50020
#define PORT_LOGGER	53662

/* 通信ソケットID */
#define SOCK_GAME	0
#define SOCK_CHAT	10
#define SOCK_LOGGER	7

/* 牌の画像関聯 */
#define TILE_WIDTH			23
#define TILE_HEIGHT			31
#define TILE_THICKNESS		10
#define TILE_THICKNESS_SIDE	11
#const TILE_BLOCK_WIDTH		TILE_WIDTH+TILE_THICKNESS*2
#const TILE_BLOCK_HEIGHT	TILE_HEIGHT+TILE_THICKNESS*3

#const TILE_BLOCK_SCREEN_X		TILE_WIDTH*9
#const TILE_BLOCK_SCREEN_Y		TILE_WIDTH*9
#const TILE_BLOCK_SCREEN_WIDTH	TILE_BLOCK_WIDTH*4
#const TILE_BLOCK_SCREEN_HEIGHT	TILE_BLOCK_HEIGHT*4
#define TILE_DICE_WIDTH			12
#define TILE_DICE_HEIGHT		12
#const TILE_RIICHISTICK_LENGTH	TILE_DICE_WIDTH*6
#define TILE_RIICHISTICK_WIDTH	6
#const TILE_CHICHAMARK_WIDTH	TILE_DICE_WIDTH*3
#define TILE_CHICHAMARK_HEIGHT	25
#const TILE_DICE_SCREEN_WIDTH	TILE_DICE_WIDTH*6
#const TILE_DICE_SCREEN_HEIGHT	TILE_DICE_HEIGHT*2+TILE_RIICHISTICK_WIDTH+TILE_CHICHAMARK_HEIGHT*4

#define TILE_SHADOW			64
#define TILE_DICE_SHADOW	144

/* ＢＧＭの番号 */
#define BGM_START	0
#define BGM_ROUNDS	28
#enum MUS_RICHI1 = BGM_ROUNDS
#enum MUS_RICHI2
#enum MUS_RICHI3
#enum MUS_OPENRICHI
#enum MUS_AGARI_SELF_1
#enum MUS_AGARI_SELF_2
#enum MUS_AGARI_SELF_3
#enum MUS_AGARI_FURIKOMI_1
#enum MUS_AGARI_FURIKOMI_2
#enum MUS_AGARI_FURIKOMI_3
#enum MUS_AGARI_OTHER_1
#enum MUS_AGARI_OTHER_2
#enum MUS_AGARI_OTHER_3
#enum MUS_RYUUKYOKU
#enum MUS_TITLE
#enum MUS_ENDING
#enum MUS_ENDING2
#enum MUS_ENDING3
#enum MUS_EFFECT
#enum MUS_FINAL
#enum MUS_SHIBARI
#define BGM_END		MUS_SHIBARI

/* 効果音の管理番号 */
#const SND_START	BGM_END+1
#enum SND_DAHAI1 = SND_START
#enum SND_DAHAI2
#enum SND_TSUMO
#enum SND_SAIKORO
#enum SND_BELL
#enum SND_COUNTDOWN
#enum SND_CUOHU
#enum SND_YAKULST1
#enum SND_YAKULST2
#enum SND_MEKURI
#enum SND_BUTTON
#enum SND_CLICK
#enum SND_PAGE
#enum SND_TYPE
#enum SND_PINGJU
#enum SND_FLASH
#enum SND_SIGNAL
#enum SND_CLOCK
#define SND_END		SND_CLOCK

#const VOX_START	SND_END+1
#enum VOX_CHI = VOX_START
#enum VOX_PON
#enum VOX_KAN
#enum VOX_RICHI
#enum VOX_TSUMO
#enum VOX_RON
#enum VOX_KYUUSHU
#enum VOX_FLOWER
#enum VOX_SIKANG
#enum VOX_SIFENG
#enum VOX_SANJIAHU
#enum VOX_SIJIARICHI
#enum VOX_RON_FURIKOMI
#define VOX_END		VOX_RON_FURIKOMI

/* 音声データの管理番号範囲 */

/* ルール管理番号 */
#define RULES_IN_PAGE		40
#define RULE_IN_LINE		80

#include "rulenum.as"

#define RULE_PAGES			int((NUM_OF_RULES+RULES_IN_PAGE-1)/RULES_IN_PAGE)
#define RULE_STRING_LINES	int((RULES_IN_PAGE*RULE_PAGES+RULE_IN_LINE-1)/RULE_IN_LINE)

/* 待ちのパターン識別コード */
#enum MACHI_INVALID = 0
#enum MACHI_RYANMEN
#enum MACHI_KANCHAN
#enum MACHI_PENCHAN
#enum MACHI_SHANPON
#enum MACHI_TANKI

/* プレイヤーの風位 */
#enum PLAYER_EAST = 0
#enum PLAYER_SOUTH
#enum PLAYER_WEST
#enum PLAYER_NORTH

/* プレイヤーの相対位置 */
#enum RELATIVE_SELF = 0
#enum RELATIVE_SHIMOCHA
#enum RELATIVE_TOIMEN
#enum RELATIVE_KAMICHA

/* 場の状態API用 */
#enum HAND_TILECODE = 0
#enum HAND_REDTILE
#enum HAND_PAGES
#enum DISCARD_TILECODE = 0
#enum DISCARD_REDTILE
#enum DISCARD_THROUGH
#enum DISCARD_PAGES
#enum MELD_TILECODE = 0
#enum MELD_REDTILE
#enum MELD_PAGES
#enum RICHI_FLAG = 0
#enum RICHI_OPENFLAG
#enum RICHI_PAGES
#enum KANG_FLAG = 0
#enum KANG_CHAINFLAG
#enum KANG_TOPFLAG
#enum KANG_CHANKAN
#enum KANG_PAGES
#enum PAO_PLAYER_PAO = 0
#enum PAO_PLAYER_AGARI
#enum PAO_PLAYER_PAGES
#enum PAO_YAKU_DAISANGEN = 0
#enum PAO_YAKU_DAISIXI
#enum PAO_YAKU_SIKANG
#enum PAO_YAKU_MINKAN
#enum PAO_YAKU_PAGES
#enum WALL_TILECODE = 0
#enum WALL_REDTILE
#enum WALL_PAGES
#enum PREVMELD_TILECODE = 0
#enum PREVMELD_STEPPED
#enum PREVMELD_PAGES
#enum DORA_OMOTE = 0
#enum DORA_URA
#enum DORA_PAGES
#enum CURRENTDISCARD_TILECODE = 0
#enum CURRENTDISCARD_REDTILE
#enum CURRENTDISCARD_PAGES
#enum DECLARATIONFLAG_RON = 0
#enum DECLARATIONFLAG_PON
#enum DECLARATIONFLAG_CHI
#enum DECLARATIONFLAG_MINKAN
#enum DECLARATIONFLAG_PAGES
#enum CURRENTPLAYER_ACTIVE = 0
#enum CURRENTPLAYER_PASSIVE
#enum CURRENTPLAYER_AGARI
#enum CURRENTPLAYER_FURIKOMI
#enum CURRENTPLAYER_PAGES

/* 役解析データ用 */
#enum YAKUINF_FU = 0
#enum YAKUINF_HAN_BASE
#enum YAKUINF_HAN_BONUS
#enum YAKUINF_DORA
#enum YAKUINF_URADORA
#enum YAKUINF_AKADORA
#enum YAKUINF_AODORA
#enum YAKUINF_ALICEDORA
#enum YAKUINF_FLOWER
#enum YAKUINF_POINTS
#enum YAKUINF_YAKULIST = (YAKUINF_POINTS+NUM_OF_DIGIT_GROUPS)
#enum YAKUINF_YAKUMANLIST
#enum YAKUINF_YAKUVALLIST
#enum YAKUINF_YAKUMANVALLIST

/* 卓環境データ用 */
#enum GAMEMODE_UNAVAILABLE = (-1)
#enum GAMEMODE_STANDALONE
#enum GAMEMODE_SERVER
#enum GAMEMODE_CLIENT

/* 役の価値の内部的な情報 */
#define YAKUVAL_MINUS_LIMIT	100
#define YAKUVAL_HALFMANGAN	12500
#const YAKUVAL_MANGAN		YAKUVAL_HALFMANGAN*2
#const YAKUVAL_HANEMAN		YAKUVAL_HALFMANGAN*3
#const YAKUVAL_BAIMAN		YAKUVAL_HALFMANGAN*4
#const YAKUVAL_SANBAIMAN	YAKUVAL_HALFMANGAN*6
#const YAKUVAL_YAKUMAN		YAKUVAL_HALFMANGAN*8

/* 牌の種類 */
#define TILE_CODE_MAXIMUM			200
#define TILE_SUIT_STEP				10
#define TILE_NUMERAL_COLORS			3
#const TILE_SUIT_CHARACTERS			TILE_SUIT_STEP*0
#const TILE_CHARACTER_ONE			TILE_SUIT_CHARACTERS+1
#const TILE_CHARACTER_TWO			TILE_SUIT_CHARACTERS+2
#const TILE_CHARACTER_THREE			TILE_SUIT_CHARACTERS+3
#const TILE_CHARACTER_FOUR			TILE_SUIT_CHARACTERS+4
#const TILE_CHARACTER_FIVE			TILE_SUIT_CHARACTERS+5
#const TILE_CHARACTER_SIX			TILE_SUIT_CHARACTERS+6
#const TILE_CHARACTER_SEVEN			TILE_SUIT_CHARACTERS+7
#const TILE_CHARACTER_EIGHT			TILE_SUIT_CHARACTERS+8
#const TILE_CHARACTER_NINE			TILE_SUIT_CHARACTERS+9
#const TILE_SUIT_CIRCLES			TILE_SUIT_STEP*1
#const TILE_CIRCLE_ONE				TILE_SUIT_CIRCLES+1
#const TILE_CIRCLE_TWO				TILE_SUIT_CIRCLES+2
#const TILE_CIRCLE_THREE			TILE_SUIT_CIRCLES+3
#const TILE_CIRCLE_FOUR				TILE_SUIT_CIRCLES+4
#const TILE_CIRCLE_FIVE				TILE_SUIT_CIRCLES+5
#const TILE_CIRCLE_SIX				TILE_SUIT_CIRCLES+6
#const TILE_CIRCLE_SEVEN			TILE_SUIT_CIRCLES+7
#const TILE_CIRCLE_EIGHT			TILE_SUIT_CIRCLES+8
#const TILE_CIRCLE_NINE				TILE_SUIT_CIRCLES+9
#const TILE_SUIT_BAMBOOS			TILE_SUIT_STEP*2
#const TILE_BAMBOO_ONE				TILE_SUIT_BAMBOOS+1
#const TILE_BAMBOO_TWO				TILE_SUIT_BAMBOOS+2
#const TILE_BAMBOO_THREE			TILE_SUIT_BAMBOOS+3
#const TILE_BAMBOO_FOUR				TILE_SUIT_BAMBOOS+4
#const TILE_BAMBOO_FIVE				TILE_SUIT_BAMBOOS+5
#const TILE_BAMBOO_SIX				TILE_SUIT_BAMBOOS+6
#const TILE_BAMBOO_SEVEN			TILE_SUIT_BAMBOOS+7
#const TILE_BAMBOO_EIGHT			TILE_SUIT_BAMBOOS+8
#const TILE_BAMBOO_NINE				TILE_SUIT_BAMBOOS+9
#const TILE_SUIT_HONORS				TILE_SUIT_STEP*TILE_NUMERAL_COLORS
#const TILE_EAST_WIND				TILE_SUIT_HONORS+1
#const TILE_SOUTH_WIND				TILE_SUIT_HONORS+2
#const TILE_WEST_WIND				TILE_SUIT_HONORS+3
#const TILE_NORTH_WIND				TILE_SUIT_HONORS+4
#const TILE_WHITE_DRAGON			TILE_SUIT_HONORS+5
#const TILE_GREEN_DRAGON			TILE_SUIT_HONORS+6
#const TILE_RED_DRAGON				TILE_SUIT_HONORS+7
#const TILE_DORA_FLOWER				TILE_SUIT_HONORS+8
#const TILE_BACK_SIDE				TILE_SUIT_HONORS+9
#const TILE_SUIT_FLOWERS			TILE_SUIT_STEP*12
#const TILE_SPRING					TILE_SUIT_FLOWERS+1
#const TILE_SUMMER					TILE_SUIT_FLOWERS+2
#const TILE_AUTUMN					TILE_SUIT_FLOWERS+3
#const TILE_WINTER					TILE_SUIT_FLOWERS+4
#const TILE_PLUM					TILE_SUIT_FLOWERS+6
#const TILE_ORCHID					TILE_SUIT_FLOWERS+7
#const TILE_CHRYSANTHEMUM			TILE_SUIT_FLOWERS+8
#const TILE_BAMBOO					TILE_SUIT_FLOWERS+9
#define TILE_MIN					0
#define TILE_WIND_MIN				TILE_EAST_WIND
#define TILE_WIND_MAX				TILE_NORTH_WIND
#define TILE_DRAGON_MIN				TILE_WHITE_DRAGON
#define TILE_DRAGON_MAX				TILE_RED_DRAGON
#define TILE_FLOWER_MIN				TILE_SPRING
#define TILE_SEASON_MIN				TILE_SPRING
#define TILE_PLANT_MIN				TILE_PLUM
#define TILE_NUMERAL_MAX			TILE_SUIT_HONORS
#define TILE_NONFLOWER_STRICT_MAX	TILE_DRAGON_MAX
#const TILE_NONFLOWER_MAX			TILE_SUIT_STEP*(TILE_NUMERAL_COLORS+1)

/* 面子の種類 */
#define MELD_TYPE_STEP 1000
#enum MELD_SEQUENCE_CONCEALED = 0
#enum MELD_SEQUENCE_EXPOSED_LOWER
#enum MELD_SEQUENCE_EXPOSED_MIDDLE
#enum MELD_SEQUENCE_EXPOSED_UPPER
#enum MELD_TRIPLET_CONCEALED
#enum MELD_TRIPLET_EXPOSED_LEFT
#enum MELD_TRIPLET_EXPOSED_CENTER
#enum MELD_TRIPLET_EXPOSED_RIGHT
#enum MELD_QUAD_CONCEALED
#enum MELD_QUAD_EXPOSED_LEFT
#enum MELD_QUAD_EXPOSED_CENTER
#enum MELD_QUAD_EXPOSED_RIGHT
#enum MELD_QUAD_ADDED_LEFT
#enum MELD_QUAD_ADDED_CENTER
#enum MELD_QUAD_ADDED_RIGHT
#define MELD_SEQUENCE_EXPOSED_MIN	MELD_SEQUENCE_EXPOSED_LOWER
#define MELD_SEQUENCE_EXPOSED_MAX	MELD_SEQUENCE_EXPOSED_UPPER
#define MELD_TRIPLET_EXPOSED_MIN	MELD_TRIPLET_EXPOSED_LEFT
#define MELD_TRIPLET_EXPOSED_MAX	MELD_TRIPLET_EXPOSED_RIGHT
#define MELD_QUAD_EXPOSED_MIN		MELD_QUAD_EXPOSED_LEFT
#define MELD_QUAD_EXPOSED_MAX		MELD_QUAD_ADDED_RIGHT
#define MELD_QUAD_ADDED_MIN			MELD_QUAD_ADDED_LEFT
#define MELD_TRIPLET				MELD_TRIPLET_CONCEALED
#define MELD_QUAD					MELD_QUAD_CONCEALED

/* 捨て牌データ用 */
#define SUTEHAI_TYPE_STEP	200
#const SUTEHAI_NORMAL		SUTEHAI_TYPE_STEP*0
#const SUTEHAI_TAKEN		SUTEHAI_TYPE_STEP*1
#const SUTEHAI_RIICHI		SUTEHAI_TYPE_STEP*2
#const SUTEHAI_RIICHI_TAKEN	SUTEHAI_TYPE_STEP*3
#const SUTEHAI_MAX			SUTEHAI_TYPE_STEP*4

/* 打牌番号用 */
#define DAHAI_TYPE_STEP			20
#const DAHAI_TYPE_NORMAL		DAHAI_TYPE_STEP*0
#const DAHAI_TYPE_KAN			DAHAI_TYPE_STEP*1
#const DAHAI_TYPE_KAKAN			DAHAI_TYPE_STEP*2
#const DAHAI_TYPE_RIICHI		DAHAI_TYPE_STEP*3
#const DAHAI_TYPE_FLOWER		DAHAI_TYPE_STEP*4
#const DAHAI_TYPE_OPENRIICHI	DAHAI_TYPE_STEP*5
#define DAHAI_TYPE_AGARI		(-1)
#define DAHAI_TYPE_KYUUSHU		(-2)
#define DAHAI_TYPE_DISCONNECT	(-3)

/* 副露処理の種類 */
#enum FUURO_ANKAN = 0
#enum FUURO_KAKAN
#enum FUURO_DAIMINKAN
#enum FUURO_NORTH
#enum FUURO_FLOWER
#enum FUURO_PON
#enum FUURO_CHII

/* 花牌フラグ用 */
#define FLOWER_SPRING			0x00000001
#define FLOWER_SUMMER			0x00000002
#define FLOWER_AUTUMN			0x00000004
#define FLOWER_WINTER			0x00000008
#define FLOWER_PLUM				0x00000010
#define FLOWER_ORCHID			0x00000020
#define FLOWER_CHRYSANTHEMUM	0x00000040
#define FLOWER_BAMBOO			0x00000080
#define FLOWER_ALL_SEASONS		(FLOWER_SPRING|FLOWER_SUMMER|FLOWER_AUTUMN|FLOWER_WINTER)
#define FLOWER_ALL_FLOWERS		(FLOWER_PLUM|FLOWER_ORCHID|FLOWER_CHRYSANTHEMUM|FLOWER_BAMBOO)
#define FLOWER_ALL				(FLOWER_ALL_SEASONS|FLOWER_ALL_FLOWERS)

/* 立直フラグ用 */
#enum RIICHI_NO = 0
#enum RIICHI_YES
#enum RIICHI_IPPATSU
#enum RIICHI_DOUBLE
#enum RIICHI_DOUBLE_IPPATSU

/* 向聴計算用のオプション */
#enum SHANTEN_ALL = 0
#enum SHANTEN_REGULAR
#enum SHANTEN_PAIRS
#enum SHANTEN_ORPHANS
#enum SHANTEN_STELLAR
#enum SHANTEN_CIVILWAR
#enum SHANTEN_SYZYGY
#enum SHANTEN_QUANBUKAO
#enum SHANTEN_PAGES

/* 和了フラグ */
#define AGARI_KUIKAE	999

/* 局終了コード */
#enum ENDKYOKU_RYUUKYOKU = 0
#enum ENDKYOKU_AGARI
#enum ENDKYOKU_CHONBO
#enum ENDKYOKU_KYUUSHUKYUUHAI
#enum ENDKYOKU_SUUKAIKAN
#enum ENDKYOKU_TRIPLERON
#enum ENDKYOKU_SUUFONRENDA
#enum ENDKYOKU_SUUCHARIICHI
#enum ENDKYOKU_NAGASHIMANGAN
#enum ENDKYOKU_DISCONNECT
#enum ENDKYOKU_UUKAIKAN
