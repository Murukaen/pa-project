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
#include "../san_conv/san_conv.h"
#include "../move_conv/move_conv.h"
#include "../log/log.h"
#include "../Init/init.h"
#include "../cur_state/cur_state.h"

/* ---- Macro #define ---- */
#define COM_SEP ' '
#define LOG_COMMAND_FILE "Log/command.log"
#define LOG_HISTORY_FILE "Log/history.log"

#define FEATURES "feature usermove=1 san=1 sigint=0 done=1\n"

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
	
		/* LOG */
		//log_print ("XBoard>Engine>Line>>" , LOG_COMMAND_FILE);
		log_print ( com , LOG_COMMAND_FILE );
		/* END LOG */
	
				
		int length = strlen(com) + 1;
		char *prop = (char *) malloc ( length * sizeof (char) );
		memcpy( prop , com , length );
		
		char * poz = prop;
		char * word;
		
		word = parse_com ( &poz );
		

		
		/* Analyse command */
				
		if ( !strcmp ( word , "quit" ) ) 		exit(0);
		if ( !strcmp ( word , "xboard" ) ) 		write_to_xboard ("\n");
		if ( !strcmp ( word , "protover" ) ) 	{ Init ( INIT_POSX) ; write_to_xboard (FEATURES); }
		if ( !strcmp ( word , "go" ) ) { 
			
				set_engine_lock (0); // Remove Lock
				if ( !is_engine_on_move() ) flip_state () ;
		}
		if ( !strcmp ( word , "force" ) ) set_engine_lock(1); // Put Lock
		if ( !strcmp ( word , "new" ) ) { set_engine_lock (1) ; Init ( INIT_NEW ) ; }
		
		/* Command is a move */
		if ( !strcmp ( word , "usermove" )) 	{ 
			
			set_engine_lock (0);
			word = parse_com ( &poz );
			
			// Now : word is command in XBoard format
			
			/* LOG */
			
			log_print ("XBoard>Engine>Move" , LOG_COMMAND_FILE );
			log_print ( word , LOG_COMMAND_FILE );
			log_print ("XBoard>Engine>SAN_to_Move" , LOG_COMMAND_FILE);
			log_print_move ( SAN_to_Move ( cur_state_get() , word ) , LOG_COMMAND_FILE );
		
			/* END LOG */
			
			/* LOG History */
			char color_text [10];
			tag_to_text ( not ( get_engine_col () ) , color_text );
			log_print ( color_text , LOG_HISTORY_FILE );
			log_print (word , LOG_HISTORY_FILE );
			/* END LOG History */
			
			update_state ( cur_state_get() , SAN_to_Move ( cur_state_get() , word ) );  
			
		}
		
		/* Free statement */
		free(prop);
		
		/* LOG */
		log_print("END read_com", LOG_COMMAND_FILE );
		/* END LOG */
		
}

void write_com (void * com , int com_tag ) {
	
	char text[30]="move ";
	char text_move[10];
	char color_text [10];
	switch (com_tag) {
		
		case T_COM_MOVE : 	strcpy ( text_move , Move_to_SAN ( (MOVE) com ) );
							/* LOG History */
							tag_to_text ( get_engine_col () , color_text );
							log_print ( color_text , LOG_HISTORY_FILE );
							log_print (text_move , LOG_HISTORY_FILE );
							/* END LOG History */
							strcat(text , text_move );
							strcat(text, "\n");
							write_to_xboard(text); 
							update_state( cur_state_get() , (MOVE) com ) ; 
							break;
		case T_COM_DRAW : write_to_xboard ("offer draw\n"); break;
		case T_COM_RESIGN : write_to_xboard ("resign\n"); break;
	}
}
