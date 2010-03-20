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

void flip_state(void){

	STATE S;
	S = cur_state_get();
	ST_set_bitmap(S,2,1152921504606846992LL);
	ST_set_bitmap(S,3,576460752303423496LL);

	// TODO flip table_p
}



