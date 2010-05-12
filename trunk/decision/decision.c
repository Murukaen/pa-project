/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "decision.h"
#include "../state/state.h"
#include "../state_generator/state_generator.h"
#include "../cur_state/cur_state.h"
#include "../evaluation/evaluation.h"

#define MINIMAX_DEPTH 1

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

int max ( int a , int b ) {
	
	if ( a > b ) return a;
	
	return b;
}

int negamax ( STATE st , int depth , int beta , int alpha ) {
	
	if ( depth == 0 ) return evaluate ( st );
	
	STATE st_son;
	for(st_son = ST_gen (st) ; st_son ; st_son = ST_gen (st) ) {
		alpha = max ( alpha , -negamax ( st_son , depth - 1 , -beta , -alpha ) );
		ST_free(st_son);
		if(alpha >= beta ) break;
	}
	
	return alpha;
}
		

STATE decide ( void ) {
	
	STATE st_cur = cur_state_get();
	
	int alpha = MIN_EVAL, beta = MAX_EVAL, temp;
	
	STATE first_son, st_chosen = NULL;
	
	for(first_son = ST_gen (st_cur); first_son ; first_son = ST_gen(st_cur) ) {	
		if ( alpha > (temp = -negamax ( first_son , MINIMAX_DEPTH - 1 , -beta , -alpha ) ) )  {
			
			alpha = temp;
			ST_free(st_chosen);
			st_chosen = first_son;
		}
		else ST_free(first_son);
	}
			
	return st_chosen;
}

