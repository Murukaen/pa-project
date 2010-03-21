/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "../bitmap/bitmap.h"
#include "state_generator.h"
#include "../read_from_file/read_from_file.h"
#include "../state/state.h"
#include "../Flags/flags.h"
#include "../valid_moves/valid_moves.h"

/* ---- Macro #define ---- */
#define NR_PIECES 5

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

STATE state_gen(STATE start_state) {

	UCHAR index = ST_get_move_index(start_state);
	List L = ST_get_move_cur_list(start_state);
	int i, j,k;
	P_LOC loc;
	BITMAP valid_moves;
	STATE new_state = ST_new();

	for (loc = first_nod_list(&L); loc; index = 0) {

		valid_moves = BM_valid_pos(
				Moves[T_N - 2][LOC_get_row(loc)][LOC_get_col(loc)],
				ST_get_bitmap(start_state, f_ENG_COL));

		for (i = index; i < 64; i++) {

			if (BM_Make_pos(i) & valid_moves) {

				ST_set_move_index(new_state, i);
				ST_set_move_cur_list(new_state, L);



				for (j = 0; j < 8; j++) {

					ST_set_bitmap(new_state, i, ST_get_bitmap(start_state, i));
				}
				if (f_ENG_COL == 0) {

					BITMAP new = ST_get_V_BMAP(start_state, 0);
					BM_Clear_piece_at_BMAP(&new, BM_Make_coord(LOC_get_row(loc), LOC_get_col(loc)));
					BM_Put_piece_at_coord(&new, i / 8, i % 8);
					ST_set_bitmap(new_state, T_WP, new);

				} else {

					BITMAP new = ST_get_V_BMAP(start_state, 1);
					BM_Clear_piece_at_BMAP(&new, BM_Make_coord(LOC_get_row(loc), LOC_get_col(loc)));
					BM_Put_piece_at_coord(&new, i / 8, i % 8);
					ST_set_bitmap(new_state, T_BP, new);
				}

				for(j = 0;j<8;j++){

					for(k=0;k<8;k++){

						ST_set_tag_Table_W(new_state,j,k,)
					}

				}

				return new_state;
			}
		}

	}

	return 0;
}

void ST_gen_init(void) {

	Read_all_possible_moves(Moves);
}
