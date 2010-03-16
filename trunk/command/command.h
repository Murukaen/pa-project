/* General description :
 * Command analyser
 */

#ifndef _COMMAND_H
#define _COMMAND_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../xboard_com/xboard_com.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

/* Description : 
 * Handles a given string interpreted as a XBoard Command. A list of all known commands is found in xboard_com.h
 * Input:
 * 1:The command as a string
 * Output:
 * 0:Modifies event flags found in flags.h
 */
void read_com ( char * );


/* Desc:
 * Gives a command to XBoard 
 * Inout:2: the command string , command type [int]
 * Output:0
 */
void write_com ( char * , int );

#endif

