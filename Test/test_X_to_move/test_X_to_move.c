#include <stdio.h>
#include <time.h>
#include "../../move/move.h"
#include "../../cur_state/cur_state.h"
#include "../../move_conv/move_conv.h"
#include "../../state/state.h"
#include "../../Flags/flags.h"
#include "../../state_generator/state_generator.h"
#include "../../read_from_file/read_from_file.h"
#include "../../Init/init.h"

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
		Init(INIT_ALL);
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
		MOVE mov = 0;
		mov = Xmove_to_intern ( com );
		/* END Calculate MOVE */
		
		/* Print MOVE */
		FILE *fout = fopen(argv[2] , "w");
		if(mov != 0 ) move_print(mov , fout );
		fclose(fout);
		/* END Print MOVE */
		
		return 0;
}

