/* General description :
 * 
 */

#ifndef _STATE_GENERATOR_H
#define _STATE_GENERATOR_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../state/state.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

/* Desc:
 * Generates the next possible state that could derive from the given state after a move
 * The procedure uses a flag to determine what player is on move
 * Input:1:first_state [state]
 * Output:1: derived_state [state]
 */

STATE ST_gen(STATE);

void ST_gen_init(void);

#endif

