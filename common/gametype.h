#pragma once

#include <cstdint>

namespace mihajong_structs {

using std::uint8_t;

enum GameTypeID : uint8_t { // ��̎��(�l���A�O��)�w��p
	Yonma = 0x01, Sanma = 0x02, Sanma4 = 0x04, SanmaS = 0x08,
	AllSanma = 0x0e, SanmaT = 0x0a, SanmaX = 0x06
};

} /* namespace */