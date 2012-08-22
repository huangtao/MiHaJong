#include "ini2map.h"

void INIParser::parseini(IniMapMap& inimap, const char* ini) {
	/*
	 *  CSVをパースして配列の配列オブジェクトに代入する
	 *
	 *  制限事項
	 *  ・CRを無視します
	 *  ・最初のセクション宣言までは無視されます
	 */
	inimap.clear(); // まずリセットする
	std::string tmpstr; // 作業用文字列
	std::string currentsection; // 現在有効なセクション名
	std::string recordname; // 現在有効なレコード名
	RECORD section;
	char tmpletter[2] = {0, 0};
	bool started = false; bool firstchr = true; bool iscomment = false;
	bool issectionname = false; bool isrecordentity = false;
	for (const char* ptr = ini; *ptr != '\0'; ptr++) { // ポインタのforとか使ったことあれへん……
		if (*ptr == '\r') continue; // just ignore a CR
		else if (*ptr == '\n') { // new line
			if (firstchr) continue; // null line
			else if (issectionname) { // End of the section declaration
				if (!section.empty()) {
					inimap.insert(IniMapMap::value_type(currentsection, section)); section.clear();
				}
				currentsection = tmpstr; tmpstr.clear();
			}
			else if ((!iscomment) && (isrecordentity)) { // End of the record
				section.insert(RECORD::value_type(recordname, tmpstr)); tmpstr.clear(); recordname.clear();
			}
			else if (!iscomment) { // Invalid: just ignore it
				tmpstr.clear(); recordname.clear();
			}
			firstchr = true; iscomment = issectionname = isrecordentity = false;
			continue;
		}
		else if ((*ptr == ';') && (firstchr)) { // beginning of a comment
			firstchr = false; iscomment = true; continue; // mark as a comment
		}
		else if ((*ptr == '[') && (firstchr)) { // beginning of a section
			firstchr = false; started = true; issectionname = true; continue;
		}
		else if ((*ptr == ']') && (issectionname)) { // end of a section name
			firstchr = false; iscomment = true; continue; // ignore until newline encountered
		}
		else if ((!iscomment) && (started)) {
			if ((*ptr == '=') && (!issectionname) && (!isrecordentity)) { // delimiter
				isrecordentity = true; recordname = tmpstr; tmpstr.clear(); firstchr = false;
			}
			else { // data
				tmpletter[0] = *ptr; tmpstr += tmpletter; firstchr = false;
			}
		}
	}
	if ((!firstchr) && (!iscomment) && (isrecordentity)) { // End of the record, without an NL
		section.insert(RECORD::value_type(recordname, tmpstr)); tmpstr.clear(); recordname.clear();
	}
	if (!section.empty()) {
		inimap.insert(IniMapMap::value_type(currentsection, section)); section.clear();
	}
}
