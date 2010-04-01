/* Main Module
 * The engine , The Shit, The Chuck, 
 */

/* ----- System #includes ----- */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
#include "../state_generator/state_generator.h"
#include "../update_state/update_state.h"

/* ---- Macro #define ---- */
#define LOG_ENGINE_FILE "Log/engine.log"

int count_main_cycles;

int main ( void ) {
	
	/* COM Inits */
	Init(INIT_PREX);
	/* END COM Inits */
	
	/* Initial Communication */
	while ( !get_init_com ()  ) { // while initial communication not done
	
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

		
		/* LOG Print Cycle Number*/
		log_print_cycle ( count_main_cycles , LOG_ENGINE_FILE );
		count_main_cycles ++;	
		/* END LOG */
		
		
		/* Poll input */
		poll_input();
		/* END Poll Input */
		
		/* IF Engine is on move : Make a move */
		if ( is_engine_on_move () ) {
			
			/* LOG */	
			log_print ("Engine on move:\n" , LOG_ENGINE_FILE);
			/* END LOG */

			chosen_state = decide ();
			
				/* LOG */	
				log_print ("Chosen State:\n" , LOG_ENGINE_FILE);
				log_print_state_Table_What ( chosen_state , LOG_ENGINE_FILE );
				/* END LOG */
			
			
			if ( chosen_state != NULL ) { // if there is a valid chosen_state
				
				
				chosen_move = determine_move ( chosen_state );
				
				/* LOG */	
				log_print ("Determine move:\n" , LOG_ENGINE_FILE);
				log_print_move ( chosen_move , LOG_ENGINE_FILE );
				/* END LOG */
	
				poll_output ( (void *) chosen_move , T_COM_MOVE );
				
			}
			
			else {   // cannot make move
			
				/* LOG Resign ( No more moves to make )*/
				log_print ("Resign" , LOG_ENGINE_FILE);
				/* END LOG */
				
				poll_output ( NULL , T_COM_RESIGN );
				sleep(2);
				

			
				
				exit(0);
			}
		}
		
	}
	
	return 0;
}


