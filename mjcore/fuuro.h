#ifndef FUURO_H
#define FUURO_H

#ifdef MJCORE_EXPORTS
#include <sstream>
#include <cassert>
#include "../sound/sound.h"
#include "strcode.h"
#include "logging.h"
#include "haifu.h"
#include "ruletbl.h"
#include "envtbl.h"
#include "tileutil.h"
#include "discard.h"
#include "bgmid.h"
#include "ai/class.h"
#include "../socket/socket.h"
#include "yaku/ykclass.h"
#include "yaku/yaku.h"
#include "remote.h"
#endif
#include "gametbl.h"
#include "endtype.h"
#include "discard.h"

enum FuuroType : unsigned { /* ���I�����̎�� */
	FuuroAnkan,     // �Þ�
	FuuroKakan,     // ����
	FuuroDaiminkan, // �喾��
	FuuroNorth,     // �����k(�O��)
	FuuroFlower,    // �Ԕv(�l��)
	FuuroPon,       // �|��
	FuuroChii,      // �`�[
};

bool fuuroproc(GameTable* const gameStat, EndType* RoundEndType, const DiscardTileNum& DiscardTileIndex, FuuroType Mode);
void checkpao(GameTable* const gameStat);
EndType ronhuproc(GameTable* const gameStat);
bool executeFuuro(GameTable* const gameStat, const DiscardTileNum& DiscardTileIndex);

#endif