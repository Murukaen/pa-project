/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
/* ----- Local #inlcudes ----- */
#include "command.h"

/* ---- Macro #define ---- */
#define LOG_FILE "./Log/log"
#define COM_SEP ' '
#define WORD_LENGTH 15

#define FEATURES "feature playother=1 usermove=1 done=1\n"

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */
/* Desc:
 * Extrage elementele unei comenzi ( separate prin spatii albe )
 * Input:1: adresa catre pozitia curenta de unde se citeste ( pozitia se deplaseaza spre dreapta ) [char **]
 * Output:1: cuvant din cadrul comenzii [char *]
 * Use:
 * char * poz = statement;//[char *]
 * while ( (cuv = parse_com ( &poz ) ) != 0 ) action(cuv); 			
 */
 			
char * parse_com ( char ** com ) {
	
		if ( *com == 0 ) return 0;
		
		while ( ** com == ' ' && **com ) (*com)++;
		if ( **com == 0 ) return 0;
			  	
		char *end = strchr ( *com , COM_SEP );
		char *aux = *com;
		if ( end == 0 ) {	
				*com = 0;
				
		}
		
		else {			
		
			*end = 0;
			*com = end + 1;
		}
			
		return aux;
}

/* --- Procedures --- */



void read_com ( char * com ) {
	
				
		int length = strlen(com) + 1;
		char *prop = (char *) malloc ( length * sizeof (char) );
		memcpy( prop , com , length );
		
		char * poz = prop;
		char * word;
		
		word = parse_com ( &poz );
		
		FILE * fout = fopen (LOG_FILE , "a");
		fprintf(fout , "*%s*\n" , word );
		fflush(fout);
		fclose(fout);
				
		if ( !strcmp ( word , "quit" ) ) exit(0);
		if ( !strcmp ( word , "xboard" ) ) write(1, "\n" , strlen("\n") );
		if ( !strcmp ( word , "protover" ) ) write (1, FEATURES , strlen (FEATURES) );
		
		
		
		if( !strcmp ( word , "e2e4" ) )  {
			
				FILE * fout = fopen (LOG_FILE , "a");
				fprintf(fout , ">%s<\n" , "move e7e5" );
				fclose(fout);
				write(1, "move e7e5\n" , strlen("move e7e5\n") );
				
		}
		
		if( !strcmp ( word , "d2d3" ) )  {
			
				FILE * fout = fopen (LOG_FILE , "a");
				fprintf(fout , ">%s<\n" , "move d7d6" );
				fclose(fout);	
				write(1, "move d7d6\n" , strlen("move d7d6\n") );
				
		}
		
		free(prop);
		
		
}
