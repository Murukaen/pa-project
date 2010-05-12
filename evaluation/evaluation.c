/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "../Util/util.h"
#include "evaluation.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

int piece_value [NR_PIECES];

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void eval_init ( void ) {
	
	piece_value[T_K - PIECES_OFF ] = MAX_EVAL; // King : INF
	piece_value[T_Q - PIECES_OFF ] = 10;       // Queen : 10
	piece_value[T_R - PIECES_OFF ] = 5;		// Rook : 5
	piece_value[T_B - PIECES_OFF ] = 3;   		// Bishop : 3
	piece_value[T_N - PIECES_OFF ] = 3;		// Knight : 3
	piece_value[T_P - PIECES_OFF ] = 1;		// Pawn : 1
}

int evaluate ( STATE st ) {
	
	int i, j, tag;
	int rez = EQU_EVAL;
	int color = ST_get_col_on_move (st);
	
	for(i=0;i<8;++i)
		for(j=0;j<8;++j) {
			tag = ST_get_tag_Table_What ( st , i , j );
			if ( is_tag_of_col ( tag , WHITE_COLOR ) ) rez+=piece_value[tag - PIECES_OFF];
			else rez-=piece_value[tag - BWP_OFF - PIECES_OFF];
		}
	
	if ( color == BLACK_COLOR ) rez = -rez;		

	return rez ;
}

