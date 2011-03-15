/*=============================
 * HSP麻雀クライアントMiHaJong
 *        [定数の定義]
 *=============================
 */

/* バージョン情報 */
#define VERSION_MAJ 1
#define VERSION_MED 4
#define VERSION_MIN 2
#define VERSION_MIC "dev"

/* フォントの指定 */
/* 必ず等幅日本語フォントを指定すること */
#define fontname "ＭＳ 明朝"

/* 基本的なゲーム用の定数 */
#ifdef SANMA
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
#enum SCR_TITLE_BACKGROUND
#enum SCR_TITLE_LOGO
#enum SCR_MAIN_BACKGROUND
#enum SCR_SPLASH_WINDOW
#enum SCR_SPLASH_BUF

/* 通信ポート番号 */
#ifdef SANMA4
	#define PORT_GAME	50040
#else
	#ifdef SANMA
		#define PORT_GAME	50010
	#else
		#define PORT_GAME	50000
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
#const TILE_DICE_SCREEN_HEIGHT	TILE_DICE_HEIGHT*2+TILE_RIICHISTICK_WIDTH+TILE_CHICHAMARK_HEIGHT*2

#define TILE_SHADOW			64
#define TILE_DICE_SHADOW	144

/* 音声データの管理番号範囲 */
#define SND_START	40
#define SND_END		57
#define VOX_START	64
#define VOX_END		76
#define BGM_START	0
#define BGM_END		35

/* ＢＧＭの番号 */
#define MUS_RICHI1				16
#define MUS_RICHI2				17
#define MUS_RICHI3				18
#define MUS_OPENRICHI			19
#define MUS_AGARI_1HAN			20
#define MUS_AGARI_2HAN			21
#define MUS_AGARI_3HAN			22
#define MUS_AGARI_MANGAN		23
#define MUS_AGARI_HANEMAN		24
#define MUS_AGARI_BAIMAN		25
#define MUS_AGARI_SANBAIMAN		26
#define MUS_AGARI_KAZOE_YAKUMAN	27
#define MUS_AGARI_YAKUMAN		28
#define MUS_RYUUKYOKU			29
#define MUS_TITLE				30
#define MUS_ENDING				31
#define MUS_ENDING2				32
#define MUS_EFFECT				33
#define MUS_FINAL				34
#define MUS_SHIBARI				35

/* 効果音の管理番号 */
#define SND_DAHAI1		40
#define SND_DAHAI2		41
#define SND_TSUMO		42
#define SND_SAIKORO		43
#define SND_BELL		44
#define SND_COUNTDOWN	45
#define SND_CUOHU		46
#define SND_YAKULST1	47
#define SND_YAKULST2	48
#define SND_MEKURI		49
#define SND_BUTTON		50
#define SND_CLICK		51
#define SND_PAGE		52
#define SND_TYPE		53
#define SND_PINGJU		54
#define SND_FLASH		55
#define SND_SIGNAL		56
#define SND_CLOCK		57

#define VOX_CHI				64
#define VOX_PON				65
#define VOX_KAN				66
#define VOX_RICHI			67
#define VOX_TSUMO			68
#define VOX_RON				69
#define VOX_KYUUSHU			70
#define VOX_FLOWER			71
#define VOX_SIKANG			72
#define VOX_SIFENG			73
#define VOX_SANJIAHU		74
#define VOX_SIJIARICHI		75
#define VOX_RON_FURIKOMI	76

