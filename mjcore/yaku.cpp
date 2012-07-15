#include "yaku.h"

namespace yaku {
	/* 構造体のサイズを返す */
	int YAKUSTAT::getSize() {
		return sizeof(YAKUSTAT);
	}

	/* 既存のインスタンスを初期化する */
	void YAKUSTAT::Init(YAKUSTAT* const myInstance) {
		myInstance->isValid = false;
		myInstance->BasePoints = 20;
		myInstance->CoreHan = myInstance->BonusHan =
			myInstance->DoraQuantity = myInstance->UraDoraQuantity =
			myInstance->AkaDoraQuantity = myInstance->AoDoraQuantity =
			myInstance->AliceDora = myInstance->FlowerQuantity = 0;
		myInstance->AgariPoints = LargeNum::fromInt(0);
		memset(myInstance->yakuNameList, 0, 1024);
		memset(myInstance->yakuValList, 0, 1024);
		memset(myInstance->yakumanNameList, 0, 1024);
		memset(myInstance->yakumanValList, 0, 1024);
	}

	/* HSPからのアクセサ */
	void YAKUSTAT::exportYakuPoint(const YAKUSTAT* const myInstance, int* const exportArray) {
		for (int i = 0; i < DIGIT_GROUPS; i++)
			*(exportArray + i) =
				myInstance->AgariPoints.digitGroup[i] /
				(i ? 1 : (signed int)(100000000u / myInstance->AgariPoints.firstArg));
	}

