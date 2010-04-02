#include "valid_moves.h"
#include <stdlib.h>
#include "../Log/log.h"
#include "../list/list.h"
#include "../Util/util.h"

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

int VM_validate_King_move(STATE st, LOC loc) {

	UCHAR row = loc.row, col = loc.col, col_on_move = ST_get_col_on_move(st),
			tag, regina, pion, tura, nebun, rege;
	LOC Locuri[8];
	int i, j;

	if (col_on_move == 1) {
		regina = T_Q;
		rege = T_K;
		pion = T_P;
		tura = T_R;
		nebun = T_B;
	} else {
		regina = T_Q + BWP_OFF;
		rege = T_K + BWP_OFF;
		pion = T_P + BWP_OFF;
		tura = T_R + BWP_OFF;
		nebun = T_B + BWP_OFF;
	}

	for (i = row + 1; i < 8; i++) { // ma uit pe linie in dreapta

		tag = ST_get_tag_Table_What(st, i, col);
		if (tag != T_NA) {
			if (tag == regina || tag == tura) {
				return 1;
			} else {
				break;
			}
		}
	}

	for (i = row - 1; i >= 0; i--) {// ma uit pe linie in stanga

		tag = ST_get_tag_Table_What(st, i, col);
		if (tag != T_NA) {
			if (tag == regina || tag == tura) {
				return 1;
			} else {
				break;
			}
		}
	}

	for (i = col + 1; i < 8; i++) {// ma uit pe col in sus

		tag = ST_get_tag_Table_What(st, row, i);
		if (tag != T_NA) {
			if (tag == regina || tag == tura) {
				return 1;
			} else {
				break;
			}
		}
	}
	for (i = col - 1; i >= 0; i--) {// ma uit pe col in jos

		tag = ST_get_tag_Table_What(st, row, i);
		if (tag != T_NA) {
			if (tag == regina || tag == tura) {
				return 1;
			} else {
				break;
			}
		}
	}

	for (i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++) { // ma uit pe diag sus stanga

		tag = ST_get_tag_Table_What(st, i, j);
		if (tag != T_NA) {
			if (tag == regina || tag == nebun) {
				return 1;
			} else {
				break;
			}
		}
	}

	for (i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++) { // ma uit pe diag sus dreapta

		tag = ST_get_tag_Table_What(st, i, j);
		if (tag != T_NA) {
			if (tag == regina || tag == nebun) {
				return 1;
			} else {
				break;
			}
		}
	}

	for (i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) { // ma uit pe diag jos dreapta

		tag = ST_get_tag_Table_What(st, i, j);
		if (tag != T_NA) {
			if (tag == regina || tag == nebun) {
				return 1;
			} else {
				break;
			}
		}
	}
	for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) { // ma uit pe diag jos stanga

		tag = ST_get_tag_Table_What(st, i, j);
		if (tag != T_NA) {
			if (tag == regina || tag == nebun) {
				return 1;
			} else {
				break;
			}
		}
	}

	if (col_on_move == 0) {
		for (i = 0; i < 8; i++) {
			if (Locuri[i].row >= 0 && Locuri[i].col < 8 && Locuri[i].row < 8
					&& Locuri[i].col >= 0)
				if (ST_get_tag_Table_What(st, row - 1, col + 1) == pion
						|| ST_get_tag_Table_What(st, row + 1, col + 1) == pion) {// daca sunt pioni in fata stanga/dreapta
					return 1;

				}
		}
	} else {
		for (i = 0; i < 8; i++) {
			if (Locuri[i].row >= 0 && Locuri[i].col < 8 && Locuri[i].row < 8
					&& Locuri[i].col >= 0)
				if (ST_get_tag_Table_What(st, row - 1, col - 1) == pion
						|| ST_get_tag_Table_What(st, row + 1, col - 1) == pion) {// daca sunt pioni in fata stanga/dreapta
					return 1;

				}
		}
	}
	return 0;
}
BITMAP VM_valid_moves(STATE st, P_LOC loc_piesa) {

	UCHAR piece_row = LOC_get_row(loc_piesa), piece_col =
			LOC_get_col(loc_piesa);
	int i, j, regina = 0;
	BITMAP rezultat = 0;
	UCHAR ce_piesa, col_on_move = ST_get_col_on_move(st), captura_stanga,
			captura_dreapta, K = T_K, B = T_B, Q = T_Q, R = T_R, P = T_P;
	UCHAR ce_piesa_e_la_loc_piesa = ST_get_tag_Table_What(st, piece_row,
			piece_col);

	if (col_on_move == 1) {
		K = T_K + BWP_OFF;
		B = T_B + BWP_OFF;
		Q = T_Q + BWP_OFF;
		R = T_R + BWP_OFF;
		P = T_P + BWP_OFF;
	}
	if (ce_piesa_e_la_loc_piesa == Q) {
		regina = 1;
	}

	if (ce_piesa_e_la_loc_piesa == R || regina == 1) {

		for (i = piece_col + 1; i < 8; i++) { // verticala  sus
			ce_piesa = ST_get_tag_Table_What(st, piece_row, i);
			if (col_on_move == 0) {// daca tura alba

				if (ce_piesa < 8) {// daca e piesa alba
					break;
				} else if (ce_piesa < T_NA) { // daca piesa neagra
					BM_Put_piece_at_coord(&rezultat, piece_row, i);
					break;
				} else {// daca pozitie libera
					BM_Put_piece_at_coord(&rezultat, piece_row, i);
				}
			} else { // daca tura neagra

				if (ce_piesa >= 8 && ce_piesa < 14) { //daca piesa neagra
					break;
				} else if (ce_piesa < 8) {// daca piesa alba
					BM_Put_piece_at_coord(&rezultat, piece_row, i);
					break;
				} else {// daca spatiu liber
					BM_Put_piece_at_coord(&rezultat, piece_row, i);
				}
			}
		}
		for (i = piece_col - 1; i >= 0; i--) { // verticala jos
			ce_piesa = ST_get_tag_Table_What(st, piece_row, i);
			if (col_on_move == 0) {// daca tura alba

				if (ce_piesa < 8) {// daca e piesa alba
					break;
				} else if (ce_piesa < T_NA) { // daca piesa neagra
					BM_Put_piece_at_coord(&rezultat, piece_row, i);
					break;
				} else {// daca pozitie libera
					BM_Put_piece_at_coord(&rezultat, piece_row, i);
				}
			} else { // daca tura neagra

				if (ce_piesa >= 8 && ce_piesa < 14) { //daca piesa neagra
					break;
				} else if (ce_piesa < 8) {// daca piesa alba
					BM_Put_piece_at_coord(&rezultat, piece_row, i);
					break;
				} else {// daca spatiu liber
					BM_Put_piece_at_coord(&rezultat, piece_row, i);
				}
			}
		}
		for (i = piece_row + 1; i < 8; i++) { // orizontala dreapta
			ce_piesa = ST_get_tag_Table_What(st, i, piece_col);
			if (col_on_move == 0) {// daca tura alba

				if (ce_piesa < 8) {// daca e piesa alba
					break;
				} else if (ce_piesa < T_NA) { // daca piesa neagra
					BM_Put_piece_at_coord(&rezultat, i, piece_col);
					break;
				} else {// daca pozitie libera
					BM_Put_piece_at_coord(&rezultat, i, piece_col);
				}
			} else { // daca tura neagra

				if (ce_piesa >= 8 && ce_piesa < 14) { //daca piesa neagra
					break;
				} else if (ce_piesa < 8) {// daca piesa alba
					BM_Put_piece_at_coord(&rezultat, i, piece_col);
					break;
				} else {// daca spatiu liber
					BM_Put_piece_at_coord(&rezultat, i, piece_col);
				}
			}
		}
		for (i = piece_row - 1; i >= 0; i--) {// orizontala stanga
			ce_piesa = ST_get_tag_Table_What(st, i, piece_col);
			if (col_on_move == 0) {// daca tura alba

				if (ce_piesa < 8) {// daca e piesa alba
					break;
				} else if (ce_piesa < T_NA) { // daca piesa neagra
					BM_Put_piece_at_coord(&rezultat, i, piece_col);
					break;
				} else {// daca pozitie libera
					BM_Put_piece_at_coord(&rezultat, i, piece_col);
				}
			} else { // daca tura neagra

				if (ce_piesa >= 8 && ce_piesa < 14) { //daca piesa neagra
					break;
				} else if (ce_piesa < 8) {// daca piesa alba
					BM_Put_piece_at_coord(&rezultat, i, piece_col);
					break;
				} else {// daca spatiu liber
					BM_Put_piece_at_coord(&rezultat, i, piece_col);
				}
			}
		}
	}

	if (ce_piesa_e_la_loc_piesa == B || regina == 1) {

		for (i = piece_row + 1, j = piece_col + 1; i < 8 && j < 8; i++, j++) { // diagonale dreapta SUS


			ce_piesa = ST_get_tag_Table_What(st, i, j);

			if (col_on_move == 0) { // daca nebun alb

				if (ce_piesa < 8) {//daca piesa alba
					break;
				} else if (ce_piesa < T_NA) {// daca piesa neagra
					BM_Put_piece_at_coord(&rezultat, i, j);
					break;
				} else { // daca spatiu liber
					BM_Put_piece_at_coord(&rezultat, i, j);
				}
			} else { // daca nebun negru

				if (ce_piesa > 7 && ce_piesa < 14) {// daca piesa neagra
					break;
				} else if (ce_piesa < 8) {//daca piesa alba
					BM_Put_piece_at_coord(&rezultat, i, j);
					break;
				} else {
					BM_Put_piece_at_coord(&rezultat, i, j);
				}
			}
		}

		for (i = piece_row + 1, j = piece_col - 1; i < 8 && j >= 0; i++, j--) {// diag dreapta jos

			ce_piesa = ST_get_tag_Table_What(st, i, j);

			if (col_on_move == 0) { // daca nebun alb

				if (ce_piesa < 8) {//daca piesa alba
					break;
				} else if (ce_piesa < T_NA) {// daca piesa neagra
					BM_Put_piece_at_coord(&rezultat, i, j);
					break;
				} else { // daca spatiu liber
					BM_Put_piece_at_coord(&rezultat, i, j);
				}
			} else { // daca nebun negru

				if (ce_piesa > 7 && ce_piesa < 14) {// daca piesa neagra
					break;
				} else if (ce_piesa < 8) {//daca piesa alba
					BM_Put_piece_at_coord(&rezultat, i, j);
					break;
				} else {
					BM_Put_piece_at_coord(&rezultat, i, j);
				}
			}
		}

		for (i = piece_row - 1, j = piece_col + 1; i >= 0 && j < 8; i--, j++) {//diagonale stanga sus


			ce_piesa = ST_get_tag_Table_What(st, i, j);

			if (col_on_move == 0) { // daca nebun alb

				if (ce_piesa < 8) {//daca piesa alba
					break;
				} else if (ce_piesa < T_NA) {// daca piesa neagra
					BM_Put_piece_at_coord(&rezultat, i, j);
					break;
				} else { // daca spatiu liber
					BM_Put_piece_at_coord(&rezultat, i, j);
				}
			} else { // daca nebun negru

				if (ce_piesa > 7 && ce_piesa < 14) {// daca piesa neagra
					break;
				} else if (ce_piesa < 8) {//daca piesa alba
					BM_Put_piece_at_coord(&rezultat, i, j);
					break;
				} else {
					BM_Put_piece_at_coord(&rezultat, i, j);
				}
			}
		}

		for (i = piece_row - 1, j = piece_col - 1; i >= 0 && j >= 0; i--, j--) { // diagonala stanga jos

			ce_piesa = ST_get_tag_Table_What(st, i, j);

			if (col_on_move == 0) { // daca nebun alb

				if (ce_piesa < 8) {//daca piesa alba
					break;
				} else if (ce_piesa < T_NA) {// daca piesa neagra
					BM_Put_piece_at_coord(&rezultat, i, j);
					break;
				} else { // daca spatiu liber
					BM_Put_piece_at_coord(&rezultat, i, j);
				}
			} else { // daca nebun negru

				if (ce_piesa > 7 && ce_piesa < 14) {// daca piesa neagra
					break;
				} else if (ce_piesa < 8) {//daca piesa alba
					BM_Put_piece_at_coord(&rezultat, i, j);
					break;
				} else {
					BM_Put_piece_at_coord(&rezultat, i, j);
				}
			}
		}
	}

	if (ce_piesa_e_la_loc_piesa == P) {

		if (col_on_move == 0) {// daca pioni albi

			if (piece_col == 1) {// daca pioni pe pozitia de start

				if (ST_get_tag_Table_What(st, piece_row, piece_col + 1) == T_NA) {// daca e liber pe prima pozitie

					BM_Put_piece_at_coord(&rezultat, piece_row, piece_col + 1);
					if (ST_get_tag_Table_What(st, piece_row, piece_col + 2)
							== T_NA) {// daca e liber pe a 2 a pozitie
						BM_Put_piece_at_coord(&rezultat, piece_row, piece_col
								+ 2);
					}
				}
			} else {// daca pioniu gica nu e pe linia de start

				if (ST_get_tag_Table_What(st, piece_row, piece_col + 1) == T_NA) {// daca e liber inaintea lui
					BM_Put_piece_at_coord(&rezultat, piece_row, piece_col + 1);
				}
			}
			// acu verific capturile
			captura_stanga = ST_get_tag_Table_What(st, piece_row - 1, piece_col
					+ 1);
			captura_dreapta = ST_get_tag_Table_What(st, piece_row + 1,
					piece_col + 1);

			if (captura_stanga > 7 && captura_stanga < 14) { // daca e piesa neagra acolo
				BM_Put_piece_at_coord(&rezultat, piece_row - 1, piece_col + 1);
			}
			if (captura_dreapta > 7 && captura_dreapta < 14) {// daca e piesa neagra acolo
				BM_Put_piece_at_coord(&rezultat, piece_row + 1, piece_col + 1);
			}
		} else { // daca pionii sunt negri

			if (piece_col == 6) {//daca pioni pe pozitia de start

				if (ST_get_tag_Table_What(st, piece_row, piece_col - 1) == T_NA) {// daca e liber pe prima pozitie

					BM_Put_piece_at_coord(&rezultat, piece_row, piece_col - 1);
					if (ST_get_tag_Table_What(st, piece_row, piece_col - 2)
							== T_NA) { // daca e liber pe a 2 a pozitie
						BM_Put_piece_at_coord(&rezultat, piece_row, piece_col
								- 2);
					}
				}
			} else { // daca pioni nigar nu e pe linia de start

				if (ST_get_tag_Table_What(st, piece_row, piece_col - 1) == T_NA) { // daca e liber inaintea lui
					BM_Put_piece_at_coord(&rezultat, piece_row, piece_col - 1);
				}
			}

			captura_stanga = ST_get_tag_Table_What(st, piece_row - 1, piece_col
					- 1);
			captura_dreapta = ST_get_tag_Table_What(st, piece_row + 1,
					piece_col - 1);

			if (captura_stanga > 1 && captura_stanga < 8) { // daca e piesa alba acolo
				BM_Put_piece_at_coord(&rezultat, piece_row - 1, piece_col - 1);
			}
			if (captura_dreapta > 1 && captura_dreapta < 8) {
				BM_Put_piece_at_coord(&rezultat, piece_row + 1, piece_col - 1);
			}
		}
	}

	if (ce_piesa_e_la_loc_piesa == K) {

		UCHAR C_DIR[8] = { 1, 1, 1, 0, -1, -1, -1, 0 }, L_DIR[8] = { -1, 0, 1,
				1, 1, 0, -1, -1 };
		LOC Locuri[8];

		for (i = 0; i < 8; i++) {
			Locuri[i].row = piece_row + L_DIR[i];
			Locuri[i].col = piece_col + C_DIR[i];
		}

		for (i = 0; i < 8; i++) {

			if (VM_validate_King_move(st, Locuri[i]) == 0) {
				if (Locuri[i].row >= 0 && Locuri[i].row < 8 && Locuri[i].col
						>= 0 && Locuri[i].col < 8) {
					BM_Put_piece_at_coord(&rezultat, Locuri[i].row,
							Locuri[i].col);
				}
			}
		}
		List l = ST_get_List_Table_Location(st, not(ST_get_col_on_move(st)),
				T_K);
		P_LOC poz = first_nod_list(&l);
		rezultat
				&= ~Moves[T_K - PIECES_OFF][LOC_get_row(poz)][LOC_get_col(poz)];
		rezultat &= ~ST_get_bitmap(st, ST_get_col_on_move(st));
	}

	return rezultat;
}
