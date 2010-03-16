/* General description :
 * 
 */

#ifndef _MOVE_H
#define _MOVE_H

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../Define/define.h"

/* ---- Macro #define ---- */

/* --- Types --- */
struct s_move;
typedef struct s_move * MOVE;


#ifndef _UCHAR
#define _UCHAR
typedef unsigned char UCHAR;
#endif

/* --- Procedures --- */

/* Desc:
 * Creates a new void move
 * Input:0
 * Output:0: new empty move [MOVE]
 */
MOVE move_new ( void );

/* Get & Set procedures */
void move_set_p_tag ( MOVE mov , UCHAR tag);

UCHAR move_get_p_tag ( MOVE mov );

void move_set_poz_src ( MOVE mov , LOC poz );

LOC move_get_poz_src ( MOVE mov );

void move_set_poz_dst ( MOVE mov , LOC poz );

LOC move_get_poz_dst ( MOVE mov );

void move_set_m_tag ( MOVE mov , UCHAR tag );

UCHAR move_get_m_tag ( MOVE mov );

void move_set_p_tag_pro ( MOVE mov, UCHAR tag );

UCHAR move_get_p_tag_pro ( MOVE mov );

void move_set_p_rock ( MOVE mov , LOC poz );

LOC move_get_p_rock ( MOVE mov );

#endif

