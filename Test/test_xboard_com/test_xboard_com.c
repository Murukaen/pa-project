/* Main Module
 * The engine
 */

/* ----- System #includes ----- */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

/* ----- Local #inlcudes ----- */
#include "../../xboard_com/xboard_com.h"
#include "../../Flags/flags.h"
#include "../../Log/log.h"

/* ---- Macro #define ---- */
#define LOG_FILE "Log/engine.log"

int count;

int main ( void ) {
	
	/* COM Inits */
	log_init ();
	xboard_com_init ();
	flags_init ();
	/* END COM Inits */
	
	/* Initial Communication */
	while ( !f_INIT_COM ) { // while initial communication not done
	
		poll_input ();
	}
	/* END Initial Communication */
	
	
	/* All Inits */
	sleep(10);
	FILE* fout = fopen ( LOG_FILE , "a" );
	log_print ( "INITS" , fout );
	fclose(fout);
	/* END All Inits */
	
	/* Define variables */
	
	while ( 1 ) {
		
		/* SEQ RUNNING */
		FILE* fout = fopen ( LOG_FILE , "a" );
		fprintf (fout , "<%d>\n" , count++);
		fflush ( fout );
		fclose(fout);
		/* END SEQ Running */
		
		/* Poll input */
		poll_input();
		/* END Poll Input */
	}
	
	return 0;
}


