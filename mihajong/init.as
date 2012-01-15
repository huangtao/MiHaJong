/*=============================
 * HSP麻雀クライアントMiHaJong
 *  [プラグインの読み込み等]
 *=============================
 */

/* コンパイル時のオプション */
#packopt hide 1
#packopt type 0
#cmpopt ppout 1
#cmpopt optcode 1
#cmpopt optinfo 0
#cmpopt varname 1
#runtime "hsp3mt"

#define WITH_MT19937AR
#define WITH_ADVANCEDCONTROL

/* 拡張機能の登録 */
#include "p2b.as"
#include "hmm.as"
#include "hspsock.as"
#include "llmod3.hsp"
#include "obj.hsp"
#include "l_tooltips.as"
#define tooltip(%1,%2) AddToolTips (%1)+1,%2
#define global STATBOX 1
#define vanish clrobj:SetToolTips
#define vanish2 clrobj 4+1+STATBOX
#ifdef WITH_MT19937AR
	#undef rnd
	#undef randomize
	#module redef
	#defcfunc rnd int p1
	#include "hspda.as"
		z=0: rndf_geti z, p1
		return z
	#deffunc randomize
		rndf_int -1
		return
	#global
#endif
#include "hspmath.as"
#include "hsplzmax.as"
#undef charlower
#undef charupper
#ifdef WITH_ADVANCEDCONTROL
	#include "mod_customizebutton.hsp"
#else
	#define global ColorButton(%1, %2, %3=0x80000000, %4=0x80000000) button %1, %2
	#define global _bc_text(%1, %2) objprm %1, %2
	#define global _bc_color(%1, %2, %3) /**/
#endif
#include "user32.as"

#ifdef NOWAIT
	#undef await
	#define global await(%1) await@hsp 0
#endif
