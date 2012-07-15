#include "yaku.h"

namespace yaku {
	/* �\���̂̃T�C�Y��Ԃ� */
	int YAKUSTAT::getSize() {
		return sizeof(YAKUSTAT);
	}

	/* �����̃C���X�^���X������������ */
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

	/* HSP����̃A�N�Z�T */
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
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "�y�[�W���Ⴂ�܂�");
		}
	}
	void YAKUSTAT::setYakuInfo(YAKUSTAT* const myInstance, int index, const char* const value) {
		switch (index) {
			case 17: strcpy_s(myInstance->yakuNameList, 1024, value); break;
			case 18: strcpy_s(myInstance->yakuValList, 1024, value); break;
			case 19: strcpy_s(myInstance->yakumanNameList, 1024, value); break;
			case 20: strcpy_s(myInstance->yakumanValList, 1024, value); break;
			default:
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "�y�[�W���Ⴂ�܂�");
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
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "�y�[�W���Ⴂ�܂�");
		}
	}
	void YAKUSTAT::addYakuInfo(YAKUSTAT* const myInstance, int index, const char* const value) {
		switch (index) {
			case 17: strcat_s(myInstance->yakuNameList, 1024, value); break;
			case 18: strcat_s(myInstance->yakuValList, 1024, value); break;
			case 19: strcat_s(myInstance->yakumanNameList, 1024, value); break;
			case 20: strcat_s(myInstance->yakumanValList, 1024, value); break;
			default:
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "�y�[�W���Ⴂ�܂�");
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
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "�y�[�W���Ⴂ�܂�");
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
				RaiseTolerant(EXCEPTION_MJCORE_INVALID_ARGUMENT, "�y�[�W���Ⴂ�܂�");
				memset(targetStr, 0, bufSize);
		}
	}

	// ---------------------------------------------------------------------

	namespace mentsuParser { // �ʎq�p�[�T

		/* ���q�̏��� */
		bool makementsu_shuntsu(Int8ByTile& countForMentsu, MELD_BUF MianziDat,
			int* const ProcessedMelds, tileCode tile)
		{ /* ���q�̏��� */
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

		/* ���q�̏��� */
		void makementsu_koutsu(Int8ByTile& countForMentsu, MELD_BUF MianziDat,
			int* const ProcessedMelds, tileCode tile)
		{ /* ���q�̏��� */
			if (countForMentsu[tile] >= 3) {
				MianziDat[*ProcessedMelds].mstat = meldTripletConcealed;
				MianziDat[(*ProcessedMelds)++].tile = tile;
				countForMentsu[tile] -= 3;
			}
			return;
		}

		/* �ʎq�ɕ������� */
		void makementsu(const GameTable* const gameStat,
			PLAYER_ID targetPlayer, ParseMode AtamaCode,
			int* const ProcessedMelds, MELD_BUF MianziDat)
		{ /* �ʎq�ɕ������� */
			memset(MianziDat, 0, sizeof(MELD_BUF)); // ������
			auto countForMentsu = countTilesInHand(gameStat, targetPlayer);
			*ProcessedMelds = 0;

			// �����ƂȂ蓾�Ȃ��v�Ȃ�߂�
			if (countForMentsu[AtamaCode.AtamaCode] < 2) return;
			MianziDat[0].tile = AtamaCode.AtamaCode; (*ProcessedMelds)++;
			countForMentsu[AtamaCode.AtamaCode] -= 2;

			// ���q(���q�D�搳�����[�h�̎�)
			if (AtamaCode.Order == Shun_Ke)
				for (int i = 1; i < TILE_SUIT_HONORS; i++)
					if (makementsu_shuntsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i))
						--i;
			// ���q(���q�D��t�����[�h�̎�)
			if (AtamaCode.Order == Shun_Ke_Rev)
				for (int i = TILE_SUIT_HONORS - 1; i > 0; i--)
					if (makementsu_shuntsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i))
						++i;

			// �Í�(�������[�h�̎�)
			if ((AtamaCode.Order == Ke_Shun)||(AtamaCode.Order == Shun_Ke))
				for (int i = 1; i < TILE_NONFLOWER_MAX; i++)
					makementsu_koutsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i);
			// �Í�(�t�����[�h�̎�)
			if ((AtamaCode.Order == Ke_Shun_Rev)||(AtamaCode.Order == Shun_Ke_Rev))
				for (int i = TILE_NONFLOWER_MAX - 1; i > 0; i--)
					makementsu_koutsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i);

			// ���q(�Í��D�搳�����[�h�̎�)
			if (AtamaCode.Order == Ke_Shun)
				for (int i = 1; i < TILE_SUIT_HONORS; i++)
					if (makementsu_shuntsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i))
						--i;
			// ���q(�Í��D��t�����[�h�̎�)
			if (AtamaCode.Order == Ke_Shun_Rev)
				for (int i = TILE_SUIT_HONORS - 1; i > 0; i--)
					if (makementsu_shuntsu(countForMentsu, MianziDat, ProcessedMelds, (tileCode)i))
						++i;

			// �����ʎq�A�Þ�
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
		/* �w��̑Ύq�����邩������ */
		int countPairs(
			const Int8ByTile tileCount, const tileCode* const targetTiles, int numOfTiles)
		{
			// �w�肵����ނ̑Ύq�𐔂���
			trace("�Ύq�̎�ނ𒲂ׂ܂��B");
			int yakuflagcount = 0;
			for (int i = 0; i < numOfTiles; i++)
				if (tileCount[targetTiles[i]] >= 2) yakuflagcount++;
			return yakuflagcount;
		}

		/* �����̍��v�𐔂���(���Ύq��) */
		int countTileNumerals(const Int8ByTile tileCount) {
			/* �����̍��v�𐔂��� */
			int Cifr = 0;
			for (int i = 1; i < (TILE_SUIT_HONORS - 1); i++)
				Cifr += tileCount[i] * (i % TILE_SUIT_STEP);
			return Cifr;
		}
	
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

		/* �v���p�֐� */
		Int8ByTile countByMelds(
			const MELD_BUF MianziDat, int* const hits,
			std::function<bool (meldStat)> f)
		{ // �v�����[�`��
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

		/* ���q�̐��𐔂��� */
		Int8ByTile countKez(const MELD_BUF MianziDat, int* const Kezi) { /* ���q�̐��𐔂��� */
			trace("���q�E�Ȏq�̎�ނ𒲂ׂ܂��B");
			return countByMelds(MianziDat, Kezi, [](meldStat x){return x >= meldTripletConcealed;});
		}

		/* �Í��q�̐��𐔂��� */
		Int8ByTile countAnKez(const MELD_BUF MianziDat, int* const Kezi) { /* �Í��q�̐��𐔂��� */
			trace("�Í��q�E�ÞȎq�̎�ނ𒲂ׂ܂��B");
			return countByMelds(MianziDat, Kezi, [](meldStat x){return ((x == meldTripletConcealed)||(x == meldQuadConcealed));});
		}

		/* �Ύq�E���q�E�Ȏq�̐��𐔂��� */
		Int8ByTile countDuiz(const MELD_BUF MianziDat) { /* �Ύq�E���q�E�Ȏq�̐��𐔂��� */
			trace("�Ύq�E���q�E�Ȏq�̎�ނ𒲂ׂ܂��B");
			auto DuiCount = countKez(MianziDat, NULL);
			++(DuiCount[MianziDat[0].tile]);
			return DuiCount;
		}

		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

		/* ���q�̐��𐔂��� */
		Int8ByTile countShunz(const MELD_BUF MianziDat) { /* ���q�̐��𐔂��� */
			trace("���q�̎�ނ𒲂ׂ܂��B");
			return countByMelds(MianziDat, NULL, [](meldStat x){return x < meldTripletConcealed;});
		}

		/* �Ï��q�̐��𐔂��� */
		Int8ByTile countAnShunz(const MELD_BUF MianziDat) { /* �Ï��q�̐��𐔂��� */
			trace("�Ï��q�̎�ނ𒲂ׂ܂��B");
			return countByMelds(MianziDat, NULL, [](meldStat x){return x == meldSequenceConcealed;});
		}

		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

		/* �Ȏq�̐��𐔂��� */
		Int8ByTile countKangz(const MELD_BUF MianziDat, int* const Kangzi) { /* �Ȏq�̐��𐔂��� */
			trace("�Ȏq�̎�ނ𒲂ׂ܂��B");
			return countByMelds(MianziDat, Kangzi, [](meldStat x){return x >= meldQuadConcealed;});
		}

		/* �ÞȎq�̐��𐔂��� */
		Int8ByTile countAnKangz(const MELD_BUF MianziDat, int* const Kangzi) { /* �ÞȎq�̐��𐔂��� */
			trace("�ÞȎq�̎�ނ𒲂ׂ܂��B");
			return countByMelds(MianziDat, Kangzi, [](meldStat x){return x == meldQuadConcealed;});
		}

		/* ���Ȃ̐��𐔂��� */
		Int8ByTile countKaKangz(const MELD_BUF MianziDat, int* const Kangzi) { /* ���Ȃ̐��𐔂��� */
			trace("���Ȃ̎�ނ𒲂ׂ܂��B");
			return countByMelds(MianziDat, Kangzi, [](meldStat x){return x >= meldQuadAddedLeft;});
		}

		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

		/* �w��̍��q�E���q�����邩������ */
		int countSpecMentz(const MELD_BUF MianziDat, const tileCode* const targetKez, int numOfKez,
			const tileCode* const targetShunz, int numOfShunz, bool Mode)
		{ // �w�肵����ނ̖ʎq�𐔂���
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

		/* �����̍��v�𐔂��� */
		int countMentzNumerals(const MELD_BUF MianziDat) { /* �����̍��v�𐔂��� */
			int Cifr = 0;
			for (int i = 0; i < SIZE_OF_MELD_BUFFER; i++) {
				if (MianziDat[i].tile % TILE_CODE_MAXIMUM < TILE_SUIT_HONORS) {
					if (i == 0) { // ����
						Cifr += (MianziDat[0].tile % TILE_SUIT_STEP) * 2;
					} else { // �ʎq
						switch (MianziDat[i].mstat) {
						case meldSequenceConcealed: case meldSequenceExposedLower:
						case meldSequenceExposedMiddle: case meldSequenceExposedUpper:
							Cifr += (((MianziDat[i].tile % TILE_SUIT_STEP)+1) * 3); // ���q
							break;
						case meldTripletConcealed: case meldTripletExposedLeft:
						case meldTripletExposedCenter: case meldTripletExposedRight:
							Cifr += ((MianziDat[i].tile % TILE_SUIT_STEP) * 3); // ���q
							break;
						default:
							Cifr += ((MianziDat[i].tile % TILE_SUIT_STEP) * 4); // �Ȏq
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

		// �ݒ肵�����[���Ɋ�Â��Ė��C���X�^���X������������
		__declspec(dllexport) void init() {
			YakuCatalog::Instantiate()->catalog.clear(); // ���Z�b�g
			info("���J�^���O�����Z�b�g���܂����B");
			/*
			 * �����ɃR���X�g���N�^����ׂ�
			 */
			YakuCatalog::Instantiate()->catalog.push_back(Yaku( // �e�X�g�p�̃_�~�[�̖�
				"�_�~�[", Yaku::YAKU_HAN(1, Han), Yaku::YAKU_HAN(),
				[](){return true;}
			));
			info("���J�^���O�̍\�z���������܂����B");
		}

		YAKUSTAT countyaku(const GameTable* const gameStat, PLAYER_ID targetPlayer) {
			// �𔻒�
			std::ostringstream o;
			o << "�𔻒菈�����J�n �v���C���[ [" << (int)targetPlayer << "]";
			debug(o.str().c_str());
			// ������
			YAKUSTAT yakuInfo; YAKUSTAT::Init(&yakuInfo);
			// �a�����Ă邩����
			if (calcShanten(gameStat, targetPlayer, shantenAll) > -1) {
				trace("�a�����Ă��Ȃ��̂Ŕ����܂�");
				return yakuInfo;
			}
			// �a�����Ă���Ȃ�
			if (calcShanten(gameStat, targetPlayer, shantenRegular) == -1) {
				// ��ʌ`�̘a��
			} else {
				// ���Ύq�A���m���o�A���̑�����Șa��
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