/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "cur_state.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */
extern state cur_state;

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

state cur_state_get ( void ) {
	
	return cur_state;
}

void cur_state_set ( state st) {
	
	cur_state = st;
}

