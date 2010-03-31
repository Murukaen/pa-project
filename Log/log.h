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

void log_print_state_Table_What ( STATE , FILE * );

void log_print_cycle ( int , FILE *);

void log_print_integer ( int , FILE *);

#endif

