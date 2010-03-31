/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <ctype.h>
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "move_conv.h"
#include "../Util/util.h"
#include "../move/move.h"
#include "../state/state.h"
#include "../cur_state/cur_state.h"


/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* Desc:
 * Parse move word from xboard letter by letter
 * Input:1: address to location in word ( is internally right shifted )
 * Output:1: letter on the current position
 */
char parse_xmove ( char ** com ) {
	
		 if(**com == 0 ) return 0;
		 (*com)++;
		 return *(*com-1);
}


/* --- Procedures --- */


MOVE Xmove_to_intern ( char * xcom ) {
	
	char c;
	int V[4]={0};
	int pos = 0;
	while ( (c = parse_xmove ( &xcom ) ) != 0 ) {
		
		if ( isalpha(c) ) c = c - 'a';
		else if ( isdigit(c) ) c = c - '1';
		V[pos++] = c;
	}
	
	// Now :  in V are ( in this order ) s_l, s_c, d_l, d_c 
	// s_l = source line , s_c = source column , d_l = destination line , d_c = destination column
	// src ( V[0] , V[1] ) ; dst ( V[2] , V[3] )
	
	MOVE mov = move_new ();
	
	LOC poz_src , poz_dst;
	
	LOCp_set_both ( &poz_src , V[0] , V[1] );
	LOCp_set_both ( &poz_dst , V[2] , V[3] );
	
	move_set_poz_src ( mov , poz_src );  // set poz_src
	move_set_poz_dst ( mov , poz_dst );  // set poz_dst
	
	STATE st = cur_state_get ();
	
	UCHAR tag = ST_get_tag_Table_What (st , V[0] , V[1] );
	if ( tag > 8 ) tag -= BWP_OFF;
	move_set_p_tag ( mov , tag );
	
	move_set_what_col ( mov , ST_get_col_on_move ( st ) );
	
	return mov;	
}

char * intern_to_Xmove ( MOVE mov ) {
	
	char * com = (char *) calloc ( 4 , sizeof ( char ) );
	
	LOC src, dst;
	src = move_get_poz_src ( mov );
	dst = move_get_poz_dst ( mov );
	
	com[0] = src.row + 'a';
	com[1] = src.col + '1';
	com[2] = dst.row + 'a';
	com[3] = dst.col + '1';
	
	return com;
}


