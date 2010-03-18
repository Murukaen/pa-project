/* General description :
 * Implements util.h
 */

/* ----- System #includes ----- */
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "util.h"

/* ---- Macro #define ---- */

/* --- Types --- */
struct LOC {
	
	int row, col;
};

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

P_LOC loc_new ( void ) {

	P_LOC L = (P_LOC) calloc(1,sizeof(struct LOC));
	return L;
}

void loc_set_both ( P_LOC  L, UCHAR lin, UCHAR col ) {

	L -> row = lin;
	L -> col = col;
}

LOC loc_get_both ( P_LOC L) {
	
	return *L;
}

UCHAR loc_get_row ( P_LOC L) {

	return L -> row;
}

UCHAR loc_get_col ( P_LOC L) {
	
	return L -> col;
}

void LOC_set_both ( LOC l, UCHAR r, UCHAR c) {
	
		l.row = r;
		l.col = c;
}

UCHAR matrix_to_linear ( LOC l ) {
	
		return l.row * SIZE_TABLE + l.col;
}

void linear_to_matrix ( UCHAR pos , LOC * l ) {
	
		(*l).row = pos / SIZE_TABLE;
		(*l).col = pos % SIZE_TABLE;
}

