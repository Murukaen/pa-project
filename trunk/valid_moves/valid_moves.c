#include "valid_moves.h"
#include <stdlib.h>
#include "../Log/log.h"

#define LOG_VALIDATE_MOVE_FILE "Log/validate_move.log"

BITMAP VM_valid_pos(BITMAP posibile, BITMAP piese_albe) {

	BITMAP rez = posibile & (~piese_albe);

	return rez;
}

UCHAR VM_is_Check_if_piece_moves(STATE st, P_LOC loc) {

	if (loc == NULL) {
		/* LOG */
		log_print("locul primit de functia vmischeck e null",
				LOG_VALIDATE_MOVE_FILE);
		/* END LOG */
		exit(1);
	}
	/*identific piesele la mutare si aflu coordonatele piesei respectiv regelui*/
	UCHAR col_on_move = ST_get_col_on_move(st);
	int i, j;
	List l = ST_get_List_Table_Location(st, col_on_move, T_K);
	P_LOC king_loc = first_nod_list(&l);
	UCHAR row_king = LOC_get_row(king_loc), col_king = LOC_get_col(king_loc),
			row_piece = LOC_get_row(loc), col_piece = LOC_get_col(loc),
			piece_to_move = ST_get_piece_to_move(st), tag;

	/*fac bitmapul cu piesa la mutare, si bitmapul care arata locurile ce ataca regele*/
	BITMAP piece_pos = BM_Make_coord(row_piece, col_piece), attack_to_king =
			Moves[T_Q - 2][row_king][col_king];

	/*verific daca piesa mutata poate afecta intr un fel regele*/

	if ((piece_pos & attack_to_king) == 0) {// daca locatia piesei n are treaba cu cea a regelui
		return 0;
	} else { // daca piesa are treaba cu regele

		if (row_king == row_piece) { //daca e pe aceeasi linie(COLOANA)

			if (col_king < col_piece) { // daca regele e sub piesa

				for (i = col_king + 1; i < 8; i++) {
					tag = ST_get_tag_Table_What(st, row_king, i);
					if (col_on_move == 0) { // daca e albu la mutare
						if (tag == piece_to_move || tag == 255) {// daca nu e nicio piesa pe pozitia respectiva sau e piesa mutata sar peste
							continue;
						} else {// daca gasesc o alta piesa
							if (tag == T_Q + BWP_OFF || tag == T_R + BWP_OFF) { // verific daca e cumva regina sau tura neagra
								return 1;
							} else {
								return 0;
							}
						}

					} else {// daca e negru la mutare
						if (tag == piece_to_move + BWP_OFF || tag == 255) {
							continue;
						} else {
							if (tag == T_Q || tag == T_R) {
								return 1;
							} else {
								return 0;
							}
						}
					}
				}// daca nu intra in for
				return 0;
			} else { // daca regele e deasupra piesei

				for (i = col_king - 1; i >= 0; i--) {
					tag = ST_get_tag_Table_What(st, row_king, i);
					if (col_on_move == 0) { // daca e albu la mutare
						if (tag == piece_to_move || tag == 255) {// daca nu e nicio piesa pe pozitia respectiva sau e piesa mutata sar peste
							continue;
						} else {// daca gasesc o alta piesa
							if (tag == T_Q + BWP_OFF || tag == T_R + BWP_OFF) { // verific daca e cumva regina sau tura neagra
								return 1;
							} else {
								return 0;
							}
						}
					} else {// daca e negru la mutare
						if (tag == piece_to_move + BWP_OFF || tag == 255) {
							continue;
						} else {
							if (tag == T_Q || tag == T_R) {
								return 1;
							} else {
								return 0;
							}
						}
					}
				}// daca nu intra in for
				return 0;
			}

		} else if (col_king == col_piece) {// daca e pe aceeasi coloana(LINIE)

			if (row_king > row_piece) { // daca regele e in dreapta piesei

				for (i = row_king - 1; i >= 0; i--) {
					tag = ST_get_tag_Table_What(st, i, col_king);
					if (col_on_move == 0) { // daca e albu la mutare
						if (tag == piece_to_move || tag == 255) {// daca nu e nicio piesa pe pozitia respectiva sau e piesa mutata sar peste
							continue;
						} else {// daca gasesc o alta piesa
							if (tag == T_Q + BWP_OFF || tag == T_R + BWP_OFF) { // verific daca e cumva regina sau tura neagra
								return 1;
							} else {
								return 0;
							}
						}

					} else {// daca e negru la mutare
						if (tag == piece_to_move + BWP_OFF || tag == 255) {
							continue;
						} else {
							if (tag == T_Q || tag == T_R) {
								return 1;
							} else {
								return 0;
							}
						}
					}
				}// daca nu intra in for
				return 0;
			} else { // daca regele e in stanga piesei

				for (i = row_king + 1; i < 8; i++) {
					tag = ST_get_tag_Table_What(st, i, col_king);
					if (col_on_move == 0) { // daca e albu la mutare
						if (tag == piece_to_move || tag == 255) {// daca nu e nicio piesa pe pozitia respectiva sau e piesa mutata sar peste
							continue;
						} else {// daca gasesc o alta piesa
							if (tag == T_Q + BWP_OFF || tag == T_R + BWP_OFF) { // verific daca e cumva regina sau tura neagra
								return 1;
							} else {
								return 0;
							}
						}
					} else {// daca e negru la mutare
						if (tag == piece_to_move + BWP_OFF || tag == 255) {
							continue;
						} else {
							if (tag == T_Q || tag == T_R) {
								return 1;
							} else {
								return 0;
							}
						}
					}
				}// daca nu intra in for
				return 0;
			}
		} else if (row_piece > row_king && col_piece > col_king) { // daca piesa e pe diagonala dreapta sus

			for (i = row_king + 1, j = col_king + 1; i < 8 && j < 8; i++, j++) {

				tag = ST_get_tag_Table_What(st, i, j);
				if (col_on_move == 0) {

					if (tag == piece_to_move || tag == 255) {
						continue;
					} else {
						if (tag == T_Q + BWP_OFF || tag == T_B + BWP_OFF) { // verific daca e cumva regina sau tura neagra
							return 1;
						} else {
							return 0;
						}
					}
				} else {
					if (tag == piece_to_move + BWP_OFF || tag == 255) {
						continue;
					} else {
						if (tag == T_Q || tag == T_B) {
							return 1;
						} else {
							return 0;
						}
					}
				}
			}
			return 0;
		} else if (row_piece < row_king && col_piece > col_king) {// daca piesa e pe diagonala stanga sus

			for (i = row_king - 1, j = col_king + 1; i >= 0 && j < 8; i--, j++) {

				tag = ST_get_tag_Table_What(st, i, j);
				if (col_on_move == 0) {

					if (tag == piece_to_move || tag == 255) {
						continue;
					} else {
						if (tag == T_Q + BWP_OFF || tag == T_B + BWP_OFF) { // verific daca e cumva regina sau tura neagra
							return 1;
						} else {
							return 0;
						}
					}
				} else {
					if (tag == piece_to_move + BWP_OFF || tag == 255) {
						continue;
					} else {
						if (tag == T_Q || tag == T_B) {
							return 1;
						} else {
							return 0;
						}
					}
				}
			}
			return 0;
		} else if (row_piece < row_king && col_piece < col_king) {// daca e pe diagonala stanga jos

			for (i = row_king - 1, j = col_king - 1; i >= 0 && j >= 0; i--, j--) {

				tag = ST_get_tag_Table_What(st, i, j);
				if (col_on_move == 0) {

					if (tag == piece_to_move || tag == 255) {
						continue;
					} else {
						if (tag == T_Q + BWP_OFF || tag == T_B + BWP_OFF) { // verific daca e cumva regina sau tura neagra
							return 1;
						} else {
							return 0;
						}
					}
				} else {
					if (tag == piece_to_move + BWP_OFF || tag == 255) {
						continue;
					} else {
						if (tag == T_Q || tag == T_B) {
							return 1;
						} else {
							return 0;
						}
					}
				}
			}
			return 0;
		} else if (row_piece > row_king && col_piece < col_king) { // daca e pe diagonala dreapta jos
			for (i = row_king + 1, j = col_king - 1; i < 8 && j >= 0; i++, j--) {

				tag = ST_get_tag_Table_What(st, i, j);
				if (col_on_move == 0) {

					if (tag == piece_to_move || tag == 255) {
						continue;
					} else {
						if (tag == T_Q + BWP_OFF || tag == T_B + BWP_OFF) { // verific daca e cumva regina sau tura neagra
							return 1;
						} else {
							return 0;
						}
					}
				} else {
					if (tag == piece_to_move + BWP_OFF || tag == 255) {
						continue;
					} else {
						if (tag == T_Q || tag == T_B) {
							return 1;
						} else {
							return 0;
						}
					}
				}
			}
			return 0;
		} else {
			/* LOG */
			log_print(
					"problema la validare mutare , verificare sah :( cam o ora debugg estimez!!",
					LOG_VALIDATE_MOVE_FILE);
			/* END LOG */

			exit(1);
		}
	}
	/* LOG */
	log_print("validare mutare sah, s a ajuns unde nu trebuia , e nashpa!",
			LOG_VALIDATE_MOVE_FILE);
	/* END LOG */

	exit(1);
	return 0;
}

BITMAP VM_valid_moves(STATE st, P_LOC loc_piesa) {

	UCHAR piece_row = LOC_get_row(loc_piesa), piece_col =
			LOC_get_col(loc_piesa);
	int i, j;
	UCHAR M[8][8], ce_piesa, col_on_move = ST_get_col_on_move(st);

	switch (ST_get_piece_to_move(st)) {

	case T_R:

		for (i = piece_col + 1; i < 8; i++) {
			ce_piesa = ST_get_tag_Table_What(st, piece_row, i);
			if (col_on_move == 0) {// daca tura alba


				if (ce_piesa < 8) {// daca e piesa alba
					break;
				} else if (ce_piesa < T_NA) { // daca piesa neagra
					M[piece_row][i] = 1;
					break;
				} else {// daca pozitie libera
					M[piece_row][i] = 1;
				}
			} else { // daca tura neagra

				if (ce_piesa >= 8 && ce_piesa < 14) { //daca piesa neagra
					break;
				} else if (ce_piesa < 8) {// daca piesa alba
					M[piece_row][i] = 1;
					break;
				} else {// daca spatiu liber
					M[piece_row][i] = 1;
				}
			}
		}

	}
}
