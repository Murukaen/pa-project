#include <stdio.h>
#include "../../update_state/update_state.h"
#include "../../cur_state/cur_state.h"
#include "../../state/state.h"
#include "../../Flags/flags.h"

#define FILE_OUT_INITIAL_STATE "Test/test_update_state/initial_state.out"

int main ( void ) {
	
		/* Inits */
		BM_init();
		flags_init();
		update_state_init ();
		/* END Inits */
		
		/* Test */
		FILE *fout = fopen (FILE_OUT_INITIAL_STATE , "w");
		state_print ( cur_state_get () , fout );
		fclose(fout);
		/* END Test */
		
		return 0;
}

