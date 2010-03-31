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

UCHAR f_INIT_COM;

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void flags_init (void) {
	
		set_engine_col (1); // Initially the engine plays black
		set_init_com (0) ; // Wait for initial Communication with XBoard
}

UCHAR get_engine_col ( void ) {
	
	return f_ENG_COL;
}

void set_engine_col ( UCHAR val ) {
	
	f_ENG_COL = val;
}

UCHAR get_init_com ( void ) {
	
	return f_INIT_COM;
}

void set_init_com ( UCHAR val ) {
	
	f_INIT_COM = val;
}


