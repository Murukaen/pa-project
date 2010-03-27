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

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			
			fread(&Moves[0][i][j], 8, 1, fin);
			fread(&Moves[1][i][j], 8, 1, fin);
			fread(&Moves[2][i][j], 8, 1, fin);	
			fread(&Moves[3][i][j], 8, 1, fin);
			fread(&Moves[4][i][j], 8, 1, fin);	
		}
	}

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

void print_all_possible_moves(FILE * fout, BITMAP Moves[5][8][8]) {

	int i, j, k;
	char text[10];
	for (i = 0; i < 5; i++) {
		
		tag_to_text ( i + PIECES_OFF , text );
		fprintf(fout, "piesa:%s\n", text );
		for (j = 0; j < 8; j++) {
			for (k = 0; k < 8; k++) {
				
				fprintf(fout ,"(%c %c)\n" , row_to_letter(j) , col_to_letter(k) );
				BM_print(Moves[i][j][k], fout);
				fprintf(fout, "\n");
			}
		}
	}
}
