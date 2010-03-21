/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdio.h>

/* ----- Local #inlcudes ----- */
#include "bitmap.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */
BITMAP M[DIM_BMAP];

/* --- Auxiliary Procedures --- */





/* --- Procedures --- */

void BM_init ( void ) {
        
       /* Init Mask vector */
       int i;
       for (i=0 , M[0] = 1 ; i < DIM_BMAP ; ++i , M[i] = M[i-1] << 1 );
}

BITMAP BM_Make_pos(UCHAR pos) {

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

UCHAR Get_first_elem_from (BITMAP B,UCHAR index){

	BITMAP mask = BM_Make_pos(index);

	B = B & mask;
}

UCHAR BM_Get_bit_from_coord(BITMAP B, int l, int c) {

	register int pos = l * SIZE_BMAP + c;
	
	return ( M[pos] & B ) ? 1 : 0;
}

UCHAR BM_Get_bit_from_pos(BITMAP B, int pos) {

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

void BM_Clear_piece_at_coord(BITMAP* B, int l, int c) {

	register int pos = l * SIZE_BMAP + c;
	
	(*B) &= ~ M [pos];
	
}
void BM_Clear_piece_at_BMAP(BITMAP* B, BITMAP P) {

	(*B) &= ~P;
}

int BM_Compare_BMAPs(BITMAP B1, BITMAP B2) {

	if ((B1 ^ B2) == 0) {
		return 1;
	} else {
		return 0;
	}

}

void BM_Clear_BMAP(BITMAP* B) {

	*B = 0;
}

void BM_Fill_BMAP(BITMAP* B) {

	(*B) = -1;
}
void BM_print(BITMAP a) {

	BITMAP i, bla, numar[64];

	for (i = 0; i < 64; i++) {

		bla = 1 & a;
		numar[i] = bla;
		a = a >> 1;
	}

	for (i = 0; i < 64; i++) {

		if (i % 8 == 0)
			printf("\n");
		printf("%lld  ", numar[i]);
	}
	printf("\n");
}
	
		

