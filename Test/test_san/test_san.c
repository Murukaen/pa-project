#include <stdio.h>
#include "../../move/move.h"
#include "../../cur_state/cur_state.h"
#include "../../san_conv/san_conv.h"
#include "../../state/state.h"
#include "../../Flags/flags.h"

#define COM_LENGTH 20

int main ( int argc , char ** argv ) {
	
		if(argc != 3 ) {
				
				printf("Usage %s file.in file.out\n" , argv[0] );
				return 0;
		}
		
		char com[COM_LENGTH];
		
		/* Inits */
		BM_init ();
		flags_init ();
		/* END Inits */
		
		/* Read from file in */
		FILE *fin = fopen (argv[1] , "r");
		fscanf(fin,"%s", com);
		fgetc(fin);	// read the '\n'
		STATE st = state_read ( fin );
		fclose(fin);
		/* END Read from file in */
		
		/* Set */
		
		
		//cur_state_set ( st );
		/* END Set */
		
		FILE *fout = fopen(argv[2] , "w");
		if( st ) state_print(st , fout );
		fclose(fout);
		return 0;
		
		
		
		/* Calculate MOVE */
		//MOVE mov = SAN_to_Move ( com );
		/* END Calculate MOVE */
		
		/* Print MOVE */
		//FILE *fout = fopen(argv[2] , "w");
		//move_print(mov , fout );
		//fclose(fout);
		/* END Print MOVE */
		
		return 0;
}
