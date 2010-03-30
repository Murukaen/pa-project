#include "valid_moves.h"
#include <stdlib.h>

BITMAP VM_valid_pos(BITMAP posibile, BITMAP piese_albe) {

	BITMAP rez = posibile & (~piese_albe);

	return rez;
}

UCHAR VM_is_Check_if_piece_moves(STATE st, P_LOC loc) {

	int i;
	if (loc == NULL) {
		printf("locul primit de functia vmischeck e null");
		exit(1);
	}
	/*identific piesele la mutare si aflu coordonatele piesei respectiv regelui*/
	UCHAR col_on_move = ST_get_col_on_move(st);
	List l = ST_get_List_Table_Location(st, col_on_move, T_K);
	P_LOC king_loc = first_nod_list ( &l );
	UCHAR row_king = LOC_get_row(king_loc), col_king = LOC_get_col(king_loc),
			row_piece = LOC_get_row(loc), col_piece = LOC_get_col(loc);

	/*fac bitmapul cu piesa la mutare, si bitmapul care arata locurile ce ataca regele*/
	BITMAP piece_pos = BM_Make_coord(row_piece, col_piece), attack_to_king =
			Moves[T_Q - 2][row_king][col_king];

	/*verific daca piesa mutata poate afecta intr un fel regele*/

	if ((piece_pos & attack_to_king) == 0) {// daca locatia piesei n are treaba cu cea a regelui
		return 0;
	} else { // daca piesa are treaba cu regele

		if (row_king == row_piece) { //daca e pe aceeasi linie(COLOANA)

			if (col_king < col_piece) { // daca regele e sub piesa

				for (i = col_king + 1; i < col_piece; i++) {

					if (ST_get_tag_Table_What(st, row_king, i) != 255) {
						return 0;
					}
				}
			}

		}

	}

}
