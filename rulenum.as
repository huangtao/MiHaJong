/*=============================
 * HSP麻雀クライアントMiHaJong
 *      [ルール管理番号]
 *=============================
 */

/* 初期設定 */
#define START_OF_SECTION 0*RULES_IN_PAGE

/* 基本のルール設定 */
#enum RULE_GAME_LENGTH = START_OF_SECTION
#enum RULE_SUDDEN_DEATH_TYPE
#enum RULE_SUDDEN_DEATH_LENGTH
#enum RULE_STARTING_POINT
#enum RULE_POINT_BASIS
#enum RULE_BUTTOBI_BORDER
#enum RULE_PENALTY_NEGATIVE
#enum RULE_RIICHI_REQUISITE
#enum RULE_YAKITORI
#enum RULE_KUIKAE
#enum RULE_RYANSHIBA
#enum RULE_ROUND_CONTINUATION
#enum RULE_AGARIYAME
#enum RULE_MULTIPLE_MAHJONG
#enum RULE_SIMULTANEOUS_MAHJONG
#enum RULE_TRIPLE_MAHJONG
#enum RULE_NINE_TERMINALS
#enum RULE_FOUR_KONG_RYUUKYOKU
#enum RULE_FIFTH_KONG
#enum RULE_FOUR_WIND_RYUUKYOKU
#enum RULE_FOUR_RIICHI_RYUUKYOKU
#enum RULE_DOUBLE_YAKUMAN
#enum RULE_ROUND_TO_MANGAN
#enum RULE_SIMPLIFIED_SCORING
#enum RULE_DOUBLE_YAKU_WIND_PAIR
#enum RULE_TSUMIBOH_RATE
#enum RULE_MINKAN_PAO
#enum RULE_NORMAL_PAO
#enum RULE_SANBAIMAN_BORDER
#enum RULE_KAZOE_BORDER
#enum RULE_RIICHI_SHIBARI
#enum RULE_ANKAN_CONCEAL
#enum RULE_ANKAN_CHANKAN
#enum RULE_KAKAN_FURITEN
#enum RULE_TSUMO_PAYMENT

/* デリミタ */
#enum END_OF_SECTION
#undef START_OF_SECTION
#enum START_OF_SECTION = ((END_OF_SECTION-1)/RULES_IN_PAGE)+1
#undef END_OF_SECTION

/* ドラとインフレルール設定 */
#enum RULE_DORA_INDICATOR = START_OF_SECTION*RULES_IN_PAGE
#enum RULE_URADORA
#enum RULE_KANDORA
#enum RULE_RED_ONE
#enum RULE_RED_TWO
#enum RULE_RED_THREE
#enum RULE_RED_FOUR
#enum RULE_RED_FIVE
#enum RULE_RED_SIX
#enum RULE_RED_SEVEN
#enum RULE_RED_EIGHT
#enum RULE_RED_NINE
#enum RULE_RED_WEST
#enum RULE_RED_NORTH
#enum RULE_HAKU_POTCHI
#enum RULE_BLUE_TILES
#enum RULE_BLUE_ONE
#enum RULE_BLUE_FIVE
#enum RULE_BLUE_NINE
#enum RULE_BLUE_LVFA
#enum RULE_ALICE
#enum RULE_FLOWER_TILES
#enum RULE_CHIP
#enum RULE_LIMITHAND_BONUS
#enum RULE_REDTILE_CHIP
#enum RULE_BLUE_CHIP
#enum RULE_WAREME
#enum RULE_DOUKASEN
#enum RULE_DORA_TWICE
#enum RULE_NAGATACHO
#enum RULE_LIMITLESS

/* デリミタ */
#enum END_OF_SECTION
#undef START_OF_SECTION
#enum START_OF_SECTION = ((END_OF_SECTION-1)/RULES_IN_PAGE)+1
#undef END_OF_SECTION

/* 基本の役設定 */
#enum RULE_KUITAN = START_OF_SECTION*RULES_IN_PAGE
#enum RULE_TSUMO_PINFU
#enum RULE_SEVEN_HONOR_PAIRS
#enum RULE_DRAGONLESS_ALL_GREEN
#enum RULE_RIICHI_IPPATSU
#enum RULE_SEVEN_PAIRS
#enum RULE_SANSHOKU_DOUKOH
#enum RULE_SANKANTSU
#enum RULE_RYANPEIKOU
#enum RULE_HONROUTOU
#enum RULE_CHINIISOH
#enum RULE_SUUKANTSU
#enum RULE_TENHOH
#enum RULE_EXPOSED_PINFU
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

