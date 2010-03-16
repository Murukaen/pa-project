/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "state.h"

/* ---- Macro #define ---- */

#define BMAP_NR_ST 8

/* --- Types --- */

struct s_state {

	BITMAP V_BMAP[BMAP_NR_ST];

	UCHAR Table_W[2][SIZE_BMAP][SIZE_BMAP]; // 8x8

	lista Table_P[2][6];

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

void ST_set_table_W(STATE st, UCHAR** T, UCHAR player_tag) {

	st -> Table_W[player_tag] = T;
}

void ST_set_table_P(STATE st, int player_tag, int piece_tag, lista list) {

	st -> Table_P[player_tag][piece_tag - 2] = list;
}

void ST_free(STATE st) {

	if (st == 0)
		return;
	free(st);
}

