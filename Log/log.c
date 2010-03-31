/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdio.h>

/* ----- Local #inlcudes ----- */
#include "log.h"
#include "../Util/util.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void log_init ( void ) {
	
	util_init(); // INIT FOR LOG_PRINT PROCEDURES
	
	FILE * fout;
	
	fout = fopen ("Log/xboard_com.log" , "w");
	fclose(fout);
	
	fout = fopen ("Log/engine.log" , "w");
	fclose(fout);
	
	fout = fopen ("Log/command.log" , "w");
	fclose(fout);
}

void log_print ( char * text , FILE * fout ) {
	
	fprintf(fout,"Time:%u:%s\n" , get_time (DEFAULT_PRECISION) , text );
	fflush(fout);
}

void log_print_state ( STATE st , FILE * fout ) {
	
	fprintf(fout,"Time:%u\n" , get_time ( DEFAULT_PRECISION) );
	state_print ( st , fout );
	fflush(fout);
}

void log_print_move ( MOVE mov , FILE * fout ) {
	
	fprintf(fout,"Time:%u\n" , get_time ( DEFAULT_PRECISION) );
	move_print ( mov , fout );
	fflush(fout);
}

	

