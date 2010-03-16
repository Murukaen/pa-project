/* General description :
 * Implements genral use types and associated procedures
 */

#ifndef _UTIL_H
#define _UTIL_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */

/* ---- Macro #define ---- */

#ifndef _UCHAR
#define _UCHAR
typedef unsigned char UCHAR;
#endif

struct LOC;
typedef struct LOC LOC;

typedef LOC* P_LOC; // --> Generic Reference

/* --- Types --- */

/* --- Procedures --- */

/* LOC Procedures */

P_LOC loc_new ( void );

/*linie-coloana*/
void loc_set_both ( P_LOC , UCHAR , UCHAR );

LOC loc_get_both ( P_LOC );

UCHAR loc_get_row ( P_LOC );

UCHAR loc_get_col ( P_LOC );

#endif

