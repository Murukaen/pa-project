/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "move.h"

/* ---- Macro #define ---- */

/* --- Types --- */
struct loc {
	
	int row, col;
};

struct s_move {
	
	int tag; // piece type ( see "state.h" for mapping )
	loc poz_src , poz_dst; // source and destination positions represented as coordinates
	
};



/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */
