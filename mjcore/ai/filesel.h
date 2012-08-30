#ifndef FILESEL_H
#define FILESEL_H

#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include "class.h"
#include "../func.h"
#include "../random.h"

class aiscript::FileSelector {
private:
	static std::vector<std::string> files; // AIのスクリプトファイル一覧をフルパスで格納
public:
	static void filelist(); // ファイル一覧を用意！
	static std::string randomfile();
};

#endif
