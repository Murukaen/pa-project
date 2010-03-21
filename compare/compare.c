/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "compare.h"
#include "../Util/util.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

int fequ_loc ( void * key1 , void * key2) {
	
	P_LOC loc1 = ( P_LOC ) key1;
	P_LOC loc2 = ( P_LOC ) key2;
	
	if ( (LOC_get_row ( loc1 ) == LOC_get_row ( loc2 )) && ( LOC_get_col ( loc2 ) == LOC_get_col ( loc2 ) ) )
			
			return 1;
	
	return 0;
}
