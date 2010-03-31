/* General description :
 * 
 */

#ifndef _LOG_H
#define _LOG_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../state/state.h"
#include "../move/move.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

void log_init ( void );

void log_print ( char * , FILE * );

void log_print_state ( STATE , FILE *);

void log_print_move ( MOVE , FILE * );

#endif

