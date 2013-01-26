#include "functbl.h"

#include "../func.h"

bool aiscript::table::functable::gametbl::luafunc::riskchk::issameasprevious
	(const GameTable* const gameStat, PLAYER_ID player, int index) { // 合わせ打ちできるかどうか
		PLAYER_ID prev_p = RelativePositionOf(player, sLeft); // 上家のプレイヤー番号
		if (chkGameType(gameStat, SanmaT) && (prev_p == 3)) prev_p = 2;
		else if (chkGameType(gameStat, Sanma4) && (playerwind(gameStat, prev_p, gameStat->GameRound) == sNorth))
			prev_p = RelativePositionOf(player, sOpposite);
		if (gameStat->Player[prev_p].Discard[gameStat->Player[prev_p].DiscardPointer].tcode.tile ==
			gameStat->Player[player].Hand[index].tile)
			return true;
		return false;
}
bool aiscript::table::functable::gametbl::luafunc::riskchk::isdora
	(const GameTable* const gameStat, PLAYER_ID player, int index) { // ドラかどうか
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		return (t == NoTile) ? false : gameStat->DoraFlag.Omote[t];
}
bool aiscript::table::functable::gametbl::luafunc::riskchk::isdorasuji
	(const GameTable* const gameStat, PLAYER_ID player, int index) { // ドラ筋かどうか
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) {return false;}
		else {
			if (((t % TILE_SUIT_STEP) >= 4) &&
				(gameStat->DoraFlag.Omote[t - 3] > 0)) return true;
			if (((t % TILE_SUIT_STEP) <= 6) &&
				(gameStat->DoraFlag.Omote[t + 3] > 0)) return true;
		}
		return false;
}
bool aiscript::table::functable::gametbl::luafunc::riskchk::isdorasoba
	(const GameTable* const gameStat, PLAYER_ID player, int index) { // ドラそばかどうか
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) {return false;}
		else {
			if (((t % TILE_SUIT_STEP) >= 2) &&
				(gameStat->DoraFlag.Omote[t - 1] > 0)) return true;
			if (((t % TILE_SUIT_STEP) >= 3) &&
				(gameStat->DoraFlag.Omote[t - 2] > 0)) return true;
			if (((t % TILE_SUIT_STEP) <= 7) &&
				(gameStat->DoraFlag.Omote[t + 2] > 0)) return true;
			if (((t % TILE_SUIT_STEP) <= 8) &&
				(gameStat->DoraFlag.Omote[t + 1] > 0)) return true;
		}
		return false;
}
bool aiscript::table::functable::gametbl::luafunc::riskchk::isnochance
	(const GameTable* const gameStat, PLAYER_ID player, int index) { // ノーチャンスかどうか
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		Int8ByTile s = countseentiles(gameStat);
		Int8ByTile h = countTilesInHand(gameStat, player);
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) {return false;}
		else {
			if (((t % TILE_SUIT_STEP) == 1) && (s[t+2] + h[t+2] >= 4)) return true;
			if (((t % TILE_SUIT_STEP) <= 2) && (s[t+1] + h[t+1] >= 4)) return true;
			if (((t % TILE_SUIT_STEP) >= 8) && (s[t-1] + h[t-1] <= 4)) return true;
			if (((t % TILE_SUIT_STEP) == 9) && (s[t-2] + h[t-2] <= 4)) return true;
		}
		return false;
}
bool aiscript::table::functable::gametbl::luafunc::riskchk::isonechance
	(const GameTable* const gameStat, PLAYER_ID player, int index) { // ワンチャンスかどうか
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		Int8ByTile s = countseentiles(gameStat);
		Int8ByTile h = countTilesInHand(gameStat, player);
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) {return false;}
		else {
			if (((t % TILE_SUIT_STEP) == 1) && (s[t+2] + h[t+2] == 3)) return true;
			if (((t % TILE_SUIT_STEP) <= 2) && (s[t+1] + h[t+1] == 3)) return true;
			if (((t % TILE_SUIT_STEP) >= 8) && (s[t-1] + h[t-1] == 3)) return true;
			if (((t % TILE_SUIT_STEP) == 9) && (s[t-2] + h[t-2] == 3)) return true;
		}
		return false;
}
bool aiscript::table::functable::gametbl::luafunc::riskchk::isneverdiscarded
	(const GameTable* const gameStat, PLAYER_ID player, int index) { // 生牌かどうか
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		Int8ByTile s = countseentiles(gameStat);
		if (t == NoTile) return false;
		else return (s[t] == 0);
}
bool aiscript::table::functable::gametbl::luafunc::riskchk::isseenfour
	(const GameTable* const gameStat, PLAYER_ID player, int index) { // 場に4枚見えているかどうか
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		Int8ByTile s = countseentiles(gameStat);
		Int8ByTile h = countTilesInHand(gameStat, player);
		if (t == NoTile) return false;
		else return (s[t] + h[t] == 4);
}

