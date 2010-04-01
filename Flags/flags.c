/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "flags.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

UCHAR f_ENG_COL;

UCHAR f_ENG_LOCK;

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void flags_init (void) {
	
		set_engine_col (1); // Initially the engine plays black
		set_engine_lock (1) ; // Wait for initial Communication with XBoard
}

UCHAR get_engine_col ( void ) {
	
	return f_ENG_COL;
}

void set_engine_col ( UCHAR val ) {
	
	f_ENG_COL = val;
}

UCHAR get_engine_lock ( void ) {
	
	return f_ENG_LOCK;
}

void set_engine_lock ( UCHAR val ) {
	
	f_ENG_LOCK = val;
}


