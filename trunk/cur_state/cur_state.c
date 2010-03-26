/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "cur_state.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */
STATE cur_state;

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

STATE cur_state_get ( void ) {
	
	return cur_state;
}

void cur_state_set ( STATE st) {
	
	cur_state = st;
}

void cur_state_free ( void ) {
	
	ST_free ( cur_state );
}

