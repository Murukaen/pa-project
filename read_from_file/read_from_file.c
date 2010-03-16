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

void Read_all_possible_moves(char* fin, BITMAP** King_moves,
		BITMAP** Queen_moves, BITMAP** Rock_moves, BITMAP**Bishop_moves,
		BITMAP** Knight_moves) {

	if ((FILE * f = fopen(fin, "rb")) == NULL) {
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

	if ((FILE * f = fopen("Database/Initial_positions.in", "rb")) == NULL) {
		printf("Eroare la deschiderea fisierului Initial_positions.in");
		exit(0);
	}

	BITMAP *T_WPos, *T_BPos, *T_Ki, *T_Q, *T_R, *T_B, *T_Kn, *T_P;

	fread(&T_WPos, 8, 1, fin);
	fread(&T_BPos, 8, 1, fin);
	fread(&T_Ki, 8, 1, fin);
	fread(&T_Q, 8, 1, fin);
	fread(&T_R, 8, 1, fin);
	fread(&T_B, 8, 1, fin);
	fread(&T_Kn, 8, 1, fin);
	fread(&T_P, 8, 1, fin);

	STATE S = ST_new();

	UCHAR Type_matrix[8][8] = { { 2, 4, 3, 1, 0, 3, 4, 2 }, { 5, 5, 5, 5, 5, 5,
			5, 5 }, { 255, 255, 255, 255, 255, 255, 255, 255 }, { 255, 255,
			255, 255, 255, 255, 255, 255 }, { 255, 255, 255, 255, 255, 255,
			255, 255 }, { 255, 255, 255, 255, 255, 255, 255, 255 }, { 5, 5, 5,
			5, 5, 5, 5, 5 }, { 2, 4, 3, 1, 0, 3, 4, 2 } };

	ST_set_table(S, Type_matrix);

	ST_set_bitmap(S, 0, *T_Ki);
	ST_set_bitmap(S, 1, *T_Q);
	ST_set_bitmap(S, 2, *T_R);
	ST_set_bitmap(S, 3, *T_B);
	ST_set_bitmap(S, 4, *T_Kn);
	ST_set_bitmap(S, 5, *T_P);
	ST_set_bitmap(S, 6, *T_WPos);
	ST_set_bitmap(S, 7, *T_BPos);

	fclose(fin);
}

