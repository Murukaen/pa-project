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

void Read_all_possible_moves(BITMAP** King_moves, BITMAP** Queen_moves,
		BITMAP** Rock_moves, BITMAP**Bishop_moves, BITMAP** Knight_moves) {

	FILE * fin = fopen("Database/All_moves.in", "rb");
	if (fin == NULL) {
		printf("Eroare la deschiderea fisierului All_moves.in");
		exit(0);
	}

	int i, j;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {

			fread(&King_moves[i][j], 8, 1, fin);
			fread(&Queen_moves[i][j], 8, 1, fin);
			fread(&Rock_moves[i][j], 8, 1, fin);
			fread(&Bishop_moves[i][j], 8, 1, fin);
			fread(&Knight_moves[i][j], 8, 1, fin);
		}
	}
	fclose(fin);
}

STATE Read_initial_state() {

	char i, j;

	STATE S = ST_new();
	UCHAR** Type_matrix = (UCHAR**) calloc(8, sizeof(UCHAR*));
	for (i = 0; i < 8; i++) {
		Type_matrix[i] = (UCHAR*) calloc(8, sizeof(UCHAR));
	}

	Type_matrix = { { 4, 6, 5, 3, 2, 5, 6, 4 },{ 7, 7, 7, 7, 7, 7, 7, 7 }, { 255, 255, 255, 255, 255, 255, 255,	255 }, { 255, 255, 255, 255, 255, 255, 255, 255 }, { 255,255, 255, 255, 255, 255, 255, 255 }, { 255, 255, 255, 255,	255, 255, 255, 255 }, { 7, 7, 7, 7, 7, 7, 7, 7 }, { 4, 6,5, 3, 2, 5, 6, 4 } };
	ST_set_table_W(S, Type_matrix);

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
			ST_set_table_P(S, i, j + 2, list);
		}
	}
}
