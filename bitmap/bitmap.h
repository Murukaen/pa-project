/* General description :
 * Imeplents bitmap entity
 */

#ifndef _BITMAP_H
#define _BITMAP_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */

/* ---- Macro #define ---- */
#define MATRIX_SIZE 8

/* --- Types --- */
typedef long long int bitmap;

/* --- Procedures --- */

/* Description :
 * Initialize bitmap working strucures
 * Input:0
 * Output:0
 */
void bitmap_init ( void );

/* Description:
 * Gets the value from a bitmap at the location determined by the row and column
 * Input:3: bitmap , row_number , col_number
 * Output:1: value of bit at that location
 */
int bitmap_get_bit ( bitmap , int , int);

/* Description:
 * Sets the value from a bitmap at the location determined by the row and column with the given bit value
 * Input:4: bitmap , row_number , col_number , value_to_set
 * Output:0
 */
void bitmap_set_bit ( bitmap , int , int , int );

#endif
