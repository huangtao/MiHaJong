#pragma once

#include "game.h"
#include "../geometry.h"
#include <tuple>
#include <functional>

namespace mihajong_graphic {

class GameTableScreen : public TableProtoScene {
private:
	static const unsigned int TableSize = Geometry::BaseSize;
	static const unsigned int TileThickness = ShowTile::HoriTileHeight - ShowTile::VertTileWidth;
	static const unsigned int DeckChainLength = 17;
	static const unsigned int DeckPosH = (TableSize - ShowTile::VertTileWidth * (DeckChainLength - 1)) / 2;
	static const unsigned int DeckPosV = (TableSize / 2) - 300;
	static const unsigned int HandLength = 13;
	static const unsigned int HandPosH = (TableSize - ShowTile::VertTileWidth * (HandLength - 1)) / 2;
	static const unsigned int HandPosV = DeckPosV - 144;
	LPDIRECT3DTEXTURE9 tBorder; LPD3DXSPRITE sBorder; // ��̘g
	LPDIRECT3DTEXTURE9 tBaize; LPD3DXSPRITE sBaize; // ���ђn
	void ReconstructYamahai(const GameTable* gameStat, PLAYER_ID targetPlayer, PLAYER_ID trueTargetPlayer); // �R�v�̍č\�z
	void ReconstructTehai(const GameTable* gameStat, PLAYER_ID targetPlayer); // ��v�̍č\�z
	class YamahaiReconst;
	friend class GameTableScreen::YamahaiReconst;
	YamahaiReconst* yamahaiReconst;
	void ReconstructPlayer(const GameTable* gameStat, PLAYER_ID targetPlayer, PLAYER_ID trueTargetPlayer); // �v���C���[�֌W�̉�ʂ̍č\�z
	void Reconstruct(const GameTable* gameStat); // ��ʂ̍ĕ`��
public:
	GameTableScreen(ScreenManipulator* const manipulator);
	~GameTableScreen();
	void Render();
};

class GameTableScreen::YamahaiReconst {
private:
	static const unsigned int MeldPosH = TableSize - 31;
	static const unsigned int MeldPosV = DeckPosV - 166;
	static const unsigned int MPosVVert = TableSize - MeldPosV;
	static const unsigned int MPosVHorU = TableSize - MeldPosV - ShowTile::VertTileWidth + 6;
	static const unsigned int MPosVHorL = TableSize - MeldPosV + 6;
	static inline const unsigned int MPosHVertR(unsigned p) {return MeldPosH - ShowTile::VertTileWidth * p;}
	static inline const unsigned int MPosHVertL(unsigned p) {return MeldPosH - ShowTile::VertTileWidth * (p - 1) - ShowTile::HoriTileHeight - 5;}
	static inline const unsigned int MPosHHor(unsigned p) {return MeldPosH - ShowTile::VertTileWidth * (p - 1) - ShowTile::HoriTileHeight + 2;}
	std::tuple<std::function<unsigned (unsigned)>, std::function<int (unsigned)>, std::function<int (unsigned)>, TileDirection, TileDirection, TileDirection>
		playerPosition(const GameTable* gameStat, PLAYER_ID targetPlayer, signed PositionOffset, unsigned IDOffset, unsigned meldID,
		unsigned h1, unsigned h2, unsigned h3, unsigned h4, unsigned v1, unsigned v2, unsigned v3, unsigned v4,
		bool r1, bool r2, bool r3, bool r4);
	void NakihaiAnkan(const GameTable* gameStat, PLAYER_ID targetPlayer, signed PositionOffset, unsigned IDOffset, unsigned meldID);
	void NakihaiKamicha(const GameTable* gameStat, PLAYER_ID targetPlayer, signed PositionOffset, unsigned IDOffset, unsigned meldID);
	void NakihaiToimen(const GameTable* gameStat, PLAYER_ID targetPlayer, signed PositionOffset, unsigned IDOffset, unsigned meldID);
	void NakihaiShimocha(const GameTable* gameStat, PLAYER_ID targetPlayer, signed PositionOffset, unsigned IDOffset, unsigned meldID);
	void MinkanKamicha(const GameTable* gameStat, PLAYER_ID targetPlayer, signed PositionOffset, unsigned IDOffset, unsigned meldID);
	void MinkanToimen(const GameTable* gameStat, PLAYER_ID targetPlayer, signed PositionOffset, unsigned IDOffset, unsigned meldID);
	void MinkanShimocha(const GameTable* gameStat, PLAYER_ID targetPlayer, signed PositionOffset, unsigned IDOffset, unsigned meldID);
	void NakihaiSelRoutine(const GameTable* gameStat, PLAYER_ID targetPlayer, signed PositionOffset, unsigned IDOffset, unsigned meldID);
public:
	GameTableScreen* caller;
	void ReconstructNakihai(const GameTable* gameStat, PLAYER_ID targetPlayer); // �����v�̍č\�z
	YamahaiReconst(GameTableScreen* parent) {caller = parent;}
};

}
