/* Main Module
 * The engine
 */

/* ----- System #includes ----- */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

/* ----- Local #inlcudes ----- */

#include "../xboard_com/xboard_com.h"

/* ---- Macro #define ---- */
#define LOG_FILE "./Log/log"



int count;



int main ( void ) {

	signal(SIGINT, SIG_IGN);

	/* Define variables */
	
	
	 /*Input listener with no stop */
	com_init();
	while ( 1 ) {
		sleep(3);
		FILE* fout = fopen ( LOG_FILE , "a" );
		fprintf (fout , "<%d>\n" , count++);
		fflush ( fout );
		fclose(fout);
		
				
		poll_input();
	}




	

	return 0;
}

