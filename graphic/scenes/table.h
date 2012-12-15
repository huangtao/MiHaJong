#pragma once

#include "game.h"
#include "../geometry.h"

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
	void ReconstructPlayer(const GameTable* gameStat, PLAYER_ID targetPlayer, PLAYER_ID trueTargetPlayer); // �v���C���[�֌W�̉�ʂ̍č\�z
	void Reconstruct(const GameTable* gameStat); // ��ʂ̍ĕ`��
public:
	GameTableScreen(ScreenManipulator* const manipulator);
	~GameTableScreen();
	void Render();
};

}
