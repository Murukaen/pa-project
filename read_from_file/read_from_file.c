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

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

void Read_all_possible_moves(BITMAP** King_moves, BITMAP** Queen_moves,
		BITMAP** Rock_moves, BITMAP**Bishop_moves, BITMAP** Knight_moves) {

	if ((FILE * f = fopen("Database/All_moves.in", "rb")) == NULL) {
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

void Read_initial_state(void) {

	BITMAP PPos, OPos, Ki, Q, R, B, Kn, P;

	STATE S = ST_new();

	UCHAR Type_matrix[8][8] = { { 4, 6, 5, 3, 2, 5, 6, 4 }, { 7, 7, 7, 7, 7, 7,
			7, 7 }, { 255, 255, 255, 255, 255, 255, 255, 255 }, { 255, 255,
			255, 255, 255, 255, 255, 255 }, { 255, 255, 255, 255, 255, 255,
			255, 255 }, { 255, 255, 255, 255, 255, 255, 255, 255 }, { 7, 7, 7,
			7, 7, 7, 7, 7 }, { 4, 6, 5, 3, 2, 5, 6, 4 } };

	ST_set_table(S, Type_matrix);

	BITMAP Ki = 576460752303423496, Q = 1152921504606846992, R =
			-9151314442816847743, B = 2594073385365405732, Kn =
			4755801206503243842, P = 71776119061282560,
			PPos = -281474976710656, OPos = 65535;

	ST_set_bitmap(S, 0, PPos);
	ST_set_bitmap(S, 1, OPos);
	ST_set_bitmap(S, 2, Ki);
	ST_set_bitmap(S, 3, Q);
	ST_set_bitmap(S, 4, R);
	ST_set_bitmap(S, 5, B);
	ST_set_bitmap(S, 6, Kn);
	ST_set_bitmap(S, 7, P);

}
