/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "flags.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

/* Desc:
 * Flags init
 * 1.Engine not on move
 * 2.Engine plays black
 * Input:0
 * Output:0
 */
void flags_init (void) {
	
		f_ENG_ON_MOVE = 0; // Initially the engine is NOT on move
		f_ENG_COL = 1; // Initially the engine plays black
}
