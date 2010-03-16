/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "../bitmap/bitmap.h"
#include "state.h"

/* ---- Macro #define ---- */

#define BMAP_NR_ST 8

/* --- Types --- */



struct s_state {
	
		BITMAP* V_BMAP;
		
		UCHAR Table_W [SIZE_BMAP][SIZE_BMAP];  // 8x8
		
};	

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

STATE ST_new(void) {

	STATE new_state = (STATE) calloc (1, sizeof(struct s_state));
	new_state -> V_BMAP = (BITMAP *) calloc ( BMAP_NR_ST , sizeof ( BITMAP ) );
 
	return new_state;
}

BITMAP ST_get_bitmap(STATE st, int tag) {

	return st -> V_BMAP[tag];
}

void ST_set_bitmap(STATE st, int tag, BITMAP b) {

	st -> V_BMAP[tag] = b;
}

void ST_set_table(STATE st, UCHAR** T){

	st -> Table_W = T;
}



void ST_free(STATE st) {

	if (st == 0)
		return;	
	if ( st -> V_BMAP != 0 ) free ( st -> V_BMAP );
	free(st);
}

