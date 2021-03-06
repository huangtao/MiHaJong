#pragma once

#ifdef _WIN32
#include <windows.h>
#endif /*_WIN32*/
#include <cstdint>
#include <string>
#include "../common/strcode.h"
#include "exports.h"

namespace mihajong_graphic {
namespace rules {

typedef void (*RetrieveTxt)(LPTSTR const /*txt*/, unsigned /*bufsize*/, uint16_t /*RuleID*/);
typedef void (*RetrieveTxtIndex)(LPTSTR const /*txt*/, unsigned /*bufsize*/, uint16_t /*RuleID*/, uint8_t /*index*/);
typedef int (*RetrieveInt)(uint16_t /*RuleID*/);
#ifdef _WIN32
typedef BOOL (*CheckDep)(uint16_t /*RuleID*/, const int* const /* ruleStat */);
#else /*_WIN32*/
typedef bool (*CheckDep)(uint16_t /*RuleID*/, const int* const /* ruleStat */);
#endif /*_WIN32*/
typedef void (*RetrieveCaption)(LPTSTR const /*txt*/, unsigned /*bufsize*/, uint8_t /*page*/);
typedef void (*RuleWrite)(const char** /*ruleTxt*/);
typedef void (*RuleRead)(char** /*ruleTxt*/);
typedef int (*ConfSave)(const char* const /*filename*/);
#ifdef _WIN32
typedef BOOL (*CheckRule)(const char* /*RuleTag*/, const char* /*Expectation*/);
#else /*_WIN32*/
typedef bool (*CheckRule)(const char* /*RuleTag*/, const char* /*Expectation*/);
#endif /*_WIN32*/
typedef unsigned int (*RetrieveUInt)(uint16_t /*RuleID*/);
typedef const char* (*RetrieveStr)(uint16_t /*RuleID*/);
typedef void (*SetStr)(uint16_t /*RuleID*/, const char* /*str*/);

#ifdef GRAPHIC_EXPORTS
extern RetrieveTxt getRuleName, getPreferenceName;
extern RetrieveTxt getRuleDescription, getPreferenceDescription;
extern RetrieveTxtIndex getRuleTxt, getPreferenceTxt;
extern RetrieveInt getRule, getPreference;
extern RetrieveInt getRuleSize, getPreferenceSize;
extern CheckDep reqFailed;
extern RetrieveCaption getPageCaption;
extern RuleWrite storeRule, storePref;
extern RuleRead exportRule, exportPref;
extern ConfSave saveConfigFile, savePreferenceFile;
extern CheckRule chkRule, chkPreference;
extern RetrieveUInt getPreferenceInputSize;
extern RetrieveStr getPreferenceRawStr;
extern SetStr setPreferenceFreeStr;
extern const char* digit;
extern std::string conffile, preffile;
#endif

EXPORT void setfunc(
	RetrieveTxt fpGetRuleName, RetrieveTxt fpGetRuleDesc, RetrieveTxtIndex fpGetRuleTxt,
	RetrieveInt fpGetRule, RetrieveInt fpGetRuleSize, CheckDep fpReqFailed,
	RetrieveCaption fpGetPageCaption, RuleWrite fpStoreRule, RuleRead fpExportRule,
	ConfSave fpSaveConfigFile, CheckRule fpChkRule, const char* pDigit,
	RuleWrite fpStorePref, RuleRead fpExportPref, ConfSave fpSavePreferenceFile,
	RetrieveTxt fpGetPreferenceName, RetrieveTxt fpGetPreferenceDesc, RetrieveTxtIndex fpGetPreferenceTxt,
	RetrieveInt fpGetPreference, RetrieveInt fpGetPreferenceSize,
	RetrieveUInt fpGetPreferenceInputSize, RetrieveStr fpGetPreferenceRawStr, SetStr fpSetPreferenceFreeStr,
	CheckRule fpChkPreference);

EXPORT void setconffile(const char* filename, const char* filename2);

}
}
