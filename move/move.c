/* General description :
 * 
 */

/* ----- System #includes ----- */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ----- Local #inlcudes ----- */
#include "move.h"

/* ---- Macro #define ---- */

#define TEXT_SEP " \n{}\t\b;:"

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
	
	char text1[10];
	char text2[10];
	char text3[10];
	tag_to_text ( mov -> p_tag , text1 );
	tag_to_text ( mov -> p_tag_pro , text2 );
	tag_to_text ( mov -> what_col , text3 );
	fprintf(fout,"{\n p_tag = %s \n\n poz_src = ( %c , %c ) \n\n poz_dst = ( %c , %c ) \n\n m_tag = %u \n\n p_tag_pro = %s \n\n p_rock = ( %c , %c ) \n\n what_col = %s \n}", text1 , row_to_letter ( LOC_get_row ( &(mov -> poz_src) ) ) , col_to_letter ( LOC_get_col ( &(mov -> poz_src) ) ), row_to_letter ( LOC_get_row ( &(mov -> poz_dst) ) ) , col_to_letter( LOC_get_col ( &(mov -> poz_dst) ) ) , mov -> m_tag , text2 , row_to_letter ( LOC_get_row ( &(mov -> p_rock) ) ), col_to_letter ( LOC_get_col ( &(mov -> p_rock) ) ) , text3 );

}

void get_both_loc_text ( char * text , UCHAR * row , UCHAR * col ) {
	
	char r , c;
	sscanf(text,"(%c,%c)", &r , &c);

	*row = letter_to_row ( r );
	*col = letter_to_column ( c ); 
}

void add_to_move ( MOVE mov , char * key , char * val ) {
	
	if ( !strcmp ( key , "p_tag" )) mov -> p_tag = text_to_tag ( val );
	if ( !strcmp ( key , "poz_src" )) get_both_loc_text ( val , & (mov -> poz_src.row) , & (mov->poz_src.col) );
	if ( !strcmp ( key , "poz_dst" )) get_both_loc_text ( val , & (mov -> poz_dst.row) , & (mov->poz_dst.col) );
	if ( !strcmp ( key , "m_tag" )) mov -> m_tag = atoi ( val );
	if ( !strcmp ( key , "p_tag_pro" )) mov -> p_tag_pro = text_to_tag ( val );
	if ( !strcmp ( key , "p_rock" )) get_both_loc_text ( val , & (mov -> p_rock.row) , & (mov->p_rock.col) );
	if ( !strcmp ( key , "what_col" )) mov -> what_col = text_to_tag ( val );
}

void parse_read_move ( char *S , MOVE mov ) {
	
	char * exp, *key, *val;
	char word[20];
	for ( exp = strtok ( S , TEXT_SEP ) ; exp ; exp = strtok ( NULL , TEXT_SEP )) {
		
		strcpy(word , exp );
		val = strchr ( word , '=');
		*val = '\0';
		val ++;
		key = word;

		add_to_move ( mov , key , val );
	}
}
		

MOVE move_read ( FILE * fin ) {
	
	char line[150];
	fgets(line , 145 , fin );
	
	MOVE mov = move_new ();
	parse_read_move ( line , mov );
	
	
	return mov;
}
