/*
 * 	XBoard Command handler
 */

/* ----- System #includes ----- */
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "xboard_com.h"
#include "../command/command.h"
#include "../log/log.h"
#include "../Flags/flags.h"

/* ---- Macro #define ---- */
#define STDIN 0
#define BUF_LENGTH 200
#define BUF_SEP "\n"

#define INIT_FEATURES "feature done=0\n"

/* --- Types --- */

/* --- Globals --- */

char read_buffer[BUF_LENGTH];
char mem_buffer [BUF_LENGTH];

/* --- Auxiliary Procedures --- */

char * get_input_buffer ( void ) {
	
	/* LOG */
	log_print ( "WAIT Input" , LOG_XBOARD_COM_FILE );
	/* END LOG */
	
	//int length = read(STDIN,read_buffer,BUF_LENGTH-1);
	//read_buffer[length] = '\0';
	
	/* TEMP !!! */
	fgets ( read_buffer , BUF_LENGTH - 1 , stdin );

	
	/* LOG */
	log_print ( "RECEIVED Input:" , LOG_XBOARD_COM_FILE );
	log_print ( read_buffer , LOG_XBOARD_COM_FILE);
	/* END LOG */

	return read_buffer;
}

void parse_buf ( char * buf ) {
	
		/*
		char *com;
		for(com = strtok(buf , BUF_SEP); com ; com = strtok(0 , BUF_SEP) ) 
				
					read_com ( com );
		*/
		buf[strlen(buf)-1]=0;
		read_com(buf);
		
}	

int is_empty_mem_buf ( void ) {
	
	return ( mem_buffer [0] == 0 );
}	

void empty_mem_buf ( void ) {
	
	mem_buffer[0] = '\0';
}

/* --- Procedures --- */

void write_to_xboard ( char * text) {
	
		/* LOG */
		log_print ( "Engine>XBoard>Line>" , LOG_XBOARD_COM_FILE );
		log_print ( text , LOG_XBOARD_COM_FILE );
		/* END LOG */
		
		write(1,text,strlen(text));
}

void xboard_com_init ( void ) {
	
		setbuf(stdin, NULL);
		empty_mem_buf ();
		write_to_xboard (INIT_FEATURES);  
}

void add_mess_to_buffer ( char * mess ) {
	
		memcpy ( mem_buffer , mess , strlen(mess) + 1);
}


void poll_input ( void ) { 
		
		if ( !is_empty_mem_buf () ) { // if there is a message stored in buffer, output it right away
				
			/* LOG */
			log_print ( "Engine>XBoard>BUF>" , LOG_XBOARD_COM_FILE );
			/* END LOG */
			
			write_to_xboard ( mem_buffer ); // flush xboard_com buffer to XBoard
			empty_mem_buf () ; // empty the memory buffer
		}
		
	
		parse_buf ( get_input_buffer () );  // wait and get all the available input
		
		/* LOG */
		log_print ("END poll_input" , LOG_XBOARD_COM_FILE );
		/* END Log */
}

void poll_output ( void * com , int com_tag) {
	
		write_com ( com , com_tag ); // send the command to the Command Unit
}




			


	
		
	
		


