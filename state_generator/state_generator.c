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
#include "../list/list.h"
#include "../compare/compare.h"

/* ---- Macro #define ---- */
#define NR_PIECES 5

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

STATE state_gen(STATE start_state) {

	UCHAR index = ST_get_move_index(start_state);
	List L = ST_get_move_cur_list(start_state);
	int i, j, k;
	P_LOC loc;
	BITMAP valid_moves;
	STATE new_state = ST_new();
	List copy_list = new_list();

	for (loc = first_nod_list(&L); loc; index = 0) {

		valid_moves = BM_valid_pos(
				Moves[T_N - 2][LOC_get_row(loc)][LOC_get_col(loc)],
				ST_get_bitmap(start_state, f_ENG_COL));

		for (i = index; i < 64; i++) {

			if (BM_Make_pos(i) & valid_moves) {

				/*setez noul index*/
				ST_set_move_index(new_state, i);
				/*setez cur list*/
				ST_set_move_cur_list(new_state, L);

				/* setez noile V_BMAP*/

				for (j = 0; j < 8; j++) { // le recopiez pe toate

					ST_set_bitmap(new_state, i, ST_get_bitmap(start_state, i));
				}

				if (f_ENG_COL == 0) { // ma uit in care bitmap de ce culoare tre sa sterg

					BITMAP new = ST_get_V_BMAP(start_state, 0);
					BM_Clear_piece_at_BMAP(&new, BM_Make_coord(
							LOC_get_row(loc), LOC_get_col(loc)));
					BM_Put_piece_at_coord(&new, i / 8, i % 8);
					ST_set_bitmap(new_state, T_WP, new);

				} else {

					BITMAP new = ST_get_V_BMAP(start_state, 1);
					BM_Clear_piece_at_BMAP(&new, BM_Make_coord(
							LOC_get_row(loc), LOC_get_col(loc)));
					BM_Put_piece_at_coord(&new, i / 8, i % 8);
					ST_set_bitmap(new_state, T_BP, new);
				}

				/*refac bitmapul pentru cai*/
				new = ST_get_V_BMAP(start_state, T_N);
				BM_Clear_piece_at_BMAP(&new, BM_Make_coord(LOC_get_row(loc),
						LOC_get_col(loc)));
				BM_Put_piece_at_coord(&new, i / 8, i % 8);
				ST_set_bitmap(new_state, T_BP, new);

				/*copiez in new_state vechea lista de pozitii pt piese*/
				for (j = 0; j < 2; j++) {
					for (k = 0; k < 6; k++) {
						ST_set_List_Table_P(new_state, j, k, copy_list(
								ST_get_List_Table_P(start_state, j, k)));
					}
				}
				/*daca a fost captura*/
				if (!BM_Compare_BMAPs(ST_get_V_BMAP(start_state, ~f_ENG_COL),
						BM_Make_coord(LOC_get_row(loc), LOC_get_col(loc)))) {

					/*identific piesa capturata*/
					UCHAR piece_to_delete = ST_get_Table_W(start_state, i / 8,
							i % 8);

					/* iau bitmapul pieselor de tipul celei capturate si il modific*/
					new = ST_get_V_BMAP(start_state, piece_to_delete);
					BM_Clear_piece_at_BMAP(&new, BM_Make_coord(i / 8, i % 8));
					ST_set_bitmap(new_state, T_BP, new);

					/* sterg din lista new_state piesa care a fost capturata*/
					delete_element_list(&ST_get_List_Table_P(new_state,
							~f_ENG_COL, piece_to_delete), loc, fequ_loc,
							ffree_loc);
				}

				/*modific din lista new_state locatia piesei mutate*/
				P_LOC loc_modificat = find_nod_list(ST_get_List_Table_P(
						new_state, f_ENG_COL, T_N), &loc, fequ_loc);
				LOCp_set_both(loc_modificat, i / 8, i % 8);

				/*am refacut table_w*/
				ST_set_tag_Table_W(new_state, i / 8, i % 8, T_N);
				ST_set_tag_Table_W(new_state, LOC_get_row(loc),
						LOC_get_col(loc));

			}

			return new_state;
		}
	}
	return 0;
}

void ST_gen_init(void) {

	Read_all_possible_moves(Moves);
}
