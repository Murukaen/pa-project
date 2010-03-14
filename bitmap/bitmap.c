/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "bitmap.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */
bitmap M [MATRIX_SIZE*MATRIX_SIZE];

/* --- Auxiliary Procedures --- */

/* Description:
 * Liniarise matrix(8x8) coefficients
 * Input:2: line , col
 * Output:1: index
 */
int mat_to_lin ( int row, int col ) {
	
	return row*MATRIX_SIZE + col;
}

/* --- Procedures --- */

void bitmap_init ( void ) {
	
	    /* Init Mask vector */
		int i;
		for (i=0 , M[0] = 1 ; i < MATRIX_SIZE*MATRIX_SIZE ; ++i , M[i] = M[i-1] << 1 );
}

int bitmap_get_bit ( bitmap bmap , int row , int col) {
	
	//TODO
}

void bitmap_set_bit ( bitmap bmap, int row, int col, int val) {

	//TODO	
}
	
		

