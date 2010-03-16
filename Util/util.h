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
typedef unsigned char UCHAR
#endif

struct LOC;
typedef struct LOC LOC;

typedef LOC* p_loc; // --> Generic Reference

/* --- Types --- */

/* --- Procedures --- */

/* LOC Procedures */

p_loc loc_new ( void );

void loc_set_both ( p_loc , UCHAR , UCHAR );

LOC loc_get_both ( p_loc );

UCHAR loc_get_row ( p_loc );

UCHAR loc_get_col ( p_loc );

#endif

