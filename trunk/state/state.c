/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "../bitmap/bitmap.h"
#include "state.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

STATE ST_new(void) {

	STATE new_state = (STATE) calloc(ST_fields, sizeof(BITMAP));

	return new_state;
}

BITMAP ST_get_bitmap(STATE st, int tag) {

	return st[tag];
}

void ST_set_bitmap(STATE st, int tag, BITMAP b) {

	st[tag] = b;
}

void ST_free(STATE st) {

	if (st == 0)
		return;
	free(st);
}

