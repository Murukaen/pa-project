/* General description :
 * Imeplents bitmap entity
 */

#ifndef _BITMAP_H
#define _BITMAP_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */

/* ---- Macro #define ---- */

#define SIZE_BMAP 8
#define DIM_BMAP (SIZE_BMAP) * (SIZE_BMAP)

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
 * 0 in coltul stanga sus si 63 in coltul dreapta jos
*/
BITMAP BM_Make_pos(int);


/* Creeaza un bitmap cu valoarea 1 pe pozitia data ca argument
 * arg1 = linia
 * arg2 = coloana  
 */
BITMAP BM_Make_coord(int,int);


/* intoarce indexul primului 1 din BITMAP,pornind din coltul stga sus -> dreapta jos
 * returneaza -1 daca nu gaseste niciun 1
 */
int BM_Get_first_elem (BITMAP);


/* Intoarce valoarea bitului de la coordonatele date ca argument */
int BM_Get_bit_from_coord(BITMAP,int ,int);


/* Intoarce valoarea bitului de la pozitia data ca argument */
int BM_Get_bit_from_pos(BITMAP,int);


/* pune in BITMAP-ul dat ca argument, valoarea 1 la coordonatele date ca parametru*/
BITMAP BM_Put_piece_at_coord (BITMAP*,int,int);


/* pune in BITMAP-ul dat ca prim argument , valoarea 1 din BITMAP-ul 2 dat ca argument*/
BITMAP BM_Put_piece_at_BMAP (BITMAP*,BITMAP);


/* intoarce 1 daca gaseste piesa la pozitia descrisa de coordonatele date ca
 * parametru,0 daca nu
 */
int BM_Is_piece_at_coord(BITMAP,int,int);


/* intoarce 1 daca gaseste piesa la pozitia indicata
 * de BITmapul al 2 lea de la argument
 */
int BM_Is_piece_at_BMAP (BITMAP,BITMAP);


/* sterge elementul de la pozitia data, nu modifica restul elementelor*/
void BM_Clear_piece_at_coord(BITMAP*,int,int);


/*arg 1 : bitmapul asupra caruia se efectueaza modificarea
 * arg 2 : bitmapul care reprezinta pozitia de va fi setata pe 0 */
void BM_Clear_piece_at_BMAP(BITMAP*,BITMAP);


/* capitane ghici ce face asta :)) intoarce 1=exista, 0=nu exista */
int BM_Compare_BMAPs(BITMAP,BITMAP);


/* pune 0 peste tot */
void BM_Clear_BMAP(BITMAP*);


/* pune :D 1 peste tot*/
void BM_Fill_BMAP(BITMAP*);


/*printeaza bitmap*/
void BM_print(BITMAP);



#endif
