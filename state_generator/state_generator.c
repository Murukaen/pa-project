/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../bitmap/bitmap.h"
#include "state_generator.h"
#include "../read_from_file/read_from_file.h"
#include "../state/state.h"

/* ---- Macro #define ---- */
#define fin "../Database/All_moves.in"

/* --- Types --- */

/* --- Globals --- */
typedef BITMAP Moves[5][8][8];

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

STATE state_gen ( STATE start_state ) {
	

}

void ST_gen_init(void){


	Read_all_possible_moves(fin,**Moves[0],**Moves[1],**Moves[2],**Moves[3],**Moves[4])
}
