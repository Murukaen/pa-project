/* General description :
 * 
 */

#ifndef _EVALUATION_H
#define _EVALUATION_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */

#include "../state/state.h"

/* ---- Macro #define ---- */

#define MAX_EVAL 100
#define MIN_EVAL (-MAX_EVAL)
#define EQU_EVAL 0

/* --- Types --- */

/* --- Procedures --- */

void eval_init ( void );

int evaluate ( STATE st );

#endif

