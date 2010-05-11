/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../bitmap/bitmap.h"
#include "../update_state/update_state.h"
#include "../state_generator/state_generator.h"
#include "../log/log.h"
#include "../xboard_com/xboard_com.h"
#include "../Flags/flags.h"
#include "init.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void Init ( int loc ) {
	
	switch ( loc ) {
		
		case INIT_PREX : 	flags_init ();
							log_init ();
							xboard_com_init ();
							break;
					
		case INIT_POSX: 	BM_init ();
							ST_gen_init ();
							break;
							
		case INIT_ALL:     	log_init ();
							flags_init ();
							Init ( INIT_POSX );
							break;
							
		case INIT_NEW:      update_state_init ();
							flags_init ();
							break;
							
	}
}
