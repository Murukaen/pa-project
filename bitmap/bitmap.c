/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdio.h>

/* ----- Local #inlcudes ----- */
#include "bitmap.h"
#include "../Util/util.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */
BITMAP M[DIM_BMAP]; // Masks : M[i] = 2^i [BITMAP]

/* --- Auxiliary Procedures --- */





/* --- Procedures --- */

void BM_init ( void ) {
        
       /* Init Mask vector */
       int i;
       for (i=0 , M[0] = 1 ; i < DIM_BMAP ; ++i , M[i] = M[i-1] << 1 );
}

BITMAP BM_Make_pos(int pos) {

	return M[pos];
}

BITMAP BM_Make_coord(int l, int c) {

	return M [ l * SIZE_BMAP + c ];
	
}

UCHAR BM_Get_first_elem(BITMAP B) {

	register UCHAR aux = 0, i;

	for (i = 0; i < 64; i++) {
		aux = B & 1;
		if (aux == 1) {
			break;
		}
		B = B >> 1;
	}
	
	return i;
}

UCHAR BM_Get_bit_from_coord(BITMAP B, int l, int c) {

	register int pos = l * SIZE_BMAP + c;
	
	return ( M[pos] & B ) ? 1 : 0;
}

UCHAR BM_Get_bit_from_index (BITMAP B, int pos) {

	return ( M[pos] & B ) ? 1 : 0;
}

UCHAR BM_Get_bit_from_BMAP (BITMAP B, BITMAP B1) {

	return ( B & B1 ) ? 1 : 0;
}

void BM_Put_piece_at_coord(BITMAP *B, int l, int c) {

	register int pos = l * SIZE_BMAP + c;
	
	(*B) |= M[pos];
}
void BM_Put_piece_at_BMAP(BITMAP* B, BITMAP P) {

	(*B) |= P;
}

void BM_Put_piece_at_pos ( BITMAP* B, int pos) {
	
	(*B) |= M[pos];
}

void BM_Clear_piece_at_coord(BITMAP* B, int l, int c) {

	register int pos = l * SIZE_BMAP + c;
	
	(*B) &= ~ M [pos];
	
}
void BM_Clear_piece_at_BMAP(BITMAP* B, BITMAP P) {

	(*B) &= ~P;
}


int BM_Compare_BMAPs(BITMAP B1, BITMAP B2) {

        if ((B1 ^ B2) == 0) return 1;
                
        return 0;
}


int BM_Equal1_BMAPs(BITMAP B1, BITMAP B2) {

	if ((B1 & B2) == 0) return 0;
		
	return 1;
}

void BM_Clear_BMAP(BITMAP* B) {

	*B = 0;
}

void BM_Fill_BMAP(BITMAP* B) {

	(*B) = -1;
}

void BM_print(BITMAP B , FILE * fout) {

	int i;
	UCHAR Mat [SIZE_BMAP][SIZE_BMAP];
	
	/* Construct Mat */	
	for(i=0;i<DIM_BMAP;++i) 
		
			Mat [ SIZE_BMAP -1 - i% 8 ][ i/8 ] = BM_Get_bit_from_index ( B , i );
			
	/* Print Mat */
	int j;
	
	fprintf(fout, "\n");
	for(i=0;i<SIZE_BMAP;++i, fprintf(fout , "\n") )
		for(j=0;j<SIZE_BMAP; ++j , fprintf(fout , " ") )
			fprintf(fout, "%u" , Mat[i][j] );
			
}

BITMAP Mat_to_BM ( UCHAR Mat [][SIZE_BMAP] ) {
	
	BITMAP b = BM_NULL;
	int i, j, pos = -1;
	for(j=0;j<=SIZE_BMAP;++j)
		for(i=SIZE_BMAP-1;i>=0;--i) {
			++pos;
			if ( Mat[i][j] ) BM_Put_piece_at_pos (&b , pos);
	}		
	return b;
}

UCHAR BM_row ( UCHAR row , UCHAR col ) {
	
	return col;
}

UCHAR BM_col ( UCHAR row , UCHAR col ) {
	
	return SIZE_BMAP - 1 - row;
}

void BM_Put_piece_at_mat_coord ( BITMAP * B, int row, int col) {
	
	BM_Put_piece_at_coord ( B , BM_row (row , col ) , BM_col (row , col) );
}



	
	
		

