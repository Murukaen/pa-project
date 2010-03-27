/* General description :
 * Implements util.h
 */

/* ----- System #includes ----- */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ----- Local #inlcudes ----- */
#include "util.h"
#include "../state/state.h"

/* ---- Macro #define ---- */

/* --- Types --- */


/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

P_LOC LOC_new ( void ) {

	P_LOC L = (P_LOC) calloc(1,sizeof(struct LOC));
	return L;
}

void LOCp_set_both ( P_LOC  L, UCHAR lin, UCHAR col ) {

	L -> row = lin;
	L -> col = col;
}

LOC LOC_get_both ( P_LOC L) {
	
	return *L;
}

UCHAR LOC_get_row ( P_LOC L) {

	return L -> row;
}

UCHAR LOC_get_col ( P_LOC L) {
	
	return L -> col;
}

void LOC_set_both ( LOC l, UCHAR r, UCHAR c) {
	
		l.row = r;
		l.col = c;
}

void LOC_free ( void * key) {
	
	P_LOC ploc = (P_LOC) key;
	free(ploc);
}

UCHAR matrix_to_linear ( LOC l ) {
	
		return l.row * SIZE_TABLE + l.col;
}

void linear_to_matrix ( UCHAR pos , LOC * l ) {
	
		(*l).row = pos / SIZE_TABLE;
		(*l).col = pos % SIZE_TABLE;
}

/* Numbers */

UCHAR not ( UCHAR b) {
	
	return (1-b);
}

/* Tags */

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

int ok_letter ( char c ){
	
	if ( 'a' <= c && c <= 'z' ) return 1;
	if ( 'A' <= c && c <= 'Z' ) return 1;
	if ( c == '-' ) return 1;
	
	return 0;
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
		
char row_to_letter ( UCHAR row ) {
	
		if ( 0<= row && row < SIZE_BMAP ) return 'a' + row;

		return 'X';
}

char col_to_letter ( UCHAR col ) {
	
		if ( 0<= col && col < SIZE_BMAP ) return '1' + col;
		
		return 'X';
}



