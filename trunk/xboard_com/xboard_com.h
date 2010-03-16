/* General desc
 * Defines the commands to communicate with Xboard 
 */

#ifndef _XBOARD_COM_H
#define _XBOARD_COM_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */


/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

/* Desc : Initializes the communication unit. Wait for all features.
 * Input:0
 * Output:0
 */
void com_init ( void );


/* Desc:
 * Checks and handles standard input. Effects are upon golbal flags.
 * Input:0
 * Output:0
 */
void poll_input ( void );

/* Desc:
 * Gives a command to XBoard 
 * Inout:2: the command string , command type [int]
 * Output:0
 */
void poll_output ( char * , int );

#endif

