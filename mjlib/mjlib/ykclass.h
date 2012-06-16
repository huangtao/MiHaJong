#ifndef YKCLASS_H
#define YKCLASS_H

#include <string>
#include <functional>

using namespace std;

typedef function<bool ()> YAKUFUNC;

class Yaku {
private:
	int yakuHan; // 縛りを満たす翻
	int incompleteHan; // 縛りを満たさない翻
	string yakuName; // 役の名前（文字列）
	YAKUFUNC yakuProc; // 役の判定方法
	Yaku() {} // Default constructor
public:
	bool checkYaku() {return this->yakuProc();} // 役を判定する
	string getName() {return this->yakuName;} // 役の名前を取得する
	// Constructor
	Yaku(string name, int han, int icHan, YAKUFUNC f) {
		this->yakuName = string(name.begin(), name.end());
		this->yakuHan = han;
		this->incompleteHan = icHan;
		this->yakuProc = YAKUFUNC(f);
	}
};

#endif
