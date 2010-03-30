#include "../../move/move.h"
#include "../../bitmap/bitmap.h"
#include "../../Flags/flags.h"
#include "../../state/state.h"
#include "../../san_conv/san_conv.h"
#include "../../state_generator/state_generator.h"
#include <stdio.h>


int main ( int argc , char ** argv ) {
	
	if(argc != 3 ) {		
		
		printf("Usage %s file.in file.out\n" , argv[0] );
		return 0;
	}
	
	/* Vars */
	MOVE mov;
	STATE st;
	/* END Vars*/
	
	/* Inits */
	BM_init();
	flags_init ();
	ST_gen_init ();
	/* END Inits */
	
	/* Read */
	FILE * fin = fopen ( argv[1] , "r" );
	mov = move_read ( fin );
	st = state_read ( fin );
	fclose(fin);
	/* END Read */
	
	cur_state_set ( st );
	
	/* Output */
	FILE * fout = fopen ( argv[2] , "w" );
	//move_print ( mov , fout );   VERIFY ONLY
	//state_print ( st , fout );   VERIFY ONLY
	fprintf(fout , "SAN:%s\n" , Move_to_SAN ( mov ) ); 
	fclose(fout);
	/* END Output */
	
	return 0;
}
