/* General desc
 * Defines the commands to communicate with Xboard 
 */

#ifndef _XBOARD_COM_H
#define _XBOARD_COM_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */


/* ---- Macro #define ---- */

/* Engine -> XBoard command types */
#define T_COM_MOVE 0
#define T_COM_RESIGN 1
#define T_COM_DRAW 2

/* --- Types --- */

/* --- Procedures --- */

/* Desc : Initializes the communication unit. Wait for all features.
 * Input:0
 * Output:0
 */
void com_init ( void );


/* Desc:
 * Accessed only from main ! Checks and handles standard input. Effects are upon golbal flags.
 * Input:0
 * Output:0
 */
void poll_input ( void );

/* Desc:
 * Accessed only from main! Gives a command to XBoard 
 * Inout:2: the command string , command type [int] ( see #define in xboard_com.h )
 * Output:0
 */
void poll_output ( void * , int );

/* Desc:
 * Write given string to exborad exactly as it is
 * Input:1: Given string
 * Output:0
 */
void write_to_xboard ( char * );

#endif

