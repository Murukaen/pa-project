/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "state.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

state state_new ( void ) {
	
	 state new_state = ( state ) calloc ( BMPS , sizeof ( bitmap ) );
	 
	 return new_state;
}

bitmap state_get_bitmap ( state st, int tag) {
	
	//TODO
}

void state_set_bitmap ( state st, int tag, bitmap bmp) {
	
	//TODO
}

void state_free ( state st) {
	
		if (st == 0 ) return;
		
	    free(st);
}

