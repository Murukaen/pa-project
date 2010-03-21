/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "../bitmap/bitmap.h"
#include "state_generator.h"
#include "../read_from_file/read_from_file.h"
#include "../state/state.h"
#include "../Flags/flags.h"

/* ---- Macro #define ---- */
#define NR_PIECES 5

/* --- Types --- */

/* --- Globals --- */


/* --- Auxiliary Procedures --- */

/* --- Procedures --- */



STATE state_gen(STATE start_state) {

	UCHAR index = ST_get_move_index(start_state);
	List L = ST_get_move_cur_list(start_state);

	P_LOC loc;

	for(loc = first_nod_list(&))




}

void ST_gen_init(void) {

	Read_all_possible_moves(Moves);
}
