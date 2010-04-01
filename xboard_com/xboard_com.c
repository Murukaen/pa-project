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
#include "../Log/log.h"

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
	FILE * fout = fopen (LOG_XBOARD_COM_FILE , "a");
	log_print ( "WAIT Input" , fout );
	fflush(fout);
	fclose(fout);
	/* END LOG */
	
	int poz = 0;
	fflush(stdin);
	while ( scanf( "%c" , &read_buffer [poz ] ) && read_buffer [poz] != '\n' ) {
			
				/* LOG */
				FILE * fout = fopen (LOG_XBOARD_COM_FILE , "a");
				log_print_character ( read_buffer[poz] , fout );
				fflush(fout);
				fclose(fout);
				/* END LOG */
				poz ++;
	}
	read_buffer [poz+1] = '\0';
	//int length = read(STDIN,read_buffer,BUF_LENGTH-1);
	//read_buffer[length] = '\0';
	//gets ( read_buffer );
	
	/* LOG */
	fout = fopen (LOG_XBOARD_COM_FILE , "a");
	log_print ( "RECEIVED Input" , fout );
	fflush(fout);
	fclose(fout);
	/* END LOG */

	return read_buffer;
}

void parse_buf ( char * buf ) {
	
		/* LOG */
		FILE * fout = fopen (LOG_XBOARD_COM_FILE , "a");
		log_print ( "XBoard>Engine>Buffer>>" , fout );
		log_print ( buf , fout );
		fclose(fout);
		/* END LOG */
	
		char *com;
		for(com = strtok(buf , BUF_SEP); com ; com = strtok(0 , BUF_SEP) ) 
				
					read_com ( com );
		
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
		FILE * fout = fopen (LOG_XBOARD_COM_FILE , "a");
		log_print ( "Engine>XBoard>>>" , fout );
		log_print ( text , fout );
		fclose(fout);
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
			FILE * fout = fopen (LOG_XBOARD_COM_FILE , "a");
			log_print ( "Engine>XBoard>BUF>>" , fout );
			log_print ( mem_buffer , fout );
			fclose(fout);
			/* END LOG */
			write_to_xboard ( mem_buffer ); // flush xboard_com buffer to XBoard
			empty_mem_buf () ; // empty the memory buffer
		}
		
	
		parse_buf ( get_input_buffer () );  // wait and get all the available input
}

void poll_output ( void * com , int com_tag) {
	
		write_com ( com , com_tag ); // send the command to the Command Unit
}




			


	
		
	
		


