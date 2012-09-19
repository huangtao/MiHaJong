#include "prepare.h"

#define settile(tilecode, pos) {tilepos[tilecode] = pos; for (unsigned int i = 0; i < 4u; ++i) {gameStat->Deck[pos++].tile = tilecode;}}
__declspec(dllexport) void shuffle(GameTable* const gameStat) { // vπobt@ΙΐΧΔAτv
	UInt8ByTile tilepos;
	{ // vπΐΧι
		unsigned int p = 0; // vΜΚuID
		if (chkGameType(gameStat, SanmaX)) {
			settile(CharacterOne, p); // δέq
			settile(CharacterNine, p); // δέq
		} else {
			for (unsigned int k = 1u; k <= 9u; ++k)
				settile((tileCode)(TILE_SUIT_CHARACTERS + k), p); // δέq
		}
		for (unsigned int k = 1u; k <= 9u; ++k)
			settile((tileCode)(TILE_SUIT_CIRCLES + k), p); // q
		for (unsigned int k = 1u; k <= 9u; ++k)
			settile((tileCode)(TILE_SUIT_BAMBOOS + k), p); // υq
		if (!chkGameType(gameStat, SanmaS)) {
			for (unsigned int k = 1u; k <= 7u; ++k)
				settile((tileCode)(TILE_SUIT_HONORS + k), p); // v
			if (RuleData::chkRule("flower_tiles", "seasons") || RuleData::chkRule("flower_tiles", "8tiles")) {
				gameStat->Deck[p++].tile = Spring; gameStat->Deck[p++].tile = Summer;
				gameStat->Deck[p++].tile = Autumn; gameStat->Deck[p++].tile = Winter;
			}
			if (RuleData::chkRule("flower_tiles", "flowers") || RuleData::chkRule("flower_tiles", "8tiles")) {
				gameStat->Deck[p++].tile = Plum; gameStat->Deck[p++].tile = Orchid;
				gameStat->Deck[p++].tile = Chrysanthemum; gameStat->Deck[p++].tile = Bamboo;
			}
		}
	}

	{ // Τhπέθ·ι
		const char tileRules[9][16] = {
			"red_one", "red_two", "red_three", "red_four", "red_five",
			"red_six", "red_seven", "red_eight", "red_nine",
		};
		for (unsigned int i = 0; i < 9; ++i) { // vΜΤh
			if (RuleData::chkRule(tileRules[i], "character_suit") || // δέq
				RuleData::chkRule(tileRules[i], "character_circle_suit") ||
				RuleData::chkRule(tileRules[i], "character_bamboo_suit") ||
				RuleData::chkRule(tileRules[i], "all_three_suits"))
				gameStat->Deck[tilepos[TILE_SUIT_CHARACTERS + i + 1]].red = AkaDora;
			if (RuleData::chkRule(tileRules[i], "circle_suit") || // q
				RuleData::chkRule(tileRules[i], "character_circle_suit") ||
				RuleData::chkRule(tileRules[i], "circle_bamboo_suit") ||
				RuleData::chkRule(tileRules[i], "all_three_suits"))
				gameStat->Deck[tilepos[TILE_SUIT_CIRCLES + i + 1]].red = AkaDora;
			if (RuleData::chkRule(tileRules[i], "bamboo_suit") || // υq
				RuleData::chkRule(tileRules[i], "circle_bamboo_suit") ||
				RuleData::chkRule(tileRules[i], "character_bamboo_suit") ||
				RuleData::chkRule(tileRules[i], "all_three_suits"))
				gameStat->Deck[tilepos[TILE_SUIT_BAMBOOS + i + 1]].red = AkaDora;
		}
	}
	// 5ΜhΝΑκ
	if (chkGameType(gameStat, SanmaX)) { // O
		if (RuleData::chkRule("red_five", "2tiles")) {
			gameStat->Deck[tilepos[CircleFive]].red = AkaDora;
			gameStat->Deck[tilepos[BambooFive]].red = AkaDora;
		}
		else if (RuleData::chkRule("red_five", "4tiles")) {
			gameStat->Deck[tilepos[CircleFive]].red = AkaDora;
			gameStat->Deck[tilepos[CircleFive] + 1].red = AkaDora;
			gameStat->Deck[tilepos[BambooFive]].red = AkaDora;
			gameStat->Deck[tilepos[BambooFive] + 1].red = AkaDora;
		}
		else if (RuleData::chkRule("red_five", "2_circle_tiles")) {
			gameStat->Deck[tilepos[CircleFive]].red = AkaDora;
			gameStat->Deck[tilepos[CircleFive] + 1].red = AkaDora;
		}
	} else { // lEvO
		if (RuleData::chkRule("red_five", "3tiles")) {
			gameStat->Deck[tilepos[CharacterFive]].red = AkaDora;
			gameStat->Deck[tilepos[CircleFive]].red = AkaDora;
			gameStat->Deck[tilepos[BambooFive]].red = AkaDora;
		}
		else if (RuleData::chkRule("red_five", "4tiles")) {
			gameStat->Deck[tilepos[CharacterFive]].red = AkaDora;
			gameStat->Deck[tilepos[CircleFive]].red = AkaDora;
			gameStat->Deck[tilepos[CircleFive] + 1].red = AkaDora;
			gameStat->Deck[tilepos[BambooFive]].red = AkaDora;
		}
		else if (RuleData::chkRule("red_five", "6tiles")) {
			gameStat->Deck[tilepos[CharacterFive]].red = AkaDora;
			gameStat->Deck[tilepos[CharacterFive] + 1].red = AkaDora;
			gameStat->Deck[tilepos[CircleFive]].red = AkaDora;
			gameStat->Deck[tilepos[CircleFive] + 1].red = AkaDora;
			gameStat->Deck[tilepos[BambooFive]].red = AkaDora;
			gameStat->Deck[tilepos[BambooFive] + 1].red = AkaDora;
		}
		else if (RuleData::chkRule("red_five", "2_circle_tiles")) {
			gameStat->Deck[tilepos[CircleFive]].red = AkaDora;
			gameStat->Deck[tilepos[CircleFive] + 1].red = AkaDora;
		}
	}
	{
		const char tileRules[2][16] = {"red_west", "red_north",};
		const tileCode tileCodes[2] = {WestWind, NorthWind,};
		for (unsigned int i = 0; i < 2; ++i) { // vΜΤh
			if (RuleData::chkRule(tileRules[i], "4tiles") || RuleData::chkRule(tileRules[i], "3tiles") ||
				RuleData::chkRule(tileRules[i], "2tiles") || RuleData::chkRule(tileRules[i], "1tile"))
				gameStat->Deck[tilepos[TILE_SUIT_CHARACTERS + i]].red = AkaDora;
			if (RuleData::chkRule(tileRules[i], "4tiles") || RuleData::chkRule(tileRules[i], "3tiles") ||
				RuleData::chkRule(tileRules[i], "2tiles"))
				gameStat->Deck[tilepos[TILE_SUIT_CHARACTERS + i + 1]].red = AkaDora;
			if (RuleData::chkRule(tileRules[i], "4tiles") || RuleData::chkRule(tileRules[i], "3tiles"))
				gameStat->Deck[tilepos[TILE_SUIT_CHARACTERS + i + 2]].red = AkaDora;
			if (RuleData::chkRule(tileRules[i], "4tiles"))
				gameStat->Deck[tilepos[TILE_SUIT_CHARACTERS + i + 3]].red = AkaDora;
		}
	}
}
