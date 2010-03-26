/* General description :
 * 
 */

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
STATE cur_state_get ( void );

/* Desc:
 * Sets the cuurent state
 * Input:1: state_to_set
 * Output:0 
 */
void cur_state_set ( STATE );

/* Desc:
 * Destructor Current State ( removes all data from the state )
 * Input:0
 * Output:0
 */
void cur_state_free ( void );

#endif

