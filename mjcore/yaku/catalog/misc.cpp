#include "../catalog.h"

extern GameTable GameStat;

void yaku::yakuCalculator::YakuCatalog::catalogInit::yakulst_misc() {
	auto chktiles = // 面子手・七対子兼用の判定関数オブジェクト
		[](const MENTSU_ANALYSIS* const analysis, const tileCode* const targetKez, int numOfKez,
		const tileCode* const targetShunz, int numOfShunz, bool noDui) -> bool {
			if (analysis->shanten[shantenRegular] == -1)
				return (yaku::countingFacility::countSpecMentz
					(analysis->MianziDat, targetKez, numOfKez, targetShunz, numOfShunz, noDui)
					== SIZE_OF_MELD_BUFFER);
			else if (analysis->shanten[shantenPairs] == -1)
				return (yaku::countingFacility::countPairs(analysis->TileCount, targetKez, numOfKez)
					== NUM_OF_TILES_IN_HAND / 2);
			else return false;
		};
	/* 緑一色 */
	{
		auto allgrean =
			[chktiles](const MENTSU_ANALYSIS* const analysis) -> bool {
				const tileCode kezi[] = {BambooTwo, BambooThree, BambooFour, BambooSix, BambooEight, GreenDragon};
				const tileCode shunzi[] = {BambooTwo};
				return chktiles(analysis, kezi, 6, shunzi, 1, false);
			};
		auto withdragon =
			[chktiles](const MENTSU_ANALYSIS* const analysis) -> bool {
				const tileCode kezi[] = {GreenDragon};
				if (analysis->shanten[shantenRegular] == -1)
					return (yaku::countingFacility::countSpecMentz
						(analysis->MianziDat, kezi, 1, NULL, 0, false) > 0);
				else if (analysis->shanten[shantenPairs] == -1)
					return (yaku::countingFacility::countPairs(analysis->TileCount, kezi, 1) > 0);
				else return false;
			};
		if (getRule(RULE_DRAGONLESS_ALL_GREEN) == 0) // 發なしでも良いルール
			yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
				"緑一色", yaku::yakuCalculator::Yaku::yval_yakuman,
				"混一色", // 清一色は複合可
				allgrean
			));
		else
			yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
				"緑一色", yaku::yakuCalculator::Yaku::yval_yakuman,
				"混一色",
				[allgrean, withdragon](const MENTSU_ANALYSIS* const analysis) -> bool {
					return allgrean(analysis) && (withdragon(analysis));
				}
			));
		if (getRule(RULE_DRAGONLESS_ALL_GREEN) == 2) // 發なしがダブル役満になるルール
			yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
				chkGameType(&GameStat, SanmaS) ? "清緑一色" : "緑一色", yaku::yakuCalculator::Yaku::yval_double_yakuman,
				"清一色",
				[allgrean, withdragon](const MENTSU_ANALYSIS* const analysis) -> bool {
					return allgrean(analysis) && (!withdragon(analysis));
				}
			));
	}
}
