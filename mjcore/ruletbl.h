#pragma once

#include "confitms.h"

#ifdef MJCORE_EXPORTS

class RuleData {
public:
	__declspec(dllexport) static void configinit();
	__declspec(dllexport) static void storeRule(const char** ruleTxt);
	__declspec(dllexport) static void exportRule(char** ruleTxt);
	__declspec(dllexport) static void getRuleName(LPTSTR const txt, unsigned bufsize, uint16_t RuleID);
	__declspec(dllexport) static void getRuleDescription(LPTSTR const txt, unsigned bufsize, uint16_t RuleID);
	__declspec(dllexport) static void getRuleTxt(LPTSTR const txt, unsigned bufsize, uint16_t RuleID, uint8_t index);
	static std::string getRuleItemTag(uint16_t RuleID, int index);
	static std::string getRuleItemTag(std::string RuleTag, int index);
	static std::string chkRule(std::string RuleTag);
	static bool chkRule(std::string RuleTag, std::string Expectation);
	static BOOL chkRule(const char* RuleTag, const char* Expectation);
	static bool chkRuleApplied(std::string RuleTag);
	static int getRule(std::string RuleTag);
	static int getRule(uint16_t RuleID);
	__declspec(dllexport) static int getRuleSize(uint16_t RuleID);
	__declspec(dllexport) static int loadConfigFile(const char* const filename);
	__declspec(dllexport) static int saveConfigFile(const char* const filename);
	static std::string getRuleMaskExpr(const std::string& RuleTag);
	__declspec(dllexport) static BOOL reqFailed(uint16_t ruleID, const int* const ruleStat);
	__declspec(dllexport) static void getPageCaption(LPTSTR const caption, unsigned bufsize, uint8_t page);
	static const char* ruleDigit();
	static void forEachRule(std::function<void (std::string, std::string)> f);
public:
	__declspec(dllexport) static void storePref(const char** ruleTxt);
	__declspec(dllexport) static void exportPref(char** ruleTxt);
	__declspec(dllexport) static int loadPreferenceFile(const char* const filename);
	__declspec(dllexport) static int savePreferenceFile(const char* const filename);
};

__declspec(dllexport) int getRule(int RuleID);
#endif
