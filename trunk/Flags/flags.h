/* General description :
 * Global Control Flags
 * Facilitates communication between modules
 * Store values describing various states of the game
 */

#ifndef _FLAGS_H
#define _FLAGS_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Flags --- */

/*Description : Determines whether or not the engine is on move
 *0 - not on move
 *1 - on move
 */
int f_ENG_ON_MOVE;

/* Description : Engine color
 *0 - white
 *1 - black
 */
int f_ENG_COL;

/* --- Procedures --- */

/* Desc:
 * Flags init
 * 1.Engine not on move
 * 2.Engine plays black
 * Input:0
 * Output:0
 */
void flags_init ();


#endif

