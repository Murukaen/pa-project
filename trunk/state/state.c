	/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdlib.h>
#include <string.h>

/* ----- Local #inlcudes ----- */
#include "state.h"
#include "../Flags/flags.h"

/* ---- Macro #define ---- */

#define BMAP_NR_ST 8 // number of bitmaps in a state ; each for each general tag (0-7)
/* --- Types --- */

/* ~~~ STATE structure ~~~ */
struct s_state {

	BITMAP V_BMAP[BMAP_NR_ST];

	UCHAR Table_What[SIZE_BMAP][SIZE_BMAP]; // 8x8 tagul piesei de pe acea pozitie white: (2-7) ; black : (8-13)
	// the diff is given by the BWP_OFFSET ( Black/White Position OFFSET) = 6

	List Table_Location[NR_COLORS][NR_PIECES]; // [2 colors] x [6 types of pieces] lista cu pozitiile pieselor pe tabla 
	// Table_Location[x][y] = lista de pozitii pe tabla de joc a piesei de culoarea x (0 - white, 1 - black )
	// si de tag(tip) ( y + PIECES_OFF (2-7) )

	/*  --- Used ONLY in state generator : --- */

	/* Desc : the TYPE ( tag ) of piece to be moved (2,7) */
	UCHAR piece_to_move;

	/* Desc : retains the index of the last made move */
	UCHAR move_index;

	/* Desc : current piece location [list] of the type (piece_to_move) which has to be processed by the state generating proocedure 
	 * It is a current element [list] in the list given by Table_Location[col_on_move][piece_to_move - PIECES_OFF] 
	 * first_nod_list ( cur_poz_in_list ) is the location [P_LOC] of the current piece to be handled with
	 */
	List cur_poz_in_list;

	UCHAR col_on_move; // color on move in this state

	P_LOC en_passant;

	UCHAR gen_init;
};
/* ~~~ END state structure ~~~ */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

STATE ST_new(void) {

	STATE new_state = (STATE) calloc(1, sizeof(struct s_state));

	return new_state;
}

BITMAP ST_get_bitmap(STATE st, int tag) {

	return st -> V_BMAP[tag];
}

void ST_set_bitmap(STATE st, int tag, BITMAP b) {

	st -> V_BMAP[tag] = b;
}

void ST_set_Table_What(STATE st, UCHAR T[][SIZE_BMAP]) {

	int i, j;
	for (i = 0; i < SIZE_BMAP; ++i)
		for (j = 0; j < SIZE_BMAP; ++j)
			st -> Table_What[i][j] = T[i][j];

}

void ST_set_tag_Table_What(STATE st, int row, int col, UCHAR tag) {

	st -> Table_What[row][col] = tag;
}

UCHAR ST_get_tag_Table_What(STATE st, int row, int col) {

	return st -> Table_What[row][col];
}

List ST_get_List_Table_Location(STATE st, int col_tag, int piece_tag) {

	return st -> Table_Location[col_tag][piece_tag - PIECES_OFF];
}

void ST_set_List_Table_Location(STATE st, int col_tag, int piece_tag, List list) {

	st -> Table_Location[col_tag][piece_tag - PIECES_OFF] = list;
}

void ST_set_piece_to_move(STATE st, UCHAR val) {

	st -> piece_to_move = val;
}

UCHAR ST_get_piece_to_move(STATE st) {

	return st -> piece_to_move;
}

void ST_set_move_index(STATE st, UCHAR val) {

	st -> move_index = val;
}

UCHAR ST_get_move_index(STATE S) {

	return S -> move_index;
}

List ST_get_cur_poz_in_list(STATE st) {

	return st -> cur_poz_in_list;
}

void ST_set_cur_poz_in_list(STATE st, List l) {

	st ->cur_poz_in_list = l;
}

void ST_set_col_on_move(STATE st, UCHAR color) {

	st -> col_on_move = color;
}

UCHAR ST_get_col_on_move(STATE st) {

	return st -> col_on_move;
}

UCHAR ST_get_gen_init ( STATE st ) {
	
	return st -> gen_init;
}

