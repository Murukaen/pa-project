/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <ctype.h>

/* ----- Local #inlcudes ----- */
#include "../Util/util.h"
#include "move_conv.h"

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
	char V[4]=0;
	int pos = 0;
	while ( (c = parse_xmove ( &xcom ) ) != 0 ) {
		
		if ( isalpha(c) ) c = c - 'a';
		else if ( isdigit(c) ) c = c - '1';
		V[pos++] = c;
	}
	
	// Now :  in V are ( in this order ) s_c, s_l, d_c, d_l 
	// s_l = source line , s_c = source column , d_l = destination line , d_c = destination column
	
	MOVE mov = move_new ();
	
	LOC poz_src , poz_dst;
	
	LOC_set_both ( poz_src , V[1] , V[0] );
	LOC_set_both ( poz_dst , V[3] , V[2] );
	
	move_set_poz_src ( mov , poz_src );
	move_set_poz_dst ( mov , poz_dst );
	
	/* !!! Pt Alin :
	 * In momentul de fata mutarea repezinta coordonatele din punctul de vedere al albului ( ca si cum suntem cu albele ).
	 * Daca suntem cu negerele notatia trebuie inversata pentru ne adapta la starea interna a jocului si a operatiilor
	 * asupra acesteia.
	 * Ideea este urmatoarea : In formatul intern (0.0) reprezinta pozitia din dreapta sus , iar (7.7) din dreapta jos
	 * In schimb, operatiile de mai sus lucreaza cu (0.0) in coltul stanga jos , iar (7.7) in coltul din dreapta sus dpdvd al albului.
	 * In acest scop se vor implementa doua functii care fac conversie intre sistemul de notatie intern si cel al XBoardului si reciproc
	 * Functiile se vor aplea doar la inceput ( pentru Xmove_to_intern ) si la final ( pentru intern_to_Xmove )
	 * 
	 * 
	 * !!! Te rog sa numeste modulul creat de tine : move_san ( cu move_san.h si move_san.c )
	 * Sa nu suprascrii fisierul asta care are ( doar ) scop de test
	 * Spor !
	 * P.S: Daca ai nevoie de ceva extern , apeleaza functiile ca si cum ar exista. Nu scrie ceva in afara pt ca la cum evolueaza lucrurile
	 * se prea poate sa o scri in van.
	 * P.S.2: Starea curenta e in cur_state
	 */
	
	return move;	
}

char * intern_to_Xmove ( MOVE ) {
	
	//TODO
}