/* デリミタ */
#enum END_OF_SECTION
#undef START_OF_SECTION
#enum START_OF_SECTION = ((END_OF_SECTION-1)/RULES_IN_PAGE)+1
#undef END_OF_SECTION

/* 順子役の設定 */
#enum RULE_CHINPEIKOU = START_OF_SECTION*RULES_IN_PAGE
#enum RULE_EXPOSED_RYANPEIKOU
#enum RULE_OHKAGAMI
#enum RULE_QINGHAIHU
#enum RULE_KYANTONHOH
#enum RULE_OKASANJUN
#enum RULE_OKASUUJUN
#enum RULE_YAMASANJUN
#enum RULE_GOLDEN_GATE_BRIDGE
#enum RULE_NISHOKU_OKASANJUN
#enum RULE_NISHOKU_OKASUUJUN
#enum RULE_NISHOKU_YAMASANJUN
#enum RULE_NISHOKU_YAMASUUJUN
#enum RULE_SANSHOKU_OKASANJUN
#enum RULE_SANSHOKU_OKASUUJUN
#enum RULE_SANSHOKU_YAMASANJUN
#enum RULE_SANSHOKU_YAMASUUJUN
#enum RULE_SHANRON_CHONCHUU
#enum RULE_SHANRON_CHONCHU_LSF
#enum RULE_SHANRON_SHANKUI
#enum RULE_SANSHOKU_SOURYUU
#enum RULE_ISSHOKU_SOURYUU
#enum RULE_SHANRON_SHIIFON
#enum RULE_SHANRON_PAOCHUU
#enum RULE_SHANRON_SHIIKUI
#enum RULE_SHANRON_TOUJA
#enum RULE_UUSHINTONKAN
#enum RULE_ITTSUU_CHANTA
#enum RULE_TOHOKU_SHINKANSEN
#enum RULE_JOETSU_ASAHI
#enum RULE_JOETSU_TOKI
#enum RULE_GAISENMON
#enum RULE_CHOUJOU
#enum RULE_QINGLONG_ZAITIAN
#enum RULE_LONGXIZHU
#enum RULE_JINLONG_DOU_BEIDOU
#enum RULE_ROUTE_246
#enum RULE_GAULUNGSING_LOKDEI
#enum RULE_GOLDRUSH
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
#enum RULE_HUALONG
#enum RULE_TANRON
#enum RULE_HUALONG_CHANTA
#enum RULE_CHII_SANKAN
#enum RULE_CHII_SANPEN
#enum RULE_CHII_SHAOSHUN
#enum RULE_CHII_TAASHUN
#enum RULE_CHII_SUUKAN
#enum RULE_CHII_SUUPEN
#enum RULE_CHII_SHAOSUUSHUN
#enum RULE_CHII_TAASUUSHUN

/* デリミタ */
#enum END_OF_SECTION
#undef START_OF_SECTION
#enum START_OF_SECTION = ((END_OF_SECTION-1)/RULES_IN_PAGE)+1
#undef END_OF_SECTION

