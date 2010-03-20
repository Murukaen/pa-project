/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "command.h"
#include "../update_state/update_state.h"
#include "../move_conv/move_conv.h"

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
		
		/* Analyse command */
				
		if ( !strcmp ( word , "quit" ) ) 		exit(0);
		if ( !strcmp ( word , "xboard" ) ) 		write_to_xboard ("\n");
		if ( !strcmp ( word , "protover" ) ) 	write_to_xboard (FEATURES);
		if ( !strcmp ( word , "usermove" )) 	{
			
			word = parse_com ( &poz );
			
			// Now : word is command in XBoard format
			
			update_state ( Xmove_to_intern ( word ) );  
			
			}
		
		/* Free statement */
		free(prop);
		
		
}

void write_com (void * com , int com_tag ) {
	
	switch (com_tag) {
		
		case T_COM_MOVE : write_to_xboard ( intern_to_Xmove ( (MOVE) com ) ); update_state( (MOVE) com ) ; break;
		case T_COM_DRAW : write_to_xboard ("offer draw\n"); break;
		case T_COM_RESIGN : write_to_xboard ("resign\n"); break;
	}
}