	void YAKUSTAT::setYakuInfo(YAKUSTAT* const myInstance, int index, int value) {
		switch (index) {
			case 0: myInstance->BasePoints = value; break;
			case 1: myInstance->CoreHan = value; break;
			case 2: myInstance->BonusHan = value; break;
			case 3: myInstance->DoraQuantity = value; break;
			case 4: myInstance->UraDoraQuantity = value; break;
			case 5: myInstance->AkaDoraQuantity = value; break;
			case 6: myInstance->AoDoraQuantity = value; break;
			case 7: myInstance->AliceDora = value; break;
			case 8: myInstance->FlowerQuantity = value; break;
			case 9: case 10: case 11: case 12:
			case 13: case 14: case 15: case 16:
				myInstance->AgariPoints.digitGroup[index - 9] = value;
				break;
			default:
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "ページが違います");
		}
	}
	void YAKUSTAT::setYakuInfo(YAKUSTAT* const myInstance, int index, const char* const value) {
		switch (index) {
			case 17: strcpy_s(myInstance->yakuNameList, 1024, value); break;
			case 18: strcpy_s(myInstance->yakuValList, 1024, value); break;
			case 19: strcpy_s(myInstance->yakumanNameList, 1024, value); break;
			case 20: strcpy_s(myInstance->yakumanValList, 1024, value); break;
			default:
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "ページが違います");
		}
	}

	void YAKUSTAT::addYakuInfo(YAKUSTAT* const myInstance, int index, int value) {
		switch (index) {
			case 0: myInstance->BasePoints += value; break;
			case 1: myInstance->CoreHan += value; break;
			case 2: myInstance->BonusHan += value; break;
			case 3: myInstance->DoraQuantity += value; break;
			case 4: myInstance->UraDoraQuantity += value; break;
			case 5: myInstance->AkaDoraQuantity += value; break;
			case 6: myInstance->AoDoraQuantity += value; break;
			case 7: myInstance->AliceDora += value; break;
			case 8: myInstance->FlowerQuantity += value; break;
			case 9: case 10: case 11: case 12:
			case 13: case 14: case 15: case 16:
				myInstance->AgariPoints.digitGroup[index - 9] += value;
				break;
			default:
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "ページが違います");
		}
	}
	void YAKUSTAT::addYakuInfo(YAKUSTAT* const myInstance, int index, const char* const value) {
		switch (index) {
			case 17: strcat_s(myInstance->yakuNameList, 1024, value); break;
			case 18: strcat_s(myInstance->yakuValList, 1024, value); break;
			case 19: strcat_s(myInstance->yakumanNameList, 1024, value); break;
			case 20: strcat_s(myInstance->yakumanValList, 1024, value); break;
			default:
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "ページが違います");
		}
	}

	int YAKUSTAT::getYakuInfo(const YAKUSTAT* const myInstance, int index) {
		switch (index) {
			case 0: return myInstance->BasePoints;
			case 1: return myInstance->CoreHan;
			case 2: return myInstance->BonusHan;
			case 3: return myInstance->DoraQuantity;
			case 4: return myInstance->UraDoraQuantity;
			case 5: return myInstance->AkaDoraQuantity;
			case 6: return myInstance->AoDoraQuantity;
			case 7: return myInstance->AliceDora;
			case 8: return myInstance->FlowerQuantity;
			case 9: case 10: case 11: case 12:
			case 13: case 14: case 15: case 16:
				return myInstance->AgariPoints.digitGroup[index - 9];
			default:
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "ページが違います");
				return 0x7fffffff;
		}
	}
	void YAKUSTAT::getYakuInfo(const YAKUSTAT* const myInstance,
		int index, char* const targetStr, int bufSize)
	{
		switch (index) {
			case 17: strcpy_s(targetStr, bufSize, myInstance->yakuNameList); break;
			case 18: strcpy_s(targetStr, bufSize, myInstance->yakuValList); break;
			case 19: strcpy_s(targetStr, bufSize, myInstance->yakumanNameList); break;
			case 20: strcpy_s(targetStr, bufSize, myInstance->yakumanValList); break;
			default:
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "ページが違います");
				memset(targetStr, 0, bufSize);
		}
	}

	// ---------------------------------------------------------------------

	namespace mentsuParser { // 面子パーサ

		/* 順子の処理 */
		bool makementsu_shuntsu(Int8ByTile& countForMentsu, MELD_BUF MianziDat,
			int* const ProcessedMelds, tileCode tile)
		{ /* 順子の処理 */
			if ((countForMentsu[tile] >= 1)&&
				(countForMentsu[tile+1] >= 1)&&
				(countForMentsu[tile+2] >= 1)) {
					MianziDat[*ProcessedMelds].mstat = meldSequenceConcealed;
					MianziDat[(*ProcessedMelds)++].tile = tile;
					--countForMentsu[tile]; --countForMentsu[tile+1];
					--countForMentsu[tile+2];
					return true;
			}
			return false;
		}

		/* 刻子の処理 */
		void makementsu_koutsu(Int8ByTile& countForMentsu, MELD_BUF MianziDat,
			int* const ProcessedMelds, tileCode tile)
		{ /* 刻子の処理 */
			if (countForMentsu[tile] >= 3) {
				MianziDat[*ProcessedMelds].mstat = meldTripletConcealed;
				MianziDat[(*ProcessedMelds)++].tile = tile;
				countForMentsu[tile] -= 3;
			}
			return;
		}

		/* 面子に分解する */
		void makementsu(const GameTable* const gameStat,
			PLAYER_ID targetPlayer, ParseMode AtamaCode,
			int* const ProcessedMelds, MELD_BUF MianziDat)
		{ /* 面子に分解する */
			memset(MianziDat, 0, sizeof(MELD_BUF)); // 初期化
			auto countForMentsu = countTilesInHand(gameStat, targetPlayer);
			*ProcessedMelds = 0;

			// 雀頭となり得ない牌なら戻る
			if (countForMentsu[AtamaCode.AtamaCode] < 2) return;
			MianziDat[0].tile = AtamaCode.AtamaCode; (*ProcessedMelds)++;
			countForMentsu[AtamaCode.AtamaCode] -= 2;

			// 順子(順子優先正順モードの時)
			if (AtamaCode.Order == Shun_Ke)
				for (int i = 1; i < TILE_SUIT_HONORS; i++)
					if (makementsu_shuntsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i))
						--i;
			// 順子(順子優先逆順モードの時)
			if (AtamaCode.Order == Shun_Ke_Rev)
				for (int i = TILE_SUIT_HONORS - 1; i > 0; i--)
					if (makementsu_shuntsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i))
						++i;

			// 暗刻(正順モードの時)
			if ((AtamaCode.Order == Ke_Shun)||(AtamaCode.Order == Shun_Ke))
				for (int i = 1; i < TILE_NONFLOWER_MAX; i++)
					makementsu_koutsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i);
			// 暗刻(逆順モードの時)
			if ((AtamaCode.Order == Ke_Shun_Rev)||(AtamaCode.Order == Shun_Ke_Rev))
				for (int i = TILE_NONFLOWER_MAX - 1; i > 0; i--)
					makementsu_koutsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i);

			// 順子(暗刻優先正順モードの時)
			if (AtamaCode.Order == Ke_Shun)
				for (int i = 1; i < TILE_SUIT_HONORS; i++)
					if (makementsu_shuntsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i))
						--i;
			// 順子(暗刻優先逆順モードの時)
			if (AtamaCode.Order == Ke_Shun_Rev)
				for (int i = TILE_SUIT_HONORS - 1; i > 0; i--)
					if (makementsu_shuntsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i))
						++i;

			// 鳴いた面子、暗槓
			for (int i = 1; i <= gameStat->Player[targetPlayer].MeldPointer; i++) {
				MianziDat[*ProcessedMelds].mstat = gameStat->Player[targetPlayer].Meld[i].mstat;
				MianziDat[*ProcessedMelds].tile = gameStat->Player[targetPlayer].Meld[i].tile;
				/*for (int j = 0; j < 4; j++)
					MianziDat[*ProcessedMelds].red[j] = gameStat->Player[targetPlayer].Meld[i].red[j];*/
				++(*ProcessedMelds);
			}
		}
	}

	// ---------------------------------------------------------------------

	namespace countingFacility {
		/* 指定の対子があるか数える */
		int countPairs(
			const Int8ByTile tileCount, const tileCode* const targetTiles, int numOfTiles)
		{
			// 指定した種類の対子を数える
			trace("対子の種類を調べます。");
			int yakuflagcount = 0;
			for (int i = 0; i < numOfTiles; i++)
				if (tileCount[targetTiles[i]] >= 2) yakuflagcount++;
			return yakuflagcount;
		}

		/* 数字の合計を数える(七対子版) */
		int countTileNumerals(const Int8ByTile tileCount) {
			/* 数字の合計を数える */
			int Cifr = 0;
			for (int i = 1; i < (TILE_SUIT_HONORS - 1); i++)
				Cifr += tileCount[i] * (i % TILE_SUIT_STEP);
			return Cifr;
		}
	
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

		/* 計数用関数 */
		Int8ByTile countByMelds(
			const MELD_BUF MianziDat, int* const hits,
			std::function<bool (meldStat)> f)
		{ // 計数ルーチン
			Int8ByTile hitCount; memset(&hitCount, 0, sizeof(hitCount));
			if (hits != NULL) *hits = 0;
			for (int i = 1; i < SIZE_OF_MELD_BUFFER; i++) {
				if (f(MianziDat[i].mstat)&&(MianziDat[i].tile != NoTile)) {
					++(hitCount[MianziDat[i].tile]);
					if (hits != NULL) ++(*hits);
				}
			}
			return hitCount;
		}

		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

		/* 刻子の数を数える */
		Int8ByTile countKez(const MELD_BUF MianziDat, int* const Kezi) { /* 刻子の数を数える */
			trace("刻子・槓子の種類を調べます。");
			return countByMelds(MianziDat, Kezi, [](meldStat x){return x >= meldTripletConcealed;});
		}

		/* 暗刻子の数を数える */
		Int8ByTile countAnKez(const MELD_BUF MianziDat, int* const Kezi) { /* 暗刻子の数を数える */
			trace("暗刻子・暗槓子の種類を調べます。");
			return countByMelds(MianziDat, Kezi, [](meldStat x){return ((x == meldTripletConcealed)||(x == meldQuadConcealed));});
		}

		/* 対子・刻子・槓子の数を数える */
		Int8ByTile countDuiz(const MELD_BUF MianziDat) { /* 対子・刻子・槓子の数を数える */
			trace("対子・刻子・槓子の種類を調べます。");
			auto DuiCount = countKez(MianziDat, NULL);
			++(DuiCount[MianziDat[0].tile]);
			return DuiCount;
		}

		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

		/* 順子の数を数える */
		Int8ByTile countShunz(const MELD_BUF MianziDat) { /* 順子の数を数える */
			trace("順子の種類を調べます。");
			return countByMelds(MianziDat, NULL, [](meldStat x){return x < meldTripletConcealed;});
		}

		/* 暗順子の数を数える */
		Int8ByTile countAnShunz(const MELD_BUF MianziDat) { /* 暗順子の数を数える */
			trace("暗順子の種類を調べます。");
			return countByMelds(MianziDat, NULL, [](meldStat x){return x == meldSequenceConcealed;});
		}

		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

		/* 槓子の数を数える */
		Int8ByTile countKangz(const MELD_BUF MianziDat, int* const Kangzi) { /* 槓子の数を数える */
			trace("槓子の種類を調べます。");
			return countByMelds(MianziDat, Kangzi, [](meldStat x){return x >= meldQuadConcealed;});
		}

		/* 暗槓子の数を数える */
		Int8ByTile countAnKangz(const MELD_BUF MianziDat, int* const Kangzi) { /* 暗槓子の数を数える */
			trace("暗槓子の種類を調べます。");
			return countByMelds(MianziDat, Kangzi, [](meldStat x){return x == meldQuadConcealed;});
		}

		/* 加槓の数を数える */
		Int8ByTile countKaKangz(const MELD_BUF MianziDat, int* const Kangzi) { /* 加槓の数を数える */
			trace("加槓の種類を調べます。");
			return countByMelds(MianziDat, Kangzi, [](meldStat x){return x >= meldQuadAddedLeft;});
		}

		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

		/* 指定の刻子・順子があるか数える */
		int countSpecMentz(const MELD_BUF MianziDat, const tileCode* const targetKez, int numOfKez,
			const tileCode* const targetShunz, int numOfShunz, bool Mode)
		{ // 指定した種類の面子を数える
			int kz = 0; int sz = 0;
			auto DuiCount = Mode ? countKez(MianziDat, NULL) : countDuiz(MianziDat);
			auto ShunzCount = countShunz(MianziDat);
			int yakuflagcount = 0;
			for (int i = 0; i < numOfKez; i++) {
				if (targetKez[i] == NoTile) continue;
				if (DuiCount[targetKez[i]] >= 1) ++yakuflagcount;
			}
			for (int i = 0; i < numOfShunz; i++) {
				if (targetShunz[i] == NoTile) continue;
				if (ShunzCount[targetShunz[i]] >= 1) ++yakuflagcount;
			}
			return yakuflagcount;
		}

		/* 数字の合計を数える */
		int countMentzNumerals(const MELD_BUF MianziDat) { /* 数字の合計を数える */
			int Cifr = 0;
			for (int i = 0; i < SIZE_OF_MELD_BUFFER; i++) {
				if (MianziDat[i].tile % TILE_CODE_MAXIMUM < TILE_SUIT_HONORS) {
					if (i == 0) { // 雀頭
						Cifr += (MianziDat[0].tile % TILE_SUIT_STEP) * 2;
					} else { // 面子
						switch (MianziDat[i].mstat) {
						case meldSequenceConcealed: case meldSequenceExposedLower:
						case meldSequenceExposedMiddle: case meldSequenceExposedUpper:
							Cifr += (((MianziDat[i].tile % TILE_SUIT_STEP)+1) * 3); // 順子
							break;
						case meldTripletConcealed: case meldTripletExposedLeft:
						case meldTripletExposedCenter: case meldTripletExposedRight:
							Cifr += ((MianziDat[i].tile % TILE_SUIT_STEP) * 3); // 刻子
							break;
						default:
							Cifr += ((MianziDat[i].tile % TILE_SUIT_STEP) * 4); // 槓子
							break;
						}
					}
				}
			}
			return Cifr;
		}
	}

	// ---------------------------------------------------------------------

	namespace yakuCalculator {
		
		YakuCatalog* YakuCatalog::Instantiate() {
			// Singleton instance accessor
			static YakuCatalog instance;
			return &instance;
		}

		// 設定したルールに基づいて役インスタンスを初期化する
		__declspec(dllexport) void init() {
			YakuCatalog::Instantiate()->catalog.clear(); // リセット
			info("役カタログをリセットしました。");
			/*
			 * ここにコンストラクタを並べる
			 */
			YakuCatalog::Instantiate()->catalog.push_back(Yaku( // テスト用のダミーの役
				"ダミー", Yaku::YAKU_HAN(1, Han), Yaku::YAKU_HAN(),
				[](){return true;}
			));
			info("役カタログの構築を完了しました。");
		}

		YAKUSTAT countyaku(const GameTable* const gameStat, PLAYER_ID targetPlayer) {
			// 役判定
			std::ostringstream o;
			o << "役判定処理を開始 プレイヤー [" << (int)targetPlayer << "]";
			debug(o.str().c_str());
			// 初期化
			YAKUSTAT yakuInfo; YAKUSTAT::Init(&yakuInfo);
			// 和了ってるか判定
			if (calcShanten(gameStat, targetPlayer, shantenAll) > -1) {
				trace("和了っていないので抜けます");
				return yakuInfo;
			}
			// 和了っているなら
			if (calcShanten(gameStat, targetPlayer, shantenRegular) == -1) {
				// 一般形の和了
			} else {
				// 七対子、国士無双、その他特殊な和了
			}
			return yakuInfo;
		}
		__declspec(dllexport) void countyaku(const GameTable* const gameStat,
			YAKUSTAT* const yakuInfo, int targetPlayer)
		{
			*yakuInfo = countyaku(gameStat, (PLAYER_ID)targetPlayer);
		}

	}
}
