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
#define T_WPos   1  // Pozitia pieselor negre
#define T_BPos 2  // Pozitia pieselor albe
#define T_Ki  3  // regi
#define T_Q  4  // regine
#define T_R  5  // ture
#define T_B 6  // nebuni
#define T_Kn   7  // cai

/* END Tags */
#define ST_fields 8

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
