#include "valid_moves.h"
#include <stdlib.h>
#include "../Log/log.h"
#include "../list/list.h"
#include "../Util/util.h"
#include "../state_generator/state_generator.h"

#define LOG_VALIDATE_MOVE_FILE "Log/validate_move.log"

BITMAP VM_valid_pos(BITMAP posibile, BITMAP piese_albe) {

	BITMAP rez = posibile & (~piese_albe);

	return rez;
}

BITMAP VM_is_Check(STATE st, int* nr, P_LOC checking_piece) {

	UCHAR tag, col_on_move = ST_get_col_on_move(st), K, Q, R, B, P, N;
	BITMAP rez = 0, cai = 0, daca_regele_ar_fi_cal = 0, rezultat_cal = 0;
	List L = ST_get_List_Table_Location(st, col_on_move, T_K);
	P_LOC king_loc = first_nod_list(&L);
	UCHAR row_king = LOC_get_row(king_loc), col_king = LOC_get_col(king_loc);

	int i, j, k, l;

	if (col_on_move == 0) {
		K = T_K + BWP_OFF;
		Q = T_Q + BWP_OFF;
		R = T_R + BWP_OFF;
		B = T_B + BWP_OFF;
		N = T_N + BWP_OFF;
		P = T_P + BWP_OFF;
	} else {
		K = T_K;
		Q = T_Q;
		R = T_R;
		B = T_B;
		N = T_N;
		P = T_P;
	}

	// ma uit pe coloana in sus

	for (i = col_king + 1; i < 8; i++) {

		tag = ST_get_tag_Table_What(st, row_king, i);
		if (tag == T_NA) {
			continue;
		} else if (tag == Q) {
			LOCp_set_both(checking_piece, row_king, i);
			nr[0] += 1;
			for (j = col_king + 1; j <= i; j++) {
				rez |= BM_Make_coord(row_king, j);
			}
			break;
		} else if (tag == R) {
			LOCp_set_both(checking_piece, row_king, i);
			nr[0] += 1;
			for (j = col_king + 1; j <= i; j++) {
				rez |= BM_Make_coord(row_king, j);
			}
			break;
		} else {
			break;
		}
	}

	//ma uit pe coloana in jos

	for (i = col_king - 1; i >= 0; i--) {

		tag = ST_get_tag_Table_What(st, row_king, i);
		if (tag == T_NA) {
			continue;
		} else if (tag == Q) {
			LOCp_set_both(checking_piece, row_king, i);
			nr[0] += 1;
			for (j = col_king - 1; j >= i; j--) {
				rez |= BM_Make_coord(row_king, j);
			}
			break;
		} else if (tag == R) {
			LOCp_set_both(checking_piece, row_king, i);
			nr[0] += 1;
			for (j = col_king - 1; j >= i; j--) {
				rez |= BM_Make_coord(row_king, j);
			}
			break;
		} else {
			break;
		}
	}

	// ma uit pe linie in stanga

	for (i = row_king - 1; i >= 0; i--) {
		tag = ST_get_tag_Table_What(st, i, col_king);
		if (tag == T_NA) {
			continue;
		} else if (tag == Q) {
			LOCp_set_both(checking_piece, i, col_king);
			nr[0] += 1;
			for (j = row_king - 1; j >= i; j--) {
				rez |= BM_Make_coord(j, col_king);
			}
			break;
		} else if (tag == R) {
			LOCp_set_both(checking_piece, i, col_king);
			nr[0] += 1;
			for (j = row_king - 1; j >= i; j--) {
				rez |= BM_Make_coord(j, col_king);
			}
			break;
		} else {
			break;
		}
	}
	// ma uit pe linie in dreapta

	for (i = row_king + 1; i < 8; i++) {
		tag = ST_get_tag_Table_What(st, i, col_king);
		if (tag == T_NA) {
			continue;
		} else if (tag == Q) {
			LOCp_set_both(checking_piece, i, col_king);
			nr[0] += 1;
			for (j = row_king + 1; j <= i; j++) {
				rez |= BM_Make_coord(j, col_king);
			}
			break;

		} else if (tag == R) {
			LOCp_set_both(checking_piece, i, col_king);
			nr[0] += 1;
			for (j = row_king + 1; j <= i; j++) {
				rez |= BM_Make_coord(j, col_king);
			}
			break;
		} else {
			break;
		}
	}
	// ma uit pe diag sus-stanga

	for (i = row_king - 1, j = col_king + 1; i >= 0 && j < 8; i--, j++) {

		tag = ST_get_tag_Table_What(st, i, j);
		if (tag == T_NA) {
			continue;
		} else if (tag == Q) {
			LOCp_set_both(checking_piece, i, j);
			nr[0] += 1;
			for (k = row_king - 1, l = col_king + 1; k >= i && l <= j; k--, l++) {
				rez |= BM_Make_coord(k, l);
			}
			break;
		} else if (tag == B) {
			LOCp_set_both(checking_piece, i, j);
			nr[0] += 1;
			for (k = row_king - 1, l = col_king - 1; k >= i && l <= j; k--, l++) {
				rez |= BM_Make_coord(k, l);
			}
			break;
		} else if ((i == row_king - 1) && (j == col_king + 1) && (col_on_move
				== 0) && (tag == P)) {
			LOCp_set_both(checking_piece, i, j);
			nr[0] += 1;
			rez |= BM_Make_coord(i, j);
			break;
		} else {
			break;
		}

	}

	// diag sus-dreapta

	for (i = row_king + 1, j = col_king + 1; i < 8 && j < 8; i++, j++) {

		tag = ST_get_tag_Table_What(st, i, j);
		if (tag == T_NA) {
			continue;
		} else if (tag == Q) {
			LOCp_set_both(checking_piece, i, j);
			nr[0] += 1;
			for (k = row_king + 1, l = col_king + 1; k <= i && l <= j; k++, l++) {
				rez |= BM_Make_coord(k, l);
			}
			break;
		} else if (tag == B) {
			LOCp_set_both(checking_piece, i, j);
			nr[0] += 1;
			for (k = row_king + 1, l = col_king + 1; k <= i && l <= j; k++, l++) {
				rez |= BM_Make_coord(k, l);
			}
			break;
		} else if ((i == row_king + 1) && (j == col_king + 1) && (col_on_move
				== 0) && (tag == P)) {
			LOCp_set_both(checking_piece, i, j);
			nr[0] += 1;
			rez |= BM_Make_coord(i, j);
			break;
		} else {
			break;
		}

	}

	//diag jos dreapta

	for (i = row_king + 1, j = col_king - 1; i < 8 && j >= 0; i++, j--) {

		tag = ST_get_tag_Table_What(st, i, j);
		if (tag == T_NA) {
			continue;
		} else if (tag == Q) {
			LOCp_set_both(checking_piece, i, col_king);
			nr[0] += 1;
			for (k = row_king + 1, l = col_king - 1; k <= i && l >= j; k++, l--) {
				rez |= BM_Make_coord(k, l);
			}
			break;
		} else if (tag == B) {
			LOCp_set_both(checking_piece, i, col_king);
			nr[0] += 1;
			for (k = row_king + 1, l = col_king - 1; k <= i && l <= j; k++, l--) {
				rez |= BM_Make_coord(k, l);
			}
			break;
		} else if ((i == row_king + 1) && (j == col_king - 1) && (col_on_move
				== 1) && (tag == P)) {
			LOCp_set_both(checking_piece, i, j);
			nr[0] += 1;
			rez |= BM_Make_coord(i, j);
			break;
		} else {
			break;
		}
	}

	// diag jos stanga

	for (i = row_king - 1, j = col_king - 1; i >= 0 && j >= 0; i--, j--) {

		tag = ST_get_tag_Table_What(st, i, j);
		if (tag == T_NA) {
			continue;
		} else if (tag == Q) {
			LOCp_set_both(checking_piece, i, col_king);
			nr[0] += 1;
			for (k = row_king - 1, l = col_king - 1; k >= i && l >= j; k--, l--) {
				rez |= BM_Make_coord(k, l);
			}
			break;
		} else if (tag == B) {
			LOCp_set_both(checking_piece, i, col_king);
			nr[0] += 1;
			for (k = row_king - 1, l = col_king - 1; k >= i && l >= j; k--, l--) {
				rez |= BM_Make_coord(k, l);
			}
			break;
		} else if ((i == row_king - 1) && (j == col_king - 1) && (col_on_move
				== 1) && (tag == P)) {
			LOCp_set_both(checking_piece, i, j);
			nr[0] += 1;
			rez |= BM_Make_coord(i, j);
			break;
		} else {
			break;
		}
	}

	cai = ST_get_bitmap(st, T_N) & ST_get_bitmap(st, not(col_on_move));
	daca_regele_ar_fi_cal = Moves[T_N - 2][row_king][col_king];

	rezultat_cal = cai & daca_regele_ar_fi_cal;

	if (rezultat_cal != 0) {
		rez |= rezultat_cal;
		nr[0] += 1;
	}

	return rez;
}