/* 刻子役の設定 */
#enum RULE_KAIMENKAZE = START_OF_SECTION*RULES_IN_PAGE
#enum RULE_URAKAZE
#enum RULE_NIINUMA_KENJI
#enum RULE_JINDAIKO
#enum RULE_THREE_OTAKAZE
#enum RULE_THREE_WINDS
#enum RULE_XIAOSANFENG
#enum RULE_FOUR_HONORS
#enum RULE_RYANDOUKOH
#enum RULE_SANSHOKU_SHOUDOUKOH
#enum RULE_ODD_TOITOI
#enum RULE_EVEN_TOITOI
#enum RULE_EAST_GREEN
#enum RULE_SOUTH_WHITE
#enum RULE_WEST_RED
#enum RULE_TINSANKOH
#enum RULE_CHINPAIKOH
#enum RULE_CHAOPAIKOH
#enum RULE_SUUCHAOPAIKOH
#enum RULE_NISHOKU_SANRENKOH
#enum RULE_NISHOKU_CHAOPAIKOH
#enum RULE_NISHOKU_CHINPAIKOH
#enum RULE_NISHOKU_TINSANKOH
#enum RULE_NISHOKU_SUURENKOH
#enum RULE_NISHOKU_SUUCHAOPAIKOH
#enum RULE_SANSHOKU_RENKOH
#enum RULE_SANSHOKU_CHAOPAIKOH
#enum RULE_SANSHOKU_CHINPAIKOH
#enum RULE_SANSHOKU_TINSANKOH
#enum RULE_SANSHOKU_SUURENKOH
#enum RULE_SANSHOKU_SUUCHAOPAIKOH
#enum RULE_GOLDEN_LADDER
#enum RULE_SILVER_LADDER
#enum RULE_SKY_LADDER
#enum RULE_KINKEI_HOUGYOU
#enum RULE_GINKEI_HOUSHUN
#enum RULE_KOUKEI_HOUGYOU
#enum RULE_UIKYOU_TOITOI
#enum RULE_UIKYOU_SHUNTSU
#enum RULE_BAXIAN_CHENGFENG
#enum RULE_BAXIAN_XIFENG
#enum RULE_BAXIAN_XISIFENG
#enum RULE_BAXIAN_XIJINGUI
#enum RULE_BAXIAN_DOU_BEIDOU
#enum RULE_BAXIAN_JUSHOU
#enum RULE_FUUKA_SETSUGETSU
#enum RULE_KACHOU_FUUGETSU
#enum RULE_TOHOKU_EXPWY
#enum RULE_HIGASHIKANTO_EXPWY
#enum RULE_NISHINAKAJIMA
#enum RULE_CHUUGEN_CHIKUROKU
#enum RULE_TURTLE_EGG
#enum RULE_KYOKUJITSU_TOUSHOU
#enum RULE_RIIRAO_SHIISHAN
#enum RULE_YOUBOU_HOKUTO
#enum RULE_BIG_DIPPER
#enum RULE_SEISOU_TAIGETSU
#enum RULE_SEIKO_JIKKEI
#enum RULE_VOLCANIC_ERRUPTION
#enum RULE_VOLCANIC_TOITOI
#enum RULE_TANFON_CHOUYOU
#enum RULE_QUEQIAOHUI
#enum RULE_YIGAN_FENGYUE
#enum RULE_SANBEI_MEIJIU
#enum RULE_DONGFENG_YADAO
#enum RULE_TAIKOU_TURTLE
#enum RULE_BAOHONGKAIHUA
#enum RULE_KOHAKU_MANJU
#enum RULE_HAKUCHO
#enum RULE_HAKUIISOO
#enum RULE_SNOW_GINKAKU
#enum RULE_KITASHIRAKAWA
#enum RULE_NEWYEAR
#enum RULE_ALCOHOLISM
#enum RULE_KYUKYUSHA
#enum RULE_TOUNANSHA
#enum RULE_SEISHUN_KUINASHI
#enum RULE_SUPERMAN
#enum RULE_RINRYANSHII
#enum RULE_BAIHUA
#enum RULE_JIGU_ECAO
#enum RULE_MIYAKONOSEIHOKU
#enum RULE_TOKYO
#enum RULE_COLONEL_MUSKA
#enum RULE_HATSUNE_MIKU
#enum RULE_KAGAMINE_RIN
#enum RULE_KAGAMINE_LEN
#enum RULE_KAGAMINE_RINLEN
#enum RULE_777
#enum RULE_CHRISTMAS
#enum RULE_NEWYEAR_DREAM
#enum RULE_MUSASHIMARU
#enum RULE_HANSHIN
#enum RULE_KOBE
#enum RULE_SAPPORO1
#enum RULE_PCRSWT
#enum RULE_AQRS
#enum RULE_SMAP
#enum RULE_MONSTER_HUNTER

/* デリミタ */
#enum END_OF_SECTION
#undef START_OF_SECTION
#enum START_OF_SECTION = ((END_OF_SECTION-1)/RULES_IN_PAGE)+1
#undef END_OF_SECTION

/* 槓子役設定 */
#enum RULE_RYANANKAN = START_OF_SECTION*RULES_IN_PAGE
#enum RULE_SANANKAN
#enum RULE_SANSHOKU_DOUKAN
#enum RULE_CHOUSANGEN
#enum RULE_CHOUSIXI
#enum RULE_TANK
#enum RULE_SANADACOIN
#enum RULE_THREE_ARROWS
#enum RULE_GRAND_CANYON
#enum RULE_YUKIGESHOU
#enum RULE_SHENGDONG_JIXI
#enum RULE_ZAONAN_CHUANGBEI
#enum RULE_SETSUBUN

