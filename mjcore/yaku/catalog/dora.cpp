#include "../catalog.h"

void yaku::yakuCalculator::YakuCatalog::catalogInit::yakulst_dora() {
	/* ドラで和了ったら1飜 */
	if (getRule(RULE_DORAHOH) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"銅鑼和", yaku::yakuCalculator::Yaku::yval_1han,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->shanten[shantenAll] == -1) && // 何かの手で和了になっている
					((analysis->GameStat->DoraFlag.Omote[analysis->TsumoHai->tile] > 0) || // ツモ牌が表ドラになっている(裏ドラは対象外)
					(analysis->TsumoHai->red != Normal))); // 赤ドラか青ドラになっている
			}
		));
	/* 北四枚抜き */
	if (getRule(RULE_FOUR_NORTHES) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"北四枚抜き", yaku::yakuCalculator::Yaku::yval_yakuman_dependent,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->shanten[shantenAll] == -1) && // 何かの手で和了になっている
					(analysis->PlayerStat->NorthFlag == 4)); // 北4枚
			}
		));
	/* 八仙過海 */
	if (getRule(RULE_EIGHT_FLOWERS) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"八仙過海", yaku::yakuCalculator::Yaku::yval_yakuman_dependent,
			"春夏秋冬", "四華開嶺", "本花季節牌", "本花草木牌",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->shanten[shantenAll] == -1) && // 何かの手で和了になっている
					(analysis->PlayerStat->FlowerFlag.Spring) && (analysis->PlayerStat->FlowerFlag.Summer) &&
					(analysis->PlayerStat->FlowerFlag.Autumn) && (analysis->PlayerStat->FlowerFlag.Winter) &&
					(analysis->PlayerStat->FlowerFlag.Plum) && (analysis->PlayerStat->FlowerFlag.Orchid) &&
					(analysis->PlayerStat->FlowerFlag.Chrys) && (analysis->PlayerStat->FlowerFlag.Bamboo));
			}
		));
	/* 春夏秋冬 */
	if (getRule(RULE_FOUR_SEASONS) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"春夏秋冬", (getRule(RULE_FOUR_SEASONS) == 1) ?
			yaku::yakuCalculator::Yaku::yval_2han_dependent :
			(getRule(RULE_FOUR_SEASONS) == 2) ? yaku::yakuCalculator::Yaku::yval_4han_dependent :
			yaku::yakuCalculator::Yaku::yval_yakuman_dependent,
			"本花季節牌",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->shanten[shantenAll] == -1) && // 何かの手で和了になっている
					(analysis->PlayerStat->FlowerFlag.Spring) && (analysis->PlayerStat->FlowerFlag.Summer) &&
					(analysis->PlayerStat->FlowerFlag.Autumn) && (analysis->PlayerStat->FlowerFlag.Winter));
			}
		));
	/* 四華開嶺 */
	if (getRule(RULE_FOUR_FLOWERS) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"四華開嶺", (getRule(RULE_FOUR_FLOWERS) == 1) ?
			yaku::yakuCalculator::Yaku::yval_2han_dependent :
			(getRule(RULE_FOUR_FLOWERS) == 2) ? yaku::yakuCalculator::Yaku::yval_4han_dependent :
			yaku::yakuCalculator::Yaku::yval_yakuman_dependent,
			"本花草木牌",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->shanten[shantenAll] == -1) && // 何かの手で和了になっている
					(analysis->PlayerStat->FlowerFlag.Plum) && (analysis->PlayerStat->FlowerFlag.Orchid) &&
					(analysis->PlayerStat->FlowerFlag.Chrys) && (analysis->PlayerStat->FlowerFlag.Bamboo));
			}
		));
	/* 本花 */
	if (getRule(RULE_OWN_FLOWER) != 0) {
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"本花季節牌", yaku::yakuCalculator::Yaku::yval_1han_dependent,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				if (analysis->shanten[shantenAll] != -1) return false; // 和了ってないなら戻る
				switch (playerwind(analysis->GameStat, analysis->player, analysis->GameStat->GameRound)) {
					case sEast: return analysis->PlayerStat->FlowerFlag.Spring;
					case sSouth: return analysis->PlayerStat->FlowerFlag.Summer;
					case sWest: return analysis->PlayerStat->FlowerFlag.Autumn;
					case sNorth: return analysis->PlayerStat->FlowerFlag.Winter;
					default:
						RaiseTolerant(EXCEPTION_MJCORE_INVALID_DATA, "自風が東南西北のどれでもありません");
						return false;
				}
			}
		));
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"本花草木牌", yaku::yakuCalculator::Yaku::yval_1han_dependent,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				if (analysis->shanten[shantenAll] != -1) return false; // 和了ってないなら戻る
				switch (playerwind(analysis->GameStat, analysis->player, analysis->GameStat->GameRound)) {
					case sEast: return analysis->PlayerStat->FlowerFlag.Plum;
					case sSouth: return analysis->PlayerStat->FlowerFlag.Orchid;
					case sWest: return analysis->PlayerStat->FlowerFlag.Chrys;
					case sNorth: return analysis->PlayerStat->FlowerFlag.Bamboo;
					default:
						RaiseTolerant(EXCEPTION_MJCORE_INVALID_DATA, "自風が東南西北のどれでもありません");
						return false;
				}
			}
		));
	}
}
