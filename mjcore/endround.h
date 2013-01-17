#pragma once

#include "endtype.h"
#include "gametbl.h"

namespace endround {
	EndType checkroundabort(GameTable* gameStat); // ÇI¹ðÌ»è
	void endround(GameTable* gameStat, EndType roundEndType, unsigned OrigTurn, unsigned OrigHonba);
	bool nextRound(GameTable* gameStat, EndType RoundEndType, unsigned int OrigTurn); // ÌÇÖ(I¹·éêÍtrue)

	namespace transfer {
		void resetDelta();
		void addDelta(PLAYER_ID player, LargeNum& deltaVal);
		void transferPoints(GameTable* gameStat, unsigned subscene, unsigned wait);
	}
}
