/*=============================
 * HSP麻雀クライアントMiHaJong
 *      [専用DLLの設定]
 *=============================
 */

#uselib "mjlib.dll"

/* ロギングツール */
/*
#func global _initlog_ "?initLogger@logger@@YAHXZ"
#func global _trace_msg_ "?trace_msg@logger@@YAXPBD@Z" str
#func global _debug_msg_ "?debug_msg@logger@@YAXPBD@Z" str
#func global _info_msg_ "?info_msg@logger@@YAXPBD@Z" str
#func global _warn_msg_ "?warn_msg@logger@@YAXPBD@Z" str
#func global _error_msg_ "?error_msg@logger@@YAXPBD@Z" str
#func global _fatal_msg_ "?fatal_msg@logger@@YAXPBD@Z" str
*/

/* ルールコンフィグ */
/*
#func global _storeRule "?storeRule@@YAXPAPAD@Z" var
#func global _exportRule "?exportRule@@YAXPAPAD@Z" var
*/
#cfunc global getRule "?getRule@@YAHH@Z" int

/* func.hspからの移植 */
#cfunc global playerwind "?playerwind@@YAHHH@Z" int, int
#cfunc global playerRelative "?playerRelative@@YAHHH@Z" int, int
#cfunc global RelativePositionOf "?RelativePositionOf@@YAHHH@Z" int, int
#cfunc global roundLoopRate "?roundLoopRate@@YAHXZ"
#cfunc global tilesLeft "?tilesLeft@@YAHPAUGameTable@@@Z" int
#func global calcRanc "?calcRanc@@YAXPAHPAUGameTable@@@Z" var, int
#cfunc global isPao "?isPao@@YAHPAUGameTable@@HH@Z" int, int, int
#cfunc global isPaoAgari "?isPaoAgari@@YAHPAUGameTable@@H@Z" int, int
#cfunc global isGotPao "?isGotPao@@YAHPAUGameTable@@H@Z" int, int
#cfunc global getPaoPlayer "?getPaoPlayer@@YAHPAUGameTable@@H@Z" int, int
#cfunc global RonPlayers "?RonPlayers@@YAHPAUGameTable@@@Z" int
