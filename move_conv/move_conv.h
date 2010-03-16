/* General description :
 * Conversion between engine internal move standard and XBoard mve standard
 */

#ifndef _MOVE_CONV_H
#define _MOVE_CONV_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../move/move.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

/* Desc:
 * Converts XBoard internal move format to engine internal move format
 * Input:1: command string in XBoard format ( without \n , just the command as characters )
 * Output:1: internal move format ( pointer ) [MOVE]
 */
MOVE Xmove_to_intern ( char * );

/* Desc:
 * Converts engine internal move standard to Xboard internal move standard
 * Input:1: internal move format ( pointer ) [MOVE]
 * Output:1: command string in XBoard format ( without \n , just the command as characters )
 */
char * intern_to_Xmove ( MOVE );

#endif

