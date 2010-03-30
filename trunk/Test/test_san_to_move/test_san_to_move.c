#include <stdio.h>
#include <time.h>
#include "../../move/move.h"
#include "../../cur_state/cur_state.h"
#include "../../san_conv/san_conv.h"
#include "../../state/state.h"
#include "../../Flags/flags.h"
#include "../../state_generator/state_generator.h"
#include "../../read_from_file/read_from_file.h"

#define COM_LENGTH 20

////////////////////////////////
//////// Notes
/*
 * 1) X in the output means that the row / column is out of range
 */
////////////////////////////////

int main ( int argc , char ** argv ) {
	
		if(argc != 3 ) {
				
				printf("Usage %s file.in file.out\n" , argv[0] );
				return 0;
		}
		
		char com[COM_LENGTH];
		
		/* Inits */
		BM_init ();
		flags_init ();
		ST_gen_init ();
		/* END Inits */
		
		/* Read from file in */
		FILE *fin = fopen (argv[1] , "r");
		fscanf(fin,"%s", com);
		fgetc(fin);	// read the '\n'
		STATE st = state_read ( fin );
		fclose(fin);
		/* END Read from file in */
	
		/* Set Current State*/
		cur_state_set ( st );
		/* END Set Current State*/
			
		/* Calculate MOVE */
		MOVE mov = SAN_to_Move ( com );
		/* END Calculate MOVE */
		
		/* Print MOVE */
		FILE *fout = fopen(argv[2] , "w");
		if(mov != 0 ) move_print(mov , fout );
		fclose(fout);
		/* END Print MOVE */
		
		return 0;
}
