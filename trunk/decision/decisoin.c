/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "decision.h"
#include "../../state_generator/state_generator.h"
#include "../../cur_state/cur_state.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

STATE decide ( void ) {
	
	return ST_gen ( cur_state_get () );
}

