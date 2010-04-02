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

int logs_on;

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void log_init ( void ) {
	
	logs_on = 1;
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
	
	fout = fopen ("Log/history.log" , "w");
	fclose(fout);
	
	fout = fopen ("Log/san_conv.log" , "w");
	fclose(fout);
	
	fout = fopen ("Log/current_state.log" , "w");
	fclose(fout);
	
	fout = fopen ("Log/move_handler.log" , "w");
	fclose(fout);
}

void log_print ( char * text , char * FILE_NAME ) {
	
	if ( logs_on ){
		FILE * fout = fopen ( FILE_NAME , "a");
		fprintf(fout,"Time:%u:%s\n" , get_time (DEFAULT_PRECISION) , text );
		fflush(fout);
		fclose ( fout );
	}
}

void log_print_state ( STATE st , char * FILE_NAME , UCHAR tag_write) {
	
	if ( logs_on ) {
		FILE * fout;
	
		switch ( tag_write ) {
		
			case WRITE_TAG_ADD : fout = fopen ( FILE_NAME , "a"); break;
		
			case WRITE_TAG_OVER : fout = fopen ( FILE_NAME , "w" ); break;
		}
	
		fprintf(fout,"Time:%u\n" , get_time ( DEFAULT_PRECISION) );
		state_print ( st , fout );
		fflush(fout);
		fclose ( fout );
	}
}

void log_print_move ( MOVE mov , char * FILE_NAME ) {
	
	if (logs_on) {
		
		FILE * fout = fopen ( FILE_NAME , "a");
		fprintf(fout,"Time:%u\n" , get_time ( DEFAULT_PRECISION) );
		move_print ( mov , fout );
		fflush(fout);
		fclose( fout );
	}
}

void log_print_state_Table_What ( STATE st , char * FILE_NAME ) {
	
	if ( logs_on ) {
		
		FILE * fout = fopen ( FILE_NAME , "a");
		int i, j;
	
		fprintf(fout,"Time:%u\n" , get_time ( DEFAULT_PRECISION) );
		fprintf(fout, "\n~~~Table_What~~~:\n\n");
		if ( st ) {
			/* Print Table_What */
			for(i=0;i<SIZE_BMAP;++i, fprintf(fout, "\n") )
				for(j=0;j<SIZE_BMAP;++j, fprintf(fout, " ") )
					fprintf(fout, "%c" , tag_to_letter ( ST_get_tag_Table_What ( st ,  BM_row(i,j) , BM_col(i,j) ) ));
			/* END Print Table_What */
		}
		else fprintf(fout, "\n Void State \n" );
		fflush(fout);
		fclose(fout);
	}
}

void log_print_cycle ( int nr , char * FILE_NAME ) {
	
	if ( logs_on ) {
		
		FILE * fout = fopen ( FILE_NAME , "a");
		fprintf(fout,"Time:%u:Cycle - %d - \n" , get_time ( DEFAULT_PRECISION) , nr);
		fflush(fout);
		fclose(fout);
	}
}

void log_print_integer ( int nr , char * FILE_NAME) {
	
	if ( logs_on ) {
		
		FILE * fout = fopen ( FILE_NAME , "a");
		fprintf(fout,"Time:%u:Value: %d\n" , get_time ( DEFAULT_PRECISION) , nr);
		fflush(fout);
		fclose(fout);
	}
}

void log_print_character ( char c, char * FILE_NAME ) {
	
	if ( logs_on ) {
		
		FILE * fout = fopen ( FILE_NAME , "a");
		fprintf(fout,"Time:%u:Char:|%c|\n" , get_time ( DEFAULT_PRECISION) , c);
		fflush(fout);
		fclose(fout);
	}
}

void log_print_bitmap ( BITMAP b , char * FILE_NAME ) {
	
	if ( logs_on ) {
		
		FILE * fout = fopen ( FILE_NAME , "a");
		fprintf(fout,"Time:%u:\n" , get_time ( DEFAULT_PRECISION) );
		BM_print ( b , fout );
		fflush(fout);
		fclose(fout);
	}
}
	

