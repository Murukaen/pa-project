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
#define TAG_P 0 // Player
#define TAG_O 1 // O
#define TAG_PW 2 // Pawns
#define TAG_N 3 // Knights
#define TAG_B 4 // Bishops
#define TAG_R 5 // Rocks
#define TAG_Q 6 // Queens
#define TAG_K 7 // Kings
/* END Tags */

#define BMPS 8

/* --- Types --- */
typedef bitmap* state; // state is a pointer to a 8-elem vector of bitmaps

/* --- Procedures --- */

/* Desc :
 * State constructor with no data inside
 * Input:0
 * Output:1: new_state [state]

state state_new ( void );

/* Description :
 * Gets the bitmap associated with the given tag from a state
 * Input:2: state , bitmap_TAG
 * Output:1: bitmap
 */
bitmap state_get_bitmap ( state , int );

/* Description :
 * Sets the bitmap associated with the given tag from a state
 * Input:2: state , bitmap_TAG , bitmap_to_set
 * Output:0
 */
void state_set_bitmap ( state , int , bitmap );


/* Desc:
 * Destructor state
 * Input:1: state
 * Output:0
 */
void state_free ( state );

#endif
