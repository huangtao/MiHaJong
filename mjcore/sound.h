#pragma once

#include "../sound/sound.h"

namespace sound {
namespace util {

void bgmload(unsigned ID, LPCSTR filename, bool looped); /* BGM�ǂݍ��� */
void soundload(unsigned ID, LPCSTR filename, bool looped); /* �T�E���h�ǂݍ��� */
void bgmstop(); /* BGM��~ */
void bgmplay(unsigned ID); /* �a�f�l�Đ� */

}
}