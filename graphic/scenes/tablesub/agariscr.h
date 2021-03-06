#pragma once

#include <cmath>
#include "tablesub.h"
#include "../../../common/yakurslt.h"
#include <vector>
#include <utility>
#include "../../../common/strcode.h"
#include "../../text.h"
#include "../table/tehai0.h"
#include "../table/nakihai0.h"

namespace mihajong_graphic {

// -------------------------------------------------------------------------

class TableSubsceneAgariScreenProto : public TableSubscene {
protected:
	static const unsigned yakuWndWidth  = 720u;
	static const unsigned yakuWndHeight = 864u;
	static const int BaseX = ((signed)Geometry::BaseSize - (signed)yakuWndWidth ) / 2;
	static const int BaseY = ((signed)Geometry::BaseSize - (signed)yakuWndHeight) / 2;
	double seconds() {return (double)myTimer.elapsed() / 1000000.0;}
	static const int handPosY = BaseY + 56;
	static const double yakuInterval;
	static const double yakuAnimStartSecond;
	bool YakumanMode();
	enum AgariStyle {agariMine, agariFurikomi, agariOthers,};
	static AgariStyle getAgariStyle();
	static ArgbColor baseColor();
protected:
	DevicePtr myDevice;
	TexturePtr windowTexture;
	TextRenderer* myTextRenderer;
protected:
	mihajong_structs::YakuResult yakuData;
	std::vector<std::pair<CodeConv::tstring, CodeConv::tstring> > yakuList;
	void parseYakuList();
protected:
	void renderWindow();
	class AgariTehai; AgariTehai* agariTehai;
	class AgariNaki; AgariNaki* agariNaki;
	class DoraTiles; class DoraTilesOmote;
	DoraTilesOmote* doraTilesOmote;
	class ShowScore; ShowScore* showScore;
	bool renderYakuName(unsigned yakuNum);
	void renderYakuName();
protected:
	bool bgmFlag;
	int maxShown;
public:
	TableSubsceneAgariScreenProto(DevicePtr device);
	TableSubsceneAgariScreenProto(const TableSubsceneAgariScreenProto&) = delete; // Delete unexpected copy constructor
	TableSubsceneAgariScreenProto& operator= (const TableSubsceneAgariScreenProto&) = delete; // Delete unexpected assign operator
	virtual ~TableSubsceneAgariScreenProto();
	virtual void skipEvent();
};

class TableSubsceneAgariScreen : public TableSubsceneAgariScreenProto {
public:
	TableSubsceneAgariScreen(DevicePtr device);
	TableSubsceneAgariScreen(const TableSubsceneAgariScreen&) = delete; // Delete unexpected copy constructor
	TableSubsceneAgariScreen& operator= (const TableSubsceneAgariScreen&) = delete; // Delete unexpected assign operator
	~TableSubsceneAgariScreen();
	void Render();
};

class TableSubsceneAgariScreenUradora : public TableSubsceneAgariScreenProto {
private:
	class DoraTilesUra;
	DoraTilesUra* doraTilesUra;
public:
	TableSubsceneAgariScreenUradora(DevicePtr device);
	TableSubsceneAgariScreenUradora(const TableSubsceneAgariScreenUradora&) = delete; // Delete unexpected copy constructor
	TableSubsceneAgariScreenUradora& operator= (const TableSubsceneAgariScreenUradora&) = delete; // Delete unexpected assign operator
	~TableSubsceneAgariScreenUradora();
	void Render();
};

// -------------------------------------------------------------------------

class TableSubsceneAgariScreenProto::AgariTehai : public ShowTehai {
private:
	TableSubsceneAgariScreenProto* myCaller;
	void Reconstruct(const GameTable* gameStat);
	bool reconstFlag;
public:
	void Render();
	explicit AgariTehai(TableSubsceneAgariScreenProto* caller);
	AgariTehai(const AgariTehai&) = delete; // Delete unexpected copy constructor
	AgariTehai& operator= (const AgariTehai&) = delete; // Delete unexpected assign operator
	~AgariTehai();
};

// -------------------------------------------------------------------------

class TableSubsceneAgariScreenProto::AgariNaki : public ShowNakihai {
private:
	TableSubsceneAgariScreenProto* myCaller;
	void Reconstruct(const GameTable* gameStat);
	bool reconstFlag;
private:
	unsigned int MeldPosH() {return BaseX + yakuWndWidth - 24;}
	unsigned int MeldPosV() {
		const double Zeit = myCaller->seconds();
		const int yOffset = (Zeit >= 1.0) ? 0 : (int)(pow(1.0 - Zeit, 2) * (double)Geometry::BaseSize);
		return handPosY - yOffset;
	}
	unsigned int MPosVVert() {return MeldPosV();}
	unsigned int MPosVHorU() {return MeldPosV() - ShowTile::VertTileWidth + 6;}
	unsigned int MPosVHorL() {return MeldPosV() + 6;}
	std::tuple<std::function<unsigned (unsigned)>, std::function<int (unsigned)>, std::function<int (unsigned)>, TileDirection, TileDirection, TileDirection>
		playerPosition(const GameTable* gameStat, PlayerID targetPlayer, signed PositionOffset, unsigned IDOffset, unsigned meldID,
		unsigned h1, unsigned h2, unsigned h3, unsigned h4, unsigned v1, unsigned v2, unsigned v3, unsigned v4,
		bool r1, bool r2, bool r3, bool r4);
public:
	void Render();
	explicit AgariNaki(TableSubsceneAgariScreenProto* caller);
	AgariNaki(const AgariNaki&) = delete; // Delete unexpected copy constructor
	AgariNaki& operator= (const AgariNaki&) = delete; // Delete unexpected assign operator
	~AgariNaki();
};

// -------------------------------------------------------------------------

class TableSubsceneAgariScreenProto::DoraTiles {
protected:
	TableSubsceneAgariScreenProto* myCaller;
	ShowTile* tileObj;
	virtual int xPos() = 0;
	virtual int yPos() = 0;
	virtual int tileIdOffset() = 0;
	virtual double startTime() = 0;
	virtual void Reconstruct();
public:
	virtual void Render();
	explicit DoraTiles(TableSubsceneAgariScreenProto* caller);
	DoraTiles(const DoraTiles&) = delete; // Delete unexpected copy constructor
	DoraTiles& operator= (const DoraTiles&) = delete; // Delete unexpected assign operator
	virtual ~DoraTiles() = 0;
};

class TableSubsceneAgariScreenProto::DoraTilesOmote : public TableSubsceneAgariScreenProto::DoraTiles {
protected:
	int xPos() {return BaseX + 32;}
	int yPos() {return BaseY + 120;}
	int tileIdOffset() {return 2;}
	double startTime() {return 1.0;}
public:
	explicit DoraTilesOmote(TableSubsceneAgariScreenProto* caller);
	DoraTilesOmote(const DoraTilesOmote&) = delete; // Delete unexpected copy constructor
	DoraTilesOmote& operator= (const DoraTilesOmote&) = delete; // Delete unexpected assign operator
	~DoraTilesOmote();
};

class TableSubsceneAgariScreenUradora::DoraTilesUra : public TableSubsceneAgariScreenProto::DoraTiles {
protected:
	int xPos() {return BaseX + 32;}
	int yPos() {return BaseY + 120 + ShowTile::HoriTileWidth;}
	int tileIdOffset() {return 1;}
	double startTime() {return 1.0625;}
public:
	explicit DoraTilesUra(TableSubsceneAgariScreenProto* caller);
	DoraTilesUra(const DoraTilesUra&) = delete; // Delete unexpected copy constructor
	DoraTilesUra& operator= (const DoraTilesUra&) = delete; // Delete unexpected assign operator
	~DoraTilesUra();
};

// -------------------------------------------------------------------------

class TableSubsceneAgariScreenProto::ShowScore {
private:
	TableSubsceneAgariScreenProto* myCaller;
	CallDigitRenderer* digitRenderer;
	TextRenderer* txtRenderer;
	void ReconstructScoreFuHan();
	void ReconstructScoreTxt();
	void ReconstructScoreRank();
	void ReconstructChipAmount();
	void Reconstruct();
private:
	bool soundFlag;
	bool timeFlag;
public:
	void Render();
	explicit ShowScore(TableSubsceneAgariScreenProto* caller);
	ShowScore(const ShowScore&) = delete; // Delete unexpected copy constructor
	ShowScore& operator= (const ShowScore&) = delete; // Delete unexpected assign operator
	~ShowScore();
};

// -------------------------------------------------------------------------

}