bool aiscript::table::functable::gametbl::luafunc::riskchk::isgembutsu
	(const GameTable* const gameStat, PLAYER_ID player, PLAYER_ID tplayer, int index) { // 現物かどうか
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		if (t == NoTile) return false;
		for (int i = 1; i <= gameStat->Player[tplayer].DiscardPointer; i++)
			if (gameStat->Player[tplayer].Discard[i].tcode.tile == t)
				return true;
		return false;
}

bool aiscript::table::functable::gametbl::luafunc::riskchk::issuji
	(const GameTable* const gameStat, PLAYER_ID player, PLAYER_ID tplayer, int index) { // 筋かどうか
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) return false; // 字牌と空白は除外
		if (((t % TILE_SUIT_STEP) >= 4) && ((t % TILE_SUIT_STEP) <= 6)) return false; // 筋心牌以外にのみ適用可能
		for (int i = 1; i <= gameStat->Player[tplayer].DiscardPointer; i++)
			if (((t % TILE_SUIT_STEP) < 4) && (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 3)))
				return true;
			else if (((t % TILE_SUIT_STEP) > 6) && (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 3)))
				return true;
		return false;
}

bool aiscript::table::functable::gametbl::luafunc::riskchk::isnakasuji
	(const GameTable* const gameStat, PLAYER_ID player, PLAYER_ID tplayer, int index) { // 中筋かどうか
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) return false; // 字牌と空白は除外
		if (((t % TILE_SUIT_STEP) < 4) || ((t % TILE_SUIT_STEP) > 6)) return false; // 筋心牌にのみ適用可能
		bool flag1 = false; bool flag2 = false;
		for (int i = 1; i <= gameStat->Player[tplayer].DiscardPointer; i++)
			if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 3))
				flag1 = true;
			else if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 3))
				flag2 = true;
		return flag1 && flag2;
}

bool aiscript::table::functable::gametbl::luafunc::riskchk::isurasuji
	(const GameTable* const gameStat, PLAYER_ID player, PLAYER_ID tplayer, int index) { // 裏筋かどうか
		/*
		 *  裏筋とは……ある牌に対し、その隣の筋である
		 *
		 *  �@２・・５�E・・・　/　・�A３・・６�F・・　/　・・�B４・・７�G・
		 *  ・・・�C５・・８�H　/　１・・４�D６・・９
		 */
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) return false; // 字牌と空白は除外
		for (int i = 1; i <= gameStat->Player[tplayer].DiscardPointer; i++) {
			if (((t % TILE_SUIT_STEP) >= 2) && ((t % TILE_SUIT_STEP) <= 6))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 1))
					return true;
			if (((t % TILE_SUIT_STEP) >= 5) && ((t % TILE_SUIT_STEP) <= 9))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 4))
					return true;
			if (((t % TILE_SUIT_STEP) >= 4) && ((t % TILE_SUIT_STEP) <= 8))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 1))
					return true;
			if (((t % TILE_SUIT_STEP) >= 1) && ((t % TILE_SUIT_STEP) <= 5))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 4))
					return true;
		}
		return false;
}


bool aiscript::table::functable::gametbl::luafunc::riskchk::isaida4ken
	(const GameTable* const gameStat, PLAYER_ID player, PLAYER_ID tplayer, int index) { // 間4ケンの筋かどうか
		/*
		 *  �@２・・５�E・・・　/　・�A３・・６�F・・　/　・・�B４・・７�G・
		 *  ・・・�C５・・８�H
		 */
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) return false; // 字牌と空白は除外
		for (int i = 1; i <= gameStat->Player[tplayer].DiscardPointer; i++) {
			if (((t % TILE_SUIT_STEP) >= 2) && ((t % TILE_SUIT_STEP) <= 5))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 1))
					if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 4))
						return true;
			if (((t % TILE_SUIT_STEP) >= 5) && ((t % TILE_SUIT_STEP) <= 8))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 4))
					if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 1))
						return true;
		}
		return false;
}

