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
		
		cur_state_set ( Read_initial_state () );
}

void update_state ( MOVE mov ) {
	
		// TODO	
		
		
}



