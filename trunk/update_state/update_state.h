/* General description :
 * 
 */

#ifndef _UPDATE_STATE_H
#define _UPDATE_STATE_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../move/move.h"
#include "../Flags/flags.h"
#include "../state/state.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

/* Desc:
 * Initialize starting state of the game
 * Input:0
 * Output:0
 */
void update_state_init(void);

/* Desc :
 * Updates the current state based on the old one and the last move
 * Input:1: move
 * Output:0
 */
void update_state(STATE, MOVE);

/* schimba pozitia initiala a pieselor(rege-regina) - pt alb sau pt negru*/
void flip_state(void);
#endif

