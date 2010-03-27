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

/* Desc:
 * Set both row and column for a LOC structure
 * Input:3: LOC structure , row , column
 * Output:0
 */
void LOC_set_both ( LOC , UCHAR , UCHAR );

#endif

