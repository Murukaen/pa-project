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

BITMAP BM_Make_pos(int pos) {

	register BITMAP new_b = 1;

	return new_b = (new_b << pos);
}
BITMAP BM_Make_coord(int l, int c) {

	register char pos = 8 * (l % 8) + c % 8;
	register BITMAP new_b = 1;

	return new_b = new_b << pos;
}
int BM_Get_first_elem(BITMAP B) {

	register char aux = 0, i;

	for (i = 0; i < 64; i++) {
		aux = B & 1;
		if (aux == 1) {
			break;
		}
		B = B >> 1;
	}
	if (i == 64)
		i = -1;
	return i;
}
int BM_Get_bit_from_coord(BITMAP B, int l, int c) {

	register char pos = 8 * (l % 8) + c % 8;
	register BITMAP new_b = 1;

	new_b = new_b << pos;

	if ((B & new_b) == 0)
		return 0;
	return 1;
}
int BM_Get_bit_from_pos(BITMAP B, int pos) {

	register BITMAP new_b = 1;

	new_b = new_b << pos;

	if ((B & new_b) == 0)
		return 0;
	return 1;
}
BITMAP BM_Put_piece_at_coord(BITMAP *B, int l, int c) {

	register char pos = 8 * (l % 8) + c % 8;
	register BITMAP new_b = 1;

	new_b = new_b << pos;

	*B = *B | new_b;

	return *B;
}
BITMAP BM_Put_piece_at_BMAP(BITMAP* B, BITMAP P) {

	*B = (*B | P);
	return *B;
}

int BM_Is_piece_at_coord(BITMAP B, int c, int l) {

	register char is, pos = 8 * (l % 8) + c % 8;

	is = (B >> pos) & 1;
	return is;
}

int BM_Is_piece_at_BMAP(BITMAP B, BITMAP B1) {

	if ((B & B1) == 0) {
		return 0;
	}
	return 1;

}
void BM_Clear_piece_at_coord(BITMAP* B, int l, int c) {

	register char pos = 8 * (l % 8) + c % 8;
	register BITMAP x = 1;

	x = x << pos;
	*B = *B ^ x;
}
void BM_Clear_piece_at_BMAP(BITMAP* B, BITMAP P) {

	*B = *B ^ P;
}

int BM_Compare_BMAPs(BITMAP B1, BITMAP B2) {

	if ((B1 & B2) == 0) {
		return 0;
	} else {
		return 1;
	}

}

void BM_Clear_BMAP(BITMAP* B) {

	*B = 0;
}

void BM_Fill_BMAP(BITMAP* B) {

	char i = 0;
	*B = 1;
	for (; i < 64; i++) {

		*B = (*B << 1) + 1;
	}
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
	
		

