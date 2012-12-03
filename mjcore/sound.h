#ifndef SOUND_H
#define SOUND_H

#include "../sound/sound.h"
#include "bgmid.h"
#include "strcode.h"
#include "func.h"
#include <vector>

namespace sound {
namespace util {

void bgmload(unsigned ID, LPCSTR filename, bool looped); /* BGMÇÝÝ */
void soundload(unsigned ID, LPCSTR filename, bool looped); /* TEhÇÝÝ */
void bgmstop(); /* BGMâ~ */
void bgmplay(unsigned ID); /* aflÄ¶ */

}
}

#endif
