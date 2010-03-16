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
#define LENGTH 100 /* !!! Definition of LENGTH */
#define BUF_SEP "\n"

#define LOG_FILE "./Log/log"

#define INIT_FEATURES "feature done=0\n"

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

char * get_input_buffer ( void ) {
	
	char * buf = (char *) calloc ( LENGTH + 1 , sizeof(char) );
	int length = read(STDIN,buf,LENGTH-1);
	buf[length] = '\0';

	return buf; 
}

void parse_buf ( char * buf ) {
	
		char *com;
		for(com = strtok(buf , BUF_SEP); com ; com = strtok(0 , BUF_SEP) ) 
				
					read_com ( com );
		
		free (buf);
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

void poll_output ( char * com , int com_tag) {
	
		write_com ( com , com_tag );
}


			


	
		
	
		


