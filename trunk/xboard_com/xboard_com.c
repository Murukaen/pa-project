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

/* ---- Macro #define ---- */
#define STDIN 0
#define BUF_LENGTH 100 
#define BUF_SEP "\n"

#define LOG_FILE "./Log/log"

#define INIT_FEATURES "feature done=0\n"

/* --- Types --- */

/* --- Globals --- */

char buffer[BUF_LENGTH];

/* --- Auxiliary Procedures --- */

char * get_input_buffer ( void ) {
	
	int length = read(STDIN,buffer,BUF_LENGTH-1);
	buffer[length] = '\0';

	return buffer;
}

void parse_buf ( char * buf ) {
	
		char *com;
		for(com = strtok(buf , BUF_SEP); com ; com = strtok(0 , BUF_SEP) ) 
				
					read_com ( com );
		
}		

/* --- Procedures --- */

void com_init ( void ) {
	
		write(1,INIT_FEATURES,strlen(INIT_FEATURES));
}


void poll_input ( void ) {
	
		struct timeval tv;
		fd_set readfds;

		tv.tv_sec = 0;
		tv.tv_usec = 0;
		
		FD_ZERO(&readfds);
		FD_SET(STDIN, &readfds);
		
		select(STDIN+1, &readfds, NULL, NULL, &tv);
		
		if (FD_ISSET(STDIN, &readfds))  
		
				parse_buf ( get_input_buffer () );
}

void poll_output ( void * com , int com_tag) {
	
		write_com ( com , com_tag );
}

void write_to_xboard ( char * text) {
	
		write(1,text,strlen(text));
}


			


	
		
	
		


