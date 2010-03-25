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

/* ~~~ state structure ~~~ */
struct s_state {

	BITMAP V_BMAP[BMAP_NR_ST];

	UCHAR Table_W[SIZE_BMAP][SIZE_BMAP]; // 8x8 ce piesa e acolo

	List Table_P[2][6]; // [2 players] x [6 types of pieces] lista cu pozitiile pieselor

	/*  --- Used only in state generator : --- */
	
	/* Desc : the TYPE ( tag ) of piece to be moved (2,7) */
	int piece_to_move;

	/* Desc : retains the index of the last made move */
	int move_index;

	/* Desc : current piece location [list] of the type (piece_to_move) which has to be processed by the state generating proocedure 
	 * It is a current element [list] in the list given by Table_P[f_ENG_COL][piece_to_move - BMAP_TP_OFF] */
	List cur_list; 

};
/* ~~~ END state structure ~~~ */

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

BITMAP ST_get_V_BMAP(STATE st,int flag){

	return st -> V_BMAP[flag];
}

void ST_set_table_W(STATE st, UCHAR ** T) {

	int i, j;
	for (i = 0; i < SIZE_BMAP; ++i)
		for (j = 0; j < SIZE_BMAP; ++j)
			st -> Table_W[i][j] = T[i][j];

}

void ST_set_tag_Table_W(STATE st, int row, int col, UCHAR tag) {

	st -> Table_W[row][col] = tag;
}

UCHAR ST_get_Table_W(STATE st,int i,int j){

	return st ->Table_W[i][j];
}

UCHAR ST_get_tag_Table_W(STATE st, int row, int col) {

	return st -> Table_W[row][col];
}

List ST_get_List_Table_P(STATE st, int col_tag, int piece_tag) {

	return st -> Table_P[col_tag][piece_tag - BMAP_TP_OFF];
}

void ST_set_List_Table_P(STATE st, int col_tag, int piece_tag, List list) {

	st -> Table_P[col_tag][piece_tag - BMAP_TP_OFF] = list;
}

void ST_set_piece_to_move(STATE st, int val) {

	st -> piece_to_move = val;
}

int ST_get_piece_to_move(STATE st){

	return st -> piece_to_move ;
}

void ST_set_move_index(STATE st, int val) {

	st -> move_index = val;
}

UCHAR ST_get_move_index(STATE S){

	return S -> move_index;
}

List ST_get_move_cur_list(STATE st){

	return st -> cur_list;
}

void ST_set_move_cur_list(STATE st,List l){

	st ->cur_list = l;
}


void ST_free(STATE st) {

	if (st == 0)
		return;
	free(st);
}
