﻿#pragma once

#include "../common/strcode.h"
#include "gametbl.h"
#include "func.h"
#include "discard.h"
#include "endtype.h"
#include "largenum.h"
#include <array>

// 牌譜関係のコードはクラスに隔離しておきましょうか。
class haifu {
private:
	static const unsigned StringElemSize =
#ifdef _UNICODE
		1u;
#else
		2u;
#endif

	/* 雀牌の名前データ */
	static const CodeConv::tstring tilecodelabel, HTtilecodelabel1, HTtilecodelabel2;
	static const std::array<CodeConv::tstring, TileFlowerMax> Xtilerefcode;

	static InfoByPlayer<LNum> origPoint;
	static CodeConv::tostringstream haifuBuffer, HThaifuBuffer, XMLhaifuBuffer, XhaifuBuffer, XhaifuBufferBody;
	static bool haifukanflag;

	class PlayerStream {
	public:
		CodeConv::tostringstream haipai, tsumo, tsumolabel, sutehai, sutehailabel, final;
		PlayerStream() {};
		PlayerStream(const PlayerStream&) = delete; // Delete unexpected copy constructor
		PlayerStream& operator= (const PlayerStream&) = delete; // Delete unexpected assign operator
	};
	class HaifuStreams {
	public:
		InfoByPlayer<PlayerStream> streamDat;
		CodeConv::tostringstream dora, uraDora, aliceDora, aliceDoraMax, resultDesc;
		HaifuStreams() {}
		HaifuStreams(const HaifuStreams&) = delete; // Delete unexpected copy constructor
		HaifuStreams& operator= (const HaifuStreams&) = delete; // Delete unexpected assign operator
	};
	static HaifuStreams haifuP, HThaifuP, XhaifuP;

	class tools {
	public:
		static const unsigned int cols = 40u;

		static void checkCycle(bool reset = false);

		static void haifuRecTime(CodeConv::tstring tagName);
		static void haifuskipX(PlayerID targetPlayer);
		static void haifuskip(
			HaifuStreams* haifuP, HaifuStreams* HThaifuP,
			PlayerID PassivePlayer, PlayerID ActivePlayer
			);
		static CodeConv::tstring haifudoraClass(doraCol Akadora);
		static CodeConv::tstring haifudoraClassX(doraCol Akadora);
		static void recordDoraStream(CodeConv::tostringstream* const p, CodeConv::tostringstream* const h, CodeConv::tostringstream* const x, TileCode tmpDora);
		static void recordTile_Inline(CodeConv::tostringstream* const p, CodeConv::tostringstream* const h, Tile tlCode, bool rotate);
		static void recordTile_Inline(CodeConv::tostringstream* const p, CodeConv::tostringstream* const h, Tile tlCode, doraCol kakanCol);
		static void recordTile_Table(CodeConv::tostringstream* const p, CodeConv::tostringstream* const h, Tile tlCode, bool omitXml = false, CodeConv::tstring tagName = _T("tile"), bool keepOpen = false);
		static void recordBlank_Table(CodeConv::tostringstream* const p, CodeConv::tostringstream* const h);
		static void haifuwritetsumohai(
			HaifuStreams* haifuP, HaifuStreams* HThaifuP,
			PlayerID ActivePlayer, Tile tlCode,
			CodeConv::tstring PText, CodeConv::tstring HTText, CodeConv::tstring XAttr
			);
		static void haifuskipall(HaifuStreams* haifuP, HaifuStreams* HThaifuP, PlayerID PassivePlayer);

		class kan_sub {
		public:
			static void recordKanOrFlower(
				const GameTable* const gameStat, const DiscardTileNum& DiscardTileIndex,
				HaifuStreams* haifuP, HaifuStreams* HThaifuP
				);
			static void inline recordChanKan(const GameTable* const gameStat, CodeConv::tstring pTxt, CodeConv::tstring hTxt, CodeConv::tstring XAttrA, CodeConv::tstring XAttrB);
			static void inline recordKan(const GameTable* const gameStat, CodeConv::tstring pTxt, CodeConv::tstring hTxt, CodeConv::tstring XAttrA, CodeConv::tstring XAttrB);
		public: /* Monostate class: cannot be instantiated */
			kan_sub() = delete;
			kan_sub(const kan_sub&) = delete;
			kan_sub& operator= (const kan_sub&) = delete;
			~kan_sub() = delete;
		};

