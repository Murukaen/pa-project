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
	FILE * fout = fopen ( argv[2] , "w" );
	STATE p_st = state_read ( fin );
	//state_print(p_st,fout);
	
	STATE n_st = state_read ( fin );
	//state_print(n_st,fout);
	fclose(fin);
	/* END Read Input */
	
	/* Sets */
	cur_state_set ( p_st );
	/* END Sets */
	
	/* Output */
	
	move_print ( determine_move ( n_st ) , fout );
	fclose(fout);
	cur_state_free();
	/* END Output */
	
	
	return 0;
}
	 
	
	

