/* General description :
 * Imeplents bitmap entity
 */

#ifndef _BITMAP_H
#define _BITMAP_H

/* ----- System #includes ----- */
#include <stdio.h>

/* ----- Local #inlcudes ----- */
#include "../Util/util.h"

/* ---- Macro #define ---- */

#define SIZE_BMAP 8
#define DIM_BMAP (SIZE_BMAP) * (SIZE_BMAP)
#define BM_NULL 0

/* --- Types --- */
typedef long long int BITMAP;

/* --- Procedures --- */

/* Desc:
 * Initialize bitmap. Create masks ( 64 ) . M[i] = 2^i .
 * Input:0
 * Output:0
 */
void BM_init ( void );


/* Creeaza un bitmap cu valoarea 1 pe pozitia data ca argument
 * 0 in coltul stanga jos si 63 in coltul dreapta sus
*/
BITMAP BM_Make_pos(int);


/* Creeaza un bitmap cu valoarea 1 pe pozitia data ca argument
 * arg1 = linia
 * arg2 = coloana  
 */
BITMAP BM_Make_coord(int,int);


/* intoarce indexul primului 1 din BITMAP,pornind din coltul stanga jos -> dreapta sus
 * returneaza -1 daca nu gaseste niciun 1
 */
UCHAR BM_Get_first_elem (BITMAP);

/* Intoarce valoarea bitului de la coordonatele date ca argument */
UCHAR BM_Get_bit_from_coord(BITMAP,int ,int);


/* Intoarce valoarea bitului de la pozitia data ca argument */
UCHAR BM_Get_bit_from_pos(BITMAP,int);

/* intoarce 1 daca gaseste piesa la pozitia indicata
 * de BITmapul al 2 lea de la argument
 */
UCHAR BM_Get_bit_from_BMAP ( BITMAP , BITMAP );


/* pune in BITMAP-ul dat ca argument, valoarea 1 la coordonatele date ca parametru*/
void BM_Put_piece_at_coord (BITMAP*,int,int);


/* pune in BITMAP-ul dat ca prim argument , valoarea 1 din BITMAP-ul 2 dat ca argument*/
void BM_Put_piece_at_BMAP (BITMAP*,BITMAP);

/* pune in BITMAP-ul dat ca prim argument , valoare 1 la pozitia data ca parametru */
void BM_Put_piece_at_pos ( BITMAP* , int );

/* sterge elementul de la pozitia data, nu modifica restul elementelor*/
void BM_Clear_piece_at_coord(BITMAP*,int,int);


/*arg 1 : bitmapul asupra caruia se efectueaza modificarea
 * arg 2 : bitmapul care reprezinta pozitia de va fi setata pe 0 */
void BM_Clear_piece_at_BMAP(BITMAP*,BITMAP);

int BM_Compare_BMAPs(BITMAP B1, BITMAP B2);

/* capitane ghici ce face asta :)) intoarce 1=exista, 0=nu exista */
int BM_Equal1_BMAPs(BITMAP,BITMAP);


/* pune 0 peste tot */
void BM_Clear_BMAP(BITMAP*);


/* pune :D 1 peste tot*/
void BM_Fill_BMAP(BITMAP*);

/* ~~~ User for Test purposes ONLY ~~~ */

/* Desc:
 * Prints a bitmap in the representation of the chess board
 * Input:1: bitmap , FILE * out
 * Output:0
 */
void BM_print( BITMAP , FILE * );

/* Desc:
 * Returns an equivalent bitmap from a binary matrix
 * The matrix is the chess table saw from the white perspective
 * The bitmap is constructed from the lower left corner to the upper right corner of the matrix
 * Input:1: Matrix
 * Output:1: bitmap
 */ 
BITMAP Mat_to_BM ( UCHAR [][SIZE_BMAP] );

/* Desc:
 * TEST ONLY
 * Puts a piece on the given coordinates seen from the white perspective on the chess board
 * Input:3: address to bitmap, row, col
 * Output:0
 */
void BM_Put_piece_at_mat_coord ( BITMAP * , int , int );

/* Desc:
 * TEST ONLY
 * Converts WVM ( White View Matrix ) loc to Bm row
 * Input:1: row int WVM
 * Output:1: row in BM
 */
UCHAR BM_row ( UCHAR , UCHAR );

/* Desc:
 * TEST ONLY
 * Converts WVM ( White View Matrix ) loc to Bm column
 * Input:1: column int WVM
 * Output:1: column in BM
 */
UCHAR BM_col ( UCHAR , UCHAR );
	 
#endif
