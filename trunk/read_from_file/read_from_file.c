/* General description :
 *
 */

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "../state/state.h"
#include "../bitmap/bitmap.h"
#include "read_from_file.h"
#include "../list/list.h"
#include "../Util/util.h"

/* ---- Macro #define ---- */
#define I_K 1152921504606846992LL
#define I_Q 576460752303423496LL
#define I_R -9151314442816847743LL
#define I_B 2594073385365405732LL
#define I_N 4755801206503243842LL
#define I_P 71776119061282560LL
#define I_WPos -281474976710656LL
#define I_BPos 65535LL

/* --- Types --- */

/* --- Procedures --- */

void Read_all_possible_moves( BITMAP Moves[5][8][8]) {

	FILE * fin = fopen("Database/All_moves.in", "rb");
	if (fin == NULL) {
		printf("Eroare la deschiderea fisierului All_moves.in");
		exit(0);
	}

	int i, j;
	BITMAP **K, **Q, **R, **B, **N;

	K = (BITMAP**) calloc(8, sizeof(BITMAP*));
	Q = (BITMAP**) calloc(8, sizeof(BITMAP*));
	R = (BITMAP**) calloc(8, sizeof(BITMAP*));
	B = (BITMAP**) calloc(8, sizeof(BITMAP*));
	N = (BITMAP**) calloc(8, sizeof(BITMAP*));

	for (i = 0; i < 8; i++) {
		K[i] = (BITMAP*) calloc(8, sizeof(BITMAP));
		Q[i] = (BITMAP*) calloc(8, sizeof(BITMAP));
		R[i] = (BITMAP*) calloc(8, sizeof(BITMAP));
		B[i] = (BITMAP*) calloc(8, sizeof(BITMAP));
		N[i] = (BITMAP*) calloc(8, sizeof(BITMAP));
	}

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {

			fread(&K[i][j], 8, 1, fin);
			Moves[0][i][j] = K[i][j];
			fread(&Q[i][j], 8, 1, fin);
			Moves[1][i][j] = Q[i][j];
			fread(&R[i][j], 8, 1, fin);
			Moves[2][i][j] = R[i][j];
			fread(&B[i][j], 8, 1, fin);
			Moves[3][i][j] =B[i][j];
			fread(&N[i][j], 8, 1, fin);
			Moves[4][i][j] = N[i][j];
		}
	}

	for (i = 0; i < 8; i++) {
		free(K[i]);
		free(Q[i]);
		free(R[i]);
		free(B[i]);
		free(N[i]);
	}
	free(K);
	free(Q);
	free(R);
	free(B);
	free(N);

	fclose(fin);
}

STATE Read_initial_state() {

	char i, j;

	STATE S = ST_new();

	UCHAR Type_matrix[8][8] = { { 4, 6, 5, 3, 2, 5, 6, 4 }, { 7, 7, 7, 7, 7, 7,
			7, 7 }, { 255, 255, 255, 255, 255, 255, 255, 255 }, { 255, 255,
			255, 255, 255, 255, 255, 255 }, { 255, 255, 255, 255, 255, 255,
			255, 255 }, { 255, 255, 255, 255, 255, 255, 255, 255 }, { 7, 7, 7,
			7, 7, 7, 7, 7 }, { 4, 6, 5, 3, 2, 5, 6, 4 } };

	ST_set_table_W(S, Type_matrix);

	/*setare V_BMAP*/
	ST_set_bitmap(S, 0, I_WPos);
	ST_set_bitmap(S, 1, I_BPos);
	ST_set_bitmap(S, 2, I_K);
	ST_set_bitmap(S, 3, I_Q);
	ST_set_bitmap(S, 4, I_R);
	ST_set_bitmap(S, 5, I_B);
	ST_set_bitmap(S, 6, I_N);
	ST_set_bitmap(S, 7, I_P);

	FILE * fin = fopen("Database/poz_locuri_piese.txt", "r");
	if (fin == NULL) {
		printf("Eroare la deschiderea fisierului poz_locuri_piese.txt");
		exit(0);
	}

	int linie, coloana;
	P_LOC loc;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 6; j++) {

			List list = new_list();

			while (1) {

				fscanf(fin, "%d", &linie);
				fscanf(fin, "%d", &coloana);
				if (linie == -1 && coloana == -1) {
					break;
				}
				loc = LOC_new();
				LOCp_set_both(loc, (UCHAR) linie, (UCHAR) coloana);
				add_nod_list(list, loc);
			}
			ST_set_List_Table_P(S, i, j + BMAP_TP_OFF , list);
		}
	}

	ST_set_move_index(S,0);
	ST_set_piece_to_move(S,T_N);

	return S;
}
