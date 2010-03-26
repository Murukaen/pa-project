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
		
		/* Read from file in */
		FILE *fin = fopen (argv[1] , "r");
		fscanf(fin,"%s", com);
		fgetc(fin);	
		STATE st = state_read ( fin );
		fclose(fin);
		/* END Read from file in */
		
		FILE *fout = fopen(argv[2] , "w");
		state_print(st , fout );
		fclose(fout);
		return 0;
		
		/* Inits */
		flags_init ();
		//cur_state_set ( st );
		/* END Inits */
		
		/* Calculate MOVE */
		MOVE mov = SAN_to_Move ( com );
		/* END Calculate MOVE */
		
		/* Print MOVE */
		FILE *fout = fopen(argv[2] , "w");
		move_print(mov , fout );
		fclose(fout);
		/* END Print MOVE */
		
		return 0;
}
