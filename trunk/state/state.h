/* General description :
 * Implementation of state entity
 */

#ifndef _STATE_H
#define _STATE_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../bitmap/bitmap.h"
#include "../list/list.h"
#include "../Util/util.h"

/* ---- Macro #define ---- */

/* Tags :*/
#define T_WP 0 // White Pieces
#define T_BP 1 // Black Pieces
#define T_K 2 // King
#define T_Q 3 // Queen
#define T_R 4 // Rock
#define T_B 5 // Bishop
#define T_N 6 // Knight
#define T_P 7 // Pawn
#define T_NA 255 // N/A / Empty square
/* END Tags */

#define NR_A_P 6 // number of all types of pieces
#define BMAP_TP_OFF 2 // bitmap tags pieces offset ( 2 - 7 )
#define BMAP_BWP_OFF 6 // bitmap black/white pieces offset ( white : 2 - 7 ; black : 8 - 13 )

/* --- Types --- */
struct s_state;
typedef struct s_state* STATE;

/* --- Procedures --- */

/* General use : */

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
void ST_set_Table_W (STATE, UCHAR [][SIZE_BMAP]);

/* Desc:
 * Gets the tag from Table_W located at a given (row,col) position
 * Input:3: state , row , column
 * Output:1: tag
 */
UCHAR ST_get_tag_Table_W ( STATE , int , int );

/* Desc:
 * Sets the tag from Table_W located at a given (row,col) position
 * Input:4: state , row , column , tag
 * Output:0
 */
void ST_set_tag_Table_W ( STATE , int , int , UCHAR );


UCHAR ST_get_Table_W(STATE,int,int);

/* Desc:
 * Gets the list of positions from Table_P from a given color tag ( 0 - 1 ) and a given piece tag ( [2 - 7] - BMAP_TP_OFF )
 * Input:3: state , col_tag , piece_tag
 * Output:1: List
 */
List ST_get_List_Table_P ( STATE , int , int );

/* Desc:
 * Sets the list of positions from Table_P from a given color tag ( 0 - 1 ) and a given piece tag ( [2 - 7] - BMAP_TP_OFF )
 * Input:3: state , col_tag , piece_tag , List
 * Output:0
 */
void ST_set_List_Table_P (STATE, int, int, List);

/* Desc:
 * Gets a bitmap from a state according to the BM_tag
 * Input:2: state , tag ( which bitmap to get )
 * Output:1: bitmap
 */
BITMAP ST_get_V_BMAP (STATE ,int );

/* Desc:
 * Destructor STATE 
 * Input:1: STATE
 * Output:0
 */
void ST_free(STATE);


/* Used by state generator : */

void ST_set_piece_to_move(STATE , UCHAR);

int ST_get_piece_to_move(STATE);

void ST_set_move_cur_list(STATE , List);

List ST_get_move_cur_list(STATE);

void ST_set_move_index(STATE , UCHAR);

UCHAR ST_get_move_index(STATE);

/* Test purposes : */

void state_print ( STATE , FILE * );

#endif
