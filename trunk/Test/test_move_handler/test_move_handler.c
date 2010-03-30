#include <stdio.h>
#include "../../move_handler/move_handler.h"
#include "../../state/state.h"
#include "../../bitmap/bitmap.h"
#include "../../Flags/flags.h"
#include "../../cur_state/cur_state.h"



int main ( int argc , char ** argv ) {
	
	if(argc != 3 ) {		
		
		printf("Usage %s file.in file.out\n" , argv[0] );
		return 0;
	}
	
	/* Inits */
	BM_init();
	flags_init();
	/* END Inits */
	
	/* Read input */
	FILE * fin = fopen ( argv[1] , "r");
	STATE p_st = state_read ( fin );
	STATE n_st = state_read ( fin );
	fclose(fin);
	/* END Read Input */
	
	/* Sets */
	cur_state_set ( p_st );
	/* END Sets */
	
	/* Output */
	FILE * fout = fopen ( argv[2] , "w" );
	move_print ( determine_move ( n_st ) , fout );
	fclose(fout);
	/* END Output */
	
	
	return 0;
}
	 
	
	

