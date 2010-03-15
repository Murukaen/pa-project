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
STATE cur_state; // Nu trebuie delarat aci extern, uite cand se fol extern:
/* extern int myGlobalVariable;
This tells the compiler "there's a variable defined in another module called
myGlobalVariable, of type integer. I want you to accept my attempts to access it,
but don't allocate storage for it because another module has already done that".
*/

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

#endif

