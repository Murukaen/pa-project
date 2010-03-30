#include <stdio.h>
#include "../../update_state/update_state.h"
#include "../../cur_state/cur_state.h"
#include "../../state/state.h"
#include "../../Flags/flags.h"
#include "../../move/move.h"
#include "../../state/state.h"


int main ( int argc , char ** argv  ) {
	
		if(argc != 3 ) {
				
				printf("Usage %s file.in file.out\n" , argv[0] );
				return 0;
		}
	
		/* Inits */
		BM_init();
		flags_init();
		/* END Inits */
		
		/* Vars */
		STATE st;
		MOVE mov;
		/* END Vars */
		
		/* Read */
		FILE *fin = fopen ( argv[1] , "r" );
		mov = move_read ( fin );
		st = state_read ( fin );
		fclose(fin);
		/* END Read */
		
		cur_state_set ( st );
		update_state ( mov );
		
		/* Output */
		FILE *fout = fopen (argv[2] , "w");
		//move_print ( mov , fout );  VERIFY ONLY
		//state_print ( st , fout );  VERIFY ONLY
		state_print ( cur_state_get () , fout );
		fclose(fout);
		/* END Output */
		
		return 0;
}
