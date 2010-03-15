/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "update_state.h"
#include "../read_from_file/read_from_file.h"
#include "../cur_state/cur_state.h"
#include "../state/state.h"
#include "../Flags/flags.h"

/* ---- Macro #define ---- */

#define DATABASE_STARTING_POS "Database/Initial_positions"

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void update_state_init ( void ) {
	
		STATE initial_state = ST_new ();
		
		//TODO : Read_initial_state (DATABASE_STARTING_POS , &(initial_state[0]) , &(initial_state[1]) , &(initial_state[2]) , &(initial_state[3]) , &(initial_state[4]) , &(initial_state[5]) , &(initial_state[6]) , &(initial_state[7]) );
		
		cur_state_set (initial_state);
}

void update_state ( MOVE mov ) {
	
		// TODO	
		
		
}



