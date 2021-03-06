﻿#include "font.h"
#include "init.h"
#include "resource.h"
#ifdef _WIN32
#include <windows.h>
#else /*_WIN32*/
#include "filenum.h"
#include <cstdio>
#include <iostream>
#endif /*_WIN32*/
#include <cstdint>
#include <sstream>
#include <cassert>

using std::uint8_t;

namespace mihajong_graphic {

namespace {
#ifdef _WIN32
	void LoadFileInResource(int name, int type, DWORD& size, const uint8_t*& data) {
		HRSRC rc = FindResource(GraphicDLL, MAKEINTRESOURCE(name), MAKEINTRESOURCE(type));
		DWORD err = GetLastError();
		assert(rc != nullptr);
		HGLOBAL rcData = LoadResource(GraphicDLL, rc);
		assert(rcData != nullptr);
		size = SizeofResource(GraphicDLL, rc);
		assert(size != 0);
		data = static_cast<const uint8_t*>(::LockResource(rcData));
	}
#else /*_WIN32*/
	void LoadFileInResource(int name, int type, size_t& size, const uint8_t*& data) {
		static uint8_t* dat = nullptr;
		std::string fileName = dataFileName(name);
		FILE* file = fopen(fileName.c_str(), "rt");
		if (!file) {
			std::cerr << "Cannot open " << fileName << std::endl;
			throw _T("フォントマップの読み込みに失敗しました");
		}
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
		dat = reinterpret_cast<uint8_t*>(realloc(dat, size + 1));
		assert(dat != nullptr); // If realloc() fails, then die!
		fread(dat, 1, size, file);
		dat[size] = 0;
		fclose(file);
		data = dat;
	}
#endif /*_WIN32*/
}

FontMap* FontMap::instantiate() {
	static FontMap myInstance;
	return &myInstance;
}

FontMapLargeChr* FontMapLargeChr::instantiate() {
	static FontMapLargeChr myInstance;
	return &myInstance;
}

FontMapSmallChr* FontMapSmallChr::instantiate() {
	static FontMapSmallChr myInstance;
	return &myInstance;
}

FontMapCallDigits* FontMapCallDigits::instantiate() {
	static FontMapCallDigits myInstance;
	return &myInstance;
}

FontMapScoreDigits* FontMapScoreDigits::instantiate() {
	static FontMapScoreDigits myInstance;
	return &myInstance;
}

void FontMapClass::readCharMap(int ResourceNum) {
#ifdef _WIN32
	DWORD size;
#else /*_WIN32*/
	size_t size;
#endif /*_WIN32*/
	const uint8_t* data;
	LoadFileInResource(ResourceNum, CHARMAP_FILE, size, data);
	std::istringstream charmap(std::string(reinterpret_cast<const char*>(data), static_cast<size_t>(size)));
	while (true) {
		unsigned chrnum, mapped_to; char flag;
		charmap >> std::hex >> chrnum >> flag >> std::dec >> mapped_to;
		if ((chrnum == 0) || (flag == '!')) break; // sentinel
		m.insert(fMapDat(static_cast<wchar_t>(chrnum), std::make_pair((flag == '*'), mapped_to)));
	}
}

FontMapClass::charAttr FontMapClass::map(wchar_t c) {
	if (m.find(c) != m.end()) return m[c];
	else return std::make_pair(true, Default_Chr());
}

FontMapClass::~FontMapClass() {
}

FontMap::FontMap() {
	readCharMap(IDB_CHARMAP_FONT);
}

FontMapLargeChr::FontMapLargeChr() {
	readCharMap(IDB_CHARMAP_FONT_HUGE);
}

FontMapSmallChr::FontMapSmallChr() {
	readCharMap(IDB_CHARMAP_FONT_SMALL);
}

FontMapCallDigits::FontMapCallDigits() {
	readCharMap(IDB_CHARMAP_CALL_DIGITS);
}

FontMapScoreDigits::FontMapScoreDigits() {
	readCharMap(IDB_CHARMAP_SCORE_DIGITS);
}

}
