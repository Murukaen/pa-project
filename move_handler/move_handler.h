/* General description :
 * Determines the move between two consecitive states
 * 
 */

#ifndef _MOVE_HANDLER_H
#define _MOVE_HANDLER_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../state/state.h"
#include "../cur_state/cur_state"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

/* Desc:
 * Given a chosen state, it determines the move made between current state and that given state
 * Input:1: Derived state
 * Output:1: Move [MOVE]
 */
MOVE determine_move ( STATE );

#endif