bool aiscript::table::functable::gametbl::luafunc::riskchk::issenkisuji
	(const GameTable* const gameStat, PLAYER_ID player, PLAYER_ID tplayer, int index) { // 疝気筋かどうか
		/*
		 *  疝気筋とは……ある牌に対し、その隣の隣の筋である
		 *
		 *  １・・４・�E・・・　/　・２・・５・�F・・　/　�@・３・・６・�G・
		 *  ・�A・４・・７・�H　/　・・�B・５・・８・　/　・・・�C・６・・９
		 */
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) return false; // 字牌と空白は除外
		for (int i = 1; i <= gameStat->Player[tplayer].DiscardPointer; i++) {
			if (((t % TILE_SUIT_STEP) >= 3) && ((t % TILE_SUIT_STEP) <= 6))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 2))
					return true;
			if (((t % TILE_SUIT_STEP) >= 6) && ((t % TILE_SUIT_STEP) <= 9))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 5))
					return true;
			if (((t % TILE_SUIT_STEP) >= 4) && ((t % TILE_SUIT_STEP) <= 7))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 2))
					return true;
			if (((t % TILE_SUIT_STEP) >= 1) && ((t % TILE_SUIT_STEP) <= 4))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 5))
					return true;
		}
		return false;
}

bool aiscript::table::functable::gametbl::luafunc::riskchk::ismatagisuji
	(const GameTable* const gameStat, PLAYER_ID player, PLAYER_ID tplayer, int index) { // 跨ぎ筋かどうか
		/*
		 *  跨ぎ筋
		 *
		 *  １�A・４・・・・・　/　１２�B４５・・・・　/　・２３�C５６・・・
		 *  ・・３４�D６７・・　/　・・・４５�E７８・　/　・・・・５６�F８９
		 *  ・・・・・６・�G９
		 */
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) return false; // 字牌と空白は除外
		for (int i = 1; i <= gameStat->Player[tplayer].DiscardPointer; i++) {
			if (((t % TILE_SUIT_STEP) >= 2) && ((t % TILE_SUIT_STEP) <= 7))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 1))
					return true;
				else if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 2))
					return true;
			if (((t % TILE_SUIT_STEP) >= 3) && ((t % TILE_SUIT_STEP) <= 8))
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 2))
					return true;
				else if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 1))
					return true;
		}
		return false;
}

bool aiscript::table::functable::gametbl::luafunc::riskchk::isnamakurasuji
	(const GameTable* const gameStat, PLAYER_ID player, PLAYER_ID tplayer, int index) { // 鈍筋かどうか
		/*
		 *  鈍筋
		 *
		 *  �@・・�C・・７・・　/　・�A・・�D・・８・　/　・・�B・・�E・・９
		 *  １・・�C・・�F・・　/　・２・・�D・・�G・　/　・・３・・�E・・�H
		 */
		::tileCode t = gameStat->Player[player].Hand[index].tile;
		if ((t >= TILE_SUIT_HONORS)||(t == NoTile)) return false; // 字牌と空白は除外
		bool flag1 = false; bool flag2 = false;
		for (int i = 1; i <= gameStat->Player[tplayer].DiscardPointer; i++) {
			if (((t % TILE_SUIT_STEP) >= 1) && ((t % TILE_SUIT_STEP) <= 3)) {
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 6))
					flag1 = true;
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 3))
					flag2 = true;
			}
			if (((t % TILE_SUIT_STEP) >= 4) && ((t % TILE_SUIT_STEP) <= 6)) {
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t + 3))
					flag1 = true;
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 3))
					flag1 = true;
			}
			if (((t % TILE_SUIT_STEP) >= 7) && ((t % TILE_SUIT_STEP) <= 9)) {
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 6))
					flag1 = true;
				if (gameStat->Player[tplayer].Discard[i].tcode.tile == (t - 3))
					flag2 = true;
			}
			if (gameStat->Player[tplayer].Discard[i].tcode.tile == t)
				flag2 = true; // 現物があったら解除
		}
		return flag1 && (!flag2);
}
