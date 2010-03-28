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
#include "../Util/util.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

STATE ST_gen(STATE start_state) {

	UCHAR index = ST_get_move_index(start_state), i, j, k;
	UCHAR col_on_move = ST_get_col_on_move(start_state);

	List L = ST_get_cur_poz_in_list(start_state);
	P_LOC loc;
	BITMAP valid_moves, new_bmap;

	STATE new_state = ST_new();

	for (loc = first_nod_list(&L); loc; index = 0, loc = first_nod_list(&L)) {

		UCHAR old_c = LOC_get_col(loc), old_r = LOC_get_row(loc);

		// mai trebuie verificat daca nu cumva e sah daca mut piesa
		valid_moves = VM_valid_pos(Moves[T_N - 2][old_r][old_c], ST_get_bitmap(
				start_state, col_on_move));

		if (valid_moves == 0) {
			break;
		}

		for (i = index; i < 64; i++) {

			UCHAR new_r = i / 8, new_c = i % 8;

			/*daca exista mutari valide,in afara de sah, ca nu am facut mai sus verificarea*/
			if ((BM_Make_pos(i) & valid_moves) != 0) {

				/*setez noul index*/
				ST_set_move_index(new_state, i + 1);

				/* setez noile V_BMAP*/

				for (j = 0; j < 8; j++) { // le recopiez pe toate

					ST_set_bitmap(new_state, j, ST_get_bitmap(start_state, j));

				}

				/*refac bitmapul pieselor de culoarea celui care muta */

				new_bmap = ST_get_bitmap(start_state, col_on_move);
				BM_Clear_piece_at_BMAP(&new_bmap, BM_Make_coord(old_r, old_c));
				BM_Put_piece_at_coord(&new_bmap, new_r, new_c);
				ST_set_bitmap(new_state, col_on_move, new_bmap);

				/*refac bitmapul pentru cai*/

				new_bmap = ST_get_bitmap(start_state, T_N);
				BM_Clear_piece_at_BMAP(&new_bmap, BM_Make_coord(old_r, old_c));
				BM_Put_piece_at_coord(&new_bmap, new_r, new_c);
				ST_set_bitmap(new_state, T_N, new_bmap);

				/*copiez in new_state vechea lista de pozitii pt piese*/
				for (j = 0; j < 2; j++) {
					for (k = 0; k < 6; k++) {
						ST_set_List_Table_Location(new_state, j,
								k + PIECES_OFF, list_copy(
										ST_get_List_Table_Location(start_state,
												j, k + PIECES_OFF), LOC_alloc));
					}
				}

				/*daca a fost captura*/
				if (BM_Equal1_BMAPs(
						ST_get_bitmap(start_state, not(col_on_move)),
						BM_Make_coord(new_r, new_c)) == 1) {

					/*identific piesa capturata*/
					UCHAR piece_to_delete = ST_get_tag_Table_What(start_state,
							new_r, new_c);
					if (col_on_move == 1) {
						piece_to_delete -= 6;
					}
					/* iau bitmapul pieselor de tipul celei capturate si il modific*/
					new_bmap = ST_get_bitmap(start_state, piece_to_delete);
					BM_Clear_piece_at_BMAP(&new_bmap, BM_Make_coord(new_r,
							new_c));
					ST_set_bitmap(new_state, piece_to_delete, new_bmap);

					/*modific bitmapul pieselor ~col_on_move*/
					new_bmap = ST_get_bitmap(start_state, not(col_on_move));
					BM_Clear_piece_at_BMAP(&new_bmap, BM_Make_coord(new_r,
							new_c));
					ST_set_bitmap(new_state, not(col_on_move), new_bmap);

					/* sterg din lista new_state piesa care a fost capturata*/
					List aux_l = ST_get_List_Table_Location(new_state, not(
							col_on_move), piece_to_delete);
					P_LOC to_del = LOC_new();
					LOCp_set_both(to_del, new_r, new_c);
					delete_elem_list(aux_l, (void *) to_del, fequ_loc, LOC_free);
				}

				/*modific din lista lui new_state locatia piesei mutate*/
				P_LOC loc_modificat = (P_LOC) find_nod_list(
						ST_get_List_Table_Location(start_state, col_on_move,
								T_N), &loc, fequ_loc);
				LOC_print(stdout, loc_modificat);
				return 0;
				LOCp_set_both(loc_modificat, new_r, new_c);

				/*pun in noua stare cur_poz in list*/
				List aux_l1 = ST_get_List_Table_Location(new_state,
						col_on_move, T_N);
				ST_set_cur_poz_in_list(new_state, aux_l1);

				/*am refacut Table_What*/
				ST_set_tag_Table_What(new_state, new_r, new_c, T_N);
				ST_set_tag_Table_What(new_state, old_r, old_c, 255);

				/*pun in noua stare culoarea la mutare*/
				ST_set_col_on_move(new_state, not(col_on_move));

				/*setez in noua stare tot calu la mutare*/
				ST_set_piece_to_move(new_state, T_N);
				return new_state;
			}

		}
	}
	printf("fara cai ");
	return 0;
}

void ST_gen_init(void) {

	Read_all_possible_moves(Moves);
}
