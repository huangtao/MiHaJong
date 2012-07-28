#ifndef YAKU_H
#define YAKU_H

#include <cstring>
#include <type_traits>
#include <functional>
#include "largenum.h"
#include "gametbl.h"
#include "tileutil.h"

namespace yaku {
	EXPORT_STRUCT YAKUSTAT {
		int BasePoints; // ��
		int CoreHan; // �|
		int BonusHan; // �|�i����𖞂����Ȃ��j
		int DoraQuantity; // �h���̐�
		int UraDoraQuantity; // ���h���̐�
		int AkaDoraQuantity; // �ԃh���̐�
		int AoDoraQuantity; // �h���̐�
		int AliceDora; // �A���X�h���̐�
		int FlowerQuantity; // �Ԕv�̐�
		LargeNum AgariPoints; // ���v�a���_
		char yakuNameList[1024];
		char yakuValList[1024];
		char yakumanNameList[1024];
		char yakumanValList[1024];
		// -----------------------------------------------------------------
		MELD_BUF MianziDat; // �ʎq�ɕ��������f�[�^
		// -----------------------------------------------------------------
		static int getSize(); // �\���̂̃T�C�Y��Ԃ�
		static void Init(YAKUSTAT* const myInstance); // �C���X�^���X������������
		static void exportYakuPoint(const YAKUSTAT* const myInstance, int* const exportArray);
		static void setYakuInfo(YAKUSTAT* const myInstance, int index, int value);
		static void setYakuInfo(YAKUSTAT* const myInstance, int index, const char* const value);
		static void addYakuInfo(YAKUSTAT* const myInstance, int index, int value);
		static void addYakuInfo(YAKUSTAT* const myInstance, int index, const char* const value);
		static int getYakuInfo(const YAKUSTAT* const myInstance, int index);
		static void getYakuInfo(const YAKUSTAT* const myInstance, int index, char* const targetStr, int bufSize);
	};
#ifdef MJCORE_EXPORTS
	static_assert(std::is_pod<YAKUSTAT>::value, "YAKUSTAT is not POD");
#endif

	// ---------------------------------------------------------------------

	enum ParseOrder : uint8_t {
		Ke_Shun, Shun_Ke, Ke_Shun_Rev, Shun_Ke_Rev
	};
	struct ParseMode {
		tileCode AtamaCode;
		ParseOrder Order;
	};

#ifdef MJCORE_EXPORTS
	static_assert(std::is_pod<ParseMode>::value, "ParseMode is not POD");
#endif

	// ---------------------------------------------------------------------

	namespace mentsuParser { // �ʎq�p�[�T
		bool makementsu_shuntsu(Int8ByTile& countForMentsu, MELD_BUF MianziDat,
			int* const ProcessedMelds, tileCode tile); /* ���q�̏��� */
		void makementsu_koutsu(Int8ByTile& countForMentsu, MELD_BUF MianziDat,
			int* const ProcessedMelds, tileCode tile); /* ���q�̏��� */

		void makementsu(const GameTable* const gameStat,
			PLAYER_ID targetPlayer, ParseMode AtamaCode,
			int* const ProcessedMelds, MELD_BUF MianziDat); /* �ʎq�ɕ������� */
		__declspec(dllexport) void makementsu(const GameTable* const gameStat,
			int targetPlayer, int AtamaCode, int* const ProcessedMelds, void* const MianziDat);

		void inline ReadAgainMentsu(MELD_BUF target, const int* const source); /* �t�ϊ� */
	}

	// ---------------------------------------------------------------------

	namespace countingFacility {
		int countPairs(
			const Int8ByTile tileCount, const tileCode* const targetTiles, int numOfTiles);
		__declspec(dllexport) int countPairs(
			const int* const tileCount, const int* const targetTiles, int numOfTiles);
		int countTileNumerals(const Int8ByTile tileCount);
		__declspec(dllexport) int countTileNumerals(const int* const tileCount);

		Int8ByTile countByMelds(
			const MELD_BUF MianziDat, int* const hits,
			std::function<bool (meldStat)> f);

		Int8ByTile countKez(const MELD_BUF MianziDat, int* const Kezi);
		__declspec(dllexport) int countKez(int* const KezCount, const int* const MianziDat);
		Int8ByTile countAnKez(const MELD_BUF MianziDat, int* const Kezi);
		__declspec(dllexport) int countAnKez(int* const KezCount, const int* const MianziDat);
		Int8ByTile countDuiz(const MELD_BUF MianziDat);
		__declspec(dllexport) void countDuiz(int* const DuiCount, const int* const MianziDat);

		Int8ByTile countShunz(const MELD_BUF MianziDat);
		__declspec(dllexport) void countShunz(int* const ShunzCount, const int* const MianziDat);
		Int8ByTile countAnShunz(const MELD_BUF MianziDat);
		__declspec(dllexport) void countAnShunz(int* const ShunzCount, const int* const MianziDat);

		Int8ByTile countKangz(const MELD_BUF MianziDat, int* const Kangzi);
		__declspec(dllexport) int countKangz(int* const KangzCount, const int* const MianziDat);
		Int8ByTile countAnKangz(const MELD_BUF MianziDat, int* const Kangzi);
		__declspec(dllexport) int countAnKangz(int* const KangzCount, const int* const MianziDat);
		Int8ByTile countKaKangz(const MELD_BUF MianziDat, int* const Kangzi);
		__declspec(dllexport) int countKaKangz(int* const KangzCount, const int* const MianziDat);

		int countSpecMentz(const MELD_BUF MianziDat, const tileCode* const targetKez, int numOfKez,
			const tileCode* const targetShunz, int numOfShunz, bool Mode);
		__declspec(dllexport) int countSpecMentz(const int* const MianziDat,
			int* const targetKez, int numOfKez, int* const targetShunz, int numOfShunz, int Mode);
		int countMentzNumerals(const MELD_BUF MianziDat);
		__declspec(dllexport) int countMentzNumerals(const int* const MianziDat);
	}
}

#endif