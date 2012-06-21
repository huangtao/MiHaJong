#include "ruletbl.h"

static char ruleConf[RULESIZE/RULE_IN_LINE][RULE_IN_LINE + 1];
static array<uint8_t, RULESIZE> Rules;
using namespace std;

void parseRule() { // ルール設定を数値に変換
	debug("ルール設定を数値配列に変換します。");
	for (int i = 0; i < RULESIZE; i++) {
		string::size_type idx = string("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ").find(
			ruleConf[i / RULE_IN_LINE][i % RULE_IN_LINE] );
		Rules[i] = ((idx == string::npos) ? 0 : (uint8_t)idx);
	}
}

__declspec(dllexport) void storeRule(const char** ruleTxt) { // HSP→C++ ルール設定転送
	debug("HSP→C++ ルール転送");
	for (int i = 0; i < (RULESIZE/RULE_IN_LINE); i++)
		memcpy(ruleConf[i], ruleTxt[i], RULE_IN_LINE);
	parseRule();
	info("設定がロードされました。");
}

__declspec(dllexport) void exportRule(char** ruleTxt) { // C++→HSP ルール設定転送
	debug("C++→HSP ルール転送");
	for (int i = 0; i < (RULESIZE/RULE_IN_LINE); i++)
		memcpy(ruleTxt[i], ruleConf[i], RULE_IN_LINE);
}

__declspec(dllexport) int getRule(int RuleID) { // ルール設定を取得する
	return (int)Rules[RuleID];
}
inline uint8_t getRule(RuleCode RuleID) { // ルール設定を取得する
	return Rules[RuleID];
}
