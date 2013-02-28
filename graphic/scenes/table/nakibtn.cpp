#ifdef _MSC_VER
#define _USE_MATH_DEFINES /* required for M_PI by MS VC++ */
#endif
#include <cmath>

#include "nakibtn.h"

#include "../../geometry.h"
#include "../../utils.h"
#include "../../gametbl.h"
#include "../../rule.h"
#include "../../event.h"
#include "../../../common/discard.h"
#include "../../../sound/sound.h"
#include "../../../common/bgmid.h"

#include "tehai.h"
#include "naki_id.h"

namespace mihajong_graphic {

const GameTableScreen::ButtonReconst::BtnData
	GameTableScreen::ButtonReconst::buttonDat[2][GameTableScreen::ButtonReconst::btnMAXIMUM] = {
		{
			{_T("���`�["),   5 + 117 * 0, Geometry::BaseSize - 40, 0xffccff66},
			{_T("�ƃ`�["),   5 + 117 * 1, Geometry::BaseSize - 40, 0xff99ff99},
			{_T("�E�`�["),   5 + 117 * 2, Geometry::BaseSize - 40, 0xff66ff99},
			{_T("�|��"),     5 + 117 * 3, Geometry::BaseSize - 40, 0xff99ccff},
			{_T("�J��"),     5 + 117 * 4, Geometry::BaseSize - 40, 0xff9966ff},
			{_T("�p�X"),     5 + 117 * 5, Geometry::BaseSize - 40, 0xffcccccc},
			{_T("����"),     5 + 117 * 6, Geometry::BaseSize - 40, 0xffffcc66},
		}, {
			{_T(""),         5 + 117 * 0, Geometry::BaseSize - 40, 0xff666666},
			{_T(""),         5 + 117 * 1, Geometry::BaseSize - 40, 0xff666666},
			{_T("����v"), 5 + 117 * 2, Geometry::BaseSize - 40, 0xff99ffff},
			{_T("�Ԕv"),     5 + 117 * 3, Geometry::BaseSize - 40, 0xff99ccff},
			{_T("�J��"),     5 + 117 * 4, Geometry::BaseSize - 40, 0xff9966ff},
			{_T("���[�`"),   5 + 117 * 5, Geometry::BaseSize - 40, 0xffff66ff},
			{_T("�c��"),     5 + 117 * 6, Geometry::BaseSize - 40, 0xffffff66},
		},
};

void GameTableScreen::ButtonReconst::Render() {
	if (getCursor() != CursorDisabled) {
#include "color.h"
		Color btnColor; btnColor.rgbaAsOneValue = buttonDat[currentButtonSet][cursor].color;
		const double Zeit = (double)(currTime() % 90000000ULL);
		btnColor.rgbaAsStruct.r = (unsigned)((double)btnColor.rgbaAsStruct.r * (sin(Zeit / 4500000.0 * M_PI) / 4.0 + 0.75));
		btnColor.rgbaAsStruct.g = (unsigned)((double)btnColor.rgbaAsStruct.g * (sin(Zeit / 4500000.0 * M_PI) / 4.0 + 0.75));
		btnColor.rgbaAsStruct.b = (unsigned)((double)btnColor.rgbaAsStruct.b * (sin(Zeit / 4500000.0 * M_PI) / 4.0 + 0.75));
		buttons->setButton(cursor,
			(sunkenButton == cursor) ? ButtonPic::sunken : (buttonEnabled[cursor] ? ButtonPic::raised : ButtonPic::clear),
			buttonDat[currentButtonSet][cursor].x * Geometry::WindowScale(),
			buttonDat[currentButtonSet][cursor].y * Geometry::WindowScale(),
			117 * Geometry::WindowScale(), 36 * Geometry::WindowScale(),
			btnColor.rgbaAsOneValue, buttonDat[currentButtonSet][cursor].label);
	}
	reconstructionCS.syncDo<void>([this]() -> void {
		buttons->Render();
		buttons->Render();
		buttons->Render();
	});
}

void GameTableScreen::ButtonReconst::reconstruct(ButtonID buttonID) {
#include "color.h"
	Color btnColor; btnColor.rgbaAsOneValue = buttonDat[currentButtonSet][buttonID].color;
	/*if (!buttonEnabled[buttonID]) { // �Ó]����
		btnColor.rgbaAsStruct.r /= 3;
		btnColor.rgbaAsStruct.g /= 3;
		btnColor.rgbaAsStruct.b /= 3;
	}*/
	buttons->setButton(buttonID,
		(sunkenButton == buttonID) ? ButtonPic::sunken : (buttonEnabled[buttonID] ? ButtonPic::raised : ButtonPic::clear),
		buttonDat[currentButtonSet][buttonID].x * Geometry::WindowScale(),
		buttonDat[currentButtonSet][buttonID].y * Geometry::WindowScale(),
		117 * Geometry::WindowScale(), 36 * Geometry::WindowScale(),
		btnColor.rgbaAsOneValue, buttonDat[currentButtonSet][buttonID].label);
	const Region nullRegion = {0, 0, -1, -1};
	if (caller->regions.size() <= (buttonID + ButtonRegionNum))
		caller->regions.resize(ButtonRegionNum + 1 + buttonID, nullRegion);
	caller->regions[buttonID + ButtonRegionNum].Left   = buttonDat[currentButtonSet][buttonID].x;
	caller->regions[buttonID + ButtonRegionNum].Top    = buttonDat[currentButtonSet][buttonID].y;
	caller->regions[buttonID + ButtonRegionNum].Right  = buttonDat[currentButtonSet][buttonID].x + 117;
	caller->regions[buttonID + ButtonRegionNum].Bottom = buttonDat[currentButtonSet][buttonID].y + 36;
}
void GameTableScreen::ButtonReconst::reconstruct() {
	reconstructionCS.syncDo<void>([this]() -> void {
		for (unsigned i = 0; i < btnMAXIMUM; ++i)
			reconstruct((ButtonID)i);
	});
}

void GameTableScreen::ButtonReconst::ChangeButtonSet(ButtonSet btnSet) {
	currentButtonSet = btnSet;
	cursor = CursorDisabled;
	sunkenButton = NoSunkenButton;
	buttonEnabled.reset();
	reconstruct();
}

void GameTableScreen::ButtonReconst::enable(ButtonID buttonID) {
	buttonEnabled[buttonID] = true; reconstruct(buttonID);
}
void GameTableScreen::ButtonReconst::disable(ButtonID buttonID) {
	buttonEnabled[buttonID] = false; reconstruct(buttonID);
}
void GameTableScreen::ButtonReconst::enable(const std::bitset<btnMAXIMUM>& flagset) {
	buttonEnabled = flagset;
	reconstruct();
}

void GameTableScreen::ButtonReconst::btnSetForDahai() { // �c���Ԃ̎��p��
	currentButtonSet = btnSetTsumo; buttonEnabled.reset(); // ��Ԃ����Z�b�g
	const GameTable* const gameStat = GameStatus::retrGameStat();
	auto tilesMoreThan = [gameStat](int tiles) {
		return (gameStat->TilePointer + tiles) < (gameStat->RinshanPointer - gameStat->DeadTiles - 1);
	};
	const PlayerID ActivePlayer = gameStat->CurrentPlayer.Active;
	const PlayerTable* const playerStat = &(gameStat->Player[ActivePlayer]);
	const Shanten shanten = utils::calcShanten(gameStat, ActivePlayer, shantenAll);
	if (utils::isRichiReqSatisfied(gameStat, ActivePlayer) && // �_�_�v���𖞂����Ă���i�_�_������Ă���j
		(shanten <= 0) && // �e���p�C���Ă���
		(playerStat->MenzenFlag || (!rules::chkRule("riichi_shibari", "no"))) && // ��O�ł��邩�A���[�`���胋�[���ł���
		(!playerStat->RichiFlag.RichiFlag) && // �܂����[�`���Ă��Ȃ�
		(tilesMoreThan((gameStat->gameType & AllSanma) ? 2 : 3))) // �c��c���v���\������Ȃ�
		buttonEnabled[btnRiichi] = true; // ���[�`�{�^����L����

	const bool DaoPaiAbilityFlag = utils::chkdaopaiability(gameStat, ActivePlayer);
	if ((DaoPaiAbilityFlag) && (playerStat->FirstDrawFlag))
		buttonEnabled[btnKyuushu] = true; // ����v�{�^��

	const bool ShisanBuDa = utils::chkShisanBuDa(gameStat, ActivePlayer);
	const bool ShisiBuDa = utils::chkShisiBuDa(gameStat, ActivePlayer);
	if (((shanten <= -1) && (playerStat->Tsumohai().tile != NoTile)) || // �a���ɂȂ��Ă��邩
		ShisanBuDa || ShisiBuDa) // �\�O�s���̏ꍇ�i�\�O�s���Ȃ��̏ꍇ���̕ϐ���false�ɂȂ�j
		buttonEnabled[btnTsumo] = true; // �a���{�^��

	const Int8ByTile TileCount = utils::countTilesInHand(gameStat, ActivePlayer);
	const int kanLim = rules::chkRule("fifth_kong", "no") ? 4 : 5;
	const bool KanFlag = [tilesMoreThan, gameStat, TileCount, playerStat, kanLim]() -> bool {
		for (int i = 1; i < TileNonflowerMax; ++i) {
			if (tilesMoreThan(0) && (gameStat->KangNum < kanLim)) {
				// �ÞȂł���ꍇ
				if (TileCount[i] == 4)
					return true;
				// ���Ȃł���ꍇ
				else if (TileCount[i] == 1) {
					for (int j = 1; j <= playerStat->MeldPointer; ++j)
						if ((playerStat->Meld[j].tile == i) &&
							((playerStat->Meld[j].mstat == meldTripletExposedLeft) ||
							(playerStat->Meld[j].mstat == meldTripletExposedCenter) ||
							(playerStat->Meld[j].mstat == meldTripletExposedRight)))
							return true;
				}
			}
		}
		return false;
	} ();
	if (KanFlag && (playerStat->Tsumohai().tile != NoTile) &&
		(!playerStat->RichiFlag.RichiFlag) || utils::chkAnkanAbility(gameStat, ActivePlayer))
		buttonEnabled[btnKan] = true;

	const TileCode flowerTile = (gameStat->gameType & SanmaX) ? NorthWind : Flower;
	const bool Flowerabilityflag = [gameStat, playerStat]() -> bool {
		if (gameStat->gameType & SanmaX)
			return (playerStat->Hand[NumOfTilesInHand].tile == NorthWind) && (!rules::chkRule("flower_tiles", "no"));
		else
			return playerStat->Hand[NumOfTilesInHand].tile > TileSuitFlowers;
	} ();
	if ((!rules::chkRule("flower_tiles", "no")) &&
		(playerStat->Tsumohai().tile != NoTile) &&
		(TileCount[flowerTile] >= 1) &&
		((!playerStat->RichiFlag.RichiFlag) || Flowerabilityflag))
		buttonEnabled[btnFlower] = true;

	reconstruct();
}

void GameTableScreen::ButtonReconst::btnSetForNaki() { // ���̎��p��
	currentButtonSet = btnSetNormal; buttonEnabled.reset(); // ��Ԃ����Z�b�g
	GameTable* const gameStat = new GameTable;
	memcpy(gameStat, GameStatus::retrGameStat(), sizeof (GameTable));
	auto tilesMoreThan = [gameStat](int tiles) {
		return (gameStat->TilePointer + tiles) < (gameStat->RinshanPointer - gameStat->DeadTiles - 1);
	};
	const PlayerID ActivePlayer = gameStat->CurrentPlayer.Active;
	const PlayerID PassivePlayer = gameStat->CurrentPlayer.Passive;
	PlayerTable* const playerStat = &(gameStat->Player[PassivePlayer]);
	playerStat->Tsumohai().tile = gameStat->CurrentDiscard.tile;
	const Shanten shanten = utils::calcShanten(gameStat, gameStat->PlayerID, shantenAll);
	playerStat->Tsumohai().tile = NoTile;

	if (gameStat->CurrentDiscard.tile > TileSuitFlowers) goto end; /* �Ԕv�̏ꍇ�͎c��̔�����X�L�b�v */
	if (playerStat->AgariHouki) goto end; /* �a���������������c��̔�����X�L�b�v */
	if ((gameStat->KangFlag.chankanFlag == chankanOfAnkan) && // �ÞȂɑ΂��靏�Ȕ���̂Ƃ��ŁA
		(utils::calcShanten(gameStat, PassivePlayer, shantenOrphans) >= 0)) // ���m���v�łȂ��ꍇ��
		goto end; // �c��̔�����X�L�b�v

	if (shanten < 0) // �o���v��������v
		buttonEnabled[btnRon] = true; // �a���{�^���i�t���e���̏ꍇ�Ȃǂ��_���j

	if (!playerStat->RichiFlag.RichiFlag) { // ���[�`���ĂȂ��Ƃ��c�c
		const Int8ByTile TileCount = utils::countTilesInHand(gameStat, PassivePlayer);
		const int kanLim = rules::chkRule("fifth_kong", "no") ? 4 : 5;

		if (TileCount[gameStat->CurrentDiscard.tile] >= 2)
			buttonEnabled[btnPon] = true; // �|��
		if ((TileCount[gameStat->CurrentDiscard.tile] >= 3) && // �o�Ă����v���Í��Ŏ����Ă���
			(gameStat->KangFlag.chankanFlag == chankanNone) && // ���Ȃ̔��蒆�ł͂Ȃ���
			(gameStat->KangNum < kanLim)) // ���x�ȓ��̏ꍇ
			buttonEnabled[btnKan] = true; // �J��

		// �`�[�ł�������F��Ƃ̎̔v�ł��邱�ƁA���A���v�ł��邱��
		if ((gameStat->gameType & Yonma) && // �l���ł���
			(gameStat->CurrentDiscard.tile < TileSuitHonors) && // ���v��
			(gameStat->KangFlag.chankanFlag == chankanNone) && // ���Ȃ̔��蒆�ł͂Ȃ���
			(gameStat->CurrentPlayer.Active == ((gameStat->CurrentPlayer.Passive + 3) % 4))) { // �̂Ă��̂����
				if ((gameStat->CurrentDiscard.tile >= 1) &&
					(TileCount[gameStat->CurrentDiscard.tile + 1] >= 1) && (TileCount[gameStat->CurrentDiscard.tile + 2] >= 1)) { // ���h
						buttonEnabled[btnChii1] = true;
				}
				if ((gameStat->CurrentDiscard.tile >= 2) &&
					(TileCount[gameStat->CurrentDiscard.tile - 1] >= 1) && (TileCount[gameStat->CurrentDiscard.tile + 1] >= 1)) { // �ƒ��h
						buttonEnabled[btnChii2] = true;
				}
				if ((gameStat->CurrentDiscard.tile >= 3) &&
					(TileCount[gameStat->CurrentDiscard.tile - 2] >= 1) && (TileCount[gameStat->CurrentDiscard.tile - 1] >= 1)) { // ��h
						buttonEnabled[btnChii3] = true;
				}
		}
	}

	if (buttonEnabled.any()) // ���炩�̃{�^�����_�����Ă����疳������{�^�����_������
		buttonEnabled[btnPass] = true;

end:
	delete gameStat;
	reconstruct();
	return;
}

GameTableScreen::ButtonReconst::ButtonReconst(GameTableScreen* parent) {
	caller = parent;
	cursor = CursorDisabled; sunkenButton = NoSunkenButton;
	buttons = new ButtonPic(caller->caller->getDevice());
	ChangeButtonSet(btnSetNormal);
};

GameTableScreen::ButtonReconst::~ButtonReconst() {
	delete buttons;
}

std::uint64_t GameTableScreen::ButtonReconst::currTime() { /* ���ݎ���(Windows�ł�100ns�P��) */
	FILETIME Zeit; GetSystemTimeAsFileTime(&Zeit);
	return ((std::uint64_t)Zeit.dwHighDateTime << 32) | Zeit.dwLowDateTime;
}

/* �{�^���������ꂽ���̏��� */
void GameTableScreen::ButtonReconst::ButtonPressed() {
	auto setMode = [&](DiscardTileNum::discardType mode, ButtonID button, std::function<bool(int, GameTable*)> f) -> void {
		caller->tileSelectMode = mode;
		this->setSunkenButton(button);
		for (int i = 0; i < btnMAXIMUM; ++i)
			if (i != button)
				this->disable((ButtonID)i);
		this->reconstruct();
		caller->tehaiReconst->enable();
		for (int i = 0; i < NumOfTilesInHand; ++i) {
			GameTable tmpStat; std::memcpy(&tmpStat, GameStatus::gameStat(), sizeof (GameTable));
			if (f(i, &tmpStat)) caller->tehaiReconst->disable(i);
		}
		caller->tehaiReconst->Reconstruct(GameStatus::gameStat(), GameStatus::gameStat()->CurrentPlayer.Active);
	};

	sound::Play(sound::IDs::sndButton);
	if (!this->isEnabled((ButtonID)this->getCursor())) {
		sound::Play(sound::IDs::sndCuohu);
	} else if (this->getButtonSet() == btnSetTsumo) {
		switch (this->getCursor()) {
		case btnTsumo:
			caller->CallTsumoAgari();
			break;
		case btnKyuushu:
			caller->CallKyuushuKyuuhai();
			break;
		case btnRiichi: // ����
			setMode(DiscardTileNum::Riichi, btnRiichi,
				[](int i, GameTable* tmpStat) -> bool {
					tmpStat->Player[tmpStat->CurrentPlayer.Active].Hand[i].tile = NoTile;
					Shanten shanten = utils::calcShanten(tmpStat, tmpStat->CurrentPlayer.Active, shantenAll);
					return (shanten > 0);
				});
			break;
		case btnKan: // �J��
			setMode(DiscardTileNum::Ankan, btnKan,
				[](int i, GameTable* tmpStat) -> bool {
					bool flag = false;
					const PlayerID ActivePlayer = tmpStat->CurrentPlayer.Active;
					const Int8ByTile TileCount = utils::countTilesInHand(tmpStat, ActivePlayer);
					const PlayerTable* const playerStat = &(tmpStat->Player[ActivePlayer]);
					if (TileCount[playerStat->Hand[i].tile] < 4) flag = true;
					if (TileCount[playerStat->Hand[i].tile] == 1) {
						for (int j = 1; j <= playerStat->MeldPointer; ++j)
							if ((playerStat->Meld[j].tile == playerStat->Hand[i].tile) &&
								((playerStat->Meld[j].mstat == meldTripletExposedLeft) ||
								(playerStat->Meld[j].mstat == meldTripletExposedCenter) ||
								(playerStat->Meld[j].mstat == meldTripletExposedRight)))
								flag = false;
					}
					return flag;
				});
			break;
		case btnFlower: // �Ԕv
			setMode(DiscardTileNum::Flower, btnFlower,
				[](int i, GameTable* tmpStat) -> bool {
					return tmpStat->Player[tmpStat->CurrentPlayer.Active].Hand[i].tile !=
						(tmpStat->gameType & SanmaX) ? NorthWind : Flower;
				});
			break;
		default:
			sound::Play(sound::IDs::sndCuohu);
			break;
		}
	} else if (this->getButtonSet() == btnSetNormal) {
		switch (this->getCursor()) {
		case btnPass:
			ui::UIEvent->set(naki::nakiNone);
			break;
		case btnRon:
			ui::UIEvent->set(naki::nakiRon);
			break;
		case btnKan:
			ui::UIEvent->set(naki::nakiKan);
			break;
		case btnPon:
			ui::UIEvent->set(naki::nakiPon);
			break;
		case btnChii1:
			ui::UIEvent->set(naki::nakiChiLower);
			break;
		case btnChii2:
			ui::UIEvent->set(naki::nakiChiMiddle);
			break;
		case btnChii3:
			ui::UIEvent->set(naki::nakiChiUpper);
			break;
		default:
			sound::Play(sound::IDs::sndCuohu);
			break;
		}
	}
}

}