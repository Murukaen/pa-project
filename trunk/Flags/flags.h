/* General description :
 * Global Control Flags
 * Facilitates communication between modules
 * Store values describing various states of the game
 */

#ifndef _FLAGS_H
#define _FLAGS_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../Util/util.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Flags --- */

/* Description : Engine color
 *0 - white
 *1 - black
 */
UCHAR f_ENG_COL;

UCHAR f_INIT_COM;

/* --- Procedures --- */

/* Desc:
 * Flags init
 * 1.Engine plays black
 * 2.Init communication = 0 ( not done )
 * Input:0
 * Output:0
 */
void flags_init ( void );

#endif

