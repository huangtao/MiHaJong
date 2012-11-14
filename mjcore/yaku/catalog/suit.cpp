#include "../catalog.h"

void yaku::yakuCalculator::YakuCatalog::catalogInit::yakulst_suit() {
	/* チンイツ */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		_T("清一色"), get_yaku_han("chiniisoh"),
		_T("混一色"), _T("純一気通貫全帯幺九"),
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return isshoku(analysis, true);
		}
	));

	// ---------------------------------------------------------------------

	/* 和了ったら死ぬ */
	auto chkHaishiki =
		[](const MENTSU_ANALYSIS* const analysis, const char* const haishiki) -> bool {
			bool yakuFlag = false;
			for (int i = 0; i < TILE_SUIT_HONORS; i += TILE_SUIT_STEP)
				if ((analysis->TileCount[i + 1] >= (int)(haishiki[0] - _T('0'))) &&
					(analysis->TileCount[i + 2] >= (int)(haishiki[1] - _T('0'))) &&
					(analysis->TileCount[i + 3] >= (int)(haishiki[2] - _T('0'))) &&
					(analysis->TileCount[i + 4] >= (int)(haishiki[3] - _T('0'))) &&
					(analysis->TileCount[i + 5] >= (int)(haishiki[4] - _T('0'))) &&
					(analysis->TileCount[i + 6] >= (int)(haishiki[5] - _T('0'))) &&
					(analysis->TileCount[i + 7] >= (int)(haishiki[6] - _T('0'))) &&
					(analysis->TileCount[i + 8] >= (int)(haishiki[7] - _T('0'))) &&
					(analysis->TileCount[i + 9] >= (int)(haishiki[8] - _T('0'))) ) yakuFlag = true;
			return yakuFlag;
		};
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		_T("九蓮宝燈"), yaku::yakuCalculator::Yaku::yval_yakuman_menzen,
		_T("清一色"), _T("九蓮花燈"),
		[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
			return chkHaishiki(analysis, "311111113");
		}
	));
	if (RuleData::chkRuleApplied("double_yakuman"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("純正九蓮宝燈"), yaku::yakuCalculator::Yaku::yval_double_yakuman_menzen,
			_T("九蓮宝燈"), _T("清一色"), _T("九蓮花燈"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				const tileCode* tsumoTile = &(analysis->TsumoHai->tile);
				if ((*tsumoTile % 10 == 1) || (*tsumoTile % 10 == 9)) {
					if (analysis->TileCount[*tsumoTile] >= 4) yakuFlag = true;
				} else {
					if (analysis->TileCount[*tsumoTile] >= 2) yakuFlag = true;
				}
				return (chkHaishiki(analysis, "311111113")) && (!analysis->MachiInfo.FuritenFlag);
			}
		));
	/* 某青い子 */
	if (RuleData::chkRuleApplied("daisharin"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("大車輪"), get_yaku_han("daisharin"),
			_T("清一色"), _T("二盃口"), _T("七対子"), _T("平和"), _T("断幺九"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (chkHaishiki(analysis, "022222220") && (analysis->TileCount[CircleFive] >= 2));
			}
		));
	/* 大竹林 */
	if (RuleData::chkRuleApplied("daichikurin"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("大竹林"), get_yaku_han("daichikurin"),
			_T("清一色"), _T("二盃口"), _T("七対子"), _T("平和"), _T("断幺九"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (chkHaishiki(analysis, "022222220") && (analysis->TileCount[BambooFive] >= 2));
			}
		));
	/* 大数隣 */
	if (RuleData::chkRuleApplied("daisuurin"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("大数隣"), get_yaku_han("daisuurin"),
			_T("清一色"), _T("二盃口"), _T("七対子"), _T("平和"), _T("断幺九"), _T("橙一色"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (chkHaishiki(analysis, "022222220") && (analysis->TileCount[CharacterFive] >= 2));
			}
		));
	/* 小車輪 */
	if (RuleData::chkRuleApplied("shosharin"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("小車輪"), get_yaku_han("shosharin"),
			_T("清一色"), _T("二盃口"), _T("七対子"), _T("平和"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->TileCount[CircleFive] >= 2) &&
					(chkHaishiki(analysis, "222222200") || chkHaishiki(analysis, "002222222")));
			}
		));
	/* 小竹林 */
	if (RuleData::chkRuleApplied("shochikurin"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("小竹林"), get_yaku_han("shochikurin"),
			_T("清一色"), _T("二盃口"), _T("七対子"), _T("平和"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->TileCount[BambooFive] >= 2) &&
					(chkHaishiki(analysis, "222222200") || chkHaishiki(analysis, "002222222")));
			}
		));
	/* 小数隣 */
	if (RuleData::chkRuleApplied("shosuurin"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("小数隣"), get_yaku_han("shosuurin"),
			_T("清一色"), _T("二盃口"), _T("七対子"), _T("平和"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->TileCount[CharacterFive] >= 2) &&
					(chkHaishiki(analysis, "222222200") || chkHaishiki(analysis, "002222222")));
			}
		));
	/* 円周率和 (3.)14159265358979 */
	if (RuleData::chkRuleApplied("pi"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("円周率和"), get_yaku_han("pi"),
			_T("清一色"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return chkHaishiki(analysis, "211131113");
			}
		));

	// ---------------------------------------------------------------------

	/* √２和 1.4142135623730 */
	if (RuleData::chkRuleApplied("square_root_two"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("√２和"), get_yaku_han("square_root_two"),
			_T("清一色"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return chkHaishiki(analysis, "323211100");
			}
		));
	/* 自然対数の底 2.7182818284590 */
	if (RuleData::chkRuleApplied("natural_logarithm"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("自然対数の底"), get_yaku_han("natural_logarithm"),
			_T("清一色"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return chkHaishiki(analysis, "230110141");
			}
		));
	/* 虚数和 (0.)207879576350761 */
	if (RuleData::chkRuleApplied("imaginary_number"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("虚数和"), get_yaku_han("imaginary_number"),
			_T("清一色"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return chkHaishiki(analysis, "111022411");
			}
		));
	/* √１０和 3.16227766016837 */
	if (RuleData::chkRuleApplied("square_root_ten"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("√１０和"), get_yaku_han("square_root_ten"),
			_T("清一色"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return chkHaishiki(analysis, "222004310");
			}
		));

	// ---------------------------------------------------------------------

	/* 清海湖 */
	if (RuleData::chkRuleApplied("qinghaihu"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("清海湖"), get_yaku_han("qinghaihu"),
			_T("清一色"), _T("純全帯幺九"), _T("二盃口"), _T("平和"),
			[chkHaishiki](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((chkHaishiki(analysis, "422000222") || chkHaishiki(analysis, "222000224")));
			}
		));
	/* 中車輪 */
	auto chuusharin =
		[chkHaishiki](const MENTSU_ANALYSIS* const analysis, int suit) -> bool {
			return ((chkHaishiki(analysis, "202222220") || chkHaishiki(analysis, "222022220") ||
				chkHaishiki(analysis, "222202220") || chkHaishiki(analysis, "222222020") ||
				chkHaishiki(analysis, "022222202") || chkHaishiki(analysis, "022220222") ||
				chkHaishiki(analysis, "022202222") || chkHaishiki(analysis, "020222222") ||
				chkHaishiki(analysis, "220222220") || chkHaishiki(analysis, "222220220") ||
				chkHaishiki(analysis, "022022222") || chkHaishiki(analysis, "022222022")) &&
				((analysis->TileCount[suit + 4] >= 2) || (analysis->TileCount[suit + 5] >= 2))
				);
		};
	if (RuleData::chkRuleApplied("chuusharin"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("中車輪"), get_yaku_han("chuusharin"),
			_T("清一色"), _T("二盃口"),
			[chuusharin](const MENTSU_ANALYSIS* const analysis) -> bool {
				return chuusharin(analysis, TILE_SUIT_CIRCLES);
			}
		));
	/* 中竹林 */
	if (RuleData::chkRuleApplied("chuuchikurin"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("中竹林"), get_yaku_han("chuuchikurin"),
			_T("清一色"), _T("二盃口"),
			[chuusharin](const MENTSU_ANALYSIS* const analysis) -> bool {
				return chuusharin(analysis, TILE_SUIT_BAMBOOS);
			}
		));
	/* 中数隣 */
	if (RuleData::chkRuleApplied("chuusuurin"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("中数隣"), get_yaku_han("chuusuurin"),
			_T("清一色"), _T("二盃口"),
			[chuusharin](const MENTSU_ANALYSIS* const analysis) -> bool {
				return chuusharin(analysis, TILE_SUIT_CHARACTERS);
			}
		));

	// ---------------------------------------------------------------------

	/* 百万石 */
	auto chiffre =
		[](const MENTSU_ANALYSIS* const analysis) -> int {
			return (analysis->shanten[ShantenAnalyzer::shantenRegular] == -1) ?
				yaku::countingFacility::countMentzNumerals(analysis->MianziDat) :
				yaku::countingFacility::countTileNumerals(analysis->TileCount);
		};
	if (RuleData::chkRuleApplied("kaga_million")) {
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("百万石"), get_yaku_han("kaga_million"),
			_T("清一色"),
			[chiffre](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isshoku(analysis, true) && (chiffre(analysis) > 100) &&
					((analysis->TsumoHai->tile / TILE_SUIT_STEP) ==
					(TILE_SUIT_CHARACTERS / TILE_SUIT_STEP)));
			}
		));
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("加賀百万石"), RuleData::chkRule("kaga_million", "double_yakuman_if_just_100") ?
			yaku::yakuCalculator::Yaku::yval_yakuman : yaku::yakuCalculator::Yaku::yval_double_yakuman,
			_T("清一色"),
			[chiffre](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isshoku(analysis, true) && (chiffre(analysis) == 100) &&
					((analysis->TsumoHai->tile / TILE_SUIT_STEP) ==
					(TILE_SUIT_CHARACTERS / TILE_SUIT_STEP)));
			}
		));
	}
	/* 筒子百万石 */
	if (RuleData::chkRuleApplied("pinzu_million"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("筒子百万石"), get_yaku_han("pinzu_million"),
			_T("清一色"),
			[chiffre](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isshoku(analysis, true) && (chiffre(analysis) >= 100) &&
					((analysis->TsumoHai->tile / TILE_SUIT_STEP) ==
					(TILE_SUIT_CIRCLES / TILE_SUIT_STEP)));
			}
		));
	/* 紀州五十五万石 */
	if (RuleData::chkRuleApplied("kishu550k"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("紀州五十五万石"), get_yaku_han("kishu550k"),
			_T("清一色"),
			[chiffre](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isshoku(analysis, true) && (chiffre(analysis) == 55) &&
					((analysis->TsumoHai->tile / TILE_SUIT_STEP) ==
					(TILE_SUIT_CHARACTERS / TILE_SUIT_STEP)));
			}
		));
	/* 水戸三十五万石 */
	if (RuleData::chkRuleApplied("mito350k"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("水戸三十五万石"), get_yaku_han("mito350k"),
			_T("清一色"),
			[chiffre](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isshoku(analysis, true) && (chiffre(analysis) <= 35) &&
					((analysis->TsumoHai->tile / TILE_SUIT_STEP) ==
					(TILE_SUIT_CHARACTERS / TILE_SUIT_STEP)));
			}
		));
	/* フルムーン */
	if (RuleData::chkRuleApplied("fullmoon"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("フルムーン"), get_yaku_han("fullmoon"),
			_T("清一色"),
			[chiffre](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isshoku(analysis, true) && (chiffre(analysis) == 88));
			}
		));

	// ---------------------------------------------------------------------

	/* 星光燦爛 */
	if (RuleData::chkRuleApplied("starlight"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("星光燦爛"), get_yaku_han("starlight"),
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isshoku(analysis, true) && (analysis->KeziCount[CircleSeven]));
			}
		));
	/* 橙一色 */
	if (RuleData::chkRuleApplied("cheniisoh"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("橙一色"), get_yaku_han("cheniisoh"),
			_T("清一色"), _T("断幺九"),
			/*
				七対子の橙一色は４枚使いを認めない限りは２２３３４４５５６６７７８８の形のみ
				これは大数隣と同じ形であり、橙一色のみ採用の場合でも面子手として扱われる
			*/
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				if (analysis->shanten[ShantenAnalyzer::shantenRegular] == -1) {
					int yakuFlagCount = 0;
					const tileCode targetKezi[] = {CharacterOne, CharacterNine,};
					const tileCode targetShunzi[] = {CharacterOne, CharacterSeven,};
					if (yaku::countingFacility::countSpecMentz(analysis->MianziDat, targetKezi, 2, targetShunzi, 2, false) == 0)
						yakuFlag = true;
				} else if (analysis->shanten[ShantenAnalyzer::shantenPairs] == -1) {
					int yakuFlagCount = 0;
					const tileCode targetDuizi[] = {CharacterOne, CharacterNine,};
					if (yaku::countingFacility::countPairs(analysis->TileCount, targetDuizi, 2) == 0)
						yakuFlag = true;
				}
				return (isshoku(analysis, true) && (yakuFlag) &&
					((analysis->TsumoHai->tile / TILE_SUIT_STEP) ==
					(TILE_SUIT_CHARACTERS / TILE_SUIT_STEP)));
			}
		));

	// ---------------------------------------------------------------------

	/* ホンイツ */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		_T("混一色"), yaku::yakuCalculator::Yaku::yval_3han_kuisagari,
		_T("一気通貫全帯幺九"),
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return isshoku(analysis, false);
		}
	));

	// ---------------------------------------------------------------------

	/* 三麻の萬子ホンイツ */
	if ((RuleData::chkRuleApplied("characters_mahjong")) && chkGameType(&GameStat, SanmaT))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("萬和"), get_yaku_han("characters_mahjong"),
			_T("混一色"), _T("混老頭"),
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isshoku(analysis, false) &&
					((analysis->TileCount[CharacterOne] >= 1)||(analysis->TileCount[CharacterNine] >= 1)));
			}
		));
	/* 東京オリンピック(ホンイツ) */
	if (RuleData::chkRuleApplied("tokyo_olympic_monochrome"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("東京オリンピック"), get_yaku_han("tokyo_olympic_monochrome"),
			_T("混一色"),
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isshoku(analysis, false) &&
					((analysis->TileCount[CircleFive] >= 1)||(analysis->TileCount[EastWind] >= 1)));
			}
		));
	/* 西郷南州 */
	if (RuleData::chkRuleApplied("saigou_nanshuu"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("西郷南州"), get_yaku_han("saigou_nanshuu"),
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isshoku(analysis, false) &&
					(analysis->KeziCount[SouthWind] >= 1) &&
					(analysis->KeziCount[WestWind] >= 1) &&
					(analysis->TotalKezi == SIZE_OF_MELD_BUFFER - 1));
			}
		));
	/* 鏡音リンレン */
	if (RuleData::chkRuleApplied("kagamine_rinlen"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("鏡音リンレン"), get_yaku_han("kagamine_rinlen"),
			_T("混一色"), _T("鏡音リン"), _T("鏡音レン"), _T("三連刻"), _T("対々和"),
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				for (int i = 1; i < TILE_SUIT_HONORS; i++)
					if ((analysis->KeziCount[i] >= 1) && (analysis->KeziCount[i + 1] >= 1) && (analysis->KeziCount[i + 2] >= 1))
						yakuFlag = true;
				return (isshoku(analysis, false) && yakuFlag &&
					(analysis->KeziCount[WhiteDragon] >= 1) &&
					(analysis->KeziCount[WestWind] >= 1) &&
					((analysis->MianziDat[0].tile / TILE_SUIT_STEP) == (TILE_SUIT_CIRCLES / TILE_SUIT_STEP)));
			}
		));
	/* 鏡音リン */
	if (RuleData::chkRuleApplied("kagamine_rin"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("鏡音リン"), get_yaku_han("kagamine_rin"),
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				int PinMian = 0;
				for (int i = 0; i < SIZE_OF_MELD_BUFFER; i++)
					if ((analysis->MianziDat[i].tile / TILE_SUIT_STEP) == (TILE_SUIT_CIRCLES / TILE_SUIT_STEP))
						++PinMian;
				return (isshoku(analysis, false) && (PinMian > 0) &&
					(analysis->DuiziCount[WhiteDragon] >= 1));
			}
		));
	/* 翻満乃歩手地 */
	if (RuleData::chkRuleApplied("honmanopotechi"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("翻満乃歩手地"), get_yaku_han("honmanopotechi"),
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				int PinMian = 0;
				if (analysis->shanten[ShantenAnalyzer::shantenRegular] == -1) {
					for (int i = 0; i < SIZE_OF_MELD_BUFFER; i++)
						if ((analysis->MianziDat[i].tile / TILE_SUIT_STEP) == (TILE_SUIT_CIRCLES / TILE_SUIT_STEP))
							++PinMian;
					return (isshoku(analysis, false) &&
						(PinMian == SIZE_OF_MELD_BUFFER - 1) &&
						(analysis->DuiziCount[GreenDragon] >= 1));
				} else if (analysis->shanten[ShantenAnalyzer::shantenPairs] == -1) {
					for (int i = (int)CircleOne; i <= (int)CircleNine; i++)
						PinMian += analysis->TileCount[i];
					return (isshoku(analysis, false) &&
						(PinMian == NUM_OF_TILES_IN_HAND - 2) &&
						(analysis->TileCount[GreenDragon] >= 2));
				} else return false;
			}
		));

	// ---------------------------------------------------------------------

	/* 絶一門 */
	auto chueiimen =
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			bool flag[TILE_SUIT_HONORS / TILE_SUIT_STEP] = {false};
			if (analysis->shanten[ShantenAnalyzer::shantenRegular] == -1) {
				for (int k = 0; k < SIZE_OF_MELD_BUFFER; k++)
					if (analysis->MianziDat[k].tile < TILE_SUIT_HONORS)
						flag[analysis->MianziDat[k].tile / TILE_SUIT_STEP] = true;
			} else if (analysis->shanten[ShantenAnalyzer::shantenPairs] == -1) {
				for (int k = 1; k < TILE_SUIT_HONORS; k++)
					if (analysis->TileCount[k] > 0) flag[k / TILE_SUIT_STEP] = true;
			}
			return (
				(flag[TILE_SUIT_CHARACTERS / TILE_SUIT_STEP] && flag[TILE_SUIT_CIRCLES / TILE_SUIT_STEP] && !flag[TILE_SUIT_BAMBOOS / TILE_SUIT_STEP]) ||
				(flag[TILE_SUIT_CHARACTERS / TILE_SUIT_STEP] && !flag[TILE_SUIT_CIRCLES / TILE_SUIT_STEP] && flag[TILE_SUIT_BAMBOOS / TILE_SUIT_STEP]) ||
				(!flag[TILE_SUIT_CHARACTERS / TILE_SUIT_STEP] && flag[TILE_SUIT_CIRCLES / TILE_SUIT_STEP] && flag[TILE_SUIT_BAMBOOS / TILE_SUIT_STEP])
				);
		};
	std::function<bool(const MENTSU_ANALYSIS* const analysis)> chueiimen1 =
		[chueiimen](const MENTSU_ANALYSIS* const analysis) -> bool {
			return chueiimen(analysis);
		};
	std::function<bool(const MENTSU_ANALYSIS* const analysis)> chueiimen2 =
		[chueiimen](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (chueiimen(analysis) &&
				(analysis->TileCount[EastWind] + analysis->TileCount[SouthWind] + analysis->TileCount[WestWind] +
				analysis->TileCount[NorthWind] + analysis->TileCount[WhiteDragon] + analysis->TileCount[GreenDragon] +
				analysis->TileCount[RedDragon] == 0));
		};
	if (RuleData::chkRuleApplied("chueiimen"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("絶一門"), yaku::yakuCalculator::Yaku::yval_1han_menzen,
			RuleData::chkRule("chueiimen", "1han_nohonors") ? chueiimen1 : chueiimen2
		));
	/* 四面楚歌 */
	if (RuleData::chkRuleApplied("simian_chuge"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("四面楚歌"), get_yaku_han("simian_chuge"),
			_T("絶一門"),
			[chueiimen2](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (chueiimen2(analysis) &&
					(analysis->shanten[ShantenAnalyzer::shantenRegular] == -1) &&
					((analysis->MianziDat[1].tile / TILE_SUIT_STEP) ==
					(analysis->MianziDat[2].tile / TILE_SUIT_STEP)) &&
					((analysis->MianziDat[2].tile / TILE_SUIT_STEP) ==
					(analysis->MianziDat[3].tile / TILE_SUIT_STEP)) &&
					((analysis->MianziDat[3].tile / TILE_SUIT_STEP) ==
					(analysis->MianziDat[4].tile / TILE_SUIT_STEP)) &&
					(analysis->Machi == yaku::yakuCalculator::machiTanki)
					);
			}
		));
	/* 五門斎 */
	auto uumenchii =
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			int mnzCount[TILE_SUIT_HONORS / TILE_SUIT_STEP + 2] = {0};
			bool yakuFlag = true;
			{
				tileCode tc;
				if (analysis->shanten[ShantenAnalyzer::shantenRegular] == -1)
				for (int i = 0; i < ((analysis->shanten[ShantenAnalyzer::shantenRegular] == -1) ?
					SIZE_OF_MELD_BUFFER : NUM_OF_TILES_IN_HAND); i++) {
						if (analysis->shanten[ShantenAnalyzer::shantenRegular] == -1) tc = analysis->MianziDat[i].tile;
						else if (analysis->shanten[ShantenAnalyzer::shantenPairs] == -1) tc = analysis->PlayerStat->Hand[i].tile;
						if (tc < TILE_SUIT_HONORS) ++mnzCount[tc / TILE_SUIT_STEP];
						else switch (tc) {
						case EastWind: case SouthWind: case WestWind: case NorthWind:
							++mnzCount[TILE_SUIT_HONORS / TILE_SUIT_STEP]; break;
						case WhiteDragon: case GreenDragon: case RedDragon:
							++mnzCount[TILE_SUIT_HONORS / TILE_SUIT_STEP + 1]; break;
						}
				}
			}
			for (int i = 0; i < (TILE_SUIT_HONORS / TILE_SUIT_STEP + 2); i++)
				if (mnzCount[i] == 0) yakuFlag = false;
			return yakuFlag;
		};
	if (RuleData::chkRuleApplied("uumenchii"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("五門斎"), get_yaku_han("uumenchii"),
			uumenchii
		));
	/* 東京オリンピック */
	if (RuleData::chkRuleApplied("tokyo_olympic_polychrome"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("東京オリンピック "), get_yaku_han("tokyo_olympic_polychrome"),
			_T("五門斎"),
			[uumenchii](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (uumenchii(analysis) &&
					(analysis->GameStat->GameRound / 4 == sEast) &&
					(playerwind(analysis->GameStat, analysis->player, analysis->GameStat->GameRound) == sEast)
					);
			}
		));
	/* 未成年 */
	if (RuleData::chkRuleApplied("minorage"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("未成年"), get_yaku_han("minorage"),
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				for (int i = 0; i < SIZE_OF_MELD_BUFFER; i++)
					if (analysis->MianziDat[i].tile >= TILE_SUIT_HONORS)
						return false;
				return ((analysis->shanten[ShantenAnalyzer::shantenRegular] == -1) &&
					(yaku::countingFacility::countMentzNumerals(analysis->MianziDat) < 20));
			}
		));
	/* 成人式 */
	if (RuleData::chkRuleApplied("comingofage"))
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			_T("成人式"), get_yaku_han("comingofage"),
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				for (int i = 0; i < SIZE_OF_MELD_BUFFER; i++)
					if (analysis->MianziDat[i].tile >= TILE_SUIT_HONORS)
						return false;
				return ((analysis->shanten[ShantenAnalyzer::shantenRegular] == -1) &&
					(yaku::countingFacility::countMentzNumerals(analysis->MianziDat) == 20));
			}
		));
}
