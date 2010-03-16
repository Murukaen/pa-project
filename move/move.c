/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "move.h"

/* ---- Macro #define ---- */
#define T_MOVE_NA 255
#define T_MOVE_ENP 1
#define T_MOV_CST 2
#define T_MOV_PRO 3


/* --- Types --- */


struct s_move {
	
	UCHAR p_tag; // piece type ( see "state.h" for mapping )
	LOC poz_src , poz_dst; // source and destination positions represented as coordinates
	UCHAR m_tag; // move tag describing an eventual special move
	UCHAR p_tag_pro; // tag of piece being promoted to
	LOC p_rock; // location of rock in castling move
};



/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

MOVE move_new ( void ) {
	
		MOVE mov = (MOVE) calloc ( 1 , sizeof ( struct s_move ) );
		
		return mov;
}

void move_set_p_tag ( MOVE mov , UCHAR tag) {
	
		mov -> p_tag = tag;
}

UCHAR move_get_p_tag ( MOVE mov ) {
	
		return mov -> p_tag;
}

void move_set_poz_src ( MOVE mov , LOC poz ) {
	
		mov -> poz_src = poz;
}

LOC move_get_poz_src ( MOVE mov ) {
	
		return mov -> poz_src;
}

void move_set_poz_dst ( MOVE mov , LOC poz ) {
	
		mov -> poz_dst = poz;
}

LOC move_get_poz_dst ( MOVE mov ) {
	
		return mov -> poz_dst;
}

void move_set_m_tag ( MOVE mov , UCHAR tag ) {
	
		mov -> m_tag = tag;
}

UCHAR move_get_m_tag ( MOVE mov ) {
	
		return mov -> m_tag;
}

void move_set_p_tag_pro ( MOVE mov, UCHAR tag ) {
	
		mov -> p_tag_pro = tag;
}

UCHAR move_get_p_tag_pro ( MOVE mov ) {
	
		return mov -> p_tag_pro;
}

void move_set_p_rock ( MOVE mov , LOC poz ) {
	
		mov -> p_rock = poz;
}

LOC move_get_p_rock ( MOVE mov ) {
	
		return mov -> p_rock;
}


	
		
