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

void log_print ( char * , char * );

void log_print_state ( STATE , char *);

void log_print_move ( MOVE , char * );

void log_print_state_Table_What ( STATE , char * );

void log_print_cycle ( int , char *);

void log_print_integer ( int , char *);

void log_print_character ( char , char *);

#endif

