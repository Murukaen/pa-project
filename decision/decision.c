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
#include "../log/log.h"

#define MINIMAX_DEPTH 2
#define LOG_DECISION_FILE "Log/decision.log"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

int max ( int a , int b ) {
	
	if ( a > b ) return a;
	
	return b;
}

int negamax ( STATE st , int depth , int alpha , int beta ) {
	
	if ( depth == 0 ) return evaluate ( st );
	
	STATE st_son;
	for(st_son = ST_gen (st) ; st_son ; st_son = ST_gen (st) ) {

		alpha = max ( alpha , -negamax ( st_son , depth - 1 , -beta , -alpha ) );
			/* LOG */
			log_print_integer(depth, LOG_DECISION_FILE);
			log_print_integer(alpha, LOG_DECISION_FILE);
			log_print_state_Table_What(st_son , LOG_DECISION_FILE);
			/* END LOG*/
		ST_free(st_son);
		if(alpha >= beta ) break;
	}
			/* LOG */
			log_print("END NEGA", LOG_DECISION_FILE);
			log_print_integer(alpha, LOG_DECISION_FILE);
			log_print_state_Table_What(st_son , LOG_DECISION_FILE);
			/* END LOG*/
	return alpha;
}
		

STATE decide ( void ) {
	
	STATE st_cur = cur_state_get();
	
	int alpha = MIN_EVAL, beta = MAX_EVAL, temp;
	
	STATE first_son, st_chosen = NULL;
	
	for(first_son = ST_gen (st_cur); first_son ; first_son = ST_gen(st_cur) ) {	
		if ( alpha < (temp = -negamax ( first_son , MINIMAX_DEPTH - 1 , -beta , -alpha ) ) )  {
			/* LOG */
			log_print_integer(MINIMAX_DEPTH, LOG_DECISION_FILE);
			log_print_state_Table_What(first_son , LOG_DECISION_FILE);
			/* END LOG*/
			alpha = temp;
			ST_free(st_chosen);
			st_chosen = first_son;
		}
		else ST_free(first_son);
	}
			
	return st_chosen;
}

