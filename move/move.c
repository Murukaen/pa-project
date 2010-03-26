/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdlib.h>
#include <stdio.h>

/* ----- Local #inlcudes ----- */
#include "move.h"

/* ---- Macro #define ---- */



/* --- Types --- */


struct s_move {
	
	UCHAR p_tag; // piece type ( see "state.h" for mapping )
	LOC poz_src , poz_dst; // source and destination positions represented as coordinates
	UCHAR m_tag; // move tag describing an eventual special move
	UCHAR p_tag_pro; // tag of piece being promoted to
	LOC p_rock; // location of rock in castling move
	UCHAR what_col; // what color is on move
	
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

void move_set_what_col ( MOVE mov , UCHAR tag ) {
	
		mov -> what_col = tag;
}

UCHAR move_get_what_col ( MOVE mov ) {
	
		return mov -> what_col;
}

void move_free ( MOVE mov ) {
	
		free(mov);
}

void move_print ( MOVE mov , FILE * fout ) {
	
	fprintf(fout,"{ p_tag = %u ; poz_src = ( %u , %u ) ; poz_dst = ( %u , %u ) ; m_tag = %u ; p_tag_pro = %u ; p_rock = ( %u , %u ) ; what_col = %u }\n", mov -> p_tag , LOC_get_row ( &(mov -> poz_src) ) , LOC_get_col ( &(mov -> poz_src) ) , LOC_get_row ( &(mov -> poz_dst) ) , LOC_get_col ( &(mov -> poz_dst) ) , mov -> m_tag , mov -> p_tag_pro , LOC_get_row ( &(mov -> p_rock) ) , LOC_get_col ( &(mov -> p_rock) ) , mov -> what_col );

}
