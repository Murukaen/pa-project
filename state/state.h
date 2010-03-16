/* General description :
 * Implementation of state entity
 */

#ifndef _STATE_H
#define _STATE_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../bitmap/bitmap.h"
#include "../list/list.h"

/* ---- Macro #define ---- */

/* Tags :*/
#define T_PP 0 // Player Pieces
#define T_OP 1 // Oponent Pieces
#define T_K 2 // King
#define T_Q 3 // Queen
#define T_R 4 // Rock
#define T_B 5 // Bishop
#define T_N 6 // Knight
#define T_P 7 // Pawn

#define T_NA 255 // N/A / Empty square

/* END Tags */

/* --- Types --- */
struct s_state;
typedef struct s_state* STATE;

#ifndef _UCHAR
#define _UCHAR
typedef unsigned char UCHAR;
#endif

/* --- Procedures --- */

/* Desc :
 * State constructor with no data inside
 * Input:0
 * Output:1: new_state [state]
*/
STATE ST_new ( void );

 /* Description :
 * Gets the bitmap associated with the given tag from a state
 * Input:2: state , bitmap_TAG
 * Output:1: bitmap
 */
BITMAP ST_get_bitmap(STATE, int);

/* Description :
 * Sets the bitmap associated with the given tag from a state
 * Input:3: state , bitmap_TAG , bitmap_to_set
 * Output:0
 */
void ST_set_bitmap(STATE, int, BITMAP);

/* Description :
 * Sets the table in a state
 * Input:2:STATE,UCHAR matrix
 * Output:0
 */
void ST_set_table_W(STATE,UCHAR**);

/* Desc:
 * Destructor state
 * Input:1: state
 * Output:0
 */
void ST_free(STATE);

void ST_set_table_P(STATE,int,int,lista);

#endif
