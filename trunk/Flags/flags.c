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

UCHAR f_ENG_QUIT;

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void flags_init (void) {
	
		set_engine_col (1); // Initially the engine plays black
		set_engine_lock (1) ; // Wait for initial Communication with XBoard
		set_engine_quit ( 0 );
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

UCHAR get_engine_quit ( void ) {
	
	return f_ENG_QUIT;
}

void set_engine_quit ( UCHAR val ) {
	
	f_ENG_QUIT = val;
}