/* デリミタ(半ページ送り) */
#enum END_OF_SECTION
#undef START_OF_SECTION
#enum START_OF_SECTION = ((END_OF_SECTION-1)/RULES_IN_PAGE)+1
#undef END_OF_SECTION

/* 七対子系の役設定 */
#enum RULE_DAICHIKURIN = START_OF_SECTION*RULES_IN_PAGE-RULES_IN_PAGE/2
#enum RULE_DAISUURIN
#enum RULE_SHOSHARIN
#enum RULE_SHOCHIKURIN
#enum RULE_SHOSUURIN
#enum RULE_DRAGON_PAIRS
#enum RULE_WIND_PAIRS
#enum RULE_ODD_PAIRS
#enum RULE_EVEN_PAIRS
#enum RULE_KOUHAKU_CHIITOI
#enum RULE_KITA_NO_DAICHI
#enum RULE_SEKAIICHI

/* デリミタ */
#enum END_OF_SECTION
#undef START_OF_SECTION
#enum START_OF_SECTION = ((END_OF_SECTION-1)/RULES_IN_PAGE)+1
#undef END_OF_SECTION

/* 全体手役の設定 */
#enum RULE_KOUITTEN = START_OF_SECTION*RULES_IN_PAGE
#enum RULE_BENIKUJAKU
#enum RULE_RYUUIISOHRIN
#enum RULE_DAISOUGEN
#enum RULE_SOUTH_DAISOUGEN
#enum RULE_HEIIISOH
#enum RULE_AO_NO_DOMON
#enum RULE_NO_RED
#enum RULE_HUAIISOH
#enum RULE_HAKUITTEN
#enum RULE_TAOYISE
#enum RULE_CHAYISE
#enum RULE_STARLIGHT
#enum RULE_UUTAARAN
#enum RULE_SIMIAN_CHUGE
#enum RULE_PRIME_NUMBER
#enum RULE_TOIPUUTAO
#enum RULE_UUMENCHII
#enum RULE_CHUEIIMEN
#enum RULE_CHUUREN_HWATON
#enum RULE_EXPOSED_CHUUREN
#enum RULE_KAGA_MILLION
#enum RULE_PINZU_MILLION
#enum RULE_KISHU550K
#enum RULE_MITO350K
#enum RULE_FULLMOON
#enum RULE_MINORAGE
#enum RULE_COMINGOFAGE
#enum RULE_PI
#enum RULE_SQUARE_ROOT_TWO
#enum RULE_SQUARE_ROOT_TEN
#enum RULE_NATURAL_LOGARITHM
#enum RULE_IMAGINARY_NUMBER
#enum RULE_HENCHANTAIYAO
#enum RULE_ALL_ONE
#enum RULE_ALL_TWO
#enum RULE_ALL_THREE
#enum RULE_ALL_FOUR
#enum RULE_ALL_FIVE
#enum RULE_ALL_SIX
#enum RULE_ALL_SEVEN
#enum RULE_ALL_EIGHT
#enum RULE_ALL_NINE
#enum RULE_XIAOYUWU
#enum RULE_DAYUWU
#enum RULE_ALL_SMALL
#enum RULE_ALL_MIDDLE
#enum RULE_ALL_LARGE
#enum RULE_CHARACTERS_MAHJONG

/* デリミタ */
#enum END_OF_SECTION
#undef START_OF_SECTION
#enum START_OF_SECTION = ((END_OF_SECTION-1)/RULES_IN_PAGE)+1
#undef END_OF_SECTION

