/* General description :
 * Implementation of state entity
 */

#ifndef _STATE_H
#define _STATE_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../bitmap/bitmap.h"

/* ---- Macro #define ---- */

/* Tags :*/
#define T_WHO 0  // Jucatorul la mutare
#define T_W   1  //  Pozitia pieselor albe
#define T_WKi 2  // Poz regelui alb
#define T_WQ  3  // Poz reginei albe
#define T_WR  4  // Poz turelor albe
#define T_WB  5  // Poz nebunilor albi
#define T_WKn 6  // Poz cailor albi
#define T_B   7  // Pozitia pieselor negre
#define T_BKi 8  // Pozitia regelui negru
#define T_BQ  9  // Pozitia reginei negre
#define	T_BR  10 // Pozitia turelor negre
#define T_BB  11 // Pozitia nebunilor negri
#define	T_BKn 12 // Pozitia cilor negri
/* END Tags */
#define ST_fields 12

/* --- Types --- */
typedef BITMAP* STATE; // state is a pointer to a 8-elem vector of bitmaps

/* --- Procedures --- */

/* Desc :
 * State constructor with no data inside
 * Input:0
 * Output:1: new_state [state]
*/
STATE ST_new ( void );

 /* Description :
 * Gets the bitmap associated with the given tag from a state
 * Input:2: state , bitmap_TAG
 * Output:1: bitmap
 */
BITMAP ST_get_bitmap(STATE, int);

/* Description :
 * Sets the bitmap associated with the given tag from a state
 * Input:2: state , bitmap_TAG , bitmap_to_set
 * Output:0
 */
void ST_set_bitmap(STATE, int, BITMAP);

/* Desc:
 * Destructor state
 * Input:1: state
 * Output:0
 */
void ST_free(STATE);

#endif
