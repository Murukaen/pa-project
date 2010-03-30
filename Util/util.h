/* General description :
 * Implements genral use types and associated procedures
 */

#ifndef _UTIL_H
#define _UTIL_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */

/* ---- Macro #define ---- */

#ifndef _UCHAR
#define _UCHAR
typedef unsigned char UCHAR;
#endif

#include <stdio.h>
#define SIZE_TABLE 8

struct LOC {
	
	UCHAR row, col;
};

typedef struct LOC LOC;

typedef LOC* P_LOC; // --> Generic Reference

/* --- Types --- */

/* --- Procedures --- */

/* LOC Procedures */

P_LOC LOC_new ( void );

/*linie-coloana*/
void LOCp_set_both ( P_LOC , UCHAR , UCHAR );

LOC LOC_get_both ( P_LOC );

UCHAR LOC_get_row ( P_LOC );

UCHAR LOC_get_col ( P_LOC );

void LOC_free ( void * );

void * LOC_alloc ( void * );

void LOC_print(FILE *,P_LOC);

/* Desc:
 * Tests if two P_LOC variables have equal content
 * Input:2: key 1 [void *] , key2 [void*]
 * Output:1:  1 - equal ; 0 - not equal
 */
int fequ_loc ( void * , void * );

/* Desc:
 * Transforms (row,col) coordinates into linear pozition equivalent 
 * Input:1: LOC structure
 * Output:1: pozition
 */
UCHAR matrix_to_linear ( LOC );

/* Desc:
 * Transforms linear pozition into (row,col) equivalent coordinates 
 * Input:2: pozition , address to LOC
 * Output:0
 */
void linear_to_matrix ( UCHAR , LOC* ); 

/* Numbers */

/* Desc:
 * Returneaza un bit negat
 */
UCHAR not ( UCHAR );

/* ~~~ Tags ~~~ */

UCHAR letter_to_tag ( char );

/* Letter to color */
UCHAR letter_to_col ( char );

/* character is in Table_What format */
int ok_letter ( char );

void tag_to_text ( UCHAR , char [] );

char tag_to_letter ( UCHAR );	

char row_to_letter ( UCHAR );

char col_to_letter ( UCHAR );

UCHAR text_to_tag ( char * );

#endif

