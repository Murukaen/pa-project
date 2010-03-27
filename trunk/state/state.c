/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdlib.h>
#include <ctype.h>
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
										 // the diff is given by the BMAP_BWP_OFFSET ( Black/White Position OFFSET) = 6

	List Table_Location[NR_COLORS][NR_PIECES]; // [2 colors] x [6 types of pieces] lista cu pozitiile pieselor pe tabla 
						// Table_Location[x][y] = lista de pozitii pe tabla de joc a piesei de culoarea x (0 - white, 1 - black )
						// si de tag(tip) ( y + PIECES_OFF (2-7) )

	/*  --- Used ONLY in state generator : --- */
	
	/* Desc : the TYPE ( tag ) of piece to be moved (2,7) */
	UCHAR piece_to_move;

	/* Desc : retains the index of the last made move */
	UCHAR move_index;

	/* Desc : current piece location [list] of the type (piece_to_move) which has to be processed by the state generating proocedure 
	 * It is a current element [list] in the list given by Table_Location[f_ENG_COL][piece_to_move - PIECES_OFF] 
	 * first_nod_list ( cur_poz_in_list ) is the location [P_LOC] of the current piece to be handled with
	 */
	List cur_poz_in_list; 

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

void ST_set_Table_What(STATE st, UCHAR T [][SIZE_BMAP]) {

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

UCHAR ST_get_piece_to_move(STATE st){

	return st -> piece_to_move ;
}

void ST_set_move_index(STATE st, UCHAR val) {

	st -> move_index = val;
}

UCHAR ST_get_move_index(STATE S){

	return S -> move_index;
}

List ST_get_cur_poz_in_list(STATE st){

	return st -> cur_poz_in_list;
}

void ST_set_cur_poz_in_list(STATE st,List l){

	st ->cur_poz_in_list = l;
}


void ST_free(STATE st) {

	if (st == 0)
		return;
	/* Free Table_Location */
	int i, j;
	for(i=0;i<NR_COLORS;++i)
		for(j=0;j<NR_PIECES;++j)
			free_list ( st -> Table_Location[i][j] , LOC_free );
			
	free(st);
}

void tag_to_text ( UCHAR tag , char text [] ) {
			
	switch ( tag ) {
			
		case 0 : strcpy ( text , "White" ); break;
		case 1 : strcpy ( text , "Black" ); break;
		case 2 : strcpy ( text , "King" ); break;
		case 3 : strcpy ( text , "Queen" ); break;
		case 4 : strcpy ( text , "Rock" ); break;
		case 5 : strcpy ( text , "Bishop" ); break;
		case 6 : strcpy ( text , "Knight" ); break;
		case 7 : strcpy ( text , "Pawn" ); break;
			
		default : strcpy ( text , "ERRTAG" ); 
	}
}

char tag_to_letter ( UCHAR tag ) {
	
	int off = ( 8<= tag && tag <=13 );
	if (off) tag-=BWP_OFF;
	char rez;
	
	switch ( tag ) {
		
		case 2 : rez = 'K'; break;
		case 3 : rez = 'Q'; break;
		case 4 : rez = 'R'; break;
		case 5 : rez = 'B'; break;
		case 6 : rez = 'N'; break;
		case 7 : rez = 'P'; break;
		
		default: rez = '-';
	}
	
	if ( off ) rez+='a' - 'A';
	
	return rez;
}
		
	

void state_print ( STATE st , FILE * fout ) {
	
	int i, j;
	List l;
	P_LOC loc;
	char text1[10]={0};
	char text2[10]={0};
	
	/* Print V_BMAP */
	fprintf(fout, "{\n~~~V_BMAP~~~ : \n" );
	for(i=0;i<SIZE_BMAP;++i) {
		
		tag_to_text ( i , text1 );
		fprintf(fout, "\n V[%s]=\n" , text1 );
		BM_print(st -> V_BMAP [i] , fout );
	}
	/* END Print V_BMAP */
	
	/* Print Table_What */
	fprintf(fout, "\n~~~Table_What~~~:\n\n");
	for(i=0;i<SIZE_BMAP;++i, fprintf(fout, "\n") )
		for(j=0;j<SIZE_BMAP;++j, fprintf(fout, " ") )
			fprintf(fout, "%c" , tag_to_letter ( st -> Table_What[BM_row(i)][BM_col(j)] ) );
	/* END Print Table_What */
	
	/* Print Table_Location */
	fprintf(fout, "\n~~~Table_Location~~~:\n");
	for(i=0;i<NR_COLORS;++i)
		for(j=0;j<NR_PIECES;++j) {
			
			tag_to_text ( i , text1 );
			tag_to_text ( j + PIECES_OFF , text2 );
			fprintf(fout, "\nTable_Location[%s][%s]:" , text1 , text2);
			l = ST_get_List_Table_Location(st, i , j + PIECES_OFF);
			for( loc = (P_LOC) first_nod_list ( &l ); loc ; fprintf(fout, " ( %u , %u ) " , LOC_get_row ( loc ) , LOC_get_col ( loc ) ) , loc = (P_LOC) first_nod_list ( &l ) );
		}
	/* END Print Table_Location */
	
	/* Print piece_to_move */
	fprintf(fout , "\n\npiece_to_move: %c\n" , tag_to_letter (st -> piece_to_move) );
	/* END Print piece_to_move */
	
	/* Print move_index */
	fprintf(fout , "\nmove_index: %u\n" , st -> move_index);
	/* END Print move_index */
	
	/* Print cur_poz_in_list */
	l = st -> cur_poz_in_list;
	loc = first_nod_list (&l);
	fprintf(fout, "\ncur_poz_in_list: ( %u , %u )\n\n}" , LOC_get_row ( loc ) , LOC_get_col ( loc ) );
	/* END Print cur_poz_in_list */
}

UCHAR letter_to_tag ( char c ) {
	
	c = toupper(c);
	
	switch (c) {
		
		case 'K' : return T_K ;
		case 'Q' : return T_Q ;
		case 'R' : return T_R ;
		case 'B' : return T_B ;
		case 'N' : return T_N ;
		case 'P' : return T_P ;
		
		default : return T_NA ;
	}
}

UCHAR letter_to_col ( char c ) {
	
	if ('a' <= c && c <= 'z' ) return 1; // black
	
	return 0; // white
}

STATE state_read ( FILE * fin ) {
	
	/* The new state */
	STATE st = ST_new ();
	/* END The new state */
	
	/* Auxiliary variables */
	int i, j;
	int row, col;
	char c;
	P_LOC loc;
	UCHAR color, tag;
	/* END Auxiliary variables */
	
	/* Structure fields */	
	BITMAP V_B[SIZE_BMAP]={0}; // all the 8 bitmaps
	UCHAR T_W [SIZE_BMAP][SIZE_BMAP];
	List T_L [NR_COLORS][NR_PIECES]; // 2 x 6
	UCHAR p_to_move;
	UCHAR m_index;
	List c_list;
	/* END Structure fields */
	
	/* Inits */
	for(i=0;i<NR_COLORS;++i)
		for(j=0;j<NR_PIECES;++j)
			T_L[i][j] = new_list ();
	/* END Inits */

	/* Read from file */
	for(i=0;i<SIZE_BMAP;++i)
		for(j=0;j<SIZE_BMAP;++j) {
				while ( fscanf(fin , "%c" , &c) && ( c == ' ' || c == '\n' || c=='\t' ) );
				row = BM_row (i);
				col = BM_col (j);
				color = letter_to_col ( c );
				tag = letter_to_tag ( c );
				if ( tag != T_NA ) {
					BM_Put_piece_at_coord ( &V_B[color] , row , col); // set the color BM
					BM_Put_piece_at_coord ( &V_B[tag] , row , col); // set the piece BM		
				}
				T_W[row][col] = tag + BWP_OFF * color; // set T_W
				if ( tag != T_NA ) {   
					loc = LOC_new ();
					LOCp_set_both ( loc , row , col );
					add_nod_list ( T_L[color][tag - PIECES_OFF] , (void *) loc );  // ser T_P
				}		
		}	
	p_to_move = ANALYZED_PIECE;
	m_index = 0;
	c_list = T_L [f_ENG_COL][ ANALYZED_PIECE - PIECES_OFF];
	/* END Read from file */
	
	/* Set the new state */
	for(i=0;i<SIZE_BMAP;++i)   // set bitmaps ( V_BMAP )
		ST_set_bitmap ( st , i , V_B[i] );
	ST_set_Table_What ( st , T_W ); // set Table_W
	for(i=0;i<NR_COLORS;++i)
		for(j=0;j<NR_PIECES;++j)
			ST_set_List_Table_Location ( st , i , j + PIECES_OFF , T_L [i][j] ); // set Table_Location
	ST_set_move_index (st , m_index ); // set move_index
	ST_set_piece_to_move ( st , p_to_move ); // set piece_to_move
	ST_set_cur_poz_in_list ( st , c_list ); // set cur_poz_in_list
	/* END Set the new state */
	
	return st;
}
	
		
	
	
						
				
			