UCHAR VM_is_Check_if_piece_moves(STATE st, P_LOC loc, P_LOC who_check) {

	if (loc == NULL || who_check == NULL) {
		/* LOG */
		log_print("locul primit de functia vmischeckifpiecemoves e null",
				LOG_VALIDATE_MOVE_FILE);
		/* END LOG */
		exit(1);
	}
	/*identific piesele la mutare si aflu coordonatele piesei respectiv ale regelui*/
	UCHAR col_on_move = ST_get_col_on_move(st);
	int i, j;
	List l = ST_get_List_Table_Location(st, col_on_move, T_K);
	P_LOC king_loc = first_nod_list(&l);
	UCHAR row_king = LOC_get_row(king_loc), col_king = LOC_get_col(king_loc),
			row_piece = LOC_get_row(loc), col_piece = LOC_get_col(loc), tag;

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
						if (i == col_piece || tag == T_NA) {// daca nu e nicio piesa pe pozitia respectiva sau e piesa mutata sar peste
							continue;
						} else {// daca gasesc o alta piesa
							if (tag == T_Q + BWP_OFF || tag == T_R + BWP_OFF) { // verific daca e cumva regina sau tura neagra
								LOCp_set_both(who_check, row_king, i);
								if (ST_get_tag_Table_What(st, row_piece,
										col_piece) == T_P) {
									return 0;
								}
								return 1;
							} else {
								return 0;
							}
						}

					} else {// daca e negru la mutare
						if (i == col_piece || tag == T_NA) {
							continue;
						} else {
							if (tag == T_Q || tag == T_R) {
								LOCp_set_both(who_check, row_king, i);
								if (ST_get_tag_Table_What(st, row_piece,
										col_piece) == T_P + BWP_OFF) {
									return 0;
								}
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
						if (i == col_piece || tag == T_NA) {// daca nu e nicio piesa pe pozitia respectiva sau e piesa mutata sar peste
							continue;
						} else {// daca gasesc o alta piesa
							if (tag == T_Q + BWP_OFF || tag == T_R + BWP_OFF) { // verific daca e cumva regina sau tura neagra
								LOCp_set_both(who_check, row_king, i);
								if (ST_get_tag_Table_What(st, row_piece,
										col_piece) == T_P) {
									return 0;
								}
								return 1;
							} else {

								return 0;
							}
						}
					} else {// daca e negru la mutare


						if (i == col_piece || tag == T_NA) {
							continue;
						} else {
							if (tag == T_Q || tag == T_R) {
								LOCp_set_both(who_check, row_king, i);
								if (ST_get_tag_Table_What(st, row_piece,
										col_piece) == T_P + BWP_OFF) {
									return 0;
								}
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
						if (i == row_piece || tag == T_NA) {// daca nu e nicio piesa pe pozitia respectiva sau e piesa mutata sar peste
							continue;
						} else {// daca gasesc o alta piesa
							if (tag == T_Q + BWP_OFF || tag == T_R + BWP_OFF) { // verific daca e cumva regina sau tura neagra
								LOCp_set_both(who_check, i, col_king);
								return 1;
							} else {
								return 0;
							}
						}

					} else {// daca e negru la mutare
						if (i == row_piece || tag == T_NA) {
							continue;
						} else {
							if (tag == T_Q || tag == T_R) {
								LOCp_set_both(who_check, i, col_king);
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
						if (i == row_piece || tag == T_NA) {// daca nu e nicio piesa pe pozitia respectiva sau e piesa mutata sar peste
							continue;
						} else {// daca gasesc o alta piesa
							if (tag == T_Q + BWP_OFF || tag == T_R + BWP_OFF) { // verific daca e cumva regina sau tura neagra
								LOCp_set_both(who_check, i, col_king);
								return 1;
							} else {
								return 0;
							}
						}
					} else {// daca e negru la mutare
						if (i == row_piece || tag == T_NA) {
							continue;
						} else {
							if (tag == T_Q || tag == T_R) {
								LOCp_set_both(who_check, i, col_king);
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

					if ((i == row_piece && j == col_piece) || tag == T_NA) {
						continue;
					} else {
						if (tag == T_Q + BWP_OFF || tag == T_B + BWP_OFF) { // verific daca e cumva regina sau tura neagra
							LOCp_set_both(who_check, i, j);
							return 1;
						} else {
							return 0;
						}
					}
				} else {
					if ((i == row_piece && j == col_piece) || tag == T_NA) {
						continue;
					} else {
						if (tag == T_Q || tag == T_B) {
							LOCp_set_both(who_check, i, j);
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

					if ((i == row_piece && j == col_piece) || tag == T_NA) {
						continue;
					} else {
						if (tag == T_Q + BWP_OFF || tag == T_B + BWP_OFF) { // verific daca e cumva regina sau tura neagra
							LOCp_set_both(who_check, i, j);
							return 1;
						} else {
							return 0;
						}
					}
				} else {
					if ((i == row_piece && j == col_piece) || tag == T_NA) {
						continue;
					} else {
						if (tag == T_Q || tag == T_B) {
							LOCp_set_both(who_check, i, j);
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

					if ((i == row_piece && j == col_piece) || tag == T_NA) {
						continue;
					} else {
						if (tag == T_Q + BWP_OFF || tag == T_B + BWP_OFF) { // verific daca e cumva regina sau tura neagra
							LOCp_set_both(who_check, i, j);
							return 1;
						} else {
							return 0;
						}
					}
				} else {
					if ((i == row_piece && j == col_piece) || tag == T_NA) {
						continue;
					} else {
						if (tag == T_Q || tag == T_B) {
							LOCp_set_both(who_check, i, j);
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

					if ((i == row_piece && j == col_piece) || tag == T_NA) {
						continue;
					} else {
						if (tag == T_Q + BWP_OFF || tag == T_B + BWP_OFF) { // verific daca e cumva regina sau tura neagra
							LOCp_set_both(who_check, i, j);
							return 1;
						} else {
							return 0;
						}
					}
				} else {
					if ((i == row_piece && j == col_piece) || tag == T_NA) {
						continue;
					} else {
						if (tag == T_Q || tag == T_B) {
							LOCp_set_both(who_check, i, j);
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

BITMAP VM_get_valid_if_check(STATE st, P_LOC pinned_piece, P_LOC checking_piece) {

	UCHAR row_checking_piece = LOC_get_row(checking_piece), col_checking_piece =
			LOC_get_col(checking_piece), col_on_move = ST_get_col_on_move(st),
			row_pinned_piece = LOC_get_row(pinned_piece), col_pinned_piece =
					LOC_get_col(pinned_piece), N = T_N, P = T_P, Q = T_Q, R =
					T_R, B = T_B;
	BITMAP rezultat = 0, unu = 0;
	int i, j, pt_regina = 0;

	if (col_on_move == 1) {
		Q += BWP_OFF;
		R += BWP_OFF;
		B += BWP_OFF;
		N += BWP_OFF;
		P += BWP_OFF;
	}
	// daca piesa in pin e cal, clar nu poate sa mute nicaieri
	if (ST_get_tag_Table_What(st, row_pinned_piece, col_pinned_piece) == N) {
		return 0;
	}
	//daca piesa in pin e pion, ar putea eventual sa captureze piesa ce il pune in pin, daca aceasta e nebun sau regina si poate captura
	if (ST_get_tag_Table_What(st, row_pinned_piece, col_pinned_piece) == P) {

		if (col_on_move == 1) {
			Q -= BWP_OFF;
			B -= BWP_OFF;
			P -= BWP_OFF;
		}

		List l = ST_get_List_Table_Location(st, col_on_move, T_K);
		P_LOC king_loc = first_nod_list(&l);
		UCHAR row_king = LOC_get_row(king_loc), col_king =
				LOC_get_col(king_loc);

		if (col_on_move == 0) {// daca e pion alb pinuit
			if (row_king > row_pinned_piece && col_king < col_pinned_piece) {// daca regele e in dreapta jos
				if ((row_pinned_piece - 1 == row_checking_piece)//si gasesc nebun sau regina neagra in stanga sus
						&& (col_pinned_piece + 1 == col_checking_piece)) {

					rezultat = BM_Make_coord(row_pinned_piece - 1,
							col_pinned_piece + 1);
					return rezultat;
				}
			}

			if (row_king < row_pinned_piece && col_king < col_pinned_piece) {// daca regele e in stanga jos
				if ((row_pinned_piece + 1 == row_checking_piece)
						&& (col_pinned_piece + 1 == col_checking_piece)) {// daca pionu alb are piesa care l pune in pin in dreapta sus

					rezultat = BM_Make_coord(row_pinned_piece + 1,
							col_pinned_piece + 1);
					return rezultat;
				}
			}
		} else {// daca e pion negru pinuit

			if (row_king > row_pinned_piece && col_king > col_pinned_piece) {// daca regele e in dreapta sus
				if ((row_pinned_piece - 1 == row_checking_piece)
						&& (col_pinned_piece - 1 == col_pinned_piece)) { // daca piesa ce l pune in pin e in stanga jos
					rezultat = BM_Make_coord(row_pinned_piece - 1,
							col_pinned_piece - 1);
					return rezultat;
				}
			}
			if (row_king < row_pinned_piece && col_king > col_pinned_piece) {// daca rege in stanga sus
				if ((row_pinned_piece + 1 == row_checking_piece)
						&& (col_pinned_piece - 1 == col_pinned_piece)) {// daca piesa ce l pune in pin e in dreapta jos
					rezultat = BM_Make_coord(row_pinned_piece + 1,
							col_pinned_piece - 1);
					return rezultat;
				}
			}
		}
		// daca nu se gaseste nicio piesa in locurile respective, nu poate muta nicaieri
		return rezultat;
	}
	// daca piesa pinuita e regina
	if (ST_get_tag_Table_What(st, row_pinned_piece, col_pinned_piece) == Q) {

		// daca piesa ce pune regina in pin e tot regina
		if (col_on_move == 0) {
			Q = T_Q + BWP_OFF;
		} else {
			Q = T_Q;
		}
		if (ST_get_tag_Table_What(st, row_checking_piece, col_checking_piece)
				== Q) {
			// daca reginele sunt conectate pe linie
			if (row_checking_piece == row_pinned_piece || col_checking_piece
					== col_pinned_piece) {

				pt_regina = 1;
			} else {
				pt_regina = 2;
			}

		}
		if (ST_get_tag_Table_What(st, row_checking_piece, col_checking_piece)
				== R) {
			pt_regina = 1;
		}
		if (ST_get_tag_Table_What(st, row_checking_piece, col_checking_piece)
				== B) {
			pt_regina = 2;
		}
	}
	if (ST_get_tag_Table_What(st, row_pinned_piece, col_pinned_piece) == R
			|| pt_regina == 1) {

		// daca sunt pe aceeasi linie
		if (row_pinned_piece == row_checking_piece) {

			// daca pinned piece e sub checking piece
			if (col_pinned_piece < col_checking_piece) {
				for (i = col_pinned_piece + 1; i <= col_checking_piece; i++) {

					unu = BM_Make_coord(row_pinned_piece, i);
					rezultat |= unu;
				}
			} else {// daca e deasupra
				for (i = col_pinned_piece - 1; i >= col_checking_piece; i--) {

					unu = BM_Make_coord(row_pinned_piece, i);
					rezultat |= unu;
				}
			}
		}
		// daca sunt pe aceeasi coloana
		if (col_pinned_piece == col_checking_piece) {

			// daca pinned piece e in stanga checkin piece
			if (row_pinned_piece < row_checking_piece) {

				for (i = row_pinned_piece + 1; i <= row_checking_piece; i++) {

					unu = BM_Make_coord(i, col_pinned_piece);
					rezultat |= unu;
				}
			} else {// daca e in dreapta

				for (i = row_pinned_piece - 1; i >= row_checking_piece; i--) {

					unu = BM_Make_coord(i, col_pinned_piece);
					rezultat |= unu;
				}
			}
		}
		return rezultat;
	}

	if (ST_get_tag_Table_What(st, row_pinned_piece, col_pinned_piece) == B
			|| pt_regina == 2) {

		// daca piesa ce da sah e pe diag dreapta sus
		if (row_checking_piece > row_pinned_piece && col_checking_piece
				> col_pinned_piece) {

			for (i = row_pinned_piece + 1, j = col_pinned_piece + 1; i
					<= row_checking_piece && j <= col_checking_piece; i++, j++) {

				unu = BM_Make_coord(i, j);
				rezultat |= unu;
			}
		}
		// daca piesa ce da sah e pe diag sus stanga
		if (row_checking_piece < row_pinned_piece && col_checking_piece
				> col_pinned_piece) {

			for (i = row_pinned_piece - 1, j = col_pinned_piece + 1; i
					>= row_checking_piece && j <= col_checking_piece; i--, j++) {

				unu = BM_Make_coord(i, j);
				rezultat |= unu;
			}
		}
		// daca piesa ce da sah e pe diag stanga jos
		if (row_checking_piece < row_pinned_piece && col_checking_piece
				< col_pinned_piece) {

			for (i = row_pinned_piece - 1, j = col_pinned_piece - 1; i
					>= row_checking_piece && j >= col_checking_piece; i--, j--) {

				unu = BM_Make_coord(i, j);
				rezultat |= unu;
			}
		}
		// daca piesa ce da sah e pe diag dreapta jos
		if (row_checking_piece > row_pinned_piece && col_checking_piece
				< col_pinned_piece) {

			for (i = row_pinned_piece + 1, j = col_pinned_piece - 1; i
					<= row_checking_piece && j >= col_checking_piece; i++, j--) {

				unu = BM_Make_coord(i, j);
				rezultat |= unu;
			}
		}

		return rezultat;

	}
	//redundant.....
	return rezultat;
}

int VM_validate_King_move(STATE st, ILOC loc) {

	int row = loc.row, col = loc.col, col_on_move = ST_get_col_on_move(st),
			tag, regina, pion, tura, nebun, rege, i, j;
	int L_DIR[8] = { -1, 0, 1, 1, 1, 0, -1, -1 }, C_DIR[8] = { 1, 1, 1, 0, -1,
			-1, -1, 0 };

	ILOC Locuri[8];

	for (i = 0; i < 8; i++) {

		Locuri[i].row = row + L_DIR[i];
		Locuri[i].col = col + C_DIR[i];
	}

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

	BITMAP cai = 0, daca_regele_ar_fi_cal, rezultat_cal;

	cai = ST_get_bitmap(st, T_N) & ST_get_bitmap(st, not(col_on_move));
	daca_regele_ar_fi_cal = Moves[T_N - 2][row][col];

	rezultat_cal = cai & daca_regele_ar_fi_cal;
	if (rezultat_cal != 0)
		return 1;

	return 0;
}
BITMAP VM_valid_moves(STATE st, P_LOC loc_piesa) {

	UCHAR piece_row = LOC_get_row(loc_piesa), piece_col =
			LOC_get_col(loc_piesa);
	int i, j, regina = 0, pinning_piece_on_col = 0, rege_pe_col = 0;
	BITMAP rezultat = 0;
	UCHAR ce_piesa, col_on_move = ST_get_col_on_move(st), captura_stanga,
			captura_dreapta, K = T_K, B = T_B, Q = T_Q, R = T_R, P = T_P, N =
					T_N;
	UCHAR ce_piesa_e_la_loc_piesa = ST_get_tag_Table_What(st, piece_row,
			piece_col);

	if (col_on_move == 1) {
		K = T_K + BWP_OFF;
		B = T_B + BWP_OFF;
		N = T_N + BWP_OFF;
		Q = T_Q + BWP_OFF;
		R = T_R + BWP_OFF;
		P = T_P + BWP_OFF;
	}

	if (ce_piesa_e_la_loc_piesa == N) {

		rezultat = VM_valid_pos(Moves[T_N - 2][piece_row][piece_col],
				ST_get_bitmap(st, col_on_move));

		return rezultat;
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
			for (i = piece_col + 1; i < 8; i++) {
				if (ST_get_tag_Table_What(st, piece_row, i) == T_Q + BWP_OFF
						|| ST_get_tag_Table_What(st, piece_row, i) == T_R
								+ BWP_OFF) {
					pinning_piece_on_col = 1;
					break;
				} else if (ST_get_tag_Table_What(st, piece_row, i) == T_NA) {
					continue;
				} else {
					break;
				}
			}
			for (i = piece_col - 1; i >= 0; i--) {

				if (ST_get_tag_Table_What(st, piece_row, i) == T_NA) {
					continue;
				} else if (ST_get_tag_Table_What(st, piece_row, i) == T_K) {
					rege_pe_col = 1;
					break;
				} else {
					break;
				}
			}

			if (pinning_piece_on_col == 0 && rege_pe_col == 0) {
				captura_stanga = ST_get_tag_Table_What(st, piece_row - 1,
						piece_col + 1);
				captura_dreapta = ST_get_tag_Table_What(st, piece_row + 1,
						piece_col + 1);

				if (captura_stanga > 7 && captura_stanga < 14) { // daca e piesa neagra acolo
					BM_Put_piece_at_coord(&rezultat, piece_row - 1, piece_col
							+ 1);
				}
				if (captura_dreapta > 7 && captura_dreapta < 14) {// daca e piesa neagra acolo
					BM_Put_piece_at_coord(&rezultat, piece_row + 1, piece_col
							+ 1);
				}
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
			for (i = piece_col - 1; i >= 0; i--) {
				if (ST_get_tag_Table_What(st, piece_row, i) == T_Q
						|| ST_get_tag_Table_What(st, piece_row, i) == T_R) {
					pinning_piece_on_col = 1;
					break;
				} else if (ST_get_tag_Table_What(st, piece_row, i) == T_NA) {
					continue;
				} else {
					break;
				}
			}
			for (i = piece_col + 1; i < 8; i++) {

				if (ST_get_tag_Table_What(st, piece_row, i) == T_NA) {
					continue;
				} else if (ST_get_tag_Table_What(st, piece_row, i) == T_K
						+ BWP_OFF) {
					rege_pe_col = 1;
					break;
				} else {
					break;
				}
			}

			if (pinning_piece_on_col == 0 && rege_pe_col == 0) {
				captura_stanga = ST_get_tag_Table_What(st, piece_row - 1,
						piece_col - 1);
				captura_dreapta = ST_get_tag_Table_What(st, piece_row + 1,
						piece_col - 1);

				if (captura_stanga > 1 && captura_stanga < 8) { // daca e piesa alba acolo
					BM_Put_piece_at_coord(&rezultat, piece_row - 1, piece_col
							- 1);
				}
				if (captura_dreapta > 1 && captura_dreapta < 8) {
					BM_Put_piece_at_coord(&rezultat, piece_row + 1, piece_col
							- 1);
				}
			}
		}
	}

	if (ce_piesa_e_la_loc_piesa == K) {

		int L_DIR[8] = { -1, 0, 1, 1, 1, 0, -1, -1 }, C_DIR[8] = { 1, 1, 1, 0,
				-1, -1, -1, 0 };

		ILOC Locuri[8];

		for (i = 0; i < 8; i++) {

			Locuri[i].row = piece_row + L_DIR[i];
			Locuri[i].col = piece_col + C_DIR[i];
		}
		ST_set_tag_Table_What(st, piece_row, piece_col, T_NA);
		for (i = 0; i < 8; i++) {

			if (VM_validate_King_move(st, Locuri[i]) == 0) {
				if (Locuri[i].row >= 0 && Locuri[i].row < 8 && Locuri[i].col
						>= 0 && Locuri[i].col < 8) {
					BM_Put_piece_at_coord(&rezultat, Locuri[i].row,
							Locuri[i].col);
				}
			}
		}
		ST_set_tag_Table_What(st, piece_row, piece_col, K);
		List l = ST_get_List_Table_Location(st, not(ST_get_col_on_move(st)),
				T_K);
		P_LOC poz = first_nod_list(&l);
		rezultat
				&= ~Moves[T_K - PIECES_OFF][LOC_get_row(poz)][LOC_get_col(poz)];
		rezultat &= ~ST_get_bitmap(st, ST_get_col_on_move(st));
	}
	return rezultat;
}
