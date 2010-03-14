/* General description :
 * 
 */

// !!! Remove this : NAME = Name of file
#ifndef _CUR_STATE_H
#define _CUR_STATE_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../state/state.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

/* Desc:
 * Gets the cuurent state
 * Input:0
 * Output: cur_state
 */
state cur_state_get ( void );

/* Desc:
 * Sets the cuurent state
 * Input:1: state_to_set
 * Output:0 
 */
void cur_state_set ( state ); 

#endif

