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

	f_ENG_COL = ~ f_ENG_COL; // flips the flag

}



