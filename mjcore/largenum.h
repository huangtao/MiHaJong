#ifndef LARGENUM_H
#define LARGENUM_H

#include <cstdint>
#include <cstdlib>
#include <memory>
#include "mjexport.h"
#include "except.h"

// 青天ルール対策
// 一応21不可思議まで表現可能……

#define DIGIT_GROUPS 8

EXPORT_STRUCT LargeNum { // ±21不可思議まで表現可能な数のクラス
	int32_t digitGroup[DIGIT_GROUPS];
	unsigned int firstArg; // 互換用。
	void fix();
	signed int compare(const LargeNum& cmp) const;
	CodeConv::tstring bignumtotext(CodeConv::tstring plusSign, CodeConv::tstring minusSign) const;
	double bignumtodbl() const;
	static LargeNum fromInt(int val);
	static LargeNum fromInt(int val, unsigned int fArg);
	void ceilHundred();
	/* ここから演算子をオーバーロード */
	const LargeNum operator+(const LargeNum& addend);
	const LargeNum operator+(const int32_t addend);
	LargeNum& operator+=(const LargeNum& addend);
	LargeNum& operator+=(const int32_t addend);
	const LargeNum operator-(const LargeNum& subtrahend);
	const LargeNum operator-(const int32_t subtrahend);
	const LargeNum operator*(const int32_t multiplier);
	LargeNum& operator*=(const int32_t multiplier);
	const LargeNum operator/(const int32_t divisor);
	LargeNum& operator/=(const int32_t divisor);
	const bool operator==(const LargeNum& cmp) const;
	const bool operator!=(const LargeNum& cmp) const;
	const bool operator<(const LargeNum& cmp) const;
	const bool operator>(const LargeNum& cmp) const;
	const bool operator<=(const LargeNum& cmp) const;
	const bool operator>=(const LargeNum& cmp) const;
};
#ifdef MJCORE_EXPORTS
static_assert(std::is_pod<LargeNum>::value, "LargeNum is not POD");
#endif

#endif
