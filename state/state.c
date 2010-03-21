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

void ST_set_table_W(STATE st, UCHAR ** T) {

	int i, j;
	for (i = 0; i < SIZE_BMAP; ++i)
		for (j = 0; j < SIZE_BMAP; ++j)
			st -> Table_W[i][j] = T[i][j];

}

void ST_set_tag_Table_W ( STATE st , int row , int col , UCHAR tag ) {
	
	st -> Table_W [row][col] = tag;
}

UCHAR ST_get_tag_Table_W ( STATE st , int row, int col) {
	
	return st -> Table_W [row][col];
}

List ST_get_List_Table_P ( STATE st , int col_tag , int piece_tag ) {
		
	return st -> Table_P [col_tag][piece_tag - BMAP_TP_OFF];
}	

void ST_set_List_Table_P (STATE st, int col_tag, int piece_tag, List list) {

	st -> Table_P [ col_tag ][ piece_tag - BMAP_TP_OFF ] = list;
}

void ST_free(STATE st) {

	if (st == 0)
		return;
	free(st);
}