/* 状況役の設定 */
#enum RULE_BIRD_RIICHI = START_OF_SECTION*RULES_IN_PAGE
#enum RULE_CHOUIPPATSU
#enum RULE_SANSEKI_TEMPUKU
#enum RULE_KISHI_KAISEI
#enum RULE_UUPIN_KAIHOH
#enum RULE_CHUNSHAN_KAIHOH
#enum RULE_TOUKANHOH
#enum RULE_RENKAN_KAIHOH
#enum RULE_SAYONARA_HOMERUN
#enum RULE_RYANZOH_CHANKAN
#enum RULE_IIPIN_MOYUE
#enum RULE_HAITEI_RAOTSEN
#enum RULE_HAITEI_RAOHWA
#enum RULE_HATSUTEI_MOYUE
#enum RULE_CHUUPIN_RAOYUI
#enum RULE_HAKUTEI_RAOYUI
#enum RULE_NITEI_RAOCHUN
#enum RULE_MAABOODOUFU
#enum RULE_THREE_YEARS_ON_STONE
#enum RULE_TSUBAME_GAESHI
#enum RULE_HIEN
#enum RULE_KEPPAIHOH
#enum RULE_JINJI_DUOSHI
#enum RULE_KAMBURI
#enum RULE_OTAKAZE_RON
#enum RULE_BREAKING_PAARENCHAN
#enum RULE_ANCHUMOSAKU
#enum RULE_DORAHOH
#enum RULE_SUMARO
#enum RULE_NAMU_HACHIMAN
#enum RULE_HOUKANSOU
#enum RULE_GEKKANJUN
#enum RULE_SHINRIISHOU
#enum RULE_KINKI_KIKAN
#enum RULE_HOKUTO_SHOUKAN
#enum RULE_DAIJA_KANKETSU
#enum RULE_DONGFENGCHUI
#enum RULE_NANFENGCHUI
#enum RULE_XIFENGCHUI
#enum RULE_BEIFENGCHUI
#enum RULE_GOLDDRAGON
#enum RULE_WHIRLWIND
#enum RULE_BOLT_FROM_THE_BLUE

/* デリミタ */
#enum END_OF_SECTION
#undef START_OF_SECTION
#enum START_OF_SECTION = ((END_OF_SECTION-1)/RULES_IN_PAGE)+1
#undef END_OF_SECTION

/* その他の役設定 */
#enum RULE_SHIIARU_RAOTAI = START_OF_SECTION*RULES_IN_PAGE
#enum RULE_KINKEI_DOKURITSU
#enum RULE_KANKOU_NO_YUKI
#enum RULE_HAOUBEN
#enum RULE_RYUUKANCHAN
#enum RULE_XIQUE_NAOMEI
#enum RULE_SEKIGAN_SEIRYUU
#enum RULE_BLACKJACK
#enum RULE_WHITE_KNIGHT
#enum RULE_SEIKAN_TUNNEL
#enum RULE_SEIKAN_SHIP
#enum RULE_TOKYO_OLYMPIC_MONOCHROME
#enum RULE_TOKYO_OLYMPIC_POLYCHROME
#enum RULE_HIGASHI_HANAZONO_TRIPLETS
#enum RULE_HIGASHI_HANAZONO_RINSHAN
#enum RULE_FUYUSONA
#enum RULE_FUYUSONA2
#enum RULE_UNIV_TOKYO
#enum RULE_UNIV_HOKKAIDO
#enum RULE_UNIV_CHUO
#enum RULE_UNIV_HAKUOH
#enum RULE_UNIV_TOHOKU
#enum RULE_UNIV_NAGOYA
#enum RULE_KARASU
#enum RULE_KARASU_RIICHI
#enum RULE_KITAMAKURA
#enum RULE_FOUR_INTO_ONE
#enum RULE_DOUBLE_FOUR_INTO_ONE
#enum RULE_TIGER_FOUR_INTO_ONE
#enum RULE_DRAGON_FOUR_INTO_ONE
#enum RULE_FOUR_INTO_THREE
#enum RULE_FOUR_INTO_THREE_ONE
#enum RULE_FOUR_INTO_FOUR
#enum RULE_DOUBLE_FOUR_INTO_FOUR
#enum RULE_GREAT_FOUR_INTO_FOUR
#enum RULE_AZURE_DRAGON
#enum RULE_VERMILION_BIRD
#enum RULE_WHITE_TIGER
#enum RULE_BLACK_TORTOISE
#enum RULE_OWN_FLOWER
#enum RULE_FOUR_SEASONS
#enum RULE_FOUR_FLOWERS
#enum RULE_EIGHT_FLOWERS
#enum RULE_FOUR_NORTHES
#enum RULE_SHIISAN_UUSHII
#enum RULE_STELLAR_UUSHII
#enum RULE_CIVIL_WAR
#enum RULE_SYZYGY
#enum RULE_GRAND_CROSS

/* 終端コード */
#enum NUM_OF_RULES
#undef END_OF_SECTION
#undef START_OF_SECTION