void ST_set_gen_init ( STATE st , UCHAR val ) {
	
	st -> gen_init = val;
}

P_LOC ST_get_en_passant ( STATE st ) {
	
	return st -> en_passant;
}

void ST_set_en_passant ( STATE st , P_LOC ploc ) {
	
	st -> en_passant = ploc;
}

void ST_free(STATE st) {

	if (st == 0)
		return;
	/* Free Table_Location */
	int i, j;
	for (i = 0; i < NR_COLORS; ++i)
		for (j = 0; j < NR_PIECES; ++j)
			free_list(st -> Table_Location[i][j], LOC_free);
			
	/* Free en_passant */
	if ( st -> en_passant ) LOC_free ( st -> en_passant );

	free(st);
}

void state_print(STATE st, FILE * fout) {
	fprintf(fout,
			"\n{\n--------------------------------------------------------------\n");
	/* Test State */
	if (st == 0) {

		fprintf(fout, "Error : Void state\n");
		fprintf(fout,
				"--------------------------------------------------------------\n}\n");
		return;
	}
	/* END Test State */

	int i, j;
	List l;
	P_LOC loc;
	char text1[10] = { 0 };
	char text2[10] = { 0 };

	/* Print V_BMAP */
	fprintf(fout, "\n~~~V_BMAP~~~ : \n");
	for (i = 0; i < SIZE_BMAP; ++i) {
		tag_to_text(i, text1);
		fprintf(fout, "\n V[%s]=\n", text1);
		BM_print(st -> V_BMAP[i], fout);
	}
	/* END Print V_BMAP */

	/* Print Table_What */
	fprintf(fout, "\n~~~Table_What~~~:\n\n");
	for (i = 0; i < SIZE_BMAP; ++i, fprintf(fout, "\n"))
		for (j = 0; j < SIZE_BMAP; ++j, fprintf(fout, " "))
			fprintf(fout, "%c", tag_to_letter(
					st -> Table_What[BM_row(i, j)][BM_col(i, j)]));
	/* END Print Table_What */

	/* Print Table_Location */
	fprintf(fout, "\n~~~Table_Location~~~:\n");
	for (i = 0; i < NR_COLORS; ++i)
		for (j = 0; j < NR_PIECES; ++j) {

			tag_to_text(i, text1);
			tag_to_text(j + PIECES_OFF, text2);
			fprintf(fout, "\nTable_Location[%s][%s]:", text1, text2);
			l = ST_get_List_Table_Location(st, i, j + PIECES_OFF);
			if (l)
				for (loc = (P_LOC) first_nod_list(&l); loc; fprintf(fout,
						" ( %c , %c ) ", row_to_letter(LOC_get_row(loc)),
						col_to_letter(LOC_get_col(loc))), loc
						= (P_LOC) first_nod_list(&l))
					;
			else
				fprintf(fout, " Void List ");
		}
	/* END Print Table_Location */

	/* Print col_on_move */
	tag_to_text(st -> col_on_move, text1);
	fprintf(fout, "\n\nColor on move : %s\n", text1);
	/* END Print col_on_move */

	/* Print piece_to_move */
	tag_to_text(st -> piece_to_move, text1);
	fprintf(fout, "\nPiece to move: %s\n", text1);
	/* END Print piece_to_move */

	/* Print move_index */
	fprintf(fout, "\nMove index: %u\n", st -> move_index);
	/* END Print move_index */

	/* Print cur_poz_in_list */
	l = st -> cur_poz_in_list;
	if (l) {
		loc = first_nod_list(&l);
		fprintf(fout, "\nCurrent piece location : ( %c , %c )\n",
				row_to_letter(LOC_get_row(loc)),
				col_to_letter(LOC_get_col(loc)));
	} else
		fprintf(fout, "\nCurrent piece location : Void List\n");
	/* END Print cur_poz_in_list */
	
	/* Print gen_init */
	fprintf( fout , "\nGen_Init : %u\n" , st -> gen_init );
	/* END Print gen_init */
	
	/* Print en_passant */
	if ( st -> en_passant ) fprintf(fout, "\nEn Passant Location : ( %c , %c )\n", row_to_letter(LOC_get_row(st -> en_passant )), col_to_letter(LOC_get_col(st -> en_passant )));
		else fprintf(fout, "\nEn Passsant Location : Void \n");
	/* END Print en_passant */
	fprintf(fout,
			"--------------------------------------------------------------\n}\n");
}

