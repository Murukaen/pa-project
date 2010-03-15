/* General description :
 *
 */

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>
#include "../bitmap/bitmap.h"

/* ----- Local #inlcudes ----- */

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

void Read_all_possible_moves(FILE* fin, BITMAP** King_moves,
		BITMAP** Queen_moves, BITMAP** Rock_moves, BITMAP**Bishop_moves,
		BITMAP** Knight_moves) {

	if ((fin = fopen("All_moves.in", "rb")) == NULL) {
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

void Read_initial_state(FILE* fin, BITMAP W_Pos, BITMAP W_Ki, BITMAP W_Q,
		BITMAP W_R, BITMAP W_B, BITMAP W_Kn, BITMAP B_Pos, BITMAP B_Ki,
		BITMAP B_Q, BITMAP B_R, BITMAP B_B, BITMAP B_Kn) {

	if ((fin = fopen("Initial_positions.in", "rb")) == NULL) {
		printf("Eroare la deschiderea fisierului Initial_positions.in");
		exit(0);
	}

	fread(&W_Pos, 8, 1, fin);
	fread(&W_Ki, 8, 1, fin);
	fread(&W_Q, 8, 1, fin);
	fread(&W_R, 8, 1, fin);
	fread(&W_B, 8, 1, fin);
	fread(&W_Kn, 8, 1, fin);

	fread(&B_Pos, 8, 1, fin);
	fread(&B_Ki, 8, 1, fin);
	fread(&B_Q, 8, 1, fin);
	fread(&B_R, 8, 1, fin);
	fread(&B_B, 8, 1, fin);
	fread(&B_Kn, 8, 1, fin);

	fclose(fin);
}

