/* General description :
 * Command analyser
 */

#ifndef _COMMAND_H
#define _COMMAND_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */

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

#endif

