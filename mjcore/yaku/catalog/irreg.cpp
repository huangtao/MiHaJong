#include "../catalog.h"

void yaku::yakuCalculator::YakuCatalog::catalogInit::yakulst_irregular()
{
	/* チートイ */
	auto isQiDui =
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return ((analysis->shanten[ShantenAnalyzer::shantenPairs] == -1)&&(analysis->shanten[ShantenAnalyzer::shantenRegular] >= 0));
		};
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"七対子", (RuleData::getRule("seven_pairs") == 1) ? /* 1翻50符のルールと2翻25符のルールがある。符はここでは設定できないです…… */
		yaku::yakuCalculator::Yaku::yval_1han_menzen : yaku::yakuCalculator::Yaku::yval_2han_menzen,
		isQiDui
	));

	auto chktiles = // 判定関数オブジェクト
		[isQiDui](const MENTSU_ANALYSIS* const analysis, const tileCode* const targetDuiz, int numOfDuiz) -> bool {
			if (isQiDui(analysis))
				return (yaku::countingFacility::countPairs(analysis->TileCount, targetDuiz, numOfDuiz)
					== NUM_OF_TILES_IN_HAND / 2);
			else return false;
		};
	// ---------------------------------------------------------------------

	/* ツーイーソー */
	if (RuleData::getRule("seven_honor_pairs") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"七福星", yaku::yakuCalculator::Yaku::yval_double_yakuman_menzen,
			"混老頭", "混一色", "三元七対子", "四喜七対子", "紅白七対",
			[isQiDui](const MENTSU_ANALYSIS* const analysis) -> bool {
				if (isQiDui(analysis))
					return (yaku::countingFacility::countPairs(analysis->TileCount, Honor_Major_Tiles()+6, 7) == NUM_OF_TILES_IN_HAND / 2);
				else return false;
			}
		));
	/* 三元七対子 */
	if (RuleData::getRule("dragon_pairs") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"三元七対子", yaku::yakuCalculator::Yaku::yval_1han_menzen,
			[isQiDui](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isQiDui(analysis) &&
					(analysis->TileCount[WhiteDragon] >= 2) &&
					(analysis->TileCount[GreenDragon] >= 2) &&
					(analysis->TileCount[RedDragon] >= 2));
			}
		));
	/* 四喜七対子 */
	if (RuleData::getRule("wind_pairs") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"四喜七対子", yaku::yakuCalculator::Yaku::yval_1han_menzen,
			[isQiDui](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isQiDui(analysis) &&
					(analysis->TileCount[EastWind] >= 2) &&
					(analysis->TileCount[SouthWind] >= 2) &&
					(analysis->TileCount[WestWind] >= 2) &&
					(analysis->TileCount[NorthWind] >= 2));
			}
		));
	/* 奇数七対子 */
	if (RuleData::getRule("odd_pairs") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"奇数七対子", yaku::yakuCalculator::Yaku::yval_1han_menzen,
			[isQiDui, chktiles](const MENTSU_ANALYSIS* const analysis) -> bool {
				const tileCode tc[15] = {
					CharacterOne, CharacterThree, CharacterFive, CharacterSeven, CharacterNine,
					CircleOne, CircleThree, CircleFive, CircleSeven, CircleNine,
					BambooOne, BambooThree, BambooFive, BambooSeven, BambooNine,
				};
				return isQiDui(analysis) && chktiles(analysis, tc, 15);
			}
		));
	/* 偶数七対子 */
	if (RuleData::getRule("even_pairs") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"偶数七対子", yaku::yakuCalculator::Yaku::yval_2han_menzen,
			"断幺九",
			[isQiDui, chktiles](const MENTSU_ANALYSIS* const analysis) -> bool {
				const tileCode tc[12] = {
					CharacterTwo, CharacterFour, CharacterSix, CharacterEight,
					CircleTwo, CircleFour, CircleSix, CircleEight,
					BambooTwo, BambooFour, BambooSix, BambooEight,
				};
				return isQiDui(analysis) && chktiles(analysis, tc, 12);
			}
		));

	// ---------------------------------------------------------------------

	/* 紅白七対 */
	if (RuleData::getRule("kouhaku_chiitoi") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"紅白七対", yaku::yakuCalculator::Yaku::yval_2han_menzen,
			[isQiDui](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (isQiDui(analysis) &&
					(analysis->TileCount[WhiteDragon] >= 2) &&
					(analysis->TileCount[RedDragon] >= 2));
			}
		));
	/* 北の大地 */
	if (RuleData::getRule("kita_no_daichi") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"北の大地", yaku::yakuCalculator::Yaku::HANFUNC(
			[](const MENTSU_ANALYSIS* const analysis) -> yaku::yakuCalculator::Yaku::YAKU_HAN {
				switch (analysis->TsumoHai->tile) { /* 何で和了ったかで分岐 */
				case NorthWind: /* 北で和了るとダブル役満 */
					return yaku::yakuCalculator::Yaku::YAKU_HAN(yaku::yakuCalculator::Yaku::YAKU_HAN::HAN::yv_double_yakuman);
				case WhiteDragon: /* 白で和了るとトリプル役満 */
					return yaku::yakuCalculator::Yaku::YAKU_HAN(yaku::yakuCalculator::Yaku::YAKU_HAN::HAN::yv_triple_yakuman);
				default:
					return yaku::yakuCalculator::Yaku::YAKU_HAN(yaku::yakuCalculator::Yaku::YAKU_HAN::HAN::yv_yakuman);
				}
			}),
			"混一色",
			[isQiDui, chktiles](const MENTSU_ANALYSIS* const analysis) -> bool {
				const tileCode tc[7] = {
					BambooTwo, BambooThree, BambooFour, BambooSix, BambooEight,
					NorthWind, WhiteDragon,
				};
				return isQiDui(analysis) && chktiles(analysis, tc, 7);
			}
		));
	/* 世界一 */
	if (RuleData::getRule("sekaiichi") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"世界一", yaku::yakuCalculator::Yaku::yval_yakuman_menzen,
			"四喜七対子", "混老頭",
			[isQiDui, chktiles](const MENTSU_ANALYSIS* const analysis) -> bool {
				const tileCode tc[7] = {
					CharacterOne, CircleOne, BambooOne,
					EastWind, SouthWind, WestWind, NorthWind,
				};
				return isQiDui(analysis) && chktiles(analysis, tc, 7);
			}
		));

	// ---------------------------------------------------------------------

	/* 三色同対 */
	if (RuleData::getRule("sanshoku_doutoi") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"三色同対", yaku::yakuCalculator::Yaku::yval_1han_menzen,
			[isQiDui](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				for (int i = 1; i <= 9; i++)
					if ((analysis->TileCount[TILE_SUIT_CHARACTERS + i] >= 2) &&
						(analysis->TileCount[TILE_SUIT_CIRCLES + i] >= 2) &&
						(analysis->TileCount[TILE_SUIT_BAMBOOS + i] >= 2))
						yakuFlag = true;
				return isQiDui(analysis) && yakuFlag;
			}
		));

	// ---------------------------------------------------------------------

	{
		auto gyakusharin =
			[isQiDui](const MENTSU_ANALYSIS* const analysis, int suit) -> bool {
				std::array<tileCode, 7> honors = {
					EastWind, SouthWind, WestWind, NorthWind,
					WhiteDragon, GreenDragon, RedDragon,
				}; int count = 0;
				for (auto k = honors.begin(); k != honors.end(); k++)
					if (analysis->TileCount[*k] >= 2) ++count;
				return isQiDui(analysis) &&
					(analysis->TileCount[suit + 1] >= 2) &&
					(analysis->TileCount[suit + 9] >= 2) &&
					(count == 5);
			};
		/* 逆車輪 */
		if (RuleData::getRule("gyakusharin") != 0)
			yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
				"逆車輪", yaku::yakuCalculator::Yaku::yval_4han_menzen,
				[gyakusharin](const MENTSU_ANALYSIS* const analysis) -> bool {
					return gyakusharin(analysis, TILE_SUIT_CIRCLES);
				}
			));
		/* 逆竹林 */
		if (RuleData::getRule("gyakuchikurin") != 0)
			yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
				"逆竹林", yaku::yakuCalculator::Yaku::yval_4han_menzen,
				[gyakusharin](const MENTSU_ANALYSIS* const analysis) -> bool {
					return gyakusharin(analysis, TILE_SUIT_BAMBOOS);
				}
			));
		/* 逆数隣 */
		if (RuleData::getRule("gyakusuurin") != 0)
			yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
				"逆数隣", yaku::yakuCalculator::Yaku::yval_4han_menzen,
				[gyakusharin](const MENTSU_ANALYSIS* const analysis) -> bool {
					return gyakusharin(analysis, TILE_SUIT_CHARACTERS);
				}
			));
	}

	// ---------------------------------------------------------------------

	/* 国士 */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"国士無双", yaku::yakuCalculator::Yaku::yval_yakuman_menzen,
		"十三不塔",
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (analysis->shanten[ShantenAnalyzer::shantenOrphans] == -1);
		}
	));
	if (RuleData::getRule("double_yakuman") == 0) /* 国士13面待ち（ダブル役満） */
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"国士無双十三面", yaku::yakuCalculator::Yaku::yval_double_yakuman_menzen,
			"国士無双", "十三不塔",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->shanten[ShantenAnalyzer::shantenOrphans] == -1) && // 国士無双になっていて、
					(/* フリテンかどうか判定する */0) && // フリテンではなくて、
					((/* 13面待ちか判定する */0)||(analysis->GameStat->TianHuFlag))); // 13面待ちか天和になっている
			}
		));
	/* 七星無靠 */
	if (RuleData::getRule("stellar_uushii") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"七星無靠", (RuleData::getRule("stellar_uushii") == 2) ?
			yaku::yakuCalculator::Yaku::yval_baiman_menzen : yaku::yakuCalculator::Yaku::yval_yakuman_menzen,
			"全不靠",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (analysis->shanten[ShantenAnalyzer::shantenStellar] == -1);
			}
		));
	/* 南北戦争 */
	if (RuleData::getRule("civil_war") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"南北戦争", yaku::yakuCalculator::Yaku::yval_yakuman_menzen,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (analysis->shanten[ShantenAnalyzer::shantenCivilWar] == -1);
			}
		));
	/* 惑星直列 */
	if (RuleData::getRule("syzygy") != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"惑星直列", yaku::yakuCalculator::Yaku::yval_yakuman_menzen,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (analysis->shanten[ShantenAnalyzer::shantenSyzygy] == -1);
			}
		));
	/* 全不靠 */
	if (RuleData::getRule("quanbukao") != 0) {
		const yaku::yakuCalculator::Yaku::MenzenHan* qbk_han = NULL;
		switch (RuleData::getRule("quanbukao")) {
		case 1: case 2:
			qbk_han = &yaku::yakuCalculator::Yaku::yval_3han_menzen;
			break;
		case 3:
			qbk_han = &yaku::yakuCalculator::Yaku::yval_4han_menzen;
			break;
		case 4:
			qbk_han = &yaku::yakuCalculator::Yaku::yval_mangan_menzen;
			break;
		case 5:
			qbk_han = &yaku::yakuCalculator::Yaku::yval_yakuman_menzen;
			break;
		}
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"全不靠", *qbk_han,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (analysis->shanten[ShantenAnalyzer::shantenQuanbukao] == -1);
			}
		));
	}
}
