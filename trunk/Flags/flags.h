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
UCHAR get_engine_col ( void );

void set_engine_col ( UCHAR );

UCHAR get_init_com ( void );

void set_init_com ( UCHAR );

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

