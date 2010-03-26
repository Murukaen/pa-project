/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "state.h"
#include "../list/list.h"

/* ---- Macro #define ---- */

#define BMAP_NR_ST 8 // number of bitmaps in a state ; each for each general tag (0-7)
/* --- Types --- */

/* ~~~ STATE structure ~~~ */
struct s_state {

	BITMAP V_BMAP[BMAP_NR_ST];

	UCHAR Table_W[SIZE_BMAP][SIZE_BMAP]; // 8x8 ce piesa e acolo

	List Table_P[2][6]; // [2 colors] x [6 types of pieces] lista cu pozitiile pieselor pe tabla 
						// Table_P[x][y] = lista de pozitii pe tabla de joc a piesei de culoarea x (0 - white, 1 - black )
						// si de tag(tip) ( y + BMAP_TP_OFF (2-7) )

	/*  --- Used ONLY in state generator : --- */
	
	/* Desc : the TYPE ( tag ) of piece to be moved (2,7) */
	UCHAR piece_to_move;

	/* Desc : retains the index of the last made move */
	UCHAR move_index;

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

void ST_set_table_W(STATE st, UCHAR ** T) {

	int i, j;
	for (i = 0; i < SIZE_BMAP; ++i)
		for (j = 0; j < SIZE_BMAP; ++j)
			st -> Table_W[i][j] = T[i][j];

}

void ST_set_tag_Table_W(STATE st, int row, int col, UCHAR tag) {

	st -> Table_W[row][col] = tag;
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

void ST_set_piece_to_move(STATE st, UCHAR val) {

	st -> piece_to_move = val;
}

int ST_get_piece_to_move(STATE st){

	return st -> piece_to_move ;
}

void ST_set_move_index(STATE st, UCHAR val) {

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

void state_print ( STATE st , FILE * fout ) {
	
	fprintf(fout, "{\n V[T_WP] = %lld ;\n V[T_WP] = %lld ;\n V[T_BP] = %lld\n; V[T_K] = %lld ;\n V[T_Q] = %lld ;\n V[T_R] = %lld ;\n V[T_B] = %lld ;\n V[T_N] = %lld ;\n V[T_P] = %lld ;\n" , st -> V[0] , st -> V[1] , st -> V[2] , st -> V[3] , st -> V[4] , st -> V[5] , st -> V[6] , st -> V[7]);
}
