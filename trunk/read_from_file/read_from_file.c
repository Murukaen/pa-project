/* General description :
 *
 */

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ----- Local #inlcudes ----- */
#include "../state/state.h"
#include "../bitmap/bitmap.h"
#include "read_from_file.h"
#include "../list/list.h"
#include "../Util/util.h"
#include "../Flags/flags.h"

/* ---- Macro #define ---- */
#define FILE_INITIAL_STATE "Database/initial_state.in"

/* --- Types --- */

/* --- Procedures --- */

void Read_all_possible_moves(BITMAP Moves[5][8][8]) {

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
			Moves[3][i][j] = B[i][j];
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

STATE Read_initial_state( void ) {
	
	/* Read from file */
	FILE *fin = fopen (FILE_INITIAL_STATE , "r");
	STATE S = state_read ( fin );
	fclose(fin);
	/* END Read from file */
	
	/* Return read State */
	return S;
}