STATE state_read(FILE * fin) {

	/* The new state */
	STATE st = ST_new();
	/* END The new state */

	/* Auxiliary variables */
	int i, j;
	int row, col;
	char c;
	P_LOC loc;
	UCHAR color, tag;
	UCHAR c_on_move;
	char line[20];
	char *color_text = 0;
	/* END Auxiliary variables */

	/* Structure fields */
	BITMAP V_B[SIZE_BMAP] = { 0 }; // all the 8 bitmaps
	UCHAR T_W[SIZE_BMAP][SIZE_BMAP];
	List T_L[NR_COLORS][NR_PIECES]; // 2 x 6
	UCHAR p_to_move;
	UCHAR m_index;
	List c_list;
	UCHAR g_init;
	/* END Structure fields */

	/* Inits */
	for (i = 0; i < NR_COLORS; ++i)
		for (j = 0; j < NR_PIECES; ++j)
			T_L[i][j] = new_list();
	/* END Inits */

	/* Read from file */
	do {
		fgets(line, 19, fin);
		line[strlen(line) - 1] = '\0'; // remove \n
		color_text = strrchr(line, '>');
	} while (color_text == 0);
	color_text++;
	for (i = 0; i < SIZE_BMAP; ++i)
		for (j = 0; j < SIZE_BMAP; ++j) {
			while (fscanf(fin, "%c", &c) && (!ok_letter(c)))
				;
			row = BM_row(i, j);
			col = BM_col(i, j);
			color = letter_to_col(c);
			tag = letter_to_tag(c);
			if (tag != T_NA) {
				BM_Put_piece_at_coord(&V_B[color], row, col); // set the color BM
				BM_Put_piece_at_coord(&V_B[tag], row, col); // set the piece BM
			}
			T_W[row][col] = tag + BWP_OFF * color; // set T_W
			if (tag != T_NA) {
				loc = LOC_new();
				LOCp_set_both(loc, row, col);
				add_nod_list(T_L[color][tag - PIECES_OFF], (void *) loc); // ser T_P
			}
		}
	p_to_move = ANALYZED_PIECE;
	m_index = 0;
	c_on_move = text_to_tag(color_text);
	c_list = T_L[c_on_move][ANALYZED_PIECE - PIECES_OFF];
	g_init = 0;
	/* END Read from file */

	/* Set the new state */
	for (i = 0; i < SIZE_BMAP; ++i) // set bitmaps ( V_BMAP )
		ST_set_bitmap(st, i, V_B[i]);
	ST_set_Table_What(st, T_W); // set Table_W
	for (i = 0; i < NR_COLORS; ++i)
		for (j = 0; j < NR_PIECES; ++j)
			ST_set_List_Table_Location(st, i, j + PIECES_OFF, T_L[i][j]); // set Table_Location
	ST_set_col_on_move(st, c_on_move);
	ST_set_move_index(st, m_index); // set move_index
	ST_set_piece_to_move(st, p_to_move); // set piece_to_move
	ST_set_cur_poz_in_list(st, c_list); // set cur_poz_in_list
	ST_set_gen_init ( st , 0 );
	/* END Set the new state */

	return st;
}

void state_print_Table_What(STATE st, FILE *fout) {

	int i,j;
	fprintf(fout, "\n~~~Table_What~~~:\n\n");
	for (i = 0; i < SIZE_BMAP; ++i, fprintf(fout, "\n"))
		for (j = 0; j < SIZE_BMAP; ++j, fprintf(fout, " "))
			fprintf(fout, "%c", tag_to_letter(
					st -> Table_What[BM_row(i, j)][BM_col(i, j)]));


}

