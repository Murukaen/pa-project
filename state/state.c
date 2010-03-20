/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "state.h"
#include "../list/list.h"

/* ---- Macro #define ---- */

#define BMAP_NR_ST 8 // number of bitmaps in a state
#define BMAP_TP_OFF 2 // bitmap tags pieces offset ( 2 - 7 )
#define BMAP_BWP_OFF 6 // bitmap black/white pieces offset ( white : 2 - 7 ; black : 8 - 13 )

/* --- Types --- */

struct s_state {

	BITMAP V_BMAP[BMAP_NR_ST];

	UCHAR Table_W [SIZE_BMAP][SIZE_BMAP]; // 8x8 

	List Table_P [2][6]; // [2 players] x [6 types of pieces]

};

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

STATE ST_new(void) {

	STATE new_state = (STATE) calloc(1, sizeof(struct s_state));

	return new_state;
}

BITMAP ST_get_bitmap(STATE st, int tag) {

	return st -> V_BMAP[tag];
}

void ST_set_bitmap(STATE st, int tag, BITMAP b) {

	st -> V_BMAP[tag] = b;
}

void ST_set_table_W (STATE st, UCHAR ** T) {

	int i,j;
	for(i=0;i<SIZE_BMAP;++i)
		for(j=0;j<SIZE_BMAP;++j)
			st -> Table_W[i][j] = T[i][j];
	
}

void ST_set_table_P(STATE st, int player_tag, int piece_tag, List list) {

	st -> Table_P[ player_tag ][ piece_tag - BMAP_TP_OFF ] = list;
}

void ST_free(STATE st) {

	if (st == 0)
		return;
	free(st);
}

