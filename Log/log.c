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
	
	fout = fopen ("Log/state_generator.log" , "w");
	fclose(fout);
	
	fout = fopen ("Log/update_state.log" , "w");
	fclose(fout);
	
	fout = fopen ("Log/move_handler.log" , "w");
	fclose(fout);
	
	fout = fopen ("Log/validate_move.log" , "w");
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

void log_print_state_Table_What ( STATE st , FILE * fout ) {
	
	int i, j;
	
	fprintf(fout,"Time:%u\n" , get_time ( DEFAULT_PRECISION) );
	/* Print Table_What */
	fprintf(fout, "\n~~~Table_What~~~:\n\n");
	for(i=0;i<SIZE_BMAP;++i, fprintf(fout, "\n") )
		for(j=0;j<SIZE_BMAP;++j, fprintf(fout, " ") )
			fprintf(fout, "%c" , tag_to_letter ( ST_get_tag_Table_What ( st ,  BM_row(i,j) , BM_col(i,j) ) ));
	/* END Print Table_What */
	fflush(fout);
}

void log_print_cycle ( int nr , FILE * fout ) {
	
	fprintf(fout,"Time:%u:Cycle - %d - \n" , get_time ( DEFAULT_PRECISION) , nr);
	fflush(fout);
}

void log_print_integer ( int nr , FILE * fout) {
	
	fprintf(fout,"Time:%u:Value: %d\n" , get_time ( DEFAULT_PRECISION) , nr);
	fflush(fout);
}

void log_print_character ( char c, FILE *fout) {
	
	fprintf(fout,"Time:%u:Char:|%c|\n" , get_time ( DEFAULT_PRECISION) , c);
	fflush(fout);
}
	

