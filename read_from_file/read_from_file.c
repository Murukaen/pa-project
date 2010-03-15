/* General description :
 *
 */

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>
#include "../bitmap/bitmap.h"
#include "read_from_file.h"

/* ----- Local #inlcudes ----- */

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

void Read_all_possible_moves(FILE* fin, BITMAP** King_moves, BITMAP** Queen_moves, BITMAP** Rock_moves, BITMAP**Bishop_moves, BITMAP** Knight_moves) {

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

void Read_initial_state(FILE* fin, BITMAP *T_WPos, BITMAP *T_BPos, BITMAP *T_Ki, BITMAP *T_Q, BITMAP *T_R, BITMAP *T_B, BITMAP *T_Kn, BITMAP *T_P) {

	if ((fin = fopen("Initial_positions.in", "rb")) == NULL) {
		printf("Eroare la deschiderea fisierului Initial_positions.in");
		exit(0);
	}

	fread(T_WPos, 8, 1, fin);
	fread(T_BPos, 8, 1, fin);
	fread(T_Ki, 8, 1, fin);
	fread(T_Q, 8, 1, fin);
	fread(T_R, 8, 1, fin);
	fread(T_B, 8, 1, fin);
	fread(T_Kn, 8, 1, fin);
	fread(T_P, 8, 1, fin);


	fclose(fin);
}

