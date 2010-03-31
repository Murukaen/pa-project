/* Main Module
 * The engine , The Shit, The Chuck, 
 */

/* ----- System #includes ----- */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

/* ----- Local #inlcudes ----- */
#include "../Init/init.h"
#include "../xboard_com/xboard_com.h"
#include "../Flags/flags.h"
#include "../Log/log.h"
#include "../bitmap/bitmap.h"
#include "../state/state.h"
#include "../move/move.h"
#include "../decision/decision.h"
#include "../cur_state/cur_state.h"
#include "../move_handler/move_handler.h"

/* ---- Macro #define ---- */
#define LOG_ENGINE_FILE "Log/engine.log"

int main ( void ) {
	
	/* COM Inits */
	Init(INIT_PREX);
	/* END COM Inits */
	
	/* Initial Communication */
	while ( !f_INIT_COM ) { // while initial communication not done
	
		poll_input ();
	}
	/* END Initial Communication */
	
	
	/* All Inits */
	Init(INIT_POSX);
	/* END All Inits */
	
	/* Variables */
	STATE chosen_state;
	MOVE chosen_move;
	/* END Variables */
	
	
	while ( 1 ) {
		
		/* Poll input */
		poll_input();
		/* END Poll Input */
		
		/* IF Engine is on move : Make a move */
		/* 
		if ( is_engine_on_move () ) {
			

			chosen_state = decide ();
			
			if ( chosen_state != NULL ) { // if there is a valid chosen_state
				
				chosen_move = determine_move ( chosen_state );
				poll_output ( (void *) chosen_move , T_COM_MOVE );
			}
			
			else {   // cannot make move
				
				poll_output ( NULL , T_COM_RESIGN );
				sleep(2);
				
			
				
				exit(0);
			}
		}
		*/
	}
	
	return 0;
}