		class hfwriter {
		private:
			class finalformWriter {
			private:
				class MeldWriter {
				public:
					static void hfChii(PlayerID player, MeldCode meld);
					static inline void hfPon1(PlayerID player, MeldCode meld);
					static void hfPon(PlayerID player, MeldCode meld);
				public: /* Monostate class: cannot be instantiated */
					MeldWriter() = delete;
					MeldWriter(const MeldWriter&) = delete;
					MeldWriter& operator= (const MeldWriter&) = delete;
					~MeldWriter() = delete;
				};
			public:
				static void hfFinalForm(const GameTable* const gameStat, PlayerID player, EndType RoundEndType);
				static void hfFlower(const GameTable* const gameStat, PlayerID player);
				static void hfExposedMeld(const GameTable* const gameStat, PlayerID player);
			public: /* Monostate class: cannot be instantiated */
				finalformWriter() = delete;
				finalformWriter(const finalformWriter&) = delete;
				finalformWriter& operator= (const finalformWriter&) = delete;
				~finalformWriter() = delete;
			};

			static void hfScoreWriteOut(const GameTable* const gameStat, PlayerID player, seatAbsolute wind);
			static void hfWriteOut(const GameTable* const gameStat, PlayerID player);

		public:
			static void hfWriteHead(const GameTable* const gameStat,
				int OrigTurn, int OrigHonba, bool tmpUraFlag, bool tmpAliceFlag,
				CodeConv::tstring ResultDesc, EndType RoundEndType);

			static void hfWriteFinalForms(const GameTable* const gameStat, int OrigTurn, EndType RoundEndType);
			static void hfWriteBottom();
		public: /* Monostate class: cannot be instantiated */
			hfwriter() = delete;
			hfwriter(const hfwriter&) = delete;
			hfwriter& operator= (const hfwriter&) = delete;
			~hfwriter() = delete;
		};
	public: /* Monostate class: cannot be instantiated */
		tools() = delete;
		tools(const tools&) = delete;
		tools& operator= (const tools&) = delete;
		~tools() = delete;
	};

public:
	static void haifubufinit();
	static void haifuinit();

	static void haifurechaipai(const GameTable* const gameStat);

	static void haifurecdora(TileCode tmpDora);
	static void haifurecuradora(TileCode tmpDora);

	static void haifurecalicedora(TileCode tmpDora);
	static void haifualicedoraupd();
	static void haifuresetalicedora();

	static void haifurecdorap();

	static void haifurecmota(const GameTable* const gameStat, const DiscardTileNum& DiscardTileIndex);

	static void haifurecfurikomi(const GameTable* const gameStat);

	static void haifurecchi(const GameTable* const gameStat);
	static void haifurecpon(const GameTable* const gameStat);
	static void haifurectsumo(const GameTable* const gameStat);
	static void haifurecminkan(const GameTable* const gameStat);

	static void haifurecnorth(const GameTable* const gameStat, const DiscardTileNum& DiscardTileIndex);
	static void haifurecchanpei(const GameTable* const gameStat);
	static void haifurecnorthproc(const GameTable* const gameStat);

	static void haifurecankan(const GameTable* const gameStat, const DiscardTileNum& DiscardTileIndex);
	static void haifurecchankan(const GameTable* const gameStat);
	static void haifureckanproc(const GameTable* const gameStat);

	static void haifurecflower(const GameTable* const gameStat, const DiscardTileNum& DiscardTileIndex);

	static void haifuwritebuffer(
		const GameTable* const gameStat,
		int OrigTurn, int OrigHonba, bool tmpUraFlag, bool tmpAliceFlag,
		LPCTSTR ResultDesc, EndType RoundEndType);

	static void haifusave(const GameTable* const gameStat);

public: /* Monostate class: cannot be instantiated */
	haifu() = delete;
	haifu(const haifu&) = delete;
	haifu& operator= (const haifu&) = delete;
	~haifu() = delete;
};
