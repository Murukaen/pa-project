/* General description :
 * Implementation of state entity
 */

#ifndef _STATE_H
#define _STATE_H

/* ----- System #includes ----- */
#include <stdio.h>

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

#define NR_PIECES 6 // number of all types of pieces
#define PIECES_OFF 2 // tags pieces offset ( 2 - 7 )
#define BWP_OFF 6 // black/white pieces offset ( white : 2 - 7 ; black : 8 - 13 )
#define NR_COLORS 2 // number of colors
#define ANALYZED_PIECE T_N // current analyzed piece 

/* --- Types --- */
struct s_state;
typedef struct s_state* STATE;

/* ----- Procedures ----- */

/* ~~~ General use : ~~~ */

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
void ST_set_Table_What (STATE, UCHAR [][SIZE_BMAP]);

/* Desc:
 * Gets the tag from Table_What located at a given (row,col) position
 * Tag : (2-7) for white , (8-13) for black 
 * Input:3: state , row , column
 * Output:1: tag
 */
UCHAR ST_get_tag_Table_What ( STATE , int , int );

/* Desc:
 * Sets the tag from Table_What located at a given (row,col) position
 * Tag : (2-7) for white , (8-13) for black 
 * Input:4: state , row , column , tag
 * Output:0
 */
void ST_set_tag_Table_What ( STATE , int , int , UCHAR );

/* Desc:
 * Gets the list of positions from Table_Location from a given color tag ( 0 - 1 ) and a given piece tag ( [2 - 7] - PIECES_OFF )
 * Input:3: state , col_tag , piece_tag ( without !! OFFSET )
 * Output:1: List
 */
List ST_get_List_Table_Location ( STATE , int , int );

/* Desc:
 * Sets the list of positions from Table_Location from a given color tag ( 0 - 1 ) and a given piece tag ( [2 - 7] - PIECES_OFF )
 * Input:3: state , col_tag , piece_tag ( without !! OFFSET ) , List
 * Output:0
 */
void ST_set_List_Table_Location (STATE, int, int, List);

/* Desc:
 * Destructor STATE . Removes ALL data from the state !
 * Input:1: STATE
 * Output:0
 */
void ST_free(STATE);


/* ~~~ Used by state generator ONLY : ~~~ */

/* Desc:
 * Sets  the piece_to_move field ( current piece tag to move ) . Has values from (2-7)
 * Input:2: state , piece_tag (2-7)
 * Important: The default value is: T_N ( !!! ONLY FOR KNIGHT ) , in rest is T_K
 * Output:0
 */
void ST_set_piece_to_move(STATE , UCHAR);

/* Desc:
 * Gets  the piece_to_move field ( current piece tag to move ) . Has values from (2-7)
 * Input:1: state 
 * Output:1: piece_tag (2-7)
 */
UCHAR ST_get_piece_to_move(STATE);

/* Desc:
 * Sets the move_index field ( current position in the bitmap of all validated pssible moves ) . Range : (0-63)
 * Input:2:state , index (0-63)
 * Important: The default value is: 0
 * Output:0
 */
void ST_set_move_index(STATE , UCHAR);

/* Desc:
 * Gets the move_index field ( current position in the bitmap of all validated pssible moves ) . Range : (0-63)
 * Input:1: state 
 * Output:1: index (0-63)
 */
UCHAR ST_get_move_index(STATE);

/* Desc:
 * Sets the current piece to move ( the current specific piece ) [List]
 * Input:2: state , address of piece location [List] ( element [List] of Table_Location[f_ENG_COL][piece_to_move - PIECES_OFF] ) 
 * first_nod_list ( cur_poz_in_list ) is the location [P_LOC] of the current piece to be handled with
 * Important: The default value is: Table_Location[f_ENG_COL][piece_to_move - PIECES_OFF]
 * Output:0
 */
void ST_set_cur_poz_in_list(STATE , List);

/* Desc:
 * Gets the current piece to move ( the current specific piece ) [List]
 * first_nod_list ( cur_poz_in_list ) is the location [P_LOC] of the current piece to be handled with
 * Input:1: state 
 * Output:1: address of piece location [List] ( element [List] of Table_Location[f_ENG_COL][piece_to_move - PIECES_OFF] ) 
 */
List ST_get_cur_poz_in_list(STATE);


/* ~~~ Test purposes ONLY : ~~~ */

/* Desc:
 * Test only. Prints the state strucutre fileds 
 * Input:2:state, file out
 * Output:0
 */
void state_print ( STATE , FILE * );

/* Desc:
 * Read a state from a file in the following format
 * 1) Matrix 8x8 of letters
 * 2) Upper case is white , lower case is black
 * 3) The letters are the usual notation of the pieces
 * Examples: K - white king , q - black queen , b - black bishop , P - white pawn , N - white knight
 * Input:1: file in
 * Output:1: created state
 */
STATE state_read ( FILE * );

void ST_set_cur_list(STATE,List);

void tag_to_text ( UCHAR , char [] );

#endif
