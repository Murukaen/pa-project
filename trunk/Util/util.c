/* General description :
 * Implements util.h
 */

/* ----- System #includes ----- */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

/* ----- Local #inlcudes ----- */
#include "util.h"
#include "../state/state.h"

#define MAX_PRECISION 5

UINT pow_ten[MAX_PRECISION];


/* ---- Macro #define ---- */

/* --- Types --- */


/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void util_init ( void ) {
	
	int i;
	for(i=1 , pow_ten[0] = 1 ; i < MAX_PRECISION ; pow_ten[i] = pow_ten[i-1] * 10 , ++i );
}

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


void LOC_free ( void * k) {
	
	P_LOC ploc = (P_LOC) k;
	free(ploc);
}

void * LOC_alloc ( void * k ) {
	
	P_LOC ploc = (P_LOC) k;
	P_LOC new_loc = LOC_new();
	LOCp_set_both ( new_loc , LOC_get_row ( ploc ) , LOC_get_col ( ploc ));
	
	return (void*) new_loc;
}

void LOC_print(FILE* fout,P_LOC loc){

	fprintf(fout,"\n (%d,%d)\n",LOC_get_row(loc),LOC_get_col(loc));
}

int fequ_loc ( void * key1 , void * key2) {
	
	P_LOC loc1 = ( P_LOC ) key1;
	P_LOC loc2 = ( P_LOC ) key2;
	
	if ( (LOC_get_row ( loc1 ) == LOC_get_row ( loc2 )) && ( LOC_get_col ( loc1 ) == LOC_get_col ( loc2 ) ) )
			
			return 1;
	
	return 0;
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

int ok_number ( char c ) {
	
	if ( '1' <= c && c <= '8' ) return 1;
	
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
		
		case T_K : rez = 'K'; break;
		case T_Q : rez = 'Q'; break;
		case T_R : rez = 'R'; break;
		case T_B : rez = 'B'; break;
		case T_N : rez = 'N'; break;
		case T_P : rez = 'P'; break;
		case T_NA : rez = '-' ; break ; 
		
		default: rez = 'X';
	}
	
	if ( off ) rez+='a' - 'A';
	
	return rez;
}
		
char row_to_letter ( UCHAR row ) {
	
		if ( 0<= row && row < SIZE_BMAP ) return 'a' + row;

		return 'X';
}

UCHAR letter_to_row ( char c ) {
	
		if ( ok_letter (c) ) return c - 'a';
		
		return T_NA;
}

char col_to_letter ( UCHAR col ) {
	
		if ( 0<= col && col < SIZE_BMAP ) return '1' + col;
		
		return 'X';
}

UCHAR letter_to_column ( char c ) {
	
		if ( ok_number (c) ) return c - '1';
		
		return T_NA;
}

void strupr ( char * text ) {
	
	for ( ; *text ; ++text ) 
		if ( 'a'<= *text && *text <='z' ) *text -= 'a' - 'A';
}

UCHAR text_to_tag ( char * text ) {
	
	strupr ( text );
	if ( ! strcmp ( text , "WHITE" ) ) return T_WP;
	if ( ! strcmp ( text , "BLACK" ) ) return T_BP;
	if ( ! strcmp ( text , "KING" ) ) return T_K;
	if ( ! strcmp ( text , "QUEEN" ) ) return T_Q;
	if ( ! strcmp ( text , "ROCK" ) ) return T_R;
	if ( ! strcmp ( text , "BISHOP" ) ) return T_B;
	if ( ! strcmp ( text , "KNIGHT" ) ) return T_N;
	if ( ! strcmp ( text , "PAWN" ) ) return T_P;
	
	
	return T_NA;
}

UINT get_time ( int prec ) {
	
	UINT cur_time = time ( NULL );
	
	return cur_time % pow_ten[prec];
}
		
		
