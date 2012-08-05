#include "../catalog.h"

void yaku::yakuCalculator::YakuCatalog::catalogInit::yakulst_triplet_1() {
	/* 四暗刻 */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"四暗刻", yaku::yakuCalculator::Yaku::yval_yakuman_menzen,
		"対々和", "三暗刻",
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (analysis->TotalAnKezi - (
				((analysis->Machi == yaku::yakuCalculator::machiShanpon) && (*analysis->TsumoAgariFlag)) ?
				1 : 0) == 4);
		}
	));
	/* 四暗刻単騎 */
	if (getRule(RULE_DOUBLE_YAKUMAN) == 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"四暗刻単騎", yaku::yakuCalculator::Yaku::yval_double_yakuman_menzen,
			"四暗刻", "対々和", "三暗刻",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (analysis->TotalAnKezi - (
					((analysis->Machi == yaku::yakuCalculator::machiShanpon) && (*analysis->TsumoAgariFlag)) ?
					1 : 0) == 4) && (
					(analysis->GameStat->TianHuFlag) ||
					((analysis->Machi == yaku::yakuCalculator::machiTanki) && (!analysis->MachiInfo.FuritenFlag))
					);
			}
		));
	/* 三暗刻 */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"三暗刻", yaku::yakuCalculator::Yaku::yval_2han,
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (analysis->TotalAnKezi - (
				((analysis->Machi == yaku::yakuCalculator::machiShanpon) && (*analysis->TsumoAgariFlag)) ?
				1 : 0) == 3);
		}
	));

	// ---------------------------------------------------------------------

	/* 五連刻 */
	if (getRule(RULE_GOLDEN_LADDER) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"金梯", yaku::yakuCalculator::Yaku::yval_double_yakuman,
			"清一色", "対々和",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				for (int i = 1; i < TILE_SUIT_HONORS; i++)
					if ((analysis->KeziCount[i] >= 1) &&
						(analysis->KeziCount[i + 1] >= 1) &&
						(analysis->KeziCount[i + 2] >= 1) &&
						(analysis->KeziCount[i + 3] >= 1) &&
						((analysis->MianziDat[0].tile == (tileCode)(i - 1)) ||
						(analysis->MianziDat[0].tile == (tileCode)(i + 4))) )
						yakuFlag = true;
				return yakuFlag;
			}
		));
	/* 四連刻 */
	auto suurenkoh =
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			bool yakuFlag = false;
			for (int i = 1; i < TILE_SUIT_HONORS; i++)
				if ((analysis->KeziCount[i] >= 1) &&
					(analysis->KeziCount[i + 1] >= 1) &&
					(analysis->KeziCount[i + 2] >= 1) &&
					(analysis->KeziCount[i + 3] >= 1))
					yakuFlag = true;
			return yakuFlag;
		};
	if (getRule(RULE_SUURENKOH) == 1)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"四連刻", yaku::yakuCalculator::Yaku::yval_yakuman,
			"金梯", "対々和",
			suurenkoh
		));
	else if (getRule(RULE_SUURENKOH) == 2)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"四連刻", yaku::yakuCalculator::Yaku::yval_6han /* 対々和込み8飜 */,
			"金梯",
			suurenkoh
		));
	/* 三連刻 */
	auto sanrenkoh =
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			bool yakuFlag = false;
			for (int i = 1; i < TILE_SUIT_HONORS; i++)
				if ((analysis->KeziCount[i] >= 1) &&
					(analysis->KeziCount[i + 1] >= 1) &&
					(analysis->KeziCount[i + 2] >= 1))
					yakuFlag = true;
			return yakuFlag;
		};
	if (getRule(RULE_SANRENKOH) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"三連刻", (getRule(RULE_SANRENKOH) == 2) ?
			yaku::yakuCalculator::Yaku::yval_3han : yaku::yakuCalculator::Yaku::yval_2han,
			"金梯", "四連刻",
			sanrenkoh
		));
	/* 鏡音レン */
	if (getRule(RULE_KAGAMINE_LEN) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"鏡音レン", yaku::yakuCalculator::Yaku::yval_2han,
			/* 三連刻に追加する役 */
			[sanrenkoh](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->KeziCount[WhiteDragon] >= 1) && sanrenkoh(analysis));
			}
		));

	// ---------------------------------------------------------------------

	/* レアな方の三色 */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"三色同刻", (getRule(RULE_SANSHOKU_DOUKOH) != 0) ?
		yaku::yakuCalculator::Yaku::yval_3han : yaku::yakuCalculator::Yaku::yval_2han,
		"三色小同刻",
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			bool yakuFlag = false;
			for (int i = 1; i <= 9; i++)
				if ((analysis->KeziCount[i + TILE_SUIT_CHARACTERS] >= 1) &&
					(analysis->KeziCount[i + TILE_SUIT_CIRCLES] >= 1) &&
					(analysis->KeziCount[i + TILE_SUIT_BAMBOOS] >= 1))
					yakuFlag = true;
			return yakuFlag;
		}
	));
	/* 四色同刻（えっ */
	if (getRule(RULE_YONSHOKU_DOUKOH) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"四色同刻", yaku::yakuCalculator::Yaku::yval_yakuman,
			"三色同刻", "三色小同刻", "対々和",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				for (int i = 1; i <= 9; i++)
					if ((analysis->KeziCount[i + TILE_SUIT_CHARACTERS] >= 1) &&
						(analysis->KeziCount[i + TILE_SUIT_CIRCLES] >= 1) &&
						(analysis->KeziCount[i + TILE_SUIT_BAMBOOS] >= 1) &&
						(analysis->KeziCount[WhiteDragon] >= 1))
						yakuFlag = true;
				return yakuFlag;
			}
		));
	/* 三色小同刻 */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"三色小同刻", yaku::yakuCalculator::Yaku::yval_1han,
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			bool yakuFlag = false;
			for (int i = 1; i <= 9; i++)
				if ((analysis->DuiziCount[i + TILE_SUIT_CHARACTERS] >= 1) &&
					(analysis->DuiziCount[i + TILE_SUIT_CIRCLES] >= 1) &&
					(analysis->DuiziCount[i + TILE_SUIT_BAMBOOS] >= 1))
					yakuFlag = true;
			return yakuFlag;
		}
	));

	// ---------------------------------------------------------------------

	/* 三元和・四喜和判定用 */
	auto WindCnt =
		[](const MENTSU_ANALYSIS* const analysis) -> int {
			return analysis->DuiziCount[EastWind] + analysis->KeziCount[EastWind] +
				 analysis->DuiziCount[SouthWind] + analysis->KeziCount[SouthWind] +
				  analysis->DuiziCount[WestWind] + analysis->KeziCount[WestWind] +
				  analysis->DuiziCount[NorthWind] + analysis->KeziCount[NorthWind];
		};
	auto DragonCnt =
		[](const MENTSU_ANALYSIS* const analysis) -> int {
			return analysis->DuiziCount[WhiteDragon] + analysis->KeziCount[WhiteDragon] +
				 analysis->DuiziCount[GreenDragon] + analysis->KeziCount[GreenDragon] +
				  analysis->DuiziCount[RedDragon] + analysis->KeziCount[RedDragon];
		};
	/* 小三元 */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"小三元", yaku::yakuCalculator::Yaku::yval_2han,
		/* 役牌2つは必ず複合する */
		[DragonCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (DragonCnt(analysis) == 5);
		}
	));
	/* 大三元 */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"大三元", yaku::yakuCalculator::Yaku::yval_yakuman,
		"役牌・白", "役牌・發", "役牌・中",
		[DragonCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (DragonCnt(analysis) == 6);
		}
	));
	/* 小四喜 */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"小四喜", yaku::yakuCalculator::Yaku::yval_yakuman,
		"混一色",
		[WindCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (WindCnt(analysis) == 7);
		}
	));
	/* 天虎 */
	if (getRule(RULE_HEAVEN_TIGER) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"天虎", yaku::yakuCalculator::Yaku::yval_triple_yakuman,
			"混一色", "小四喜", "字一色", "役牌・發",
			[WindCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((WindCnt(analysis) == 7)&&(analysis->KeziCount[GreenDragon] >= 1));
			}
		));
	/* 大怪湖 */
	if (getRule(RULE_DAIKAIKO) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"大怪湖", yaku::yakuCalculator::Yaku::yval_triple_yakuman,
			"混一色", "小四喜", "字一色", "役牌・白",
			[WindCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((WindCnt(analysis) == 7)&&(analysis->KeziCount[WhiteDragon] >= 1));
			}
		));
	/* 千年虫 */
	if (getRule(RULE_Y2KBUG) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"千年虫", yaku::yakuCalculator::Yaku::yval_double_yakuman,
			"混一色", "小四喜", "混老頭",
			[WindCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((WindCnt(analysis) == 7)&&
					(analysis->KeziCount[CharacterNine] >= 1)&&(analysis->KeziCount[SouthWind] == 1));
			}
		));
	/* 大四喜 */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"大四喜", (getRule(RULE_DOUBLE_YAKUMAN) == 0) ?
		yaku::yakuCalculator::Yaku::yval_double_yakuman : yaku::yakuCalculator::Yaku::yval_yakuman,
		"混一色", "対々和", "役牌・場風", "役牌・自風", "役牌・開門風", "役牌・裏風",
		[WindCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (WindCnt(analysis) == 8);
		}
	));
	/* 弾葯 */
	if (getRule(RULE_DAN_YAKU) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"弾葯", yaku::yakuCalculator::Yaku::yval_triple_yakuman,
			"混一色", "対々和", "役牌・場風", "役牌・自風", "役牌・開門風", "役牌・裏風", "大四喜", "混老頭",
			[WindCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((WindCnt(analysis) == 8)&&(analysis->DuiziCount[CharacterNine] >= 1));
			}
		));
	/* 仙人掌 */
	if (getRule(RULE_CACTUS) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"仙人掌", yaku::yakuCalculator::Yaku::yval_quad_yakuman,
			"混一色", "対々和", "役牌・場風", "役牌・自風", "役牌・開門風", "役牌・裏風", "大四喜", "字一色",
			[WindCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((WindCnt(analysis) == 8)&&(analysis->DuiziCount[RedDragon] >= 1));
			}
		));

	// ---------------------------------------------------------------------

	/* 対々和 */
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"対々和", yaku::yakuCalculator::Yaku::yval_2han,
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (analysis->TotalKezi == SIZE_OF_MELD_BUFFER - 1);
		}
	));

	// ---------------------------------------------------------------------

	/* 役牌 */
	auto bakaze =
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (analysis->KeziCount[Wind2Tile(analysis->GameStat->GameRound / 4)] >= 1);
		};
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"役牌・場風", yaku::yakuCalculator::Yaku::yval_1han,
		bakaze
	));
	auto jikaze =
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (analysis->KeziCount[Wind2Tile((uint8_t)playerwind(analysis->GameStat,
				analysis->player, analysis->GameStat->GameRound))] >= 1);
		};
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"役牌・自風", yaku::yakuCalculator::Yaku::yval_1han,
		jikaze
	));
	YAKUFUNC kaimenkaze, urakaze;
	if (getRule(RULE_KAIMENKAZE) != 0) {
		kaimenkaze =
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (analysis->KeziCount[Wind2Tile((uint8_t)playerwind(analysis->GameStat,
					analysis->GameStat->WaremePlayer, analysis->GameStat->GameRound)))] >= 1);
			};
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"役牌・開門風", yaku::yakuCalculator::Yaku::yval_1han,
			kaimenkaze
		));
	} else {
		kaimenkaze = 
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return false;
			};
	}
	if (getRule(RULE_URAKAZE) != 0) {
		urakaze =
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (analysis->KeziCount[Wind2Tile((uint8_t)playerwind(analysis->GameStat,
					RelativePositionOf(analysis->player, sOpposite), analysis->GameStat->GameRound)))] >= 1);
			};
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"役牌・裏風", yaku::yakuCalculator::Yaku::yval_1han,
			urakaze
		));
	} else {
		urakaze = 
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return false;
			};
	}
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"役牌・白", yaku::yakuCalculator::Yaku::yval_1han,
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (analysis->KeziCount[WhiteDragon] >= 1);
		}
	));
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"役牌・發", yaku::yakuCalculator::Yaku::yval_1han,
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (analysis->KeziCount[GreenDragon] >= 1);
		}
	));
	yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
		"役牌・中", yaku::yakuCalculator::Yaku::yval_1han,
		[](const MENTSU_ANALYSIS* const analysis) -> bool {
			return (analysis->KeziCount[RedDragon] >= 1);
		}
	));

	// ---------------------------------------------------------------------

	/* 新沼けんじ */
	if (getRule(RULE_NIINUMA_KENJI) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"新沼けんじ", yaku::yakuCalculator::Yaku::yval_1han,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (analysis->KeziCount[BambooOne] >= 1);
			}
		));
	/* 陣太鼓 */
	if (getRule(RULE_JINDAIKO) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"陣太鼓", yaku::yakuCalculator::Yaku::yval_1han,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (analysis->KeziCount[CircleOne] >= 1);
			}
		));

	// ---------------------------------------------------------------------

	/* 小三風 */
	if (getRule(RULE_XIAOSANFENG) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"小三風", yaku::yakuCalculator::Yaku::yval_1han,
			[WindCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (WindCnt(analysis) == 5);
			}
		));
	/* 三風刻 */
	if (getRule(RULE_THREE_WINDS) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"三風刻", yaku::yakuCalculator::Yaku::yval_2han,
			[WindCnt](const MENTSU_ANALYSIS* const analysis) -> bool {
				return (WindCnt(analysis) == 6);
			}
		));
	/* 客風三刻 */
	if (getRule(RULE_THREE_OTAKAZE) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"客風三刻", yaku::yakuCalculator::Yaku::yval_3han,
			"三風刻",
			[WindCnt, bakaze, jikaze, kaimenkaze, urakaze]
			(const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((WindCnt(analysis) == 6) &&
					(!bakaze(analysis)) &&
					(!jikaze(analysis)) &&
					(!kaimenkaze(analysis)) &&
					(!urakaze(analysis)));
			}
		));
	/* 客風小三刻 */
	if (getRule(RULE_OTAKAZE_XIAOSANFENG) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"客風小三刻", yaku::yakuCalculator::Yaku::yval_2han,
			"小三刻",
			[WindCnt, bakaze, jikaze, kaimenkaze, urakaze]
			(const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((WindCnt(analysis) == 5) &&
					(!bakaze(analysis)) &&
					(!jikaze(analysis)) &&
					(!kaimenkaze(analysis)) &&
					(!urakaze(analysis)));
			}
		));

	// ---------------------------------------------------------------------

	/* 西中島南方 */
	if (getRule(RULE_NISHINAKAJIMA) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"西中島南方", yaku::yakuCalculator::Yaku::yval_yakuman,
			"役牌・場風", "役牌・自風", "役牌・中",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				if ((analysis->GameStat->GameRound / 4 == sWest) &&
					(playerwind(analysis->GameStat, analysis->player, analysis->GameStat->GameRound) == sSouth))
					yakuFlag = true;
				if ((analysis->GameStat->GameRound / 4 == sSouth) &&
					(playerwind(analysis->GameStat, analysis->player, analysis->GameStat->GameRound) == sWest))
					yakuFlag = true;
				return ((analysis->KeziCount[SouthWind] >= 1) &&
					(analysis->KeziCount[WestWind] >= 1) &&
					(analysis->KeziCount[RedDragon] >= 1) &&
					(yakuFlag));
			}
		));
	/* 雪月花 */
	if (getRule(RULE_SETSUGETSUKA) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"雪月花", (getRule(RULE_SETSUGETSUKA) == 2) ?
			yaku::yakuCalculator::Yaku::yval_3han : yaku::yakuCalculator::Yaku::yval_2han,
			"役牌・白",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->KeziCount[WhiteDragon] >= 1) &&
					(analysis->KeziCount[CircleOne] >= 1) &&
					(analysis->KeziCount[CircleFive] >= 1));
			}
		));
	/* 風花雪月 */
	if (getRule(RULE_FUUKA_SETSUGETSU) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"風花雪月", yaku::yakuCalculator::Yaku::yval_yakuman,
			"雪月花", "対々和", "役牌・場風", "役牌・自風",
			[bakaze, jikaze](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->KeziCount[WhiteDragon] >= 1) &&
					(analysis->KeziCount[CircleOne] >= 1) &&
					(analysis->KeziCount[CircleFive] >= 1) &&
					(bakaze(analysis) || jikaze(analysis)));
			}
		));
	/* 花鳥風月 */
	if (getRule(RULE_KACHOU_FUUGETSU) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"花鳥風月", yaku::yakuCalculator::Yaku::yval_yakuman,
			"雪月花", "対々和", "役牌・場風", "役牌・自風",
			[bakaze, jikaze](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->KeziCount[BambooOne] >= 1) &&
					(analysis->KeziCount[CircleOne] >= 1) &&
					(analysis->KeziCount[CircleFive] >= 1) &&
					(bakaze(analysis) || jikaze(analysis)));
			}
		));
	/* 東北自動車道 */
	if (getRule(RULE_TOHOKU_EXPWY) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"東北自動車道", yaku::yakuCalculator::Yaku::yval_yakuman,
			"対々和", "混一色",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->DuiziCount[CircleTwo] >= 1) &&
					(analysis->DuiziCount[CircleFour] >= 1) &&
					(analysis->DuiziCount[CircleSix] >= 1) &&
					(analysis->DuiziCount[EastWind] >= 1) &&
					(analysis->DuiziCount[NorthWind] >= 1));
			}
		));
	/* 東関東自動車道 */
	if (getRule(RULE_HIGASHIKANTO_EXPWY) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"東関東自動車道", yaku::yakuCalculator::Yaku::yval_yakuman,
			"対々和", "混一色",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->DuiziCount[CircleTwo] >= 1) &&
					(analysis->DuiziCount[CircleFour] >= 1) &&
					(analysis->DuiziCount[CircleSix] >= 1) &&
					(analysis->DuiziCount[EastWind] >= 1) &&
					(analysis->DuiziCount[WestWind] >= 1));
			}
		));
	/* 中国系のおめでたい役 */
	if (getRule(RULE_KOUKEI_HOUGYOU) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"紅鶏報暁", yaku::yakuCalculator::Yaku::yval_yakuman,
			"対々和", "混一色", "絶一門", "役牌・白", "役牌・中", "金鶏報暁", "銀鶏報春",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->analysis->MianziDat[0].tile == CircleOne) &&
					(analysis->KeziCount[BambooOne] >= 1) &&
					(analysis->KeziCount[EastWind] >= 1) &&
					(analysis->KeziCount[WhiteDragon] >= 1) &&
					(analysis->KeziCount[RedDragon] >= 1));
			}
		));
	if (getRule(RULE_KINKEI_HOUGYOU) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"金鶏報暁", yaku::yakuCalculator::Yaku::yval_3han,
			"役牌・中",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->KeziCount[BambooOne] >= 1) &&
					(analysis->KeziCount[EastWind] >= 1) &&
					(analysis->KeziCount[RedDragon] >= 1));
			}
		));
	if (getRule(RULE_GINKEI_HOUSHUN) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"銀鶏報春", yaku::yakuCalculator::Yaku::yval_5han,
			"役牌・白",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				return ((analysis->KeziCount[BambooOne] >= 1) &&
					(analysis->KeziCount[EastWind] >= 1) &&
					(analysis->KeziCount[WhiteDragon] >= 1) &&
					(analysis->PlayerStat->FlowerFlag.Spring));
			}
		));

	// ---------------------------------------------------------------------

	/* 四跳牌刻 */
	if (getRule(RULE_SUUCHAOPAIKOH) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"四跳牌刻", yaku::yakuCalculator::Yaku::yval_yakuman,
			"対々和", "跳牌刻",
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				for (int i = 0; i < TILE_SUIT_HONORS; i += TILE_SUIT_STEP)
					for (int k = 1; k <= 9-6; k++)
						if ((analysis->KeziCount[i + k] >= 1) &&
							(analysis->KeziCount[i + k + 2] >= 1) &&
							(analysis->KeziCount[i + k + 4] >= 1) &&
							(analysis->KeziCount[i + k + 6] >= 1))
							yakuFlag = true;
				return yakuFlag;
			}
		));
	/* 跳牌刻 */
	if (getRule(RULE_CHAOPAIKOH) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"跳牌刻", yaku::yakuCalculator::Yaku::yval_2han,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				for (int i = 0; i < TILE_SUIT_HONORS; i += TILE_SUIT_STEP)
					for (int k = 1; k <= 9-4; k++)
						if ((analysis->KeziCount[i + k] >= 1) &&
							(analysis->KeziCount[i + k + 2] >= 1) &&
							(analysis->KeziCount[i + k + 4] >= 1))
							yakuFlag = true;
				return yakuFlag;
			}
		));
	/* 筋牌刻 */
	if (getRule(RULE_CHINPAIKOH) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"筋牌刻", yaku::yakuCalculator::Yaku::yval_2han,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				for (int i = 0; i < TILE_SUIT_HONORS; i += TILE_SUIT_STEP)
					for (int k = 1; k <= 9-6; k++)
						if ((analysis->KeziCount[i + k] >= 1) &&
							(analysis->KeziCount[i + k + 3] >= 1) &&
							(analysis->KeziCount[i + k + 6] >= 1))
							yakuFlag = true;
				return yakuFlag;
			}
		));
	/* 頂三刻 */
	if (getRule(RULE_TINSANKOH) != 0)
		yaku::yakuCalculator::YakuCatalog::Instantiate()->catalog.push_back(Yaku(
			"頂三刻", yaku::yakuCalculator::Yaku::yval_2han,
			[](const MENTSU_ANALYSIS* const analysis) -> bool {
				bool yakuFlag = false;
				for (int i = 0; i < TILE_SUIT_HONORS; i += TILE_SUIT_STEP)
					if ((analysis->KeziCount[i + 1] >= 1) &&
						(analysis->KeziCount[i + 5] >= 1) &&
						(analysis->KeziCount[i + 9] >= 1))
						yakuFlag = true;
				return yakuFlag;
			}
		));
}