/* ルール管理番号 */
#enum RULE_GAME_LENGTH = 0
#enum RULE_CHIP
#enum RULE_YAKITORI
#enum RULE_PENALTY_NEGATIVE
#enum RULE_STARTING_POINT
#enum RULE_POINT_BASIS
#enum RULE_KUIKAE
#enum RULE_LIMITHAND_BONUS
#enum RULE_RYANSHIBA
#enum RULE_ROUND_CONTINUATION
#enum RULE_MULTIPLE_MAHJONG
#enum RULE_SIMULTANEOUS_MAHJONG
#enum RULE_TRIPLE_MAHJONG
#enum RULE_NINE_TERMINALS
#enum RULE_FOUR_KONG_RYUUKYOKU
#enum RULE_FIFTH_KONG
#enum RULE_FOUR_WIND_RYUUKYOKU
#enum RULE_FOUR_RIICHI_RYUUKYOKU
#enum RULE_AGARIYAME
#enum RULE_KUITAN
#enum RULE_URADORA
#enum RULE_KANDORA
#enum RULE_RED_FIVE
#enum RULE_RED_THREE
#enum RULE_RED_SEVEN
#enum RULE_WAREME
#enum RULE_DOUKASEN
#enum RULE_DORA_TWICE
#enum RULE_LIMITLESS
#enum RULE_NAGATACHO
#enum RULE_FLOWER_TILES
#enum RULE_ALICE
#enum RULE_DORA_INDICATOR
#enum RULE_TSUMO_PINFU
#enum RULE_DOUBLE_YAKUMAN
#enum RULE_SEVEN_HONOR_PAIRS
#enum RULE_DRAGONLESS_ALL_GREEN
#enum RULE_RIICHI_IPPATSU
#enum RULE_SEVEN_PAIRS
#enum RULE_RIICHI_SHIBARI
#enum RULE_EXPOSED_PINFU
#enum RULE_ROUND_TO_MANGAN
#enum RULE_RED_ONE
#enum RULE_RED_NINE
#enum RULE_RED_TWO
#enum RULE_RED_FOUR
#enum RULE_RED_SIX
#enum RULE_RED_EIGHT
#enum RULE_OPEN_RIICHI
#enum RULE_DAISHARIN
#enum RULE_SANRENKOH
#enum RULE_SUURENKOH
#enum RULE_ISSHOKU_SANJUN
#enum RULE_ISSHOKU_SUUJUN
#enum RULE_RENHOH
#enum RULE_SHIISAN_PUUTAA
#enum RULE_PAARENCHAN
#enum RULE_NAGASHI_MANGAN
#enum RULE_SANSHOKU_DOUKOH
#enum RULE_SANKANTSU
#enum RULE_RYANPEIKOU
#enum RULE_HONROUTOU
#enum RULE_CHINIISOH
#enum RULE_SUUKANTSU
#enum RULE_TENHOH
#enum RULE_DAICHIKURIN
#enum RULE_DAISUURIN
#enum RULE_BENIKUJAKU
#enum RULE_KOUITTEN
#enum RULE_RYUUIISOHRIN
#enum RULE_HEIIISOH
#enum RULE_NO_RED
#enum RULE_KAGA_MILLION
#enum RULE_SHIISAN_UUSHII
#enum RULE_STELLAR_UUSHII
#enum RULE_BREAKING_PAARENCHAN
#enum RULE_THREE_OTAKAZE
#enum RULE_THREE_WINDS
#enum RULE_FOUR_HONORS
#enum RULE_FUUKA_SETSUGETSU
#enum RULE_KACHOU_FUUGETSU
#enum RULE_TOHOKU_SHINKANSEN
#enum RULE_TOHOKU_EXPWY
#enum RULE_CIVIL_WAR
#enum RULE_GOLDEN_GATE_BRIDGE
#enum RULE_AO_NO_DOMON
#enum RULE_UUMENCHII
#enum RULE_KAMBURI
#enum RULE_TOUKANHOH
#enum RULE_RENKAN_KAIHOH
#enum RULE_UUPIN_KAIHOH
#enum RULE_RYANZOH_CHANKAN
#enum RULE_IIPIN_MOYUE
#enum RULE_CHUUPIN_RAOYUI
#enum RULE_TSUBAME_GAESHI
#enum RULE_DRAGON_PAIRS
#enum RULE_WIND_PAIRS
#enum RULE_CHINPEIKOU
#enum RULE_SHANRON_CHONCHUU
#enum RULE_KYANTONHOH
#enum RULE_RYANDOUKOH
#enum RULE_UUSHINTONKAN
#enum RULE_ITTSUU_CHANTA
#enum RULE_HUALONG
#enum RULE_TANRON
#enum RULE_SANSHOKU_RENKOH
#enum RULE_TINSANKOH
#enum RULE_CHAOPAIKOH
#enum RULE_CHINPAIKOH
#enum RULE_SHIIARU_RAOTAI
#enum RULE_KINKEI_DOKURITSU
#enum RULE_KANKOU_NO_YUKI
#enum RULE_SUUCHAOPAIKOH
#enum RULE_KAIMENKAZE
#enum RULE_URAKAZE
#enum RULE_RYANANKAN
#enum RULE_SANANKAN
#enum RULE_EXPOSED_RYANPEIKOU
#enum RULE_TOIPUUTAO
#enum RULE_PINZU_MILLION
#enum RULE_CHUEIIMEN
#enum RULE_NISHINAKAJIMA
#enum RULE_SUMARO
#enum RULE_KINKEI_HOUGYOU
#enum RULE_GINKEI_HOUSHUN
#enum RULE_KOUKEI_HOUGYOU
#enum RULE_UIKYOU_TOITOI
#enum RULE_BAXIAN_CHENGFENG
#enum RULE_UIKYOU_SHUNTSU
#enum RULE_BAXIAN_XIFENG
#enum RULE_BAXIAN_XISIFENG
#enum RULE_BAXIAN_XIJINGUI
#enum RULE_BAXIAN_DOU_BEIDOU
#enum RULE_BAXIAN_JUSHOU
#enum RULE_CHUUREN_HWATON
#enum RULE_EXPOSED_CHUUREN
#enum RULE_OKASANJUN
#enum RULE_OKASUUJUN
#enum RULE_SANSHOKU_OKASANJUN
#enum RULE_YAMASANJUN
#enum RULE_SANSHOKU_YAMASANJUN
#enum RULE_ANKAN_CONCEAL
#enum RULE_ANKAN_CHANKAN
#enum RULE_NISHOKU_OKASANJUN
#enum RULE_NISHOKU_OKASUUJUN
#enum RULE_SANSHOKU_OKASUUJUN
#enum RULE_NISHOKU_YAMASANJUN
#enum RULE_NISHOKU_YAMASUUJUN
#enum RULE_GOLDEN_LADDER
#enum RULE_SANSHOKU_YAMASUUJUN
#enum RULE_HAKU_POTCHI
#enum RULE_GAISENMON
#enum RULE_CHOUJOU
#enum RULE_QINGLONG_ZAITIAN
#enum RULE_ODD_TOITOI
#enum RULE_EVEN_TOITOI
#enum RULE_ODD_PAIRS
#enum RULE_EVEN_PAIRS
#enum RULE_LONGXIZHU
#enum RULE_CHUUGEN_CHIKUROKU
#enum RULE_NISHOKU_SANRENKOH
#enum RULE_NISHOKU_SUURENKOH
#enum RULE_NISHOKU_CHAOPAIKOH
#enum RULE_NISHOKU_CHINPAIKOH
#enum RULE_NISHOKU_TINSANKOH
#enum RULE_NISHOKU_SUUCHAOPAIKOH
#enum RULE_SANSHOKU_CHAOPAIKOH
#enum RULE_SANSHOKU_CHINPAIKOH
#enum RULE_SANSHOKU_TINSANKOH
#enum RULE_SANSHOKU_SUURENKOH
#enum RULE_SANSHOKU_SUUCHAOPAIKOH
#enum RULE_GRAND_CANYON
#enum RULE_NITEI_RAOCHUN
#enum RULE_SKY_LADDER
#enum RULE_TURTLE_EGG
#enum RULE_SHANRON_SHANKUI
#enum RULE_SHANRON_CHONCHU_LSF
#enum RULE_SANSHOKU_SOURYUU
#enum RULE_ISSHOKU_SOURYUU
#enum RULE_SHANRON_SHIIFON
#enum RULE_SHANRON_PAOCHUU
#enum RULE_SHANRON_SHIIKUI
#enum RULE_KYOKUJITSU_TOUSHOU
#enum RULE_RIIRAO_SHIISHAN
#enum RULE_OTAKAZE_RON
#enum RULE_JINLONG_DOU_BEIDOU
#enum RULE_YOUBOU_HOKUTO
#enum RULE_STARLIGHT
#enum RULE_BIG_DIPPER
#enum RULE_SEISOU_TAIGETSU
#enum RULE_UUTAARAN
#enum RULE_NAMU_HACHIMAN
#enum RULE_SEIKO_JIKKEI
#enum RULE_KOUHAKU_CHIITOI
#enum RULE_VOLCANIC_ERRUPTION
#enum RULE_TANFON_CHOUYOU
#enum RULE_HAOUBEN
#enum RULE_RYUUKANCHAN
#enum RULE_OHKAGAMI
#enum RULE_KITA_NO_DAICHI
#enum RULE_SHUANGFENG_ZHAYUN
#enum RULE_NANBING_WANZHONG
#enum RULE_LEIFENG_XIZHAO
#enum RULE_LIULANG_WENYING
#enum RULE_DUANQIAO_CANXUE
#enum RULE_SUDI_CHUNXIAO
#enum RULE_HUAGANG_GUANYU
#enum RULE_SANTAN_YINYUE
#enum RULE_QUYUAN_FENGHE
#enum RULE_PINGHU_QIUYUE
#enum RULE_SYZYGY
#enum RULE_GRAND_CROSS
#enum RULE_XIQUE_NAOMEI
#enum RULE_QUEQIAOHUI
#enum RULE_HUAIISOH
#enum RULE_YIGAN_FENGYUE
#enum RULE_PI
#enum RULE_SQUARE_ROOT_TWO
#enum RULE_NATURAL_LOGARITHM
#enum RULE_IMAGINARY_NUMBER
#enum RULE_SQUARE_ROOT_TEN
#enum RULE_CHII_SANKAN
#enum RULE_CHII_SANPEN
#enum RULE_CHII_SHAOSHUN
#enum RULE_CHII_TAASHUN
#enum RULE_CHII_SUUKAN
#enum RULE_CHII_SUUPEN
#enum RULE_CHII_SHAOSUUSHUN
#enum RULE_CHII_TAASUUSHUN
#enum RULE_YUKIGESHOU
#enum RULE_HOUKANSOU
#enum RULE_SEKIGAN_SEIRYUU
#enum RULE_AZURE_DRAGON
#enum RULE_VERMILION_BIRD
#enum RULE_WHITE_TIGER
#enum RULE_BLACK_TORTOISE
#enum RULE_SANBEI_MEIJIU
#enum RULE_SHENGDONG_JIXI
#enum RULE_DONGFENG_YADAO
#enum RULE_ZAONAN_CHUANGBEI
#enum RULE_GEKKANJUN
#enum RULE_TAIKOU_TURTLE
#enum RULE_HAITEI_RAOTSEN
#enum RULE_HAITEI_RAOHWA
#enum RULE_DORAHOH
#enum RULE_SIMPLIFIED_SCORING
#enum RULE_SILVER_LADDER
#enum RULE_SHANRON_TOUJA
#enum RULE_SHINRIISHOU
#enum RULE_KINKI_KIKAN
#enum RULE_HOKUTO_SHOUKAN
#enum RULE_DAIJA_KANKETSU
#enum RULE_DONGFENGCHUI
#enum RULE_NANFENGCHUI
#enum RULE_XIFENGCHUI
#enum RULE_BEIFENGCHUI
#enum RULE_FOUR_INTO_ONE
#enum RULE_DOUBLE_FOUR_INTO_ONE
#enum RULE_TIGER_FOUR_INTO_ONE
#enum RULE_DRAGON_FOUR_INTO_ONE
#enum RULE_FOUR_INTO_THREE
#enum RULE_FOUR_INTO_THREE_ONE
#enum RULE_FOUR_INTO_FOUR
#enum RULE_DOUBLE_FOUR_INTO_FOUR
#enum RULE_GREAT_FOUR_INTO_FOUR
#enum RULE_ALL_ONE
#enum RULE_ALL_TWO
#enum RULE_ALL_THREE
#enum RULE_ALL_FOUR
#enum RULE_ALL_FIVE
#enum RULE_ALL_SIX
#enum RULE_ALL_SEVEN
#enum RULE_ALL_EIGHT
#enum RULE_ALL_NINE
#enum RULE_OWN_FLOWER
#enum RULE_FOUR_SEASONS
#enum RULE_FOUR_FLOWERS
#enum RULE_EIGHT_FLOWERS
#enum RULE_DOUBLE_YAKU_WIND_PAIR
#enum RULE_TSUMIBOH_RATE
#enum RULE_MINKAN_PAO
#enum RULE_NORMAL_PAO
#enum RULE_REDTILE_CHIP
#enum RULE_RED_WEST
#enum RULE_RED_NORTH
#enum RULE_BLUE_TILES
#enum RULE_BLUE_ONE
#enum RULE_BLUE_FIVE
#enum RULE_BLUE_NINE
#enum RULE_BLUE_LVFA
#enum RULE_BLUE_CHIP
#enum RULE_BUTTOBI_BORDER
#enum RULE_RIICHI_REQUISITE
#enum RULE_SANBAIMAN_BORDER
#enum RULE_KAZOE_BORDER
#enum RULE_HIEN
#enum RULE_KISHU550K
#enum RULE_JOETSU_ASAHI
#enum RULE_JOETSU_TOKI
#enum RULE_HAKUITTEN
#enum RULE_XIAOSANFENG
#enum RULE_MITO350K

#const NUM_OF_RULES			RULE_MITO350K+1
#define RULES_IN_PAGE		40
#define RULE_PAGES			int((NUM_OF_RULES+RULES_IN_PAGE-1)/RULES_IN_PAGE)
#define RULE_IN_LINE		80
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

/* 牌の種類 */
#define TILE_CODE_MAXIMUM			200
#define TILE_SUIT_STEP				10
#define TILE_NUMERAL_COLORS			3
#const TILE_SUIT_CHARACTERS			TILE_SUIT_STEP*0
#const TILE_SUIT_CIRCLES			TILE_SUIT_STEP*1
#const TILE_SUIT_BAMBOOS			TILE_SUIT_STEP*2
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
