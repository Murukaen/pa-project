/* General description :
 * 
 */

// !!! Remove this : NAME = Name of file
#ifndef _UPDATE_STATE_H
#define _UPDATE_STATE_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../state/state.h"
#include "../cur_state/cur_state.h"
#include "../move/move.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

/* Desc :
 * Updates the current state based on the old one and the last move
 * Input:1: move
 * Output:0
 */
void update_state ( move );

#endif

